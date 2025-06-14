#ifndef _LAWNMOWER_LEVEL_INDICATOR_H_
#define _LAWNMOWER_LEVEL_INDICATOR_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Object.h"
#include "Sprite.h"
#include "Player.h"

// ------------------------------------------------------------------------------
// Constantes Globais

class LifeIndicator : public Object
{
private:
    Sprite * fullLife = nullptr;
	Sprite* threeQuartersLife = nullptr;
	Sprite* halfLife = nullptr;
	Sprite* almostDead = nullptr;
    Sprite* gameOver = nullptr;

	Player * player = nullptr;

public:
    LifeIndicator(Player* player);  // construtor
    ~LifeIndicator();  // destrutor
    void Update();
    void Draw();                    // desenha jogo
};

#endif
