#include "../../include/Input/Input.hpp"

Tasq::Input::Input()
{
}

Tasq::Input::~Input()
{
}

int Tasq::Input::isKeyDown(lua_State *L)
{

    const char *key = luaL_checkstring(L, 1);

    const Uint8 *keyBoard = SDL_GetKeyboardState(NULL);

    SDL_Scancode scanCode = SDL_GetScancodeFromName(key);

    if (scanCode == SDL_SCANCODE_UNKNOWN)
    {
        std::cerr << "CPP: Tecla não existente!\n";
        lua_pushboolean(L, 0);
        return 1;
    }

    bool pressed = keyBoard[scanCode];

    lua_pushboolean(L, pressed);

    return 1;
}
