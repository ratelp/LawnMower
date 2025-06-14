#ifndef _LAWNMOWER_LEVEL1_H_
#define _LAWNMOWER_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "LifeIndicator.h"
#include "Timer.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite * background = nullptr;       // background
    bool viewBBox = false;               // habilita visualização da bounding box
    Player * player = nullptr;
	LifeIndicator* lifeIndicator = nullptr; // indicador de vida do jogador

    Timer scoreTimer;
    
public:
    static Scene * scene;             // gerenciador de cena
    static bool playerDead;
    static bool grassCut;               // determina se o grass já foi todo cortado

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
    bool allGrassCut();             // verifica se toda grama foi cortada
};

#endif
