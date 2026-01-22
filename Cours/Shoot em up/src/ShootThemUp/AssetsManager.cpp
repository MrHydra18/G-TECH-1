#include "AssetsManager.h"
#include "SDL_image.h"
#include <iostream>

SDL_Texture* AssetsManager::GetTexture(std::string texturePath)
{
    if (textureMap.find(texturePath) != textureMap.end()) {
        textureMap[texturePath].count++;
        return textureMap[texturePath].texture;
    }
    std::string fullPath = "../../res/" + texturePath;
    SDL_Surface* s = IMG_Load(fullPath.c_str());

    if (!s) {
        std::cerr << "[AssetsManager] Error while loading surface from: " << fullPath << "\n";
        std::cerr << "[AssetsManager] IMG_Load Error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    std::cout << "[AssetsManager] Successfully loaded surface from: " << fullPath << "\n";

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, s);
    if (!tex) {
        SDL_FreeSurface(s);
        std::cerr << "[AssetsManager] Error while creating texture from surface, path: " << fullPath << "\n";
        std::cerr << "[AssetsManager] SDL_CreateTextureFromSurface Error: " << SDL_GetError() << "\n";
        return nullptr;
    }

    SDL_FreeSurface(s);
    textureMap[texturePath] = { tex, 1 };
    return tex;
}

void AssetsManager::onTextureDelete(std::string texturePath)
{
    if (textureMap.find(texturePath) != textureMap.end()) {
        textureMap[texturePath].count--;
    }
}

void AssetsManager::clean()
{

    for (auto& texData : textureMap) {
        SDL_DestroyTexture(texData.second.texture);
    }

    textureMap.clear();


}
