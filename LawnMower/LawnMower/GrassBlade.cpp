#include "LawnMower.h"
#include "GrassBlade.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

GrassBlade::GrassBlade(float x, float y)
    : windPhase((float)rand() / RAND_MAX * 2.0f * 3.1415926f)
{
    grassBlade = new Sprite("Resources/grass_blade.png");
    sombra = new Sprite("Resources/sombra.png");
    rotation = 0.0f; // Começa em 0 (reto)
    targetRotation = 0.0f; // A rotação para a qual estamos indo
    rotationSpeed = 2.0f; // Velocidade de rotação
    float initialWind = windAmplitude * sinf(windPhase);
    rotation = initialWind;
    targetRotation = initialWind;

    // imagem do grass é 61x61
    BBox(new Rect(-8, -8, 8, 8));
    MoveTo(x, y);

    type = GRASSBLADE;
}

// ---------------------------------------------------------------------------------

GrassBlade::~GrassBlade()
{
    delete grassBlade;
    delete sombra;
}

// ---------------------------------------------------------------------------------

void GrassBlade::Update()
{
    // 1) acumula o tempo
    timeAccumulator += gameTime;
    // 2) calcula o balanço de vento
    float windRot = windAmplitude
        * sinf(2.0f * 3.1415926f * windFreq * timeAccumulator + windPhase);

    // se não foi tocada, o vento é o alvo
    if (!touched)
        targetRotation = windRot;

    if (touched)
    {
        timeSinceCollision += gameTime;
        if (timeSinceCollision >= returnDelay)
        {
            targetRotation = 0.0f; // Volta para posição neutra
            touched = false;
        }
    }

    if (rotation < targetRotation)
    {
        rotation += rotationSpeed * gameTime;
        if (rotation > targetRotation)
            rotation = targetRotation;
    }
    else if (rotation > targetRotation)
    {
        rotation -= rotationSpeed * gameTime;
        if (rotation < targetRotation)
            rotation = targetRotation;
    }

    // após atualizar 'rotation'...
    if (markedForDeletion && hasBeenHit && rotation == targetRotation)
    {
        // A rotação chegou no alvo pela primeira vez  corta o mato
        Level1::scene->Delete();
        // opcionalmente, zere a flag pra não chamar de novo
        markedForDeletion = false;
    }
}

// ---------------------------------------------------------------------------------

void GrassBlade::OnCollision(Object* obj)
{
    if (obj->Type() == PLAYER && !hasBeenHit)
    {
        // Usa a posição do player para determinar a direção
        float dx = obj->X() - x;
        float dy = obj->Y() - y;

        // Calcula o ângulo do vetor (simples estimativa da direção do toque)
        float angle = atan2f(dy, dx);

        // Define uma rotação inclinada com base no ângulo
        targetRotation = sinf(angle) * 0.4f; // escala o valor final

        timeSinceCollision = 0.0f;
        touched = true;

        // Marca pra só processar a remoção após esta primeira rotação
        hasBeenHit = true;
        markedForDeletion = true;
    }
    if (obj->Type() == VILLAIN && !hasBeenHit)
    {
        // Usa a posição do player para determinar a direção
        float dx = obj->X() - x;
        float dy = obj->Y() - y;

        // Calcula o ângulo do vetor (simples estimativa da direção do toque)
        float angle = atan2f(dy, dx);

        // Define uma rotação inclinada com base no ângulo
        targetRotation = sinf(angle) * 0.4f; // escala o valor final

        timeSinceCollision = 0.0f;
        touched = true;
    }
}

// ---------------------------------------------------------------------------------

void GrassBlade::Draw()
{
    // 1) calcula o pivot (na base e centro horizontal):
    float pivotX = x;
    float pivotY = y;        // y é o ponto do “pé” do mato

    // 2) dimensões do sprite:
    float w = grassBlade->Width();
    float h = grassBlade->Height();

    // 3) deslocamento do sprite para que o pivot fique na base do sprite:
    //    queremos que o ponto (0,0) após a transformação fique na parte de baixo central do sprite
    float offsetX = -w * 0.5f;
    float offsetY = -h;
    
    // ponto local antes da rotação
    float localX = -w * 0.5f;
    float localY = -h;

    // aplica rotação em torno da origem local (0,0)
    float cosR = cosf(rotation);
    float sinR = sinf(rotation);
    float rotX = localX * cosR - localY * sinR;
    float rotY = localX * sinR + localY * cosR;

    // traslada para o mundo
    float finalX = pivotX + rotX;
    float finalY = pivotY + rotY;

    // então desenha seu sprite com âncora no topo-esquerdo em (finalX, finalY)
    grassBlade->Draw(finalX + 10, finalY + 15, Layer::UPPER, 1.2, rotation, { 0.7, 0.7, 1, 1 });
    sombra->Draw(x, y, Layer::MIDDLE, 0.3f);
}

// ---------------------------------------------------------------------------------
