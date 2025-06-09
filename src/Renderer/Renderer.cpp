#include "../../include/Renderer/Renderer.hpp"

SDL_Renderer *Tasq::Renderer::renderer = nullptr;

Tasq::Renderer::Renderer()
{
    renderer = nullptr;
}

bool Tasq::Renderer::init(SDL_Window *window)
{

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        return false;
    }

    return true;
}

void Tasq::Renderer::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

SDL_Renderer *Tasq::Renderer::getRenderer() const
{
    return renderer;
}

int Tasq::Renderer::drawRect(lua_State *L)
{
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    double w = luaL_checknumber(L, 3);
    double h = luaL_checknumber(L, 4);

    SDL_Rect rect{(int)x, (int)y, (int)w, (int)h};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    return 0;
}

int Tasq::Renderer::drawTexture(lua_State *L)
{
    SDL_Texture* texture = static_cast<SDL_Texture*>(lua_touserdata(L, 1));

    double x = luaL_checknumber(L, 2);
    double y = luaL_checknumber(L, 3);
    double w = luaL_checknumber(L, 4);
    double h = luaL_checknumber(L, 5);

    SDL_Rect rect{(int)x, (int)y, (int)w, (int)h};

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    return 0;
}

Tasq::Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}