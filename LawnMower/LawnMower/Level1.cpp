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
	Player* player = new Player();
	scene->Add(player, MOVING);

    // cria vilão
    Villain* villain = new Villain();
    scene->Add(villain, STATIC);

    // cria gramas
    Grass* grass;
    /*for (int i = 365; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 179);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -368; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 179);
        scene->Add(grass, STATIC);
    }
    for (int i = 365; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 118);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -368; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 118);
        scene->Add(grass, STATIC);
    }
    for (int i = 365; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 57);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -368; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() - 57);
        scene->Add(grass, STATIC);
    }
    for (int i = 365; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 4);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -368; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 4);
        scene->Add(grass, STATIC);
    }
    for (int i = 365; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 65);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -368; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 65);
        scene->Add(grass, STATIC);
    }*/
    /*for (int i = 182; i >= -1; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 126);
        scene->Add(grass, STATIC);
    }
    for (int i = -1; i > -185; i -= 61) {
        grass = new Grass(window->CenterX() + i, window->CenterY() + 126);
        scene->Add(grass, STATIC);
    }*/

    Wall* wall = new Wall(82, 52, 0, 0, 794, 8);
    scene->Add(wall, STATIC);

    wall = new Wall(74, 61, 0, 0, 8, 304);
    scene->Add(wall, STATIC);
    wall = new Wall(874, 61, 0, 0, 8, 304);
    scene->Add(wall, STATIC);

    wall = new Wall(82, 365, 0, 0, 182, 55);
    scene->Add(wall, STATIC);
    wall = new Wall(691, 365, 0, 0, 182, 55);
    scene->Add(wall, STATIC);

    wall = new Wall(265, 420, 0, 0, 147, 76);
    scene->Add(wall, STATIC);
    wall = new Wall(547, 420, 0, 0, 144, 76);
    scene->Add(wall, STATIC);

    wall = new Wall(412, 496, 0, 0, 135, 8);
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
    } else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
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
