#include "HandleEvents.h"
#include "Game.h"
#include "Boutton.h"
#include <iostream>

void HandleEvents::Events(Game& g, Boutton& b)
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
		{
			g.isPlaying = false;
		}
		if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
		{
			g.isPlaying = false;
		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouseX = e.button.x;
			mouseY = e.button.y;
			mousePress = true;
		}
		if (mousePress &&
			GetClickX() >= b.GetBouttonChangeColor().x &&
			GetClickX() <= b.GetBouttonChangeColor().x + b.GetBouttonChangeColor().w &&
			GetClickY() >= b.GetBouttonChangeColor().y &&
			GetClickY() <= b.GetBouttonChangeColor().y + b.GetBouttonChangeColor().h)
		{
			b.ChangeColor();
			mousePress = false;
		}

		if (mousePress &&
			GetClickX() >= b.GetBouttonQuit().x &&
			GetClickX() <= b.GetBouttonQuit().x + b.GetBouttonQuit().w &&
			GetClickY() >= b.GetBouttonQuit().y &&
			GetClickY() <= b.GetBouttonQuit().y + b.GetBouttonQuit().h)
		{
			if (b.Quit())
			{
				g.isPlaying = false;
			}
			mousePress = false;
		}
	}
}