#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGEX_WIDGETS
#include "olcWidgets.h"

class olcWidgetsExample : public olc::PixelGameEngine
{
public:
	olcWidgetsExample()
	{
		sAppName = "olcWidgets Example";
	}

private:
	olc::widgets::Button* button;
	olc::widgets::SpriteButton* spriteBtn;
	olc::widgets::DropDownList* dropDownList;

public:
	bool OnUserCreate() override
	{
		//Initialize olcWidgets
		olc::widgets::Widget::Init(this);

		//Construct Desired Widgets

		//Button
 		button = new olc::widgets::Button(
			{ 10, 10 },
			{ 130, 30 },
			"Button"
		);

		//Sprite Button
 		spriteBtn = new olc::widgets::SpriteButton(
			{ button->getPosition().x + button->getSize().x + 30, 10 },
			{ 130, 40 },
			"Sprite Btn",
			"btnSpr130x40.png"
		);

		//DropDownList
		//Note: get dropdown list selected item type Button using dropDownList->getSelectedItem()
		dropDownList = new olc::widgets::DropDownList(
			{ 10, 60 },
			{ 130, 30 },
			{"First!!", "Select Me", "DropDownList", "No! select mee"},
			2 //default index
		);

	
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);


		//Update
		button->Update(fElapsedTime);
		spriteBtn->Update(fElapsedTime);
		if (button->isPressed()){/*Do Something*/ }
		dropDownList->Update(fElapsedTime);


		//Draw
		button->Draw();
		spriteBtn->Draw();
		dropDownList->Draw();

		return true;
	}

	bool OnUserDestroy() override
	{
		delete button;
		delete spriteBtn;
		delete dropDownList;

		return true;
	}
};



int main()
{
	olcWidgetsExample demo;
	if (demo.Construct(640, 480, 2, 2))
		demo.Start();
	return 0;
}