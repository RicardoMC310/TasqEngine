#pragma once

#include <iostream>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "../Renderer/Renderer.hpp"

namespace Tasq
{
    class Texture
    {
        static SDL_Renderer* renderer;

    public:
        Texture(SDL_Renderer* renderer);
        
        static int saveTexture(lua_State *L);
        
        ~Texture();
    };

};