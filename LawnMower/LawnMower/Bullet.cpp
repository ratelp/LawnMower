#include "Bullet.h"
#include "Level1.h"
#include <cmath>

// ---------------------------------------------------------------------------------  

Bullet::Bullet(Image* image, Player* currentPlayer) 
{  
    sprite = new Sprite(image);
    speed = 250;

    // Define ponto inicial da bala
    float startX = x;
    float startY = y;

    // Cria BBox
    BBox(new Rect(-(sprite->Width() / 2.0f), -(sprite->Height() / 2.0f), (sprite->Width() / 2.0f), (sprite->Height() / 2.0f)));

    // Calcula para onde a bala deve ir (ponto final)
    Rect* playerBBox = static_cast<Rect*>(currentPlayer->BBox());
    whereToX = playerBBox->Left() + (playerBBox->Right() - playerBBox->Left()) / 2.0f;
    whereToY = playerBBox->Top() + (playerBBox->Bottom() - playerBBox->Top()) / 2.0f;

    // Velocidades vetoriais
    speedX = 0.0f;
    speedY = 0.0f;
}  

// ---------------------------------------------------------------------------------  

Bullet::~Bullet()
{  
    delete sprite;  
}  

// ---------------------------------------------------------------------------------  

void Bullet::Update()
{
    if (speedX == 0.0f && speedY == 0.0f) {
        // 1. Obter BBoxes
        Rect* bulletBBox = static_cast<Rect*>(this->BBox());

        // 2. Calcular o centro da bala
        float bulletOriginX = bulletBBox->Left() + (bulletBBox->Right() - bulletBBox->Left()) / 2.0f;
        float bulletOriginY = bulletBBox->Top() + (bulletBBox->Bottom() - bulletBBox->Top()) / 2.0f;

        // Calcular o vetor de direção (da bala para o alvo whereToX/Y)
        float dirX = whereToX - bulletOriginX;
        float dirY = whereToY - bulletOriginY;

        // Normalizar o vetor de direção
        float distance = std::sqrt(dirX * dirX + dirY * dirY);

        // Previne divisão por zero
        if (distance > 0.0001f) {
            float normalizedX = dirX / distance;
            float normalizedY = dirY / distance;

            // Define a velocidade vetorial da bala
            speedX = normalizedX * speed;
            speedY = normalizedY * speed;
        } else {
            // Se a bala for criada exatamente na posição do alvo, ela não se move
            speedX = 0.0f;
            speedY = 0.0f;
        }
    }

    Translate(speedX * gameTime, speedY * gameTime);

    if (x < -sprite->Width() || x > window->Width() + sprite->Width() || y < -sprite->Height() || y > window->Height() + sprite->Height())
        Level1::scene->Delete();
}  

// ---------------------------------------------------------------------------------
