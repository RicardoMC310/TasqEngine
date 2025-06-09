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
        

    public:

        static SDL_Renderer *renderer;
        Renderer();
        bool init(SDL_Window *window);
        void render();
        SDL_Renderer *getRenderer() const;
        ~Renderer();

        static int drawRect(lua_State *L);
        static int drawTexture(lua_State *L);
    };

};