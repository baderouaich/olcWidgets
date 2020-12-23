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
#include <iomanip>

namespace olc { namespace widgets
{

	////////////////////////////////////////////////////////////////////
	/////////======= Widget Base Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	enum class WidgetState { IDLE = 0, HOVER, PRESSED, FOCUSED };
	enum Orientation { VERTICAL, HORIZONTAL };
	struct WidgetTheme
	{
		//Widget text scale x,y
		vf2d textScale = { 1.0f, 1.0f };

		//widget on idle color
		Pixel idleColor   = olc::Pixel(33, 66, 99);
		//widget on hover color
		Pixel hoverColor = olc::Pixel(54, 104, 156);
		//widget on active color
		Pixel activeColor = olc::Pixel(66, 121, 179);
#if 0
		//widget on idle color
		Pixel idleColor   = olc::Pixel(56, 73, 105);
		//widget on hover color
		Pixel hoverColor  = olc::Pixel(73, 107, 171);
		//widget on active color
		Pixel activeColor = olc::Pixel(78, 99, 173);
#endif
		//widget text on active color
		Pixel textIdleColor   = olc::Pixel(200, 200, 200);
		//widget text on hover color
		Pixel textHoverColor  = olc::Pixel(255, 255, 255);
		//widget text on active color
		Pixel textActiveColor = olc::Pixel(255, 255, 255);
		//widget bottom and right line to simulate shadow color (for buttons mostly)
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
			const float max_click_secs = 0.3f; // time to wait before performing a new click event, to avoid clicking repeatedly due high FPS.

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
		Widget(const vf2d& position, const vf2d& size, const WidgetTheme& theme = WidgetTheme(), WidgetState state = WidgetState::IDLE);
		virtual ~Widget() = default;
		
		virtual void Update(const float& dt);
		virtual void Draw();

	public:
		//Accessors
		constexpr bool isPressed() const noexcept { return state == WidgetState::PRESSED; }
		constexpr bool isHover()   const noexcept { return state == WidgetState::HOVER; }
		constexpr bool isIdle()    const noexcept { return state == WidgetState::IDLE; }
		constexpr bool isFocused() const noexcept { return state == WidgetState::FOCUSED || state == WidgetState::PRESSED; }

		const unsigned short getId() const noexcept { return id; }
		const vf2d& getPosition() const noexcept { return this->pos; }
		const vf2d& getSize() const noexcept { return this->size; }

		//Modificators
		void setId(unsigned short id) noexcept { this->id = id; }
		void setSize(const vf2d& size) noexcept { this->size = size; }
		void setPosition(const vf2d& position) noexcept { this->pos = position; }

	protected:
		unsigned short id;
		vf2d pos;
		vf2d size;
		WidgetTheme theme;
		WidgetState state;

	private:
		static unsigned short idc; // id incremental counter 

	protected:
		constexpr bool contains(const olc::vf2d& point) const noexcept { return (point.x >= pos.x && point.y >= pos.y && point.x < pos.x + size.x * theme.textScale.x && point.y < pos.y + size.y * theme.textScale.y); }
		void setState(WidgetState state) noexcept { this->state = state; }
		WidgetState getState() const noexcept { return state; }

	protected:
		static PixelGameEngine* pge;
	};

	//Initialize Static Memmbers
	olc::PixelGameEngine* olc::widgets::Widget::pge = nullptr;
	unsigned short olc::widgets::Widget::idc = 0u;
	////////////////////////////////////////////////////////////////////
	/////////======= Widget Base Class Definition END =======///////////
	////////////////////////////////////////////////////////////////////




	////////////////////////////////////////////////////////////////////
	/////////======= Label Class Definition BEGIN =======///////////////
	////////////////////////////////////////////////////////////////////
	class Label : public Widget
	{
	public:
		Label(const vf2d& position, const std::string& text, const WidgetTheme& theme = WidgetTheme());
		virtual ~Label() noexcept;

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

		//Accessors
		const std::string& getText() const noexcept { return m_text; }

		//Modificators
		void setText(const std::string& text) noexcept { m_text = text; }


	private:
		std::string m_text;
		Pixel m_text_color;

	};
	////////////////////////////////////////////////////////////////////
	//////////======= Label Class Definition END =======////////////////
	////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Definition BEGIN =======//////////////
	////////////////////////////////////////////////////////////////////
	class Button : public Widget
	{		
	public:
		Button(const vf2d& position, const vf2d& size, const std::string& text, const WidgetTheme& theme = WidgetTheme());
		virtual ~Button() noexcept;

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

		//Accessors
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
	//////////======= Button Class Definition END =======///////////////
	////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////
	/////////====== SpriteButton Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class SpriteButton : public Button
	{		
	public:
		SpriteButton(const vf2d& position, const vf2d& size, const std::string& text, const std::string& sprPath, const WidgetTheme& theme = WidgetTheme());
		virtual ~SpriteButton() noexcept;

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	private:
		Renderable m_renderable;

	};
	////////////////////////////////////////////////////////////////////
	/////////====== SpriteButton Class Definition END =======///////////
	////////////////////////////////////////////////////////////////////








	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Class Definition BEGIN =======////////
	////////////////////////////////////////////////////////////////////
	class DropDownList : public Widget
	{
	public:
		DropDownList(const vf2d& position, const vf2d& size, const std::vector<std::string>& elementsList, size_t defaultIndex, const WidgetTheme& theme = WidgetTheme());
		virtual ~DropDownList() noexcept;

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	public:
		//Accessors
		const Button* getSelectedItem() const noexcept { return m_active_element; }
		size_t getSelectedItemIndex() const
		{
			for (size_t i = 0; i < m_elements_list.size(); i++)
				if (m_elements_list[i]->getId() == m_active_element->getId())
					return i;
			return 0;
		}

	private:
		Button* m_active_element;
		std::vector<Button*> m_elements_list;
		bool m_show_list;
	};
	////////////////////////////////////////////////////////////////////
	/////////======= DropDownList Class Definition END =======//////////
	////////////////////////////////////////////////////////////////////





	////////////////////////////////////////////////////////////////////
	/////////======= ProgressBar Class Definition BEGIN =======/////////
	////////////////////////////////////////////////////////////////////
	class ProgressBar : public Widget
	{
	public:
		ProgressBar(const vf2d& position, const vf2d& size, float value = 0.0f, Pixel progressColor = GREEN, const WidgetTheme& theme = WidgetTheme());
		virtual ~ProgressBar() noexcept;

		virtual void Update(const float& dt) override;
		virtual void Draw() override;

	public:
		//Modificators

		//Set percentage value [0.0f...100.0f]
		void setValue(float value) noexcept 
		{
			//Clamp value
			if (value < 0.0f)
				m_value = 0.0f;
			else if (value > 100.0f)
				m_value = 100.0f;
			else
				m_value = value;
		}


		//Accessors
		float getValue() const noexcept { return m_value; }

	private:
		float m_value;
		Pixel m_progress_color;
	};
	////////////////////////////////////////////////////////////////////
	/////////======= ProgressBar Class Definition END =======///////////
	////////////////////////////////////////////////////////////////////







#if 0
	////////////////////////////////////////////////////////////////////
	/////////========= Layout Class Definition BEGIN =======////////////
	////////////////////////////////////////////////////////////////////
	enum Alignment {SPACE_BETWEEN, SPACE_AROUND, SPACE_EVENLY};
	class Layout : public Widget
	{
	public:
		//Vertical Layout
		Layout(const vf2d& position, int spacing, Orientation orientation = Orientation::VERTICAL)
			:
			Widget(position, { 0, 0 }), //Dynamic size,
			m_widgets(),
			m_spacing(spacing),
			m_orientation(orientation),
			m_widgets_height_sum(0)
		{
		}
		virtual ~Layout()
		{
			Destroy();
		}

		virtual void Update(const float& dt) override
		{

			for (auto& w : m_widgets)
					w->Update(dt);
			
		}
		virtual void Draw() override
		{

			for (auto& w : m_widgets)
					w->Draw();
		}

		/**
		 * Add a new widget in the container
		 * The container will take care of widget deallocation
		 * @return added widget
		 */
		void Add(Widget* widget)
		{
			m_widgets_height_sum += widget->getSize().y;

		
			widget->setPosition(
				{ 
					this->pos.x, 
					this->pos.y + m_widgets_height_sum + m_spacing
				}
			); // y+ spacing for vertical
			m_widgets.emplace_back(widget);

			std::cout << widget->getPosition().x << ", " << widget->getPosition().y << std::endl;
			std::cout << "m_widgets_height_sum: " << m_widgets_height_sum << std::endl<< std::endl;
		}

	
		/// Helpers
		//Button* addButton(const sf::String& string, std::function<void(void)> callback);
		//Label* addLabel(const sf::String& string);
		//FormLayout* addFormLayout();
		//HBoxLayout* addHBoxLayout();
		//VBoxLayout* addVBoxLayout();

		void Destroy()
		{
			for (auto& w : m_widgets)
			{
				if (w)
				{
					delete w;
					w = nullptr;
				}
			}
			m_widgets.clear();
		}
	private:
		std::vector<Widget*> m_widgets;
		int m_spacing;
		Orientation m_orientation;
		int m_widgets_height_sum;
	};



	////////////////////////////////////////////////////////////////////
	/////////========= Layout Class Definition END =======//////////////
	////////////////////////////////////////////////////////////////////
#endif




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

	Widget::Widget(const vf2d& position, const vf2d& size, const WidgetTheme& theme, WidgetState state)
		:
		pos(position),
		size(size),
		state(state),
		theme(theme)
	{
		assert(pge && "olcGUI Must be Initialized, have you called olc::widgets::Widget::Init(this); in OnUserCreate() ?");
		
		//each widget has a unique incremental id 
		id = ++idc;
	}

	void Widget::Update(const float& dt)
	{
		//Update Clock
		clock.Update(dt);

		//Nothing is happening so far
		state = WidgetState::IDLE;

		//Hover
		if (this->contains({ float(this->pge->GetMouseX()) ,float(this->pge->GetMouseY()) }))
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
	/////////======= Label Class Implementation BEGIN =======///////////
	////////////////////////////////////////////////////////////////////
	Label::Label(const vf2d& position,
		const std::string& text,
		const WidgetTheme& theme)
		:
		Widget(position, {0, 0}, theme),
		m_text(text),
		m_text_color(theme.textIdleColor)
	{
		const vf2d textSize = pge->GetTextSizeProp(m_text);
		this->setSize(textSize);
	}
	
	void Label::Update(const float& dt)
	{
		Widget::Update(dt);

		//Update Label & Text Color depending on state.
		switch (this->state)
		{
		case WidgetState::IDLE:
			m_text_color = this->theme.textIdleColor;
			break;
		case WidgetState::HOVER:
			m_text_color = this->theme.textHoverColor;
			break;
		case WidgetState::PRESSED:
			m_text_color = this->theme.textActiveColor;
			break;
		default: //Error state
			m_text_color = RED;
			break;
		}
	}

	void Label::Draw()
	{
		Widget::Draw();

		//Draw Label Text
		pge->DrawStringPropDecal(pos, m_text, m_text_color, this->theme.textScale);

		//pge->DrawStringPropDecal
		//(
		//	//put text in middle
		//	{
		//		this->pos.x + (this->size.x / 2.0f) - (pge->GetTextSizeProp(m_text).x / 2.0f),
		//		this->pos.y + (this->size.y / 2.0f) - (pge->GetTextSizeProp(m_text).y / 2.0f)
		//	},
		//	m_text,
		//	m_text_color,
		//	this->theme.textScale
		//);
	}
	Label::~Label() noexcept
	{

	}

	////////////////////////////////////////////////////////////////////
	/////////======= Label Class Implementation END =======/////////////
	////////////////////////////////////////////////////////////////////




	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Implementation BEGIN =======//////////
	////////////////////////////////////////////////////////////////////
	Button::Button(const vf2d& position, 
		const vf2d& size, 
		const std::string& text, 
		const WidgetTheme& theme)
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
		pge->DrawStringPropDecal
		(
			//put text in middle
			{
				this->pos.x + (this->size.x / 2.0f) - (pge->GetTextSizeProp(m_text).x / 2.0f),
				this->pos.y + (this->size.y / 2.0f) - (pge->GetTextSizeProp(m_text).y / 2.0f)
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
			pge->DrawLine(static_cast<std::uint32_t>(pos.x), static_cast<std::uint32_t>(pos.y + size.y), static_cast<std::uint32_t>(pos.x + size.x), static_cast<std::uint32_t>(pos.y + size.y), this->theme.shadowColor);
			//Right (to pos.y + size.y - 1: to not meet with bottom light, this will douplicate alpha color shadow at one point)
			pge->DrawLine(static_cast<std::uint32_t>(pos.x + size.x), static_cast<std::uint32_t>(pos.y), static_cast<std::uint32_t>(pos.x + size.x), static_cast<std::uint32_t>(pos.y + size.y - 1), this->theme.shadowColor);
			//Disable opacity
			pge->SetPixelMode(Pixel::NORMAL);
		}
		

	}

	Button::~Button() noexcept
	{
	}
	////////////////////////////////////////////////////////////////////
	/////////======= Button Class Implementation END =======////////////
	////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////
	///////===== SpriteButton Class Implementation BEGIN =======////////
	////////////////////////////////////////////////////////////////////
	SpriteButton::SpriteButton(
		const vf2d& position, const vf2d& size,
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
			this->isHover() ? vf2d(0.99f, 0.99f) : this->theme.textScale
		);

		//Draw Transparent Button base above the Sprite
		Button::Draw();

		//Reset draw mode
		pge->SetPixelMode(Pixel::NORMAL);
	}

	SpriteButton::~SpriteButton() noexcept
	{
	}
	////////////////////////////////////////////////////////////////////
	///////======= SpriteButton Class Implementation END =======////////
	////////////////////////////////////////////////////////////////////








	////////////////////////////////////////////////////////////////////
	///////===== DropDownList Class Implementation BEGIN =======////////
	////////////////////////////////////////////////////////////////////
	DropDownList::DropDownList(const vf2d& position, 
		const vf2d& size, 
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
			
			//TODO: If user pressed outside dropdownlist, close it
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


	DropDownList::~DropDownList() noexcept
	{
		delete m_active_element;
		for (auto& element : m_elements_list)
			delete element;
	}
	////////////////////////////////////////////////////////////////////
	///////===== DropDownList Class Implementation END =====///////
	////////////////////////////////////////////////////////////////////















	////////////////////////////////////////////////////////////////////
	///////===== ProgressBar Class Implementation BEGIN ======//////////
	////////////////////////////////////////////////////////////////////
	ProgressBar::ProgressBar(
		const vf2d& position,
		const vf2d& size,
		float value,
		Pixel progressColor,
		const WidgetTheme& theme)
		:
		Widget(position, size, theme),
		m_value(value),
		m_progress_color(progressColor)
	{
		
	}

	void ProgressBar::Update(const float& dt)
	{
		//Update Base class first
		Widget::Update(dt);


	}

	void ProgressBar::Draw()
	{
		//Draw Base class first
		Widget::Draw();

		//Draw Rect to be filled by progress
		pge->DrawRect(
			this->pos,
			this->size,
			this->theme.idleColor
		);

		//Draw transparent fill progress rect  (not the value, background of value)
		pge->FillRect(
			static_cast<std::uint32_t>(this->pos.x + 1),
			static_cast<std::uint32_t>(this->pos.y + 1),
			static_cast<std::uint32_t>(this->size.x - 1), 
			static_cast<std::uint32_t>(this->size.y - 1),
			Pixel(255, 255, 255, 200)
		);


		//Draw Line to fill progress rect according to progress value
		pge->FillRect(
			static_cast<std::uint32_t>(this->pos.x + 1),
			static_cast<std::uint32_t>(this->pos.y + 1),
			static_cast<std::uint32_t>(((this->size.x - 1) * m_value) / 100.0f), // calculate percentage value
			static_cast<std::uint32_t>(this->size.y - 1),
			m_progress_color
		);

		//Draw Percentage text e.g: 0.0%...100.0%
		{		
			std::ostringstream ss;
			ss	<< std::fixed
				<< std::setprecision(m_value >= 100.0f || m_value <= 0.0f ? 0 : 2)
				<< m_value << "%";

			pge->DrawStringPropDecal(
				{
					this->pos.x + (this->size.x / 2.0f) - (pge->GetTextSizeProp(ss.str()).x / 2.0f),
					this->pos.y + (this->size.y / 2.0f) - (pge->GetTextSizeProp(ss.str()).y / 2.0f)
				},
				ss.str(),
				this->theme.textActiveColor,
				this->theme.textScale
			);
		}
	}

	ProgressBar::~ProgressBar() noexcept
	{
	}
	////////////////////////////////////////////////////////////////////
	//////===== ProgressBar Class Implementation END =======///////
	////////////////////////////////////////////////////////////////////



















}}

#endif