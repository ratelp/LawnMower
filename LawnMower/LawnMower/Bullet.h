#ifndef _LAWNMOWER_BULLET_H_
#define _LAWNMOWER_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"              // tipos específicos da engine
#include "Object.h"             // interface de object
#include "Sprite.h"             // interface de sprites
#include "Image.h"              // interface de image

// ---------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite * sprite;
    float speed;

public:
    Bullet(Image * img);
    ~Bullet();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline void Bullet::Draw()
{ sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
