#include "LawnMower.h"
#include "Grass.h"

// ---------------------------------------------------------------------------------

Grass::Grass(float x, float y)
{
    aliveGrass = new Sprite("Resources/grassNoBG.png");
    cuttedGrass = new Sprite("Resources/grassNoBGcut.png");
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
    if(life < maxLife/2.0f){
        state = CUTTED;
    }
    if (life <= 0) {
        state = DEAD;
        DeleteBBox();
    }

}

// ---------------------------------------------------------------------------------

void Grass::OnCollision(Object* obj)
{
    if (obj->Type() == PLAYER) {
        life -= maxLife  *gameTime;
    }
}

// ---------------------------------------------------------------------------------

void Grass::Draw()
{
    if (state == ALIVE)
        aliveGrass->Draw(x, y, Layer::LOWER);
    else if (state == CUTTED)
        cuttedGrass->Draw(x, y, Layer::LOWER);
    else
        deadGrass->Draw(x, y, Layer::LOWER);
}

// ---------------------------------------------------------------------------------
