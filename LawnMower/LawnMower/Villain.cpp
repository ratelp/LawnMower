#include "LawnMower.h"
#include "Villain.h"
#include "Bullet.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

Villain::Villain(Player* currentPlayer)
{
    spriteL = new Sprite("Resources/villain1.png");
    spriteR = new Sprite("Resources/villain1.png");
    spriteU = new Sprite("Resources/villain1.png");
    spriteD = new Sprite("Resources/villain1.png");

    spriteL2 = new Sprite("Resources/villain2.png");
    spriteR2 = new Sprite("Resources/villain2.png");
    spriteU2 = new Sprite("Resources/villain2.png");
    spriteD2 = new Sprite("Resources/villain2.png");

    spriteL3 = new Sprite("Resources/villain3.png");
    spriteR3 = new Sprite("Resources/villain3.png");
    spriteU3 = new Sprite("Resources/villain3.png");
    spriteD3 = new Sprite("Resources/villain3.png");

    spriteL4 = new Sprite("Resources/villain4.png");
    spriteR4 = new Sprite("Resources/villain4.png");
    spriteU4 = new Sprite("Resources/villain4.png");
    spriteD4 = new Sprite("Resources/villain4.png");

    bullet = new Image("Resources/villainBullets.png");

    player = currentPlayer;

    // imagem do pacman é 48x48 (com borda transparente de 4 pixels)
    BBox(new Rect(- (spriteL->Width() / 2.0f), -(spriteL->Width() / 2.0f - 4), (spriteL->Width() / 2.0f), (spriteL->Width() / 2.0f - 2)));
    MoveTo(window->CenterX(), window->CenterY() - 210);
    
    type = VILLAIN;
}

// ---------------------------------------------------------------------------------

Villain::~Villain()
{
    delete spriteL;
    delete spriteR;
    delete spriteU;
    delete spriteD;

    delete spriteL2;
    delete spriteR2;
    delete spriteU2;
    delete spriteD2;

    delete spriteL3;
    delete spriteR3;
    delete spriteU3;
    delete spriteD3;

    delete spriteL4;
    delete spriteR4;
    delete spriteU4;
    delete spriteD4;

    delete bullet;
}

// ---------------------------------------------------------------------------------

void Villain::Stop()
{
}

// ---------------------------------------------------------------------------------

void Villain::Up()
{
}

// ---------------------------------------------------------------------------------

void Villain::Down()
{
}

// ---------------------------------------------------------------------------------

void Villain::Left()
{
}

// ---------------------------------------------------------------------------------

void Villain::Right()
{
}

// ---------------------------------------------------------------------------------

void Villain::Update()
{
    if (player->playerLife == ALIVEP)
    {
        bulletsCooldownTimer -= gameTime;

        if (bulletsCooldownTimer <= 0.0f) {
            Bullet* b = new Bullet(bullet, player);
            b->MoveTo(x, y + spriteL->Height() / 2.0f, Layer::FRONT);
            Level1::scene->Add(b, MOVING);

            bulletsCooldownTimer = bulletsCooldownMaxTimer;
        }
    }
}

// ---------------------------------------------------------------------------------

void Villain::OnCollision(Object * obj)
{
}

// ---------------------------------------------------------------------------------

void Villain::Draw()
{

    spriteL->Draw(x, y, Layer::UPPER);

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
