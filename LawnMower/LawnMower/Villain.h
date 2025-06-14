#ifndef _LAWNMOWER_VILLAIN_H_
#define _LAWNMOWER_VILLAIN_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados possíveis para o jogador
enum VILLAINSTATE { VILLAIN_UP, VILLAIN_DOWN, VILLAIN_LEFT, VILLAIN_RIGHT };
enum VILLAINLIFE { VILLAIN1, VILLAIN2, VILLAIN3, VILLAIN4 };

// ---------------------------------------------------------------------------------

class Villain : public Object
{
private:
    Sprite * spriteL = nullptr;         // sprite do villain indo para esquerda
    Sprite * spriteR = nullptr;         // sprite do villain indo para direita
    Sprite * spriteU = nullptr;         // sprite do villain indo para cima
    Sprite * spriteD = nullptr;         // sprite do villain indo para baixo

    Sprite * spriteL2 = nullptr;         // sprite do villain indo para esquerda
    Sprite * spriteR2 = nullptr;         // sprite do villain indo para direita
    Sprite * spriteU2 = nullptr;         // sprite do villain indo para cima
    Sprite * spriteD2 = nullptr;         // sprite do villain indo para baixo

    Sprite * spriteL3 = nullptr;         // sprite do villain indo para esquerda
    Sprite * spriteR3 = nullptr;         // sprite do villain indo para direita
    Sprite * spriteU3 = nullptr;         // sprite do villain indo para cima
    Sprite * spriteD3 = nullptr;         // sprite do villain indo para baixo

    Sprite * spriteL4 = nullptr;         // sprite do villain indo para esquerda
    Sprite * spriteR4 = nullptr;         // sprite do villain indo para direita
    Sprite * spriteU4 = nullptr;         // sprite do villain indo para cima
    Sprite * spriteD4 = nullptr;         // sprite do villain indo para baixo

    Image * bullet = nullptr;            // imagem utilizada para gerar as sprites de bullets

    Player * player = nullptr;           // referência ao objeto player

    float bulletsCooldownMaxTimer = 2.0f;
    float bulletsCooldownTimer = bulletsCooldownMaxTimer;   // cooldown do knockback causado pelo villain
    
    int maxSpriteChangeCounter = 4;
    int spriteChangeCounter = 4;

    float bulletBurstCooldownMax = 0.2f;                            // Tempo máximo entre tiros dentro de um burst (ex: 0.1s, 0.2s)
    float bulletBurstCooldownTimer = 0.0f;        // Tempo restante para o próximo tiro dentro de um burst
    int bulletsToShootInBurst = 0;                                      // Quantas balas ainda faltam para atirar no burst atual
public:
    uint currState = 4u;           // estado atual do jogador
    uint nextState = 4u;           // próximo estado do jogador
    uint currSprite = 0u;

    Villain(Player* player);                           // construtor
    ~Villain();                                        // destrutor

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
