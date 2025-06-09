#pragma onde

#include <iostream>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>

namespace Tasq
{

    class Input
    {        
    public:
        Input();
        ~Input();

        static int isKeyDown(lua_State *L);

    };

};