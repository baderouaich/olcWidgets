#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGEX_WIDGETS
#include "olcWidgets.h"

class GameMenuExample : public olc::PixelGameEngine
{
public:
	GameMenuExample()
	{
		sAppName = "olcWidgets Game Menu Example";
	}

private:

	std::map<std::string, std::unique_ptr<olc::widgets::Widget>> widgets;

public:
	bool OnUserCreate() override
	{
		using namespace olc::widgets;

		/// Initialize olcWidgets
		Widget::init(this);

		/// Construct Desired Widgets
		constexpr auto LABEL_TEXT = "Amazing Game Menu!";
		const auto LABEL_TEXT_SIZE = GetTextSizeProp(LABEL_TEXT);
		
		WidgetTheme labelTheme{};
		labelTheme.textScale = { 1.5f, 1.5f };
		labelTheme.textIdleColor = olc::WHITE;
		labelTheme.textHoverColor = olc::CYAN;
		labelTheme.textActiveColor = olc::RED;
		widgets["MenuLabel"].reset(new Label(
			{ (ScreenWidth() - LABEL_TEXT_SIZE.x * labelTheme.textScale.x ) / 2.0f, (ScreenHeight() / 6.0f) },
			"Amazing Game Menu!",
			labelTheme
		));

		constexpr float BUTTON_WIDTH = 250.0f;
		constexpr float BUTTON_HEIGHT = 30.0f;

		widgets["StartButton"].reset(new Button(
			{ (ScreenWidth() - BUTTON_WIDTH) / 2.0f, (ScreenHeight() / 4.0f) },
			{ BUTTON_WIDTH, BUTTON_HEIGHT },
			"Start"
			));
		widgets["HistoryButton"].reset(new Button(
			{ (ScreenWidth() - BUTTON_WIDTH) / 2.0f, (ScreenHeight() / 3.0f) },
			{ BUTTON_WIDTH, BUTTON_HEIGHT },
			"History"
		));
		WidgetTheme exitButtonTheme{};
		exitButtonTheme.idleColor = olc::DARK_RED;
		exitButtonTheme.activeColor = olc::RED;
		exitButtonTheme.hoverColor = olc::VERY_DARK_RED;
		exitButtonTheme.textScale = { 1.3f, 1.3f };
		widgets["ExitButton"].reset(new Button(
			{ (ScreenWidth() - BUTTON_WIDTH) / 2.0f, (ScreenHeight() / 2.0f) },
			{ BUTTON_WIDTH, BUTTON_HEIGHT },
			"Exit",
			exitButtonTheme
		));


		widgets["LoadingBar"].reset(new ProgressBar(
			{ (ScreenWidth() - BUTTON_WIDTH) / 2.0f, (ScreenHeight() / 1.5f) },
			{ BUTTON_WIDTH, BUTTON_HEIGHT / 2.0f},
			0.0f
		));


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		using namespace olc::widgets;

		Clear(olc::VERY_DARK_CYAN);

		/// Update & Draw your Widgets

		//Update
		for (const auto& [name, widget] : widgets) // c++17
		{
			widget->Update(fElapsedTime);
		}


		{ // ProgressBar
			static float v = 0.0f;
			auto& pbr = dynamic_cast<ProgressBar&>(*widgets["LoadingBar"]);
			pbr.setValue(v);
			v += fElapsedTime * 9.f;
			if (v >= 100.0f) v = 0.0;
		}

		//Draw
		for (const auto& [name, widget] : widgets) // c++17
		{
			widget->Draw();
		}

		return not widgets["ExitButton"]->isPressed();
	}

	bool OnUserDestroy() override
	{
		widgets.clear();
		return true;
	}
};



int main()
{
	GameMenuExample demo;
	if (demo.Construct(640, 480, 2, 2))
		demo.Start();
	return 0;
}