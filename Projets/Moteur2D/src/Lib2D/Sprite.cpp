#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "Window.h"

Sprite::Sprite(float PosX, float PosY, const char* TexturePath) : Transformable(PosX, PosY)
{
	LoadPicture(TexturePath);
}

void Sprite::LoadPicture(const char* TexturePath)
{
	if (m_Texture) {
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

	if (m_Surface) {
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
	}

	m_Surface = IMG_Load(TexturePath);
	if (m_Surface == nullptr)
	{
		std::cout << "erreure de chargement de la surface" << std::endl;
		exit(1);
	}
}

void Sprite::Draw(Window* win)
{
	if (m_Texture == nullptr) {

		m_Texture = SDL_CreateTextureFromSurface(win->m_Renderer, m_Surface);
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
		SDL_QueryTexture(m_Texture, NULL, NULL, &m_Width, &m_Height);
	}

	SDL_Rect dst = { Position.GetX(), Position.GetY(), m_Width, m_Height };

	int error = SDL_RenderCopy(win->m_Renderer, m_Texture, NULL, &dst);
	if (error != 0)
		std::cout << "erreure render copy";
}

void Sprite::ChangeColor(Window* win)
{
	SDL_Texture* target = SDL_CreateTexture(win->m_Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_Width, m_Height);
	SDL_Texture* OldTextur = SDL_GetRenderTarget(win->m_Renderer);
	SDL_SetRenderTarget(win->m_Renderer, target);
	SDL_RenderCopy(win->m_Renderer, m_Texture, NULL, NULL);
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, m_Width, m_Height, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_RenderReadPixels(win->m_Renderer, NULL, surface->format->format, surface->pixels, surface->pitch);

	//Choix aleatoire d'un facteur entre 0.5 et 2
	float facteurR = (rand() % 150 + 50) / 100.0f;
	float facteurG = (rand() % 150 + 50) / 100.0f;
	float facteurB = (rand() % 150 + 50) / 100.0f;

	Uint32* pixels = static_cast<Uint32*>(surface->pixels);
	int pixelCount = m_Width * m_Height;
	for (int i = 0; i < pixelCount; ++i)
	{
		Uint8 r, g, b, a;
		SDL_GetRGBA(pixels[i], surface->format, &r, &g, &b, &a);

		//Nouvelle valeur de chaque pixel
		Uint8 newR = (Uint8)std::min(255, (int)(r * facteurR));
		Uint8 newG = (Uint8)std::min(255, (int)(g * facteurG));
		Uint8 newB = (Uint8)std::min(255, (int)(b * facteurB));

		pixels[i] = SDL_MapRGBA(surface->format, newR, newG, newB, a);
	}
	SDL_SetRenderTarget(win->m_Renderer, OldTextur);
	SDL_DestroyTexture(m_Texture);
	m_Texture = SDL_CreateTextureFromSurface(win->m_Renderer, surface);
	SDL_QueryTexture(m_Texture, NULL, NULL, &m_Width, &m_Height);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(target);
}

void Sprite::Resize(int width, int height)
{
	float FactorWidth = width / m_Width;
	float FactorHeight = height / m_Height;

	float FactorMin = std::min(FactorWidth, FactorHeight);

	m_Width *= FactorMin;
	m_Height *= FactorMin;
}

void Sprite::Delet()
{
	m_DirectionX = NULL;
	m_DirectionY = NULL;

	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

	m_Width = NULL;
	m_Height = NULL;
}
