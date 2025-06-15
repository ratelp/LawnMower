#ifndef _LAWNMOWER_BULLET_H_
#define _LAWNMOWER_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"              // tipos específicos da engine
#include "Object.h"             // interface de object
#include "Sprite.h"             // interface de sprites
#include "Image.h"              // interface de image
#include "Player.h"
#include "Villain.h"


// ---------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite * sprite;
    float speed;
    float speedX;
    float speedY;
    float whereToX;
    float whereToY;

public:
    Bullet(Image* image, float targetX, float targetY);
    //Bullet(Image * img, Player * currentPlayer);
    ~Bullet();

    void OnCollision(Object * obj);     // resolução da colisão

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline void Bullet::Draw()
{ sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
