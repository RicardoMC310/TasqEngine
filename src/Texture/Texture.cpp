#include "../../include/Texture/Texture.hpp"

SDL_Renderer *Tasq::Texture::renderer;

Tasq::Texture::Texture(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

int Tasq::Texture::saveTexture(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    const char *url = luaL_checkstring(L, 2);

    SDL_Surface *surface = IMG_Load(url);
    if (!surface)
    {
        std::cerr << "CPP: Erro IMG_Load falhou: " << IMG_GetError() << std::endl;
        lua_pushnil(L);
        return 1;
    }

    if (!renderer)
    {
        std::cerr << "CPP: Erro SDL_Renderer não inicializado!" << std::endl;
        SDL_FreeSurface(surface);
        lua_pushnil(L);
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cerr << "CPP: Erro SDL_CreateTextureFromSurface falhou: " << SDL_GetError() << std::endl;
        lua_pushnil(L);
        return 1;
    }

    lua_pushlightuserdata(L, texture);
    return 1;
}

Tasq::Texture::~Texture()
{
}