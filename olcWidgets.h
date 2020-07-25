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
		Widget(const vi2d& position, const vi2d& size);
		virtual ~Widget() = default;
		
		virtual void Update(const float& dt);
		virtual void Draw();

	public:
		//Accessors
		const unsigned short getId() const { return id; }
		const vi2d& getPosition()  const noexcept { return this->pos; }
		const vi2d& getSize()  const	noexcept { return this->size; }

		//Modificators
		void setId(unsigned short id) noexcept { this->id = id; }
		void setSize(const vi2d& size) noexcept { this->size = size; }
		void setPosition(const vi2d& position) noexcept { this->pos = position; }

	protected:
		unsigned short id;
		vi2d pos;
		vi2d size;

	private:
		static unsigned short cid; // id incremental counter 

	protected:
		constexpr bool contains(const olc::vi2d& point) const noexcept { return (point.x >= pos.x && point.y >= pos.y && point.x < pos.x + size.x && point.y < pos.y + size.y); }
	
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
	enum  ButtonState { IDLE = 0, HOVER, PRESSED };
	class Button : public Widget
	{
	public:
		Button(const vi2d& position, const vi2d& size,
			const std::string& text, vf2d textScale,
			Pixel idleColor, Pixel hoverColor, Pixel activeColor,
			Pixel textIdleColor, Pixel textHoverColor, Pixel textActiveColor,
			Pixel shadowColor = Pixel(60, 60, 60, 200));
		virtual ~Button();

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

		//Accessors
		constexpr bool isPressed() const noexcept { return m_button_state == ButtonState::PRESSED; }
		constexpr bool isHover()   const noexcept { return m_button_state == ButtonState::HOVER;   }
		constexpr bool isIdle()    const noexcept { return m_button_state == ButtonState::IDLE;    }
		
		const std::string& getText() const noexcept { return m_text; }
		const vf2d& getTextScale()   const noexcept { return m_text_scale; }

		//Modificators
		void setText(const std::string& text) noexcept { m_text = text; }
		void setTextScale(const vf2d& text_scale) noexcept { m_text_scale = text_scale; }
		void setTextIdleColor(const Pixel color) noexcept   { m_text_idle_color = color;   }
		void setTextHoverColor(const Pixel color) noexcept  { m_text_hover_color = color;  }
		void setTextActiveColor(const Pixel color) noexcept { m_text_active_color = color; }
		void setIdleColor(const Pixel color)   noexcept { m_idle_color = color;   }
		void setHoverColor(const Pixel color)  noexcept { m_hover_color = color;  }
		void setActiveColor(const Pixel color) noexcept { m_active_color = color; }
		void setShadowColor(const Pixel color) noexcept { m_shadow_color = color; }


	private:
		ButtonState m_button_state;

	protected:
		Pixel m_color, m_text_color; //Current state color

		Pixel m_idle_color;
		Pixel m_hover_color;
		Pixel m_active_color;

		std::string m_text;
		vf2d m_text_scale;
		Pixel m_text_idle_color;
		Pixel m_text_hover_color;
		Pixel m_text_active_color;

		Pixel m_shadow_color; // Button Bottom & Left shadow color

	};
	////////////////////////////////////////////////////////////////////
	/////////======= Button Base Class Definition END =======/////////
	////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class DropDownList : public Widget
	{
	public:
		DropDownList(const vi2d& position, const vi2d& size, const std::vector<std::string>& elementsList, size_t defaultIndex = 0);
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

	Widget::Widget(const vi2d& position, const vi2d& size)
		:
		pos(position),
		size(size)
	{
		assert(pge && "olcGUI Must be Initialized, have you called olc::widgets::Widget::Init(this); in OnUserCreate() ?");
		
		//each widget has a unique incremental id 
		id = cid++;
	}

	void Widget::Update(const float& dt)
	{
		//Update Clock
		clock.Update(dt);
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
		const std::string& text, vf2d textScale,
		Pixel idleColor, Pixel hoverColor, Pixel activeColor,
		Pixel textIdleColor, Pixel textHoverColor, Pixel textActiveColor,
		Pixel shadowColor)
		:
		Widget(position, size),
		m_idle_color(idleColor),
		m_hover_color(hoverColor),
		m_active_color(activeColor),
		m_text(text),
		m_text_scale(textScale),
		m_text_idle_color(textIdleColor),
		m_text_hover_color(textHoverColor),
		m_text_active_color(textActiveColor),
		m_button_state(ButtonState::IDLE),
		m_shadow_color(shadowColor)
	{

	}

	void Button::Update(const float& dt)
	{
		//Update Base class first
		Widget::Update(dt);

		//Nothing is happening so far
		m_button_state = ButtonState::IDLE;
		
		//Hover
		if (this->contains({ this->pge->GetMouseX() ,this->pge->GetMouseY() }))
		{
			m_button_state = ButtonState::HOVER;
			
			//Check Pressed, If the left mouse pressed while hovering, its a Press event
			if (pge->GetMouse(0).bHeld)
			{
				m_button_state = ButtonState::PRESSED;
			}
		}

		//Update Button & Text Colors depending on button state.
		switch (m_button_state)
		{
		case ButtonState::IDLE:
			m_color = m_idle_color;
			m_text_color = m_text_idle_color;
			break;
		case ButtonState::HOVER:
			m_color = m_hover_color;
			m_text_color = m_text_hover_color;
			break;
		case ButtonState::PRESSED:
			m_color = m_active_color;
			m_text_color = m_text_active_color;
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
		vi2d bounds(pge->GetTextSize(m_text));
		pge->DrawStringDecal
		(
			//put text in middle
			{
				this->pos.x + (this->size.x / 2.0f) - (pge->GetTextSize(m_text).x / 2.0f),
				this->pos.y + (this->size.y / 2.0f) - (pge->GetTextSize(m_text).y / 2.0f)

			},
			m_text,
			m_text_color,
			m_text_scale
		);
		//Draw Shadow bellow button container
		if (m_button_state != ButtonState::PRESSED)
		{
			//Enable opacity
			pge->SetPixelMode(Pixel::ALPHA);
			//Bottom
			pge->DrawLine(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, m_shadow_color);
			//Right (to pos.y + size.y - 1: to not meet with bottom light, this will douplicate alpha color shadow at one point)
			pge->DrawLine(pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y - 1, m_shadow_color);
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
	/////////======= DropDownList Class Implementation BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	DropDownList::DropDownList(const vi2d& position, const vi2d& size, const std::vector<std::string>& elementsList, size_t defaultIndex)
		:
		Widget(position, size),
		m_active_element(nullptr),
		m_show_list(false) // list Hidden by default
	{
		//Set default active element
		m_active_element = new Button
		(
			position,
			size,
			elementsList[defaultIndex], {1.0f, 1.0f},
			Pixel(70, 70, 70, 200), Pixel(150, 150, 150, 200), Pixel(20, 20, 20, 200),
			Pixel(255, 255, 255, 150), Pixel(255, 255, 255, 200), Pixel(20, 20, 20, 50)
		);

		//Add elements to list
		for (size_t i = 0; i < elementsList.size(); i++)
		{
			m_elements_list.push_back(new Button
			(
				{ position.x, position.y + (((int)i + 1) * size.y) }, // y + (i+1) * height: push down one bellow one
				 size,
				elementsList[i], { 1.0f, 1.0f },
				Pixel(70, 70, 70, 200), Pixel(150, 150, 150, 200), Pixel(20, 20, 20, 200),
				Pixel(255, 255, 255, 150), Pixel(255, 255, 255, 255), Pixel(20, 20, 20, 50)
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
	/////////======= DropDownList Base Class Implementation END =======/////////
	////////////////////////////////////////////////////////////////////

}}

#endif