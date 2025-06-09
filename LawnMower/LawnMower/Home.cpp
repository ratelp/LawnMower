#include "Engine.h"
#include "Home.h"
#include "Level1.h"


void Home::Init()
{
    background = new Sprite("Resources/home_background_temp.jpg");

    /*villain1 = new Sprite("Resources/villain1.png");
    villain2 = new Sprite("Resources/villain2.png");
    villain3 = new Sprite("Resources/villain3.png");
    villain4 = new Sprite("Resources/villain4.png");
    bullet = new Sprite("Resources/villainBullets.png");
    player1 = new Sprite("Resources/player1.png");
    player2 = new Sprite("Resources/player2.png");
    player3 = new Sprite("Resources/player3.png");
    grass = new Sprite("Resources/grass.png");
    noGrass = new Sprite("Resources/noGrass.png");*/
}

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyDown(VK_RETURN))
        Engine::Next<Level1>();
}

void Home::Draw()
{
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    /*villain1->Draw(window->CenterX() - 300, window->CenterY(), Layer::FRONT);

    villain2->Draw(window->CenterX() - 150, window->CenterY(), Layer::FRONT);
    villain3->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
    villain4->Draw(window->CenterX() + 150, window->CenterY(), Layer::FRONT);
    bullet->Draw(window->CenterX() + 300, window->CenterY(), Layer::FRONT);

    player1->Draw(window->CenterX() - 150, window->CenterY() +150, Layer::FRONT);
    player2->Draw(window->CenterX(), window->CenterY() + 150, Layer::FRONT);
    player3->Draw(window->CenterX() + 150, window->CenterY() + 150, Layer::FRONT);*/

    /*for (int i = 365; i >= -1 ; i = i-61)
        grass->Draw(window->CenterX() + i, window->CenterY() - 179, Layer::FRONT);
    for (int i = -1; i > -368; i = i - 61)
        grass->Draw(window->CenterX() + i, window->CenterY() - 179, Layer::FRONT);
    for (int i = 365; i >= -1; i = i - 61)
        noGrass->Draw(window->CenterX() + i, window->CenterY() - 118, Layer::FRONT);
    for (int i = -1; i > -368; i = i - 61)
        noGrass->Draw(window->CenterX() + i, window->CenterY() - 118, Layer::FRONT);*/
}

void Home::Finalize()
{
    delete background;
}
