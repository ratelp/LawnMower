#ifndef _LAWNMOWER_PLAYER_H_
#define _LAWNMOWER_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss�veis para o jogador
enum PLAYERSTATE { STOPPED, UP, DOWN, LEFT, RIGHT };
enum PLAYERLIFE { DEADP, ALIVEP };

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
	float inertiaX = 0.0f;               // in�rcia horizontal do player
	float inertiaY = 0.0f;               // in�rcia vertical do player
    float knockbackCooldownTimer = 0.0f;  // cooldown do knockback causado pelo villain
    float knockbackSpeedX = 0.0f;         // velocidade do knockback no eixo X
    float knockbackSpeedY = 0.0f;         // velocidade do knockback no eixo Y
    
    const int maxLife = 4;

    
public:
    int life = maxLife;                   // valor de vida do player
    uint currState = STOPPED;           // estado atual do jogador
    uint nextState = STOPPED;           // pr�ximo estado do jogador
    uint playerLife = ALIVEP;

    Player();                           // construtor
    ~Player();                          // destrutor

    void Stop();                        // p�ra jogador
    void Up();                          // muda dire��o para cima
    void Down();                        // muda dire��o para baixo
    void Left();                        // muda dire��o para esquerda
    void Right();                       // muda dire��o para direita

    int MaxLife();
    int Life();
    void Life(int life);

    void OnCollision(Object * obj);     // resolu��o da colis�o
    //void PivotCollision(Object * obj);  // revolve colis�o com piv�

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline int Player::MaxLife()
{ return maxLife; }

inline int Player::Life()
{ return life; }

inline void Player::Life(int life)
{ this->life = life; }

#endif
