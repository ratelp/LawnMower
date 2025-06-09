#ifndef _LAWNMOWER_LEVEL1_H_
#define _LAWNMOWER_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite * background = nullptr;       // background
    Scene * scene = nullptr;             // gerenciador de cena
    bool viewBBox = false;               // habilita visualiza��o da bounding box

public:
    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

#endif
