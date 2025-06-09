#ifndef _LAWNMOWER_HOME_H_
#define _LAWNMOWER_HOME_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    Sprite * background = nullptr;  // plano de fundo

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif
