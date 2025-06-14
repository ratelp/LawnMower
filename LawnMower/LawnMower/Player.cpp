#include "LawnMower.h"
#include "Player.h"
#include "Level1.h"
#include <algorithm> // Necessário para std::min e std::max
#include <cmath>
#include <sstream>

// ---------------------------------------------------------------------------------

Player::Player()
{
    spriteL = new Sprite("Resources/originalplayer1left.png");
    spriteR = new Sprite("Resources/originalplayer1right.png");
    spriteU = new Sprite("Resources/originalplayer1up.png");
    spriteD = new Sprite("Resources/originalplayer1down.png");

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
    // --- 1. Store previous frame's velocity ---
    float previousFrameVelX = velX;
    float previousFrameVelY = velY;

    static float slideTimer = 0.0f;

    // --- 2. Determine current frame's input-driven velocity ---
    velX = 0.0f; // Reset base velocity for this frame
    velY = 0.0f;

    bool currentInputDetected = false;

    if (window->KeyDown(VK_UP)) {
        Up(); // Assumes Up() sets velX=0, velY=-playerSpeedConstant
        currState = UP;
        currentInputDetected = true;
    }
    else if (window->KeyDown(VK_LEFT)) {
        Left(); // Assumes Left() sets velX=-playerSpeedConstant, velY=0
		currState = LEFT;
        currentInputDetected = true;
    }
    else if (window->KeyDown(VK_RIGHT)) {
        Right(); // Assumes Right() sets velX=playerSpeedConstant, velY=0
		currState = RIGHT;
        currentInputDetected = true;
    }
    else if (window->KeyDown(VK_DOWN)) {
        Down(); // Assumes Down() sets velX=0, velY=playerSpeedConstant
		currState = DOWN;
        currentInputDetected = true;
    }

    // --- 3. Manage Inertia Initiation ---
    // Variables for slide tuning
    const float MAX_SLIDE_DURATION = 0.6f; // Tune this: e.g., 0.2 seconds for a short slide
    const float SLIDING_INERTIA_INITIAL_MULTIPLIER = 0.9f; // Tune this: how strong the slide starts (e.g., 70% of previous speed)
    const float SLIDE_DECAY_RATE_FACTOR = 3.0f; // Tune this: higher value = faster slowdown of the slide.
    // This is a factor applied over the duration, not absolute speed.

// Check if the player's intended velocity changed or stopped
    bool velocityChanged = (velX != previousFrameVelX) || (velY != previousFrameVelY);

    if (velocityChanged) {
        // If a change occurred AND the player was actually moving before this change,
        // initiate a new slide with its full initial speed and reset the timer.
        if (previousFrameVelX != 0.0f || previousFrameVelY != 0.0f) {
            slideTimer = MAX_SLIDE_DURATION; // Reset the timer for a new slide
            // Set initial inertia based on previous velocity and desired initial strength
            inertiaX = previousFrameVelX * SLIDING_INERTIA_INITIAL_MULTIPLIER;
            inertiaY = previousFrameVelY * SLIDING_INERTIA_INITIAL_MULTIPLIER;
        }
        else {
            // If player wasn't moving, ensure no slide is active.
            inertiaX = 0.0f;
            inertiaY = 0.0f;
            slideTimer = 0.0f;
        }
    }

    // --- 4. Apply Decay to Inertia during the slide duration ---
    if (slideTimer > 0.0f) {
        slideTimer -= gameTime; // Countdown the timer

        // Apply a framerate-independent decay to the inertia values.
        // This makes the slide velocity decrease over its duration.
        // The decay amount is proportional to gameTime and the remaining strength of the slide.
        // We use a factor (SLIDE_DECAY_RATE_FACTOR) to control how quickly it slows down.

        float currentDecayAmount = SLIDE_DECAY_RATE_FACTOR * gameTime;
        // Cap the decay to prevent negative scaling if gameTime is very large
        if (currentDecayAmount > 1.0f) currentDecayAmount = 1.0f;

        // Apply decay
        inertiaX *= (1.0f - currentDecayAmount);
        inertiaY *= (1.0f - currentDecayAmount);

        // Ensure inertia doesn't flip sign or go past zero
        if ((previousFrameVelX > 0 && inertiaX < 0) || (previousFrameVelX < 0 && inertiaX > 0)) {
            inertiaX = 0.0f;
        }
        if ((previousFrameVelY > 0 && inertiaY < 0) || (previousFrameVelY < 0 && inertiaY > 0)) {
            inertiaY = 0.0f;
        }

        // If the timer just ran out, ensure inertia is exactly zero
        if (slideTimer <= 0.0f) {
            inertiaX = 0.0f;
            inertiaY = 0.0f;
        }
    }
    else {
        // If slide timer is not active, ensure inertia is zero.
        inertiaX = 0.0f;
        inertiaY = 0.0f;
    }


    // --- 5. Handle Knockback (framerate-independent decay) ---
    if (knockbackCooldownTimer > 0.0f) {
        knockbackCooldownTimer -= gameTime;

        if (knockbackCooldownTimer <= 0.0f) {
            knockbackSpeedX = 0.0f;
            knockbackSpeedY = 0.0f;
        }
        else {
            float knockbackDecayFactor = 2.0f; // Tune this
            float currentKnockbackDecay = knockbackDecayFactor * gameTime;
            if (currentKnockbackDecay > 1.0f) currentKnockbackDecay = 1.0f;

            knockbackSpeedX *= (1.0f - currentKnockbackDecay);
            knockbackSpeedY *= (1.0f - currentKnockbackDecay);
        }
    }

    // --- 6. Calculate Final Movement Velocity for this frame ---
    float finalSpeedX = velX; // Input-driven velocity
    float finalSpeedY = velY;

    finalSpeedX += knockbackSpeedX;
    finalSpeedY += knockbackSpeedY;

    // Add inertia only if the slide is currently active (slideTimer > 0)
    // and contributes to movement.
    finalSpeedX += inertiaX;
    finalSpeedY += inertiaY;


    // --- 7. Apply Translation ---
    Translate(finalSpeedX * gameTime, finalSpeedY * gameTime);
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{

    Rect* playerBBox = static_cast<Rect*>(this->BBox());

    if (obj->Type() == VILLAIN) {
        const float knockbackDistance = 1000.0f;

        // 1. Obter BBoxes
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
        life -= 1;

        if (life <= 0) {
            Level1::scene->Delete(this, MOVING);
            playerLife = DEADP;
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
