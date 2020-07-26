#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGEX_WIDGETS
#include "olcWidgets.h"

class olcGuiExample : public olc::PixelGameEngine
{
public:
	olcGuiExample()
	{
		//Initialize olcWidgets
		olc::widgets::Widget::Init(this);

		sAppName = "olcGUI Example";
	}

private:
	olc::widgets::Button* button;
	olc::widgets::DropDownList* dropDownList;
	olc::widgets::CheckBox* checkBox;
	bool isChecked = false;

public:
	bool OnUserCreate() override
	{
 		button = new olc::widgets::Button(
			{ 10, 10 },
			{ 160, 45 },
			"Hi I am a Button!!!"
		);


		//Note: get dropdown list selected item type Button using dropDownList->getSelectedItem()
		dropDownList = new olc::widgets::DropDownList(
			{ 160 + 30, 10 },
			{ 160, 45 },
			{"Hello", "Select Me", "I am default", "No! select mee", "here we go again"},
			2 //default index
		);


		checkBox = new olc::widgets::CheckBox(
			{  10, 100 },
			{ 160, 45 },
			"Check Me up!",
			&isChecked
		);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Update
		button->Update(fElapsedTime);
		if (button->isPressed())
		{
			//Do Something
		}
		dropDownList->Update(fElapsedTime);
		checkBox->Update(fElapsedTime);


		//Draw
		Clear(olc::GREY);
		//FillRect(button->getPosition(), { 300, 300 }, olc::YELLOW); // to see shadow opacity
		button->Draw();
		dropDownList->Draw();
		checkBox->Draw();

		return true;
	}

	bool OnUserDestroy() override
	{
		delete button;
		delete dropDownList;
		delete checkBox;

		return true;
	}
};



int main()
{
	olcGuiExample demo;
	if (demo.Construct(640, 480, 2, 2))
		demo.Start();
	return 0;
}