#ifndef _LAWNMOWER_SCORE_H_
#define _LAWNMOWER_SCORE_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "LifeIndicator.h"
#include "Timer.h"
#include "ScoreStruct.h"
#include "Font.h"

// ------------------------------------------------------------------------------

enum Interval {One, Two, Three, NotFound};

// ------------------------------------------------------------------------------

class Score : public Game
{
private:
    Sprite * background = nullptr;       // background
    ScoreStruct score;

    Sprite * allStars = nullptr;
    Sprite* twoStars = nullptr;
    Sprite* oneStar = nullptr;
    Sprite* noStars = nullptr;

    Font * terminal30 = nullptr;
    Font * terminal25 = nullptr;
    Font * terminal24 = nullptr;
    Font * terminal23 = nullptr;
    Font * terminal22 = nullptr;
    Font * terminal20 = nullptr;

public:
    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

#endif
