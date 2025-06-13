#include "LawnMower.h"
#include "Grass.h"

// ---------------------------------------------------------------------------------

Grass::Grass(float x, float y)
{
    aliveGrass = new Sprite("Resources/grass.png");
    deadGrass = new Sprite("Resources/noGrass.png");

    // imagem do grass é 61x61
    BBox(new Rect(-31, -31, 30, 30));
    MoveTo(x, y);
    
    type = GRASS;
    state = ALIVE;
}

// ---------------------------------------------------------------------------------

Grass::~Grass()
{
    delete aliveGrass;
    delete deadGrass;
}

// ---------------------------------------------------------------------------------

void Grass::Update()
{
    if (state == DEAD) BBox(new Rect(0, 0, 0, 0));
}

// ---------------------------------------------------------------------------------

void Grass::OnCollision(Object* obj)
{
    if (obj->Type() == PLAYER) {
        state = DEAD;
    }
}

// ---------------------------------------------------------------------------------

void Grass::Draw()
{
    if (state == ALIVE)
        aliveGrass->Draw(x, y, Layer::LOWER);
    else
        deadGrass->Draw(x, y, Layer::LOWER);
}

// ---------------------------------------------------------------------------------
