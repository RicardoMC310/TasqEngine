#include "../../include/Platform/Platform.hpp"

struct Tasq::Window
{
    SDL_Window *window;
    Renderer renderer;
};

Tasq::Platform::Platform()
{
    std::cout << "CPP: Iniciando plataforma..." << '\n';
    L = luaL_newstate();
    luaL_openlibs(L);

    isRunning = true;
}

const char *Tasq::Platform::getButtonName(Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return "Left";
    case SDL_BUTTON_MIDDLE:
        return "Middle";
    case SDL_BUTTON_RIGHT:
        return "Right";
    case SDL_BUTTON_X1:
        return "X1";
    case SDL_BUTTON_X2:
        return "X2";
    default:
        return "unknown";
    }
}

bool Tasq::Platform::openFile(const char *path)
{
    std::cout << "CPP: Lendo arquivo..." << '\n';

    if (luaL_dofile(L, path) != LUA_OK)
    {
        return false;
    }

    return true;
}

const char *Tasq::Platform::getError()
{
    return lua_tostring(L, -1);
}

void Tasq::Platform::registerAllFuncs()
{
    struct LuaFunc
    {
        const char *name;
        lua_CFunction func;
    };

    LuaFunc funcs[] = {
        {"init", Platform::init},
        {"createWindow", Platform::createWindow},
        {"destroyWindow", Platform::destroyWindow},
    };

    for (const auto &f : funcs)
    {
        lua_register(L, f.name, f.func);
    }
}

void Tasq::Platform::run()
{
    lua_getglobal(L, "start");

    if (!lua_isfunction(L, -1))
    {
        std::cerr << "CPP: Função start() não definida.\n";
        lua_pop(L, 1);
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != LUA_OK)
    {
        std::cerr << "CPP: Erro ao executar o start()\n"
                  << getError();
        return;
    }

    SDL_Event event;

    Uint32 lastTime = SDL_GetTicks();
    while (isRunning)
    {

        Uint32 currentTime = SDL_GetTicks();
        double deltaTime = ((double)currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                lua_getglobal(L, "cleanup");

                if (!lua_isfunction(L, -1))
                {
                    std::cerr << "CPP: Função cleanup() não definida.\n";
                    lua_pop(L, 1);
                    return;
                }

                if (lua_pcall(L, 0, 0, 0) != LUA_OK)
                {
                    std::cerr << "CPP: Erro ao executar o cleanup()\n"
                              << getError();
                    return;
                }

                isRunning = false;

                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:

                lua_getglobal(L, "onKeyEvent");

                if (lua_isfunction(L, -1))
                {
                    const char *key = SDL_GetKeyName(event.key.keysym.sym);
                    const char *action = (event.type == SDL_KEYDOWN) ? "pressed" : "released";
                    lua_pushstring(L, key);
                    lua_pushstring(L, action);

                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onKeyEvent(key, action)\n"
                                  << getError() << '\n';
                        lua_pop(L, 1);
                    }
                }
                else
                {
                    lua_pop(L, 1);
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:

                lua_getglobal(L, "onMouseButton");

                if (lua_isfunction(L, -1))
                {
                    const char *action = (event.type == SDL_MOUSEBUTTONDOWN) ? "pressed" : "released";

                    const char *button = getButtonName(event.button.button);
                    int x = event.button.x;
                    int y = event.button.y;

                    lua_pushstring(L, button);
                    lua_pushstring(L, action);
                    lua_pushinteger(L, x);
                    lua_pushinteger(L, y);

                    if (lua_pcall(L, 4, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onMouseButton(button, action, x, y)\n"
                                  << getError();
                        lua_pop(L, 1);
                    }
                }
                else
                {
                    lua_pop(L, 1);
                }

                break;

            case SDL_MOUSEMOTION:

                lua_getglobal(L, "onMouseMotion");

                if (lua_isfunction(L, -1))
                {

                    int x = event.motion.x;
                    int y = event.motion.y;
                    int xrel = event.motion.xrel;
                    int yrel = event.motion.yrel;

                    lua_pushinteger(L, x);
                    lua_pushinteger(L, y);
                    lua_pushinteger(L, xrel);
                    lua_pushinteger(L, yrel);

                    if (lua_pcall(L, 4, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onMouseMotion(x, y, xrel, yrel)\n"
                                  << getError();
                        lua_pop(L, 1);
                    }
                }
                else
                {
                    lua_pop(L, 1);
                }

                break;

            case SDL_MOUSEWHEEL:

                lua_getglobal(L, "onMouseWheel");

                if (lua_isfunction(L, -1))
                {

                    int x = event.wheel.x;
                    int y = event.wheel.y;

                    if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                    {
                        x *= -1;
                        y *= -1;
                    }

                    lua_pushinteger(L, x);
                    lua_pushinteger(L, y);

                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onMouseWhell(x, y)\n"
                                  << getError();
                        lua_pop(L, 1);
                    }
                }
                else
                {
                    lua_pop(L, 1);
                }

                break;
            }
        }

        lua_getglobal(L, "update");

        if (!lua_isfunction(L, -1))
        {
            std::cerr << "CPP: Função update(deltaTime) não definida.\n";
            lua_pop(L, 1);
            destroyWindow(L);
            isRunning = false;
        }

        lua_pushnumber(L, deltaTime);
        if (lua_pcall(L, 1, 0, 0) != LUA_OK)
        {
            std::cerr << "CPP: Erro ao executar o update(deltatime)\n"
                      << getError();
            return;
        }
    }
}

int Tasq::Platform::init(lua_State *L)
{
    bool sucess = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "CPP: Erro ao inicializar SDL2!\n";
        sucess = false;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        std::cerr << "Erro ao inicializar SDL_image: " << IMG_GetError() << std::endl;
        return -1;
    }

    lua_pushboolean(L, sucess);

    return 1;
}

int Tasq::Platform::createWindow(lua_State *L)
{
    const char *title = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);

    Window *window = (Window *)malloc(sizeof(Window));

    window->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);

    if (!window->window)
    {
        std::cerr << "CPP: Erro ao criar janela SDL2\n"
                  << SDL_GetError() << '\n';
        lua_pushnil(L);
        return 1;
    }

    window->renderer = Renderer();

    if (window->renderer.init(window->window)) {
        std::cerr << "CPP: Erro ao criar \n"
                  << SDL_GetError() << '\n';
        lua_pushnil(L);
        return 1;
    }

    lua_pushlightuserdata(L, window);

    return 1;
}

int Tasq::Platform::destroyWindow(lua_State *L)
{
    std::cout << "CPP: Finalizando Plataforma\n";
    Window *window = static_cast<Window *>(lua_touserdata(L, 1));

    SDL_DestroyWindow(window->window);
    window->renderer.~Renderer();

    SDL_Quit();
    IMG_Quit();

    delete window;
    window = nullptr;

    exit(0);

    return 0;
}
