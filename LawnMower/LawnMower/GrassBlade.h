#ifndef _LAWNMOWER_GRASSBLADE_H_
#define _LAWNMOWER_GRASSBLADE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Timer.h"                      // interface de temporizadores

// ---------------------------------------------------------------------------------
// Constantes Globais

// ---------------------------------------------------------------------------------

class GrassBlade : public Object
{
private:
    Sprite * grassBlade = nullptr;
    Sprite * sombra = nullptr;
	float rotation = 0.0f;              // rotação do objeto
	float targetRotation = 0.0f;        // rotação alvo do objeto
	float rotationSpeed = 2.0f;         // velocidade de rotação do objeto
	uint direction = 0;              // direção do objeto (0 = direita, 1 = esquerda)
    float returnDelay = 0.5f;       // Tempo antes de voltar à posição original
    bool markedForDeletion = false;   // vai sinalizar que deve ser deletado
    bool hasBeenHit = false;          // garante que só delete na primeira rotação
    float timeSinceCollision = 0.0f;
    bool touched = false;
    float windPhase;
    float timeAccumulator = 0.0f;              // acumula o tempo de jogo
    static constexpr float windFreq = 0.7f;  // ciclos por segundo (ajuste baixo)
    static constexpr float windAmplitude = 0.1f; // amplitude suave (radianos)
    // substitua seu código de interpolações manuais por isso:
    static float Lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

public:

    GrassBlade(float, float);               // construtor
    ~GrassBlade();                          // destrutor

    void OnCollision(Object* obj);     // resolução da colisão
    //void PivotCollision(Object * obj);  // revolve colisão com pivô

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif
