#include "GameManager.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const float TARGET_DELTA = 1000.0f / FPS;

    GameManager& game = GameManager::GetInstance();


    game.Init();

    Uint64 lastTime = SDL_GetTicks();


    while (game.running()) {


        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;


        game.handleEvents();
        game.Update(deltaTime);
        game.render();


        Uint64 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < TARGET_DELTA) {
            SDL_Delay((TARGET_DELTA - frameTime));
        }
    }

    game.Shutdown();

    std::cout << "[Main] Game exited cleanly\n";
    return 0;
}
