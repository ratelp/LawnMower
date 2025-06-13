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

    Image * bullet = nullptr;

    Player * player = nullptr;

public:
    uint currState = 4u;           // estado atual do jogador
    uint nextState = 4u;           // próximo estado do jogador

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
