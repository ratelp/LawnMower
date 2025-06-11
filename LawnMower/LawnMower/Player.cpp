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
    
    MoveTo(480.0f, 456.0f);
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
    /*if (currState == UP && y - spriteU->Height() / 2.0f < 60)
        MoveTo(x, 51 + spriteU->Height() / 2.0f);
    else if (currState == LEFT && y - spriteL->Height() / 2.0f < 60)
        MoveTo(x, 53 + spriteL->Height() / 2.0f);
    else if (currState == RIGHT && y - spriteR->Height() / 2.0f < 60)
        MoveTo(x, 53 + spriteR->Height() / 2.0f);

    if (currState == UP && x + spriteU->Width() / 2.0f > 885)
        MoveTo(885 - spriteU->Width() / 2.0f, y);
    else if (currState == LEFT && x + spriteL->Width() / 2.0f > 885)
        MoveTo(885 - spriteL->Width() / 2.0f, y);
    else if (currState == RIGHT && x + spriteR->Width() / 2.0f > 885)
        MoveTo(885 - spriteR->Width() / 2.0f, y);
    else if (currState == DOWN && x + spriteD->Width() / 2.0f > 885)
        MoveTo(885 - spriteD->Width() / 2.0f, y);*/
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    /*if (obj->Type() != VILLAIN) {
        if (currState == UP)
            MoveTo(x, y + 1);
        else if (currState == DOWN)
            MoveTo(x, y - 1);
        else if (currState == LEFT)
            MoveTo(x + 1, y);
        else if (currState == RIGHT)
            MoveTo(x - 1, y);
    }
    else {
        if (currState == UP)
            Translate(0, 80);
        else if (currState == LEFT)
            Translate(80,0);
        else if (currState == RIGHT)
            Translate(-80, 0);
    }*/

    if (obj->Type() == WALL) {
        Geometry* playerGeo = BBox();
        Geometry* wallGeo = obj->BBox();

        Rect* playerRect = dynamic_cast<Rect*>(playerGeo);
        Rect* wallRect = dynamic_cast<Rect*>(wallGeo);

        if (playerRect && wallRect) {
            // Calcule as sobreposições em cada direção
            float overlapX_left = playerRect->right - wallRect->left;    // Player à esquerda da parede
            float overlapX_right = playerRect->left - wallRect->right; // Player à direita da parede
            float overlapY_top = playerRect->bottom - wallRect->top;    // Player acima da parede
            float overlapY_bottom = playerRect->top - wallRect->bottom; // Player abaixo da parede

            // Determine a menor sobreposição absoluta em X e Y
            float minOverlapX = 0.0f;
            if (overlapX_left > 0 && overlapX_right < 0) { // Existe sobreposição em X
                if (std::abs(overlapX_left) < std::abs(overlapX_right)) {
                    minOverlapX = overlapX_left; // Colisão da esquerda para a direita
                } else {
                    minOverlapX = overlapX_right; // Colisão da direita para a esquerda
                }
            }

            float minOverlapY = 0.0f;
            if (overlapY_top > 0 && overlapY_bottom < 0) { // Existe sobreposição em Y
                if (std::abs(overlapY_top) < std::abs(overlapY_bottom)) {
                    minOverlapY = overlapY_top; // Colisão de cima para baixo
                } else {
                    minOverlapY = overlapY_bottom; // Colisão de baixo para cima
                }
            }

            // Lógica de Desambiguação de Eixo (aqui é o ponto crítico sem prevPos)
            // Se houve sobreposição em ambos os eixos, decida qual o "melhor" eixo para resolver
            if (minOverlapX != 0.0f && minOverlapY != 0.0f) {
                // Se a colisão horizontal é mais "rasa" (menor penetração)
                if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
                    MoveTo(X() - minOverlapX, Y()); // Ajusta apenas X
                } else {
                    MoveTo(X(), Y() - minOverlapY); // Ajusta apenas Y
                }
            }
            // Se a sobreposição foi apenas no eixo X
            else if (minOverlapX != 0.0f) {
                MoveTo(X() - minOverlapX, Y());
            }
            // Se a sobreposição foi apenas no eixo Y
            else if (minOverlapY != 0.0f) {
                MoveTo(X(), Y() - minOverlapY);
            }
        }
    }
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
