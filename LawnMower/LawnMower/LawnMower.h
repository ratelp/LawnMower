#ifndef _LAWNMOWER_H_
#define _LAWNMOWER_H_

// ---------------------------------------------------------------------------------

enum LawnMowerObjects { PLAYER, GRASS, VILLAIN, WALL, BULLET };
enum { VILLAIN_SPRITE_CHANGE, SHOT1, SHOT2, KNOCKBACK, HIT, CAR_NOISE, GAME_OVER, WINNER};
// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"

class LawnMower : public Game
{
private:
    static Game* level;            // nível atual do jogo

public:

    static Audio* audio;


    void Init();                    // inicializa jogo
    void Update();                  // atualiza jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

#endif
