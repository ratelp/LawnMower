#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Player.h"
#include "Villain.h"
#include "GrassBlade.h"
#include "Grass.h"
#include "Wall.h"
#include "LifeIndicator.h"
#include "ScoreStruct.h"
#include "Score.h"
#include <fstream>
#include <sstream>
#include "LawnMower.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene * Level1::scene = nullptr;

bool Level1::playerDead = false;
bool Level1::villainDead = false;
bool Level1::grassCut = false;

// ------------------------------------------------------------------------------

void Level1::Init()
{

	// cria gerenciador de cena
	scene = new Scene();

	// cria background
	background = new Sprite("Resources/background.png");

	// cria jogador
	player = new Player();
	scene->Add(player, MOVING);
    LawnMower::audio->Play(CAR_NOISE);
    carNoiseTimer.Start();

    
    Grass* grass;
    GrassBlade* grassBlade;

    const int BLOCK_LOGICAL = 61;     // usado no MoveTo / colisão
    const int BLOCKS_X = 13;
    const int BLOCKS_Y = 6;     // 5 linhas + aquela “fileira extra” em Y
    float fieldW = BLOCKS_X * BLOCK_LOGICAL;
    float fieldH = BLOCKS_Y * BLOCK_LOGICAL;
    const int SPRITE_SIZE = 67;   // tamanho real do sprite de grama
    const int BLADE_SIZE = 16;   // tamanho de cada lâmina
    // quantas lâminas em X/Y para não deixar gap?
    int cols = (int)std::ceil(SPRITE_SIZE / (float)BLADE_SIZE); // ceil(67/16) = 5
    int rows = (int)std::ceil(SPRITE_SIZE / (float)BLADE_SIZE); // idem = 5

    // agora cada “célula” tem:
    float cellW = SPRITE_SIZE / (float)cols; // ? 13.4px
    float cellH = SPRITE_SIZE / (float)rows; // ? 13.4px

    float startOffset = SPRITE_SIZE / 2.0f;    // pra tirar do centro do bloco e ir pro canto
    float left_x = window->CenterX() - 367;
    float top_y = window->CenterY() - 179;

    // --- para cada bloco de grama: ---
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 5; j++) {
            float centerX = left_x + i * BLOCK_LOGICAL;
            float centerY = top_y + j * BLOCK_LOGICAL;
            scene->Add(new Grass(centerX, centerY), STATIC);

            // canto superior-esquerdo do sprite
            float startX = centerX - startOffset;
            float startY = centerY - startOffset;

            // distribui exatamente cols×rows lâminas:
            for (int y = 0; y < rows; y++) {
                for (int x = 0; x < cols; x++) {
                    float bladeX = startX + cellW * (x + 0.5f);
                    float bladeY = startY + cellH * (y + 0.5f);
                    scene->Add(new GrassBlade(bladeX, bladeY), STATIC);
                }
            }
        }
    }

    // --- fileira extra 1×7 ---
    for (int i = 3; i <= 9; i++) {
        float x = left_x + i * BLOCK_LOGICAL;
        float y = top_y + 5 * BLOCK_LOGICAL;
        scene->Add(new Grass(x, y), STATIC);
    }

    Wall* wall = new Wall(82,30, 0, 0, 794, 30);
    scene->Add(wall, STATIC);

    wall = new Wall(54, 61, 0, 0, 30, 304);
    scene->Add(wall, STATIC);
    wall = new Wall(874, 61, 0, 0, 30, 304);
    scene->Add(wall, STATIC);

    wall = new Wall(82, 365, 0, 0, 182, 55);
    scene->Add(wall, STATIC);
    wall = new Wall(691, 365, 0, 0, 182, 55);
    scene->Add(wall, STATIC);

    wall = new Wall(265, 425, 0, 0, 147, 76);
    scene->Add(wall, STATIC);
    wall = new Wall(547, 425, 0, 0, 144, 76);
    scene->Add(wall, STATIC);

    wall = new Wall(412, 510, 0, 0, 135, 50);
    scene->Add(wall, STATIC);

    // cria vilão
    Villain* villain = new Villain(player);
    scene->Add(villain, MOVING);

    lifeIndicator = new LifeIndicator(player);
	scene->Add(lifeIndicator, STATIC);

    scoreTimer.Start();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	delete background;
	delete scene;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    bool jumpScore = false; // verificar se está sendo passado direto pro score
    bool jumpHome= false; // verificar se está sendo passado direto pra home
    bool playerStateTemp = Level1::playerDead; // Para identificar se deve ou n fazer a verificação nas gramas
    bool villainStateTemp = Level1::villainDead;

    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
    {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE))
    {
        jumpHome= true;
        // volta para a tela de abertura
        LawnMower::audio->Stop(CAR_NOISE);
        LawnMower::NextLevel<Home>();
    } else if (window->KeyPress('N'))
    {
        ScoreStruct score{ playerDead, scoreTimer.Elapsed() };

        playerDead = false;
        villainDead = false;
        grassCut = false;

        // passa manualmente para o próximo nível
        jumpScore = true;
        LawnMower::audio->Stop(CAR_NOISE);
        LawnMower::NextLevel<Score>();
    } else if (playerDead || villainDead) {
        ScoreStruct score{ playerDead, scoreTimer.Elapsed() };

        playerDead = false;
        villainDead = false;
        grassCut = false;

        std::ofstream fout;
        fout.open("Resources/level1_score.dat", std::ios_base::out | std::ios_base::binary);
        fout.write((char*)&score, sizeof(ScoreStruct));
        fout.close();

        LawnMower::audio->Stop(CAR_NOISE);
        LawnMower::NextLevel<Score>();
    }
    else if (window->KeyPress('G')) {
        // Retira todas as gramas de uma vez

        scene->Begin();

        Object* obj;
        while ((obj = scene->Next()) != nullptr) {
            if (GrassBlade* grassBlade = dynamic_cast<GrassBlade*>(obj)) { // Verifica se o objeto é do tipo GrassBlade
                scene->Delete(obj, STATIC);
            }
        }
    }else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
    }

    if (!playerStateTemp && !villainStateTemp && !jumpScore && !jumpHome) allGrassCut();

    if (carNoiseTimer.Elapsed() > 16.0f) {
        carNoiseTimer.Reset();
        LawnMower::audio->Play(CAR_NOISE);
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

bool Level1::allGrassCut()
{
    //if (grassCut) return false;
    //return grassCut = true;

	scene->Begin();

    Object* obj;
    while ((obj = scene->Next()) != nullptr) {
        if (GrassBlade* grassBlade = dynamic_cast<GrassBlade*>(obj)) { // Verifica se o objeto é do tipo GrassBlade
            return false;
        }
    }

    return grassCut = true;
}
