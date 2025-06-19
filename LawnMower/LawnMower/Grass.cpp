#include "LawnMower.h"
#include "Grass.h"

// ---------------------------------------------------------------------------------

Grass::Grass(float x, float y)
{
    cuttedGrass = new Sprite("Resources/grassNoBGcut.png");
    deadGrass = new Sprite("Resources/noGrass.png");
	//aliveGrass = new Sprite("Resources/grassNoBG.png");

    aliveGrass = new TileSet("Resources/grass_sprite_sheet.png", 67, 67, 5, 1);
    animation = new Animation(aliveGrass, 0.15f, true);

    uint Seq1[5] = { 0, 1, 2, 3, 4 };

    animation->Add(ALIVE, Seq1, 5);

    cutTimer = new Timer();

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
    //delete animation;
}

// ---------------------------------------------------------------------------------

void Grass::Update()
{
    if (state == ALIVE) {
        animation->NextFrame();
    }
    if(life < maxLife/2.0f && state != DEAD){
        if (state == ALIVE) {
            state = CUTTED;
            cutTimer->Start();
        }
        else if (cutTimer->Elapsed() > 10) {
            life = maxLife;
            state = ALIVE;
			cutTimer->Reset();
        }
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
		//aliveGrass->Draw(x, y, Layer::LOWER);
        animation->Draw(x, y, Layer::LOWER);
    else if (state == CUTTED)
        cuttedGrass->Draw(x, y, Layer::LOWER);
    else
        deadGrass->Draw(x, y, Layer::LOWER);
}

// ---------------------------------------------------------------------------------
