#pragma once

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace Tasq
{

    class Renderer
    {
        SDL_Renderer *renderer;  
        
        lua_State *L;

    public:
        Renderer();
        bool init(SDL_Window* window, lua_State *L);
        void render();
        SDL_Renderer* getRenderer() const;
        ~Renderer();
    };

};