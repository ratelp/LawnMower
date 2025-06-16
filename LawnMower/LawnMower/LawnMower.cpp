#include "Engine.h"
#include "resource.h"
#include "Home.h"
#include "LawnMower.h"


Game* LawnMower::level = nullptr;
Audio* LawnMower::audio = nullptr;

void LawnMower::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(VILLAIN_SPRITE_CHANGE, "Resources/villain_sprite_change_audio.wav");
    audio->Add(SHOT1, "Resources/shot1_audio.wav");
    audio->Add(SHOT2, "Resources/shot2_audio.wav");
    audio->Add(KNOCKBACK, "Resources/knockback_audio.wav");
    audio->Add(HIT, "Resources/car_hit_audio.wav");
    audio->Add(CAR_NOISE, "Resources/car_noise_audio.wav");
    audio->Add(GAME_OVER, "Resources/game_over_2_audio.wav");
    audio->Add(WINNER, "Resources/winner_audio.wav");

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void LawnMower::Update()
{

    // atualiza nível
    level->Update();
}

// ------------------------------------------------------------------------------

void LawnMower::Draw()
{
    // desenha nível
    level->Draw();
}

// ------------------------------------------------------------------------------

void LawnMower::Finalize()
{
    level->Finalize();
    delete audio;
    delete level;
}





// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(72, 72, 72);
    engine->window->Title("LawnMower");
    engine->window->Icon(IDI_ICON1);
    engine->window->Cursor(IDC_CURSOR2);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new LawnMower());

    // destrói engine e jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------
