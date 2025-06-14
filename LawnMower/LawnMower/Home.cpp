#include "Engine.h"
#include "Home.h"
#include "Level1.h"


void Home::Init()
{
    background = new Sprite("Resources/home_background_temp.jpg");
}

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_RETURN))
        Engine::Next<Level1>();
}

void Home::Draw()
{
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

void Home::Finalize()
{
    delete background;
}
