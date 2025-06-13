#ifndef _LAWNMOWER_LEVEL1_H_
#define _LAWNMOWER_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite * background = nullptr;       // background
    bool viewBBox = false;               // habilita visualiza��o da bounding box
    Player * player = nullptr;
    bool grassCut = false;               // determina se o grass j� foi todo cortado

public:
    static Scene * scene;             // gerenciador de cena

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
    bool allGrassCut();             // verifica se toda grama foi cortada
};

#endif
