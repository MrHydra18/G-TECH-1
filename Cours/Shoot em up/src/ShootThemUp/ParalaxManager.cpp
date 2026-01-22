#include "ParalaxManager.h"
#include "game.h"

void ParalaxManager::resetParalax()
{
	paralaxs.clear();
	for (const auto& entry : std::filesystem::directory_iterator("../../res/" + path)) {
		if (entry.is_regular_file()) {
			if (entry.path().extension() == ".png") {
				Paralax p;
				std::cout << "load: " << path + entry.path().filename().string() << std::endl;
				p.texture = AssetsManager::getInstance().GetTexture(path + entry.path().filename().string());
				p.rect.x = 0;
				p.rect.y = 0;
				p.rect.w = 0;
				p.rect.h = 0;
				p.exactPosition = {0, 0}; 
				paralaxs.push_back(p);
			}
		}
	}
}

void ParalaxManager::update(float deltaTime)
{

	if (!game) return;

	int winH = game->windowHeight;
	int winW = game->windowWidth;

	float scaleRatioX = (float)winW / 1600.0f;

	Vector2D scaledParalaxSpeed = baseParalaxSpeed * scaleRatioX;

	for (int i = 0; i < paralaxs.size(); i++) {
		paralaxs[i].rect.w = winW;
		paralaxs[i].rect.h = winH;

		paralaxs[i].exactPosition.x += i * scaledParalaxSpeed.x * deltaTime;

		if (paralaxs[i].exactPosition.x >= winW) {
			paralaxs[i].exactPosition.x -= winW * 2;
		}


		paralaxs[i].rect.x = (int)paralaxs[i].exactPosition.x;

	}

}

void ParalaxManager::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < paralaxs.size(); i++) {
		SDL_RenderCopy(renderer, paralaxs[i].texture, 0, &paralaxs[i].rect);
		SDL_Rect otherRect = paralaxs[i].rect;
		otherRect.x = paralaxs[i].rect.x < 0 ? paralaxs[i].rect.x + paralaxs[i].rect.w : paralaxs[i].rect.x - paralaxs[i].rect.w;
		SDL_RenderCopyEx(renderer, paralaxs[i].texture, 0, &otherRect, 0, 0, SDL_FLIP_HORIZONTAL);





	}

}
