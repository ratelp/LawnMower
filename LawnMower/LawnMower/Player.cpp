#include "LawnMower.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    spriteL = new Sprite("Resources/player1left.png");
    spriteR = new Sprite("Resources/player1right.png");
    spriteU = new Sprite("Resources/player1up.png");
    spriteD = new Sprite("Resources/player1down.png");

    // imagem do player up é 84x92
    BBox(new Rect(- (spriteL->Width() / 2.0f - 10), - (spriteL->Width() / 2.0f - 8), (spriteL->Width() / 2.0f - 10), (spriteL->Width() / 2.0f - 8)));
    
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
        currState = UP;
    }
    if (window->KeyDown(VK_LEFT)) {
        Left();
        Translate(velX, velY);
        currState = LEFT;
    }
    if (window->KeyDown(VK_RIGHT)) {
        Right();
        Translate(velX, velY);
        currState = RIGHT;
    }
    if (window->KeyDown(VK_DOWN)) {
        Down();
        Translate(velX, velY);
        currState = DOWN;
    }

    // Consertar posíveis saídas do cenário por cima
    if (currState == UP && y - spriteU->Height() / 2.0f < 60)
        MoveTo(x, 50 + spriteU->Height() / 2.0f);
    else if (currState == LEFT && y - spriteL->Height() / 2.0f < 60)
        MoveTo(x, 50 + spriteL->Height() / 2.0f);
    else if (currState == RIGHT && y - spriteR->Height() / 2.0f < 60)
        MoveTo(x, 50 + spriteR->Height() / 2.0f);
    else if (currState == DOWN && y - spriteD->Height() / 2.0f < 60)
        MoveTo(x, 50 + spriteD->Height() / 2.0f);
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
        default:    spriteU->Draw(x, y, Layer::UPPER);
        }
    }
}

// ---------------------------------------------------------------------------------
