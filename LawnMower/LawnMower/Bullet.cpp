#include "Bullet.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

Bullet::Bullet(Image* image)
{
	sprite = new Sprite(image);
	speed = 250;
}

// ---------------------------------------------------------------------------------

Bullet::~Bullet()
{
	delete sprite;
}

// ---------------------------------------------------------------------------------

void Bullet::Update()
{
    // míssil se move apenas no eixo y
    Translate(0, speed * gameTime);

    // remove mísseis que saem da janela
    if (y < window->Height())
        Level1::scene->Delete();
}

// ---------------------------------------------------------------------------------
