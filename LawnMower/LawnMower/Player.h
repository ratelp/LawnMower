#ifndef _LAWNMOWER_PLAYER_H_
#define _LAWNMOWER_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados possíveis para o jogador
enum PLAYERSTATE { STOPPED, UP, DOWN, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite * spriteL = nullptr;           // sprite do player indo para esquerda
    Sprite * spriteR = nullptr;           // sprite do player indo para direita
    Sprite * spriteU = nullptr;           // sprite do player indo para cima
    Sprite * spriteD = nullptr;           // sprite do player indo para baixo
    float velX = 0.0f;                    // velocidade horizontal do player
    float velY = 0.0f;                    // velocidade vertical do player
    float knockbackCooldownTimer = 0.0f;  // cooldown do knockback causado pelo villain
    float knockbackSpeedX = 0.0f;         // velocidade do knockback no eixo X
    float knockbackSpeedY = 0.0f;         // velocidade do knockback no eixo Y

public:
    uint currState = STOPPED;           // estado atual do jogador
    uint nextState = STOPPED;           // próximo estado do jogador

    Player();                           // construtor
    ~Player();                          // destrutor

    void Stop();                        // pára jogador
    void Up();                          // muda direção para cima
    void Down();                        // muda direção para baixo
    void Left();                        // muda direção para esquerda
    void Right();                       // muda direção para direita

    void OnCollision(Object * obj);     // resolução da colisão
    //void PivotCollision(Object * obj);  // revolve colisão com pivô

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
