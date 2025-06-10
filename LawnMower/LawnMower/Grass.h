#ifndef _LAWNMOWER_GRASS_H_
#define _LAWNMOWER_GRASS_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss�veis para o jogador
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

    void OnCollision(Object * obj);     // resolu��o da colis�o
    //void PivotCollision(Object * obj);  // revolve colis�o com piv�

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
