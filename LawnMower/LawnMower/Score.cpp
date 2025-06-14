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
    
    std::ifstream fin;
    fin.open("Resources/level1_score.dat", std::ios_base::in, std::ios_base::binary);
    fin.read((char*)&score, sizeof(ScoreStruct));
    fin.close();

	// score.playerDead = false;
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

		switch (ivalue) {
			case One:
				allStars->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				break;
			case Two:
				twoStars->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				break;
			case Three:
				oneStar->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
				break;
			default:
				oneStar->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
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
