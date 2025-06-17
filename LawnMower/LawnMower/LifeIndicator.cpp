#include "LifeIndicator.h"
#include <sstream>

LifeIndicator::LifeIndicator(Player * play)
{
	fullLife = new Sprite("Resources/full_life - Copia.png");
	threeQuartersLife = new Sprite("Resources/three_quarters_life - Copia.png");
	halfLife = new Sprite("Resources/half_life - Copia.png");
	almostDead = new Sprite("Resources/almost_dead - Copia.png");
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
		fullLife->Draw(85, 25, Layer::FRONT);
		break;
	case 3:
		threeQuartersLife->Draw(85, 25, Layer::UPPER);
		break;
	case 2:
		halfLife->Draw(85, 25, Layer::UPPER);
		break;
	case 1:
		almostDead->Draw(85, 25, Layer::UPPER);
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