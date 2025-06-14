#ifndef _LAWNMOWER_VILLAIN_H_
#define _LAWNMOWER_VILLAIN_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss�veis para o jogador
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

    Player * player = nullptr;           // refer�ncia ao objeto player

    float bulletsCooldownMaxTimer = 2.0f;
    float bulletsCooldownTimer = bulletsCooldownMaxTimer;   // cooldown do knockback causado pelo villain
    
    int maxSpriteChangeCounter = 4;
    int spriteChangeCounter = 4;

    float bulletBurstCooldownMax = 0.2f;                            // Tempo m�ximo entre tiros dentro de um burst (ex: 0.1s, 0.2s)
    float bulletBurstCooldownTimer = 0.0f;        // Tempo restante para o pr�ximo tiro dentro de um burst
    int bulletsToShootInBurst = 0;                                      // Quantas balas ainda faltam para atirar no burst atual
public:
    uint currState = 4u;           // estado atual do jogador
    uint nextState = 4u;           // pr�ximo estado do jogador
    uint currSprite = 0u;

    Villain(Player* player);                           // construtor
    ~Villain();                                        // destrutor

    void Stop();                        // p�ra jogador
    void Up();                          // muda dire��o para cima
    void Down();                        // muda dire��o para baixo
    void Left();                        // muda dire��o para esquerda
    void Right();                       // muda dire��o para direita

    void OnCollision(Object * obj);     // resolu��o da colis�o
    //void PivotCollision(Object * obj);  // revolve colis�o com piv�

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
