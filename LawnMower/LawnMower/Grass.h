#ifndef _LAWNMOWER_GRASS_H_
#define _LAWNMOWER_GRASS_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados possíveis para o jogador
enum GRASSSTATE { ALIVE, DEAD };

// ---------------------------------------------------------------------------------

class Grass : public Object
{
private:
    Sprite * aliveGrass = nullptr;      // sprite da grama viva
    Sprite * deadGrass = nullptr;       // sprite da grama morta

public:
    uint state;

    Grass(float, float);               // construtor
    ~Grass();                          // destrutor

    void OnCollision(Object * obj);     // resolução da colisão
    //void PivotCollision(Object * obj);  // revolve colisão com pivô

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
