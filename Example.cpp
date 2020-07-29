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
	olc::widgets::DropDownList* dropDownList;
	olc::widgets::SpriteButton* spriteBtn;
	olc::widgets::ProgressBar* progressBar;
	olc::widgets::Label* label;

public:
	bool OnUserCreate() override
	{
		/// Initialize olcWidgets
		olc::widgets::Widget::Init(this);

		/// Construct Desired Widgets

		//Button
 		button = new olc::widgets::Button(
			{ 10, 10 },
			{ 130, 30 },
			"Button"
		);


		//DropDownList
		dropDownList = new olc::widgets::DropDownList(
			{ button->getPosition().x + button->getSize().x + 30, 10 },
			{ 130, 30 },
			{"First!!", "Select Me", "DropDownList", "No! select mee"},
			2 //default index
		);
		

		//Sprite Button
		spriteBtn = new olc::widgets::SpriteButton(
			{ dropDownList->getPosition().x + dropDownList->getSize().x + 30, 10 },
			{ 130, 40 },
			"Sprite Btn",
			"btnSpr130x40.png"
		);


		//ProgressBar
		progressBar = new olc::widgets::ProgressBar(
			{ spriteBtn->getPosition().x + spriteBtn->getSize().x + 30, 10 },
			{ 130, 20 },
			50.0f // 50%
		);
		progressBar->setValue(progressBar->getValue() + 10.0f); // 60%: 50% + 10%

		

		//Label
		label = new olc::widgets::Label(
			{ 30, 60 },
			"Label"
		);


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);

		/// Update & Draw your Widgets

		//Update
		button->Update(fElapsedTime); if (button->isPressed()) {/*Do Something*/ }
		dropDownList->Update(fElapsedTime);
		spriteBtn->Update(fElapsedTime);
		progressBar->Update(fElapsedTime);  progressBar->setValue(progressBar->getValue() + (GetMouseWheel() > 0 ? 100 * fElapsedTime : GetMouseWheel() < 0 ? -100 * fElapsedTime : 0));
		label->Update(fElapsedTime); 

		//Draw
		button->Draw();
		dropDownList->Draw();
		spriteBtn->Draw();
		progressBar->Draw();
		label->Draw();

		return true;
	}

	bool OnUserDestroy() override
	{
		delete button;
		delete dropDownList;
		delete spriteBtn;
		delete progressBar;
		delete label;

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