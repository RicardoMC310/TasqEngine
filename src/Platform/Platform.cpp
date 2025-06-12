#include "../../include/Platform/Platform.hpp"

SDL_Window *Tasq::Platform::window = nullptr;
SDL_Event Tasq::Platform::event = {};
Tasq::Renderer Tasq::Platform::renderer;
Tasq::Texture Tasq::Platform::texture(nullptr);
Tasq::Input Tasq::Platform::input;

Tasq::Platform::Platform()
{
    std::cout << "CPP: Iniciando Plataforma..." << '\n';
    L = luaL_newstate();
    luaL_openlibs(L);

    this->window = nullptr;

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
    std::cout << "CPP: Executando Arquivo..." << '\n';

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
        {"drawRect", Renderer::drawRect},
        {"drawTexture", Renderer::drawTexture},
        {"saveTexture", Texture::saveTexture},
        {"destroyTexture", Platform::destroyTexture},
        {"isKeyDown", Input::isKeyDown}};

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
            case SDL_KEYUP:
            case SDL_KEYDOWN:

                lua_getglobal(L, "onKeyEvent");

                if (lua_isfunction(L, -1))
                {

                    const char *key = SDL_GetKeyName(this->event.key.keysym.sym);

                    lua_pushstring(L, key);
                    lua_pushstring(L, (this->event.type == SDL_KEYDOWN) ? "Pressed" : "Released");

                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar onKeyEvent(key, action)\n"
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

                lua_getglobal(L, "onMouseClick");

                if (lua_isfunction(L, -1))
                {

                    const char *button = getButtonName(this->event.button.button);

                    lua_pushstring(L, button);
                    lua_pushstring(L, (this->event.type == SDL_MOUSEBUTTONDOWN) ? "Pressed" : "Released");
                    lua_pushinteger(L, this->event.button.x);
                    lua_pushinteger(L, this->event.button.y);

                    if (lua_pcall(L, 4, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar onMouseClick(button, action, x, y)\n"
                                  << getError() << '\n';
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

                    lua_pushinteger(L, this->event.motion.x);
                    lua_pushinteger(L, this->event.motion.y);
                    lua_pushinteger(L, this->event.motion.xrel);
                    lua_pushinteger(L, this->event.motion.yrel);

                    if (lua_pcall(L, 4, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar onMouseMotion(x, y, xrel, yrel)\n"
                                  << getError() << '\n';
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

                    int x = this->event.wheel.x;
                    int y = this->event.wheel.y;

                    if (this->event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                        x *= -1;
                        y *= -1;
                    }

                    lua_pushinteger(L, x);
                    lua_pushinteger(L, y);

                    if (lua_pcall(L, 2, 0, 0) != LUA_OK)
                    {
                        std::cerr << "CPP: Erro ao executar onMouseWheel(x, y)\n"
                                  << getError() << '\n';
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

        renderer.render();

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

        SDL_RenderPresent(renderer.getRenderer());
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
        return 0;
    }

    renderer = Renderer();

    if (!renderer.init(window))
    {
        std::cerr << "CPP: Erro ao criar renderizador!\n"
                  << SDL_GetError() << '\n';
        return 0;
    }

    texture = Texture(renderer.getRenderer());
    input = Input();

    return 0;
}

int Tasq::Platform::destroyWindow(lua_State *L)
{
    std::cout << "CPP: Finalizando Plataforma...\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    window = nullptr;
    event = {};
    lua_close(L);

    return 0;
}

int Tasq::Platform::destroyTexture(lua_State *L)
{

    SDL_Texture *texture = static_cast<SDL_Texture *>(lua_touserdata(L, 1));
    SDL_DestroyTexture(texture);
    texture = nullptr;

    return 0;
}
