#include"Boutton.h"
#include"Game.h"
#include<iostream>

void Boutton::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, buttonChangeColorColor.r, buttonChangeColorColor.g, buttonChangeColorColor.b, buttonChangeColorColor.a);
	SDL_RenderFillRect(renderer, &buttonChangeColorRect);


	SDL_SetRenderDrawColor(renderer, buttonQuitColor.r, buttonQuitColor.g, buttonQuitColor.b, buttonQuitColor.a);
	SDL_RenderFillRect(renderer, &buttonQuitRect);

	SDL_RenderPresent(renderer);
}

void Boutton::ChangeColor()
{
	std::cout << "Change Color\n";
	if (color.r == 0 && color.g == 0 && color.b == 0) {
		color = { 0,255, 255, 255 };
	}
	else if (color.r == 0 && color.g == 255 && color.b == 255) {
		color = { 255, 255, 0, 255 };
	}
	else if (color.r == 255 && color.g == 255 && color.b == 0) {
		color = { 0, 0, 0, 255 };
	}
}

bool Boutton::Quit()
{
	std::cout << "Quit\n";
	return true;
}

