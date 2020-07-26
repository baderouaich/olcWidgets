/*
	olcWidgets.h
	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension            |
	|                   olcWidgets - 1.0v                         |
	+-------------------------------------------------------------+
	What is this?
	~~~~~~~~~~~~~
	This is an extension to the olcPixelGameEngine, which provides
	a quick and easy to use, flexible, skinnable context pop-up
	menu system.
	License (OLC-3)
	~~~~~~~~~~~~~~~
	Copyright 2018 - 2020 OneLoneCoder.com
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.
	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com

	Authors
	~~~~~~
	Bader Eddine Ouaich
	David Barr, aka javidx9, ©OneLoneCoder 2020
*/

#ifndef OLC_PGEX_WIDGETS_DEF
#define OLC_PGEX_WIDGETS_DEF

#include <cassert>
#include <vector>

namespace olc { namespace widgets
{

	////////////////////////////////////////////////////////////////////
	/////////======= Widget Base Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	enum WidgetState { IDLE = 0, HOVER, PRESSED, FOCUSED };
	struct WidgetTheme
	{
		vf2d textScale = { 1.0f, 1.0f };

		Pixel idleColor   = olc::Pixel(56, 73, 105);
		Pixel hoverColor  = olc::Pixel(73, 107, 171);
		Pixel activeColor = olc::Pixel(78, 99, 173);

		Pixel textIdleColor   = olc::Pixel(200, 200, 200);
		Pixel textHoverColor  = olc::Pixel(255, 255, 255);
		Pixel textActiveColor = olc::Pixel(255, 255, 255);
		
		//Pixel idleColor   = olc::VERY_DARK_GREY;
		//Pixel hoverColor  = olc::DARK_GREY;
		//Pixel activeColor = olc::DARK_CYAN;
		//
		//Pixel textIdleColor   = olc::GREY;
		//Pixel textHoverColor  = olc::WHITE;
		//Pixel textActiveColor = olc::WHITE;

		Pixel shadowColor = Pixel(60, 60, 60, 200);
	};
	class Widget
	{
	public:
		static void Init(PixelGameEngine* pixel_game_engine);

	protected:
		struct Clock
		{
			float timer = 0.0f;
			const float max_click_secs = 0.3f; // time to wait before performing a new click event, to avoid repeated click due high FPS.

			void Update(const float& dt) { timer += dt; }

			////////////////
			bool canClick() 
			{
				if (timer >= max_click_secs)
				{
					timer = 0.0f; //restart
					return true;
				}
				return false;
			}
		} clock;


	public:
		Widget(const vi2d& position, const vi2d& size, const WidgetTheme& theme = WidgetTheme(), WidgetState state = WidgetState::IDLE);
		virtual ~Widget() = default;
		
		virtual void Update(const float& dt);
		virtual void Draw();

	public:
		//Accessors
		const unsigned short getId() const { return id; }
		const vi2d& getPosition() const noexcept { return this->pos; }
		const vi2d& getSize() const noexcept { return this->size; }

		//Modificators
		void setId(unsigned short id) noexcept { this->id = id; }
		void setSize(const vi2d& size) noexcept { this->size = size; }
		void setPosition(const vi2d& position) noexcept { this->pos = position; }

	protected:
		unsigned short id;
		vi2d pos;
		vi2d size;
		WidgetTheme theme;
		WidgetState state;

	private:
		static unsigned short cid; // id incremental counter 

	protected:
		constexpr bool contains(const olc::vi2d& point) const noexcept { return (point.x >= pos.x && point.y >= pos.y && point.x < pos.x + size.x && point.y < pos.y + size.y); }
		void setState(WidgetState state) noexcept { state = state; }
		WidgetState getState() const noexcept { return state; }

	protected:
		static PixelGameEngine* pge;
	};

	//Initialize Static Memmbers
	olc::PixelGameEngine* olc::widgets::Widget::pge = nullptr;
	unsigned short olc::widgets::Widget::cid = 0;
	////////////////////////////////////////////////////////////////////
	/////////======= Widget Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////







	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class Button : public Widget
	{		
	public:
		Button(const vi2d& position, const vi2d& size, const std::string& text, const WidgetTheme& theme = WidgetTheme());
		virtual ~Button();

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

		//Accessors
		constexpr bool isPressed() const noexcept { return state == WidgetState::PRESSED; }
		constexpr bool isHover()   const noexcept { return state == WidgetState::HOVER;   }
		constexpr bool isIdle()    const noexcept { return state == WidgetState::IDLE;    }
		constexpr bool isFocused() const noexcept { return state == WidgetState::FOCUSED || state == WidgetState::PRESSED; }

		const std::string& getText() const noexcept { return m_text; }
		const vf2d& getTextScale()   const noexcept { return this->theme.textScale; }

		//Modificators
		void setText(const std::string& text) noexcept { m_text = text; }
		void setTextScale(const vf2d& text_scale) noexcept { this->theme.textScale = text_scale; }
		void setTextIdleColor(const Pixel color) noexcept   { this->theme.textIdleColor = color;   }
		void setTextHoverColor(const Pixel color) noexcept  { this->theme.textHoverColor = color;  }
		void setTextActiveColor(const Pixel color) noexcept { this->theme.textActiveColor = color; }
		void setIdleColor(const Pixel color)   noexcept { this->theme.idleColor = color;   }
		void setHoverColor(const Pixel color)  noexcept { this->theme.hoverColor = color;  }
		void setActiveColor(const Pixel color) noexcept { this->theme.activeColor = color; }
		void setShadowColor(const Pixel color) noexcept { this->theme.shadowColor = color; }


	protected:
		Pixel m_color, m_text_color; //Current state color
		std::string m_text;

	};
	////////////////////////////////////////////////////////////////////
	/////////======= Button Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////
	/////////======= SpriteButton Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class SpriteButton : public Button
	{		
	public:
		SpriteButton(const vi2d& position, const vi2d& size, const std::string& text, const std::string& sprPath, const WidgetTheme& theme = WidgetTheme());
		virtual ~SpriteButton();

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	protected:
		Renderable m_renderable;

	};
	////////////////////////////////////////////////////////////////////
	/////////======= SpriteButton Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////








	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class DropDownList : public Widget
	{
	public:
		DropDownList(const vi2d& position, const vi2d& size, const std::vector<std::string>& elementsList, size_t defaultIndex, const WidgetTheme& theme = WidgetTheme());
		virtual ~DropDownList();

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	public:
		//Accessors
		const Button* getSelectedItem() const noexcept { return m_active_element; }

	private:
		Button* m_active_element;
		std::vector<Button*> m_elements_list;
		bool m_show_list;
	};
	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////







	////////////////////////////////////////////////////////////////////
	/////////======= CheckBox Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
#if 0
	class CheckBox : public Widget
	{
	public:
		CheckBox(const vi2d& position, const vi2d& size, const std::string& labelText, bool* checked = (bool*)false, const WidgetTheme& theme = WidgetTheme());
		virtual ~CheckBox();

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	public:
		bool isChecked() const noexcept { return *m_checked; }
		void setChecked(bool v) noexcept { *m_checked = v; }

	private:
		Button* m_button;
		bool*   m_checked;
	};
#endif
	////////////////////////////////////////////////////////////////////
	/////////======= CheckBox Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////


}
}
#endif




#ifdef OLC_PGEX_WIDGETS
#undef OLC_PGEX_WIDGETS


////////////////////////////////////////////////////////////////////
/////////////////======= Implementation ========////////////////////
////////////////////////////////////////////////////////////////////


namespace olc { namespace widgets
{
	////////////////////////////////////////////////////////////////////
	//////======= Widget Base Class Implementation BEGIN ========///////
	////////////////////////////////////////////////////////////////////
	void Widget::Init(PixelGameEngine* pixel_game_engine)
	{
		pge = pixel_game_engine;
	}

	Widget::Widget(const vi2d& position, const vi2d& size, const WidgetTheme& theme, WidgetState state)
		:
		pos(position),
		size(size),
		state(state),
		theme(theme)
	{
		assert(pge && "olcGUI Must be Initialized, have you called olc::widgets::Widget::Init(this); in OnUserCreate() ?");
		
		//each widget has a unique incremental id 
		id = cid++;
	}

	void Widget::Update(const float& dt)
	{
		//Update Clock
		clock.Update(dt);

		//Nothing is happening so far
		state = WidgetState::IDLE;

		//Hover
		if (this->contains({ this->pge->GetMouseX() ,this->pge->GetMouseY() }))
		{
			state = WidgetState::HOVER;

			//Check Pressed, If the left mouse pressed while hovering, its a Press event
			if (pge->GetMouse(0).bHeld)
			{
				state = WidgetState::PRESSED;
			}
		}


	}

	void Widget::Draw()
	{
	}
	////////////////////////////////////////////////////////////////////
	///////======= Widget Base Class Implementation END ========////////
	////////////////////////////////////////////////////////////////////





	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Implementation BEGIN =======//////////
	////////////////////////////////////////////////////////////////////
	Button::Button(const vi2d& position, const vi2d& size, 
		const std::string& text, const WidgetTheme& theme)
		:
		Widget(position, size, theme, WidgetState::IDLE),
		m_text(text)
	{

	}

	void Button::Update(const float& dt)
	{
		//Update Base class first
		Widget::Update(dt);

		//Update Button & Text Colors depending on button state.
		switch (state)
		{
		case WidgetState::IDLE:
			m_color = this->theme.idleColor;
			m_text_color = this->theme.textIdleColor;
			break;
		case WidgetState::HOVER:
			m_color = this->theme.hoverColor;
			m_text_color = this->theme.textHoverColor;
			break;
		case WidgetState::PRESSED:
			m_color = this->theme.activeColor;
			m_text_color = this->theme.textActiveColor;
			break;
		default: //Error state
			m_color = RED;
			m_text_color = WHITE;
			break;
		}
	}

	void Button::Draw()
	{
		//Draw Base class first
		Widget::Draw();

		/// Render button
		//background
		pge->FillRect(this->pos, this->size, m_color);

		//text
		pge->DrawStringDecal
		(
			//put text in middle
			{
				this->pos.x + (this->size.x / 2.0f) - (pge->GetTextSize(m_text).x / 2.0f),
				this->pos.y + (this->size.y / 2.0f) - (pge->GetTextSize(m_text).y / 2.0f)

			},
			m_text,
			m_text_color,
			this->isHover() ? vf2d(0.95f, 0.95f) : this->theme.textScale
		);

		//Draw Shadow bellow button container
		if (state != WidgetState::PRESSED)
		{
			//Enable opacity
			pge->SetPixelMode(Pixel::ALPHA);
			//Bottom
			pge->DrawLine(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, this->theme.shadowColor);
			//Right (to pos.y + size.y - 1: to not meet with bottom light, this will douplicate alpha color shadow at one point)
			pge->DrawLine(pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y - 1, this->theme.shadowColor);
			//Disable opacity
			pge->SetPixelMode(Pixel::NORMAL);
		}


	}

	Button::~Button()
	{
	}
	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Implementation END =======////////////
	////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////
	/////////======= SpriteButton Class Implementation BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	
	SpriteButton::SpriteButton(
		const vi2d& position, const vi2d& size,
		const std::string& text, 
		const std::string& sprPath,
		const WidgetTheme& theme)
		:
		Button(position, size, text, theme)
	{
		//Load sprite
		m_renderable.Load(sprPath);
		//Hide background button
		this->setIdleColor(olc::Pixel(0, 0, 0, 0));
		this->setHoverColor(olc::Pixel(0, 0, 0, 0));
		this->setActiveColor(olc::Pixel(0, 0, 0, 0));
		this->setShadowColor(olc::Pixel(0, 0, 0, 0));
	}
	
	void SpriteButton::Update(const float& dt)
	{
		//Update Button base class first
		Button::Update(dt);



	}

	void SpriteButton::Draw()
	{	
		//Dont draw the transparent button!
		pge->SetPixelMode(Pixel::ALPHA);
	
		//Draw Sprite Decal
		pge->DrawDecal(
			this->pos,
			m_renderable.Decal(),
			// scale decale alongside with text on hover
			this->isHover() ? vf2d(0.95f, 0.95f) : this->theme.textScale 
		);

		//Draw Button base class first
		Button::Draw();

		//Reset draw mode
		pge->SetPixelMode(Pixel::NORMAL);
	}

	SpriteButton::~SpriteButton()
	{
	}
	////////////////////////////////////////////////////////////////////
	/////////======= SpriteButton Base Class Implementation END =======/////////
	////////////////////////////////////////////////////////////////////








	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Class Implementation BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	DropDownList::DropDownList(const vi2d& position, 
		const vi2d& size, 
		const std::vector<std::string>& elementsList, 
		size_t defaultIndex,
		const WidgetTheme& theme)
		:
		Widget(position, size, theme),
		m_active_element(nullptr),
		m_show_list(false) // list Hidden by default
	{
		//Set default active element
		m_active_element = new Button
		(
			position,
			size,
			elementsList[defaultIndex], 
			theme
		);

		//Add elements to list
		for (size_t i = 0; i < elementsList.size(); i++)
		{
			m_elements_list.push_back(new Button
			(
				{ position.x, position.y + (((int)i + 1) * size.y) }, // y + (i+1) * height: push down one bellow one
				 size,
				elementsList[i],
				theme
			));
		}
	}
	

	void DropDownList::Update(const float& dt)
	{ 
		//Update Base class first
		Widget::Update(dt);

		m_active_element->Update(dt); //Update default active element

		//Show & Hide the list, If active element is pressed, we show the dropdownlist elements list
		if (m_active_element->isPressed() && this->clock.canClick()) // btn isPressed has built in canclick clock
		{
			m_show_list = !m_show_list; // On/Off
		}

		if (m_show_list) //Only update list if should show
		{
			//Update each button element
			for (auto& element : m_elements_list)
			{
				element->Update(dt);

				//If menu item clicked
				if (element->isPressed())
				{
					//Hide drop down list
					m_show_list = false;
					//Set active element to selected
					m_active_element->setText(element->getText());
					//Set id to active element to selected one
					m_active_element->setId(element->getId());
				}
			}
		}

	}


	void DropDownList::Draw()
	{
		//Draw Base class first
		Widget::Draw();

		m_active_element->Draw(); //Draw default active element
								  
		//TODO: Draw down arrow as hint thats a drop down lisst
		{
			//vi2d p1 = { this->pos.x + this->size.x - 15, this->pos.y + (this->pos.y / 2) }; //LEFT
			//vi2d p2 = { this->pos.x + this->size.x - 12, this->pos.y + int(this->pos.y / 2) } ; // CENTER BOTTOM
			//vi2d p3 = { this->pos.x + this->size.x - 10, this->pos.y + (this->pos.y / 4) };//RIGHT

			////pge->DrawString(p1, "1", olc::RED); // MEFT
			////pge->DrawString(p2, "2", olc::GREEN);
			////pge->DrawString(p3, "3", olc::BLUE);
			//pge->FillTriangle(
			//	p1, 
			//	p2, 
			//	p3, 
			//	this->theme.textActiveColor
			//);
		}

		if (m_show_list) //Only Draw list if should show
		{
			for (auto& element : m_elements_list)
			{
				element->Draw();
			}
		}
	}


	DropDownList::~DropDownList()
	{
		delete m_active_element;
		for (auto& element : m_elements_list)
			delete element;
	}
	////////////////////////////////////////////////////////////////////
	///////===== DropDownList Base Class Implementation END =====///////
	////////////////////////////////////////////////////////////////////
















	////////////////////////////////////////////////////////////////////
	/////////======= CheckBox Class Implementation BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
#if 0
	CheckBox::CheckBox(const vi2d& position, const vi2d& size,
		const std::string& labelText,
		bool* checked,
		const WidgetTheme& theme)
		:
		Widget(position, size, theme),
		m_checked(checked),
		m_button(nullptr)
	{

		m_button = new Button(
			position,
			{
				// extra 25% for check cross 
				size.x + int(size.x * 0.25),
				size.y
			}, 
			labelText,
			theme
		);
	}

	void CheckBox::Update(const float& dt)
	{
		//Update Base class first
		Widget::Update(dt);

		/// Update button
		m_button->Update(dt);

		// Update Checked/Unchecked
		if (m_button->isPressed() && this->clock.canClick())
		{
			*m_checked = !(*m_checked);
		}
	}


	void CheckBox::Draw() 
	{		
		//Draw Base class first
		Widget::Draw();


		/// Render button
		m_button->Draw();

		//Draw Empty rect to the right to draw cross inside it when its checked
		pge->DrawRect(
			this->pos.x + this->size.x , //minus extra width 25%
			this->pos.y + 1, // +1 after shadow line
			int(size.x * 0.25),
			size.y - 1, // -1 before shadow line
			olc::GREY
		);

		// Draw Cross if its checked
		if (*m_checked)
		{
			pge->FillRect(
				(this->pos.x + this->size.x) - 10,
				(this->pos.y) + 10,
				20, 20,
				olc::RED
			);
		}
		
	}


	CheckBox::~CheckBox()
	{
		delete m_button;
	}
	////////////////////////////////////////////////////////////////////
	/////////======= CheckBox Base Class Implementation END =======/////////
	////////////////////////////////////////////////////////////////////
#endif











}}

#endif