#include "LifeIndicator.h"
#include <sstream>

LifeIndicator::LifeIndicator(Player * play)
{
	fullLife = new Sprite("Resources/full_life.png");
	threeQuartersLife = new Sprite("Resources/three_quarters_life.png");
	halfLife = new Sprite("Resources/half_life.png");
	almostDead = new Sprite("Resources/almost_dead.png");
	gameOver = new Sprite("Resources/game_over.png");

	player = play;
}

LifeIndicator::~LifeIndicator()
{
	delete fullLife;
	delete threeQuartersLife;
	delete halfLife;
	delete almostDead;
	delete gameOver;
}

void LifeIndicator::Draw()
{
	switch (player->life)
	{
	case 4:
		fullLife->Draw(50, 10, Layer::FRONT);
		break;
	case 3:
		threeQuartersLife->Draw(50, 10, Layer::UPPER);
		break;
	case 2:
		halfLife->Draw(50, 10, Layer::UPPER);
		break;
	case 1:
		almostDead->Draw(50, 10, Layer::UPPER);
		break;
	case 0:
		gameOver->Draw(50, 10, Layer::UPPER);
		break;
	
	default:
		break;
	}
}

void LifeIndicator::Update()
{
	return;
}