#pragma once

#include <iostream>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Renderer/Renderer.hpp"

namespace Tasq
{
    struct Window;

    class Platform
    {

        SDL_Window* window;
        Renderer* renderer;

        lua_State *L;

        bool isRunning;

    public:
        Platform();
        ~Platform() = default;

        // Funções internas da engine
        bool openFile(const char *path);
        const char *getError();
        void registerAllFuncs();
        void run();
        const char* getButtonName(Uint8 button);

        // Funções que vão para a linguagem lua
        static int createWindow(lua_State *L);
        static int init(lua_State *L);
        static int destroyWindow(lua_State *L);
    };

};
