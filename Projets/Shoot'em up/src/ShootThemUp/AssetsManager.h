#pragma once
#include <map>
#include <string>
#include <SDL.h>

struct TextureData {
	SDL_Texture* texture;
	int count;
};


class AssetsManager {
private:

	SDL_Renderer* renderer = nullptr;
	std::map<std::string, TextureData> textureMap;


public:

	static AssetsManager& getInstance() {
		static AssetsManager instance;
		return instance;
	}

	void init(SDL_Renderer* rend) { renderer = rend;}

	SDL_Texture* GetTexture(std::string texturePath);

	void onTextureDelete(std::string);


	void clean();

};