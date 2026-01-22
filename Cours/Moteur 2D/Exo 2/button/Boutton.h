#pragma once
#include<SDL3/SDL.h>

class Boutton
{
private:

	SDL_FRect buttonChangeColorRect = { 300, 275, 200, 50 };
	SDL_Color buttonChangeColorColor = { 255, 255, 255, 255 };
	SDL_FRect buttonQuitRect = { 300, 475, 200, 50 };
	SDL_Color buttonQuitColor = { 255, 0, 0, 255 };
	SDL_Color color = { 0, 0, 0, 255 };

public:

	SDL_FRect GetBouttonChangeColor() { return buttonChangeColorRect; }
	SDL_FRect GetBouttonQuit() { return buttonQuitRect; }
	void Draw(SDL_Renderer* renderer);
	void ChangeColor();
	bool Quit();
};