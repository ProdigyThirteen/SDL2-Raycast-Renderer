#pragma once

#include "../Templates/Singleton.h"
#include <map>
#include <memory>

#include "Renderer.h"
#include "RaycastRenderer.h"

class RenderInstanceManager final : public Singleton<RenderInstanceManager>
{
private:
    /// @brief Map of renderer ids to renderer instances
    std::map<const char*, std::unique_ptr<GameRenderer>> _renderers;

public:
    RenderInstanceManager(token);
    ~RenderInstanceManager();

    /// @brief Creates a new renderer with the given id
    /// @param id
    /// @return GameRenderer*
    GameRenderer* AddRenderer(const char* id);

    /// @brief Creates a new raycast renderer with the given id
    /// @param id
    /// @return RaycastRenderer*
    RaycastRenderer* AddRaycastRenderer(const char* id);

    /// @brief Removes the renderer with the given id
    /// @param id
    void RemoveRenderer(const char* id);

    /// @brief Removes all renderers
    void ClearRenderers();

    /// @brief Returns the renderer with the given id
    /// @param id
    /// @return GameRenderer*
    GameRenderer* GetRenderer(const char* id);
};