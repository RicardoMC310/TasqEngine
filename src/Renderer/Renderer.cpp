#include "../../include/Renderer/Renderer.hpp"

Tasq::Renderer::Renderer() {
    renderer = nullptr;
}

bool Tasq::Renderer::init(SDL_Window* window, lua_State *L) {

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        return false;
    }

    this->L = L;

    return true;
}

void Tasq::Renderer::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

}

SDL_Renderer* Tasq::Renderer::getRenderer() const {
    return renderer;
}

Tasq::Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}