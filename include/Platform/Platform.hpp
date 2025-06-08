#pragma once

#include <iostream>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Tasq
{
    class Platform
    {
        enum MouseButton {
            PRESSED, RELEASED
        };

        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static SDL_Event event;

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
        void loadEnumMouseButtonToLua();
        const char* getButtonName(Uint8 button);

        // Funções que vão para a linguagem lua
        static int createWindow(lua_State *L);
        static int init(lua_State *L);
        static int destroyWindow(lua_State *L);
    };

};
