#include "../../include/Platform/Platform.hpp"

SDL_Window *Tasq::Platform::window = nullptr;
SDL_Renderer *Tasq::Platform::renderer = nullptr;
SDL_Event Tasq::Platform::event = {};

Tasq::Platform::Platform()
{
    std::cout << "CPP: Iniciando plataforma..." << '\n';
    L = luaL_newstate();
    luaL_openlibs(L);

    this->window = nullptr;
    this->renderer = nullptr;

    isRunning = true;
}

void Tasq::Platform::loadEnumMouseButtonToLua()
{
    lua_newtable(L);

    lua_pushliteral(L, "PRESSED");
    lua_pushinteger(L, static_cast<int>(MouseButton::PRESSED));
    lua_settable(L, -3);

    lua_pushliteral(L, "RELEASED");
    lua_pushinteger(L, static_cast<int>(MouseButton::RELEASED));
    lua_settable(L, -3);

    lua_setglobal(L, "MouseButton");

    lua_newtable(L);
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

    loadEnumMouseButtonToLua();

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

    Uint32 lastTime = SDL_GetTicks();
    while (isRunning)
    {

        Uint32 currentTime = SDL_GetTicks();
        double deltaTime = ((double)currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        while (SDL_PollEvent(&this->event))
        {

            switch (this->event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:

                lua_getglobal(L, "onKeyDown");

                if (lua_isfunction(L, -1))
                {
                    lua_pushstring(L, SDL_GetKeyName(this->event.key.keysym.sym));

                    if (lua_pcall(L, 1, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onKeyDown(key)\n"
                                  << getError();
                        lua_pop(L, 1);
                    }
                }
                else
                {
                    lua_pop(L, 1);
                }

                break;

            case SDL_KEYUP:

                lua_getglobal(L, "onKeyUp");

                if (lua_isfunction(L, -1))
                {
                    const char *key = SDL_GetKeyName(this->event.key.keysym.sym);
                    lua_pushstring(L, key);

                    if (lua_pcall(L, 1, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar o onKeyUp(key)\n"
                                  << getError();
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
                    int action = (this->event.type == SDL_MOUSEBUTTONDOWN) ? MouseButton::PRESSED : MouseButton::RELEASED;

                    const char *button = getButtonName(this->event.button.button);
                    int x = this->event.button.x;
                    int y = this->event.button.y;

                    lua_pushstring(L, button);
                    lua_pushinteger(L, action);
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

                    int x = this->event.motion.x;
                    int y = this->event.motion.y;
                    int xrel = this->event.motion.xrel;
                    int yrel = this->event.motion.yrel;

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

                if (lua_isfunction(L, -1)) {

                    int x = this->event.wheel.x;
                    int y = this->event.wheel.y;

                    if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
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

                }else {
                    lua_pop(L, 1);
                }

                break;
            }
        }

        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);

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

        SDL_RenderPresent(this->renderer);
    }

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

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "CPP: Erro ao criar janela!\n"
                  << SDL_GetError() << '\n';
        lua_pushlightuserdata(L, nullptr);
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "CPP: Erro ao criar renderizador!\n"
                  << SDL_GetError() << '\n';
        lua_pushlightuserdata(L, nullptr);
        return 1;
    }

    lua_pushlightuserdata(L, window);

    return 1;
}

int Tasq::Platform::destroyWindow(lua_State *L)
{
    std::cout << "CPP: Finalizando Plataforma...\n";
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    window = nullptr;
    renderer = nullptr;
    event = {};
    exit(0);

    return 0;
}
