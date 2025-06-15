#include "Engine.h"
#include "Score.h"
#include "Home.h"
#include <fstream>
#include <sstream>
#include <map>

void Score::Init()
{
    //background = new Sprite("Resources/home_background_temp.jpg");

    allStars = new Sprite("Resources/threeStars.png");
    twoStars = new Sprite("Resources/twoStars.png");
    oneStar = new Sprite("Resources/oneStars.png");
    noStars = new Sprite("Resources/failStars.png");

	terminal30 = new Font("Resources/terminal30.png");
	terminal30->Spacing(80);
	terminal22 = new Font("Resources/terminal22.png");
	terminal22->Spacing(55);
	terminal20 = new Font("Resources/terminal20.png");
	terminal20->Spacing(34);
    
    std::ifstream fin;
    fin.open("Resources/level1_score.dat", std::ios_base::in, std::ios_base::binary);
    fin.read((char*)&score, sizeof(ScoreStruct));
    fin.close();

	//score.playerDead = false;
}

void Score::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
        Engine::Next<Home>();
}

void Score::Draw()
{
    //background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	if (score.playerDead) {
		noStars->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
		terminal30->Draw(window->CenterX() - 285, window->CenterY() - 150, "GAME OVER");
	} else {
		std::map<float, Interval> imap{
			{0.0f, One},
			{60.0f, Two},
			{120.0f, Three},
			{121.0f, NotFound}
		};

		Interval ivalue = NotFound;
		auto it = imap.upper_bound(score.time);
		
		if (it != imap.begin()) {
			it--;
			ivalue = it->second;
		} else ivalue = One;

		std::stringstream text;
		switch (ivalue) {
			case One:
				text << "Seu Tempo: " << std::round(score.time) << 's';
				
				allStars->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				terminal22->Draw(window->CenterX() - 325, window->CenterY() - 150, "CONGRATULATIONS");
				terminal20->Draw(window->CenterX() - 135, window->CenterY() + 150, text.str().c_str());

				text.str("");
				break;
			case Two:
				text << "Seu Tempo: " << std::round(score.time) << 's';

				twoStars->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				terminal30->Draw(window->CenterX() - 285, window->CenterY() - 150, "GREAT JOB");
				terminal20->Draw(window->CenterX() - 135, window->CenterY() + 150, text.str().c_str());

				text.str("");
				break;
			case Three:
				text << "Seu Tempo: " << std::round(score.time) << 's';

				oneStar->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				terminal30->Draw(window->CenterX() - 75, window->CenterY() - 150, "NICE");
				terminal20->Draw(window->CenterX() - 135, window->CenterY() + 150, text.str().c_str());

				text.str("");
				break;
			default:
				text << "Seu Tempo: " << std::round(score.time) << 's';

				oneStar->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				terminal30->Draw(window->CenterX() - 75, window->CenterY() - 150, "NICE");
				terminal20->Draw(window->CenterX() - 135, window->CenterY() + 150, text.str().c_str());

				text.str("");
				break;
		}
	}
}

void Score::Finalize()
{
    //delete background;
	delete allStars;
	delete twoStars;
	delete oneStar;
	delete noStars;
}
