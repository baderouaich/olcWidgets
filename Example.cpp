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
	olc::widgets::ProgressBar* progressBar;

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

		//Sprite Button
 		spriteBtn = new olc::widgets::SpriteButton(
			{ button->getPosition().x + button->getSize().x + 30, 10 },
			{ 130, 40 },
			"Sprite Btn",
			"btnSpr130x40.png"
		);
		

		//DropDownList
		dropDownList = new olc::widgets::DropDownList(
			{ spriteBtn->getPosition().x + button->getSize().x + 30, 10 },
			{ 130, 30 },
			{"First!!", "Select Me", "DropDownList", "No! select mee"},
			2 //default index
		);
		

		//ProgressBar
		progressBar = new olc::widgets::ProgressBar(
			{ dropDownList->getPosition().x + button->getSize().x + 30, 10 },
			{ 130, 20 },
			50.0f // 50%
		);
		progressBar->setValue(progressBar->getValue() + 10.0f); // 60%: 50% + 10%


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREY);

		//Update
		button->Update(fElapsedTime); if (button->isPressed()) {/*Do Something*/ }
		spriteBtn->Update(fElapsedTime);
		dropDownList->Update(fElapsedTime);
		progressBar->Update(fElapsedTime);  progressBar->setValue(progressBar->getValue() + (GetMouseWheel() > 0 ? 100 * fElapsedTime : GetMouseWheel() < 0 ? -100 * fElapsedTime : 0));

		//Draw
		button->Draw();
		spriteBtn->Draw();
		dropDownList->Draw();
		progressBar->Draw();

		return true;
	}

	bool OnUserDestroy() override
	{
		delete button;
		delete spriteBtn;
		delete dropDownList;
		delete progressBar;

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