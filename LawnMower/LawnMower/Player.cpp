#include "LawnMower.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    spriteL = new Sprite("Resources/player1.png");
    spriteR = new Sprite("Resources/player1.png");
    spriteU = new Sprite("Resources/player1.png");
    spriteD = new Sprite("Resources/player1.png");

    // imagem do pacman é 48x48 (com borda transparente de 4 pixels)
    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(480.0f, 460.0f);
    type = PLAYER;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete spriteL;
    delete spriteR;
    delete spriteU;
    delete spriteD;
}

// ---------------------------------------------------------------------------------

void Player::Stop()
{
    velX = 0;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Up()
{
    velX = 0;
    velY = -200.0f * gameTime;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
    velX = 0;
    velY = 200.0f * gameTime;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
    velX = -200.0f * gameTime;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
    velX = 200.0f * gameTime;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    if (window->KeyDown(VK_UP)) {
        Up();
        Translate(velX, velY);
    }
    if (window->KeyDown(VK_LEFT)) {
        Left();
        Translate(velX, velY);
    }
    if (window->KeyDown(VK_RIGHT)) {
        Right();
        Translate(velX, velY);
    }
    if (window->KeyDown(VK_DOWN)) {
        Down();
        Translate(velX, velY);
    }
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    switch (currState)
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
    }
}

// ---------------------------------------------------------------------------------
