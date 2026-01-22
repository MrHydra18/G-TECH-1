#include "ConfirmationMenu.h"
#include "MainMenu.h"


ConfirmationMenu::ConfirmationMenu(SDL_Renderer* rend, Game* game, std::function<void()> OQ) : Menu("ConfirmationMenu", rend, game), onQuit(OQ) {
	AssetsManager& AM = AssetsManager::getInstance();
	titleBannerTexture = AM.GetTexture("Buttons/DEFAULT.png");

	for (size_t i = 0; i < buttonsTexte.size(); i++) {
		SDL_Texture* tex = AM.GetTexture("Buttons/" + buttonsTexte[i] + ".png");
		if (!tex) {
			tex = AM.GetTexture("Buttons/DEFAULT.png");
		}
		buttonsTexture.push_back(tex);
	}
}


void ConfirmationMenu::onEnter()
{
	std::cout << "[ConfirmationMenu] Entering Confirmation Menu\n";
	selected = 0;
}

bool ConfirmationMenu::handleInput()
{
	InputManager& input = InputManager::getInstance();


	if (input.IsKeyReleased(SDLK_DOWN) || input.IsKeyReleased(SDLK_s)) {
		selected = (selected + 1) % buttonsTexte.size();
		return true;
	}
	if (input.IsKeyReleased(SDLK_UP) || input.IsKeyReleased(SDLK_z)) {
		selected = (selected - 1 + buttonsTexte.size()) % buttonsTexte.size();
		return true;
	}
	if (input.IsKeyReleased(SDLK_RETURN) || input.IsKeyReleased(SDLK_RETURN)) {
		executeOption();
		return true;
	}

	if (input.IsKeyDown(SDLK_ESCAPE)) {
		UIManager::getInstance().popMenu();
		return true;
	}

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	bool mouseMoved = (mouseX != lastMouseX || mouseY != lastMouseY);
	lastMouseX = mouseX;
	lastMouseY = mouseY;


	if (mouseMoved) {
		for (size_t i = 0; i < buttonsRect.size(); i++) {
			if (isMouseInRect(mouseX, mouseY, buttonsRect[i])) {
				selected = i;
				break;
			}
		}
	}


	if (input.IsMouseDown(SDL_BUTTON_LEFT)) {
		for (size_t i = 0; i < buttonsRect.size(); i++) {
			if (isMouseInRect(mouseX, mouseY, buttonsRect[i])) {
				executeOption();
				return true;
			}
		}
	}

	return false;
}

void ConfirmationMenu::render()
{
	int winW = game->windowWidth;
	int winH = game->windowHeight;

	int titleWidth = (int)(winW * 0.4f);
	int titleHeight = (int)(winH * 0.15f);
	int titleX = (int)((winW - titleWidth) / 2);
	int titleY = (int)(winH * 0.05f);

	SDL_Rect titleRect = { titleX, titleY, titleWidth, titleHeight };

	SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
	SDL_RenderFillRect(renderer, &titleRect);

	if (titleBannerTexture) {
		SDL_RenderCopy(renderer, titleBannerTexture, nullptr, &titleRect);
	}

	SDL_Color titleColor = { 200, 200, 200, 255 };	
	int titleFontSize = (int)(winH * 0.1f);
	int textFontSize = (int)(winH * 0.08f);
	UIManager::getInstance().renderTitle("Are you sure ? ", (int)(titleX + titleWidth * 0.03f), (int)(titleY + titleHeight * 0.13f), titleColor, titleFontSize);


	int startY = (int)(winH * 0.25f);
	int spacing = (int)(winH * 0.13f);
	int buttonWidth = (int)(winW * 0.3f);
	int buttonHeight = (int)(winH * 0.1f);
	int startX = (int)((winW - buttonWidth) / 2);


	buttonsRect.clear();

	for (size_t i = 0; i < buttonsTexte.size(); ++i)
	{
		SDL_Rect rect = { startX, startY + (int)(i * spacing), buttonWidth, buttonHeight };
		buttonsRect.push_back(rect);

		if (i == static_cast<size_t>(selected)) {
			SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
			SDL_RenderFillRect(renderer, &rect);
		}

		if (i < buttonsTexture.size() && buttonsTexture[i] != nullptr) {
			SDL_RenderCopy(renderer, buttonsTexture[i], nullptr, &rect);
		}


		SDL_Rect innerRect = { rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4 };
		SDL_SetRenderDrawColor(renderer, 60, 60, 70, 255);

	}

}

void ConfirmationMenu::executeOption()
{
	switch (selected) {
	case 0:
		UIManager::getInstance().popMenu();
		break;
	case 1:
		onQuit();
		break;
	}
}
