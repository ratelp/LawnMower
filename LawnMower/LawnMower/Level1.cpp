#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Player.h"
#include "Villain.h"

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
        //scene->CollisionDetection();
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
