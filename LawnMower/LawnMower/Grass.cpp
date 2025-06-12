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

    /*switch (currState)
    {
    case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
    case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
    case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
    case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
    default:
        switch (nextState)
        {
        case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
        case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
        case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
        default:    spriteL->Draw(x, y, Layer::UPPER);
        }
    }*/
}

// ---------------------------------------------------------------------------------
