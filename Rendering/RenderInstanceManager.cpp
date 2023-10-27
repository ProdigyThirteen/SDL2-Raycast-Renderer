#include "RenderInstanceManager.h"

#include <iostream> // std::cout, std::endl
#include "GameWindow.h" // GameWindow::instance
#include <SDL2/SDL.h> // SDL_Renderer, SDL_CreateRenderer, SDL_DestroyRenderer

#include "Renderer.h" // GameRenderer
#include "RaycastRenderer.h" // RaycastRenderer

RenderInstanceManager::RenderInstanceManager(token)
{}

RenderInstanceManager::~RenderInstanceManager()
{
    std::cout << "Clearing renderers" << std::endl;
    ClearRenderers();
}

GameRenderer* RenderInstanceManager::AddRenderer(const char* id)
{
    if (_renderers.find(id) == _renderers.end())
    {
        _renderers[id] = std::unique_ptr<GameRenderer>(new GameRenderer(GameWindow::instance().GetWindow(), id));
        std::cout << "Renderer created" << std::endl;
    }

    return _renderers.at(id).get();
}

RaycastRenderer* RenderInstanceManager::AddRaycastRenderer(const char* id)
{
    if (_renderers.find(id) == _renderers.end())
    {
        _renderers[id] = std::unique_ptr<RaycastRenderer>(new RaycastRenderer(GameWindow::instance().GetWindow(), id));
        std::cout << "Renderer " << id << " created" << std::endl;
    }

    return static_cast<RaycastRenderer*>(_renderers.at(id).get());
}

void RenderInstanceManager::RemoveRenderer(const char* id)
{
    if (_renderers.find(id) != _renderers.end())
    {
        _renderers.erase(id);
        std::cout << "Renderer " << id << " destroyed" << std::endl;
    }
}

void RenderInstanceManager::ClearRenderers()
{
    _renderers.clear();
    std::cout << "Destroyed all renderers" << std::endl;
}

GameRenderer* RenderInstanceManager::GetRenderer(const char* id)
{
    //DAN
    GameRenderer* renderer = &*_renderers[id].get();
    //DAN
    if (_renderers.find(id) != _renderers.end())
    {
        return _renderers[id].get();
    }
    std::cout << "Renderer not found" << std::endl;
    return nullptr;
}