#ifndef _LAWNMOWER_WALL_H_
#define _LAWNMOWER_WALL_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                          // tipos espec�ficos da engine
#include "Object.h"                         // interface de Object

// ---------------------------------------------------------------------------------

class Wall : public Object
{
public:
    Wall(float, float, int, int, int, int);  // construtor
    ~Wall();                               // destrutor

    void Update() {};                       // atualiza��o
    void Draw() {};                         // desenho
};

// ---------------------------------------------------------------------------------

#endif
