#pragma once
#include <SDL.h>
#include "Drawable.h"
#include "Transformable.h"

class Sprite : public Drawable, public Transformable
{
private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

public:
	Sprite(float PosX, float PosY, const char* TexturePath);
	void LoadPicture(const char* TexturePath);

	void Draw(Window* win) override;
	void ChangeColor(Window* win) override;
	void Resize(int width, int height);

	void Delet();
};