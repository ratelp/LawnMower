#ifndef _LAWNMOWER_WALL_H_
#define _LAWNMOWER_WALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                          // tipos específicos da engine
#include "Object.h"                         // interface de Object

// ---------------------------------------------------------------------------------

class Wall : public Object
{
public:
    Wall(float, float, float, float, float, float);  // construtor
    ~Wall();                                         // destrutor

    void Update() {};                       // atualização
    void Draw() {};                         // desenho
};

// ---------------------------------------------------------------------------------

#endif
