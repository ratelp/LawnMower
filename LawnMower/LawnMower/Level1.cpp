#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Player.h"
#include "Villain.h"
#include "Grass.h"
#include "Wall.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene * Level1::scene = nullptr;

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

    // cria gramas
	int GRASS_SIZE = 61;
    Grass* grass;
	int left_x = (int) window->CenterX() - 367;
	int top_y = (int) window->CenterY() - 179;
    
    // quadrado de 13x5 gramas
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 5; j++) {
            grass = new Grass((float) left_x + (i * GRASS_SIZE), (float) top_y + (j * GRASS_SIZE));
            scene->Add(grass, STATIC);
        }
	}
    // quadrado de 1x7 gramas
    for (int i = 3; i <= 9; i++) {
        grass = new Grass((float) left_x + (i * GRASS_SIZE), (float) top_y + (5 * GRASS_SIZE));
        scene->Add(grass, STATIC);
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
    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
    {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress(VK_ESCAPE))
    {
        // volta para a tela de abertura
        Engine::Next<Home>();
    } else if (window->KeyPress('N'))
    {
        // passa manualmente para o próximo nível
        //Engine::Next<Level2>();
    }
    else if (window->KeyPress('G')) {

        // Retira todas as gramas de uma vez

        scene->Begin();

        Object* obj;
        while ((obj = scene->Next()) != nullptr) {
            if (Grass* grass = dynamic_cast<Grass*>(obj)) { // Verifica se o objeto é do tipo Grass
                if (grass->state == ALIVE) { // Se alguma grama não foi cortada
                    grass->state = DEAD;
                    obj->DeleteBBox();
                }
            }
        }

    }else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
    }

    if (allGrassCut())
    {
        // cria vilão
        Villain* villain = new Villain(player);
        scene->Add(villain, STATIC);
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
    if (grassCut) return false;

	Scene* scene = Level1::scene; // Inicia a iteração sobre os objetos da cena
    scene->Begin();

    Object* obj;
    while ((obj = scene->Next()) != nullptr) {
        if (Grass* grass = dynamic_cast<Grass*>(obj)) { // Verifica se o objeto é do tipo Grass
            if (grass->state == ALIVE or grass->state == CUTTED) { // Se alguma grama não foi cortada
                return false; // Retorna falso
			}
        }
    }

    return grassCut = true;
}
