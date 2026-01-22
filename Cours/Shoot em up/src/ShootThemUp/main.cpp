#pragma once
#include "Game.h"

int main(int argc, char** argv) {

    const int FPS = 60;
    const float TARGET_DELTA = 1000.0f / FPS;  

    Game* game  = Game::getInstance();

    if (!game->init("Shoot'em Up", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        false)) 
    {
        std::cerr << "[Main] Failed to initialize game!\n";
        return 1;
    }

    std::cout << "[Main] Game loop starting...\n";

 
    Uint64 lastTime = SDL_GetTicks();

    
    
    while (game->running()) {

     
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;  
        lastTime = currentTime;

  
        game->handleEvents();
        game->update(deltaTime);
        game->render();


        Uint64 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < TARGET_DELTA) {
            SDL_Delay((TARGET_DELTA - frameTime));
        }
    }
    
    game->clean();

    std::cout << "[Main] Game exited cleanly\n";
    return 0;
}
