#include "LawnMower.h"
#include "Player.h"
#include "Level1.h"
#include <algorithm> // Necessário para std::min e std::max
#include <cmath>
#include <sstream>

// ---------------------------------------------------------------------------------

Player::Player()
{
    spriteL = new Sprite("Resources/player1left.png");
    spriteR = new Sprite("Resources/player1right.png");
    spriteU = new Sprite("Resources/player1up.png");
    spriteD = new Sprite("Resources/player1down.png");

    // imagem do player up é 84x92
    BBox(new Rect(- (spriteL->Width() / 2.0f - 10), - (spriteL->Width() / 2.0f - 8), (spriteL->Width() / 2.0f - 10), (spriteL->Width() / 2.0f - 8)));
    
    MoveTo(480.0f, 466.0f);
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
    velY = -200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
    velX = 0;
    velY = 200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
    velX = -200.0f;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
    velX = 200.0f;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    velX = 0.0f;
    velY = 0.0f;

    if (window->KeyDown(VK_UP)) {
        Up();
        //Translate(velX, velY);
        currState = UP;
    }
    if (window->KeyDown(VK_LEFT)) {
        Left();
        //Translate(velX, velY);
        currState = LEFT;
    }
    if (window->KeyDown(VK_RIGHT)) {
        Right();
        //Translate(velX, velY);
        currState = RIGHT;
    }
    if (window->KeyDown(VK_DOWN)) {
        Down();
        //Translate(velX, velY);
        currState = DOWN;
    }

    if (knockbackCooldownTimer > 0.0f) {
        knockbackCooldownTimer -= gameTime;

        if (knockbackCooldownTimer <= 0.0f) {
            knockbackSpeedX = 0.0f;
            knockbackSpeedY = 0.0f;
        } else {
            knockbackSpeedX *= (1.0f - (0.5f * gameTime));
            knockbackSpeedY *= (1.0f - (0.5f * gameTime));
        }
    }

    float finalSpeedX = velX;
    float finalSpeedY = velY;

    finalSpeedX += knockbackSpeedX;
    finalSpeedY += knockbackSpeedY;

    Translate(finalSpeedX * gameTime, finalSpeedY * gameTime);
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == VILLAIN) {
        const float knockbackDistance = 1000.0f;

        // 1. Obter BBoxes
        Rect* playerBBox = static_cast<Rect*>(this->BBox());
        Rect* villainBBox = static_cast<Rect*>(obj->BBox());

        // 2. Calcular o centro do jogador e do vilão
        float playerCenterX = playerBBox->Left() + (playerBBox->Right() - playerBBox->Left()) / 2.0f;
        float playerCenterY = playerBBox->Top() + (playerBBox->Bottom() - playerBBox->Top()) / 2.0f;

        float villainCenterX = villainBBox->Left() + (villainBBox->Right() - villainBBox->Left()) / 2.0f;
        float villainCenterY = villainBBox->Top() + (villainBBox->Bottom() - villainBBox->Top()) / 2.0f;

        // 3. Calcular o vetor de direção (do vilão para o jogador)
        float dirX = playerCenterX - villainCenterX;
        float dirY = playerCenterY - villainCenterY;

        // 4. Normalizar o vetor de direção
        float distance = sqrt(dirX * dirX + dirY * dirY);

        float normalizedX = 0.0f;
        float normalizedY = 0.0f;

        // Previne divisão por zero
        if (distance > 0.0001f) {
            normalizedX = dirX / distance;
            normalizedY = dirY / distance;
        }

        // 5. Aplicar o knockback
        if (knockbackCooldownTimer <= 0.0f) {
            // Define a velocidade inicial do knockback
            knockbackSpeedX = normalizedX * knockbackDistance;
            knockbackSpeedY = normalizedY * knockbackDistance;

            knockbackCooldownTimer = 0.2f;
        }
    }
    
    if (obj->Type() == WALL) {
        // 1. Obter as Bounding Boxes (BBox) do jogador e da parede
        // Usamos static_cast porque sabemos que a geometria é um retângulo (Rect)
        Rect* playerBBox = static_cast<Rect*>(this->BBox());
        Rect* wallBBox = static_cast<Rect*>(obj->BBox());

        // 2. Calcular a sobreposição (penetração) nos eixos X e Y
        float overlapX = min(playerBBox->Right(), wallBBox->Right()) - max(playerBBox->Left(), wallBBox->Left());
        float overlapY = min(playerBBox->Bottom(), wallBBox->Bottom()) - max(playerBBox->Top(), wallBBox->Top());

        // 3. Determinar o lado da colisão e resolver com base na menor penetração
        if (overlapX < overlapY)
        {
            // Colisão horizontal é menor

            // Se o centro do jogador está à esquerda do centro da parede
            if (playerBBox->X() + (playerBBox->Right() - playerBBox->Left()) / 2.0f < wallBBox->X() + (wallBBox->Right() - wallBBox->Left()) / 2.0f) {
                // Colisão pela esquerda, empurra para a esquerda
                Translate(-overlapX, 0);
            }
            else {
                // Colisão pela direita, empurra para a direita
                Translate(overlapX, 0);
            }
            velX = 0;
        }
        else
        {
            // Colisão vertical é menor ou igual

            // Se o centro do jogador está acima do centro da parede (considerando Y crescente para baixo)
            if (playerBBox->Y() + (playerBBox->Bottom() - playerBBox->Top()) / 2.0f < wallBBox->Y() + (wallBBox->Bottom() - wallBBox->Top()) / 2.0f) {
                // Colisão por cima, empurra para cima
                Translate(0, -overlapY);
            }
            else {
                // Colisão por baixo, empurra para baixo
                Translate(0, overlapY);
            }
            velY = 0;
        }  
    }

    if (obj->Type() == BULLET) {
        Level1::scene->Delete(obj, MOVING);
        life -= maxLife / 3.0f;
        
        std::stringstream text;
        text << "Life: " << life << '\n';
        OutputDebugString(text.str().c_str());
        text.str("");

        //if (life <= 0) Level1::scene->Delete();
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
