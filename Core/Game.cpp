#include "Game.h"
#include <iostream> // std::cout, std::endl
#include <SDL2/SDL.h> // SDL_Init, SDL_Quit
#include "../Rendering/GameWindow.h"
#include "../Rendering/RenderInstanceManager.h"
#include "InputManager.h"
#include "../Level/LevelManager.h"
#include "../Level/LevelFactory.h"
#include "../Globals/DeltaTime.h"

Game::Game(token)
{
    std::cout << "Game instance created" << std::endl;
}

Game::~Game()
{
    std::cout << "Game instance destroyed" << std::endl;
}

bool Game::Init()
{
    bool ret = 0;

    ret = SDL_Init(SDL_INIT_EVERYTHING);
    if (ret != 0)
    {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    ret = GameWindow::instance().Init();
    if (!ret)
    {
        std::cout << "GameWindow::Init failed" << std::endl;
        return false;
    }

    //if (!RenderInstanceManager::instance().AddRaycastRenderer())
    if (!RenderInstanceManager::instance().AddRaycastRenderer("main"))
    {
        std::cout << "GameRenderer::Init failed" << std::endl;
        return false;
    }

    RenderInstanceManager::instance().GetRenderer("main")->Init();

    ret = InputManager::instance().Init();
    if (!ret)
    {
        std::cout << "InputManager::Init failed" << std::endl;
        return false;
    }

    LevelManager::instance().LoadLevel(LevelFactory::instance().CreateLevel());

    LevelManager::instance().GetLevel()->GetPlayer()->Init();

    _running = true;
    return true;
}

void Game::Update()
{
    DeltaTime::UpdateDeltaTime();

    // SDL Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                // Quit game on esc
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    _running = false;
                }
                break;
            case SDL_QUIT:
                _running = false;
                break;

            default:
                break;
        }
    }

    // Update level
    LevelManager::instance().UpdateLevel();

    // Updates input state and performs any bound callbacks
    InputManager::instance().Update();

    RenderInstanceManager::instance().GetRenderer(0)->DrawFrame();
    RenderInstanceManager::instance().GetRenderer(0)->Present();

    // Calculate average fps over past 10 seconds
    _frameCount++;
    _frameTime += DeltaTime::GetDeltaTime();
    if (_frameTime >= 10.f)
    {
        std::cout << "Average FPS: " << _frameCount / _frameTime << std::endl;
        _frameCount = 0;
        _frameTime = 0.f;
    }
}