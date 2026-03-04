
#include "CreditsMenu.h"
#include "AudioManager.h"

CreditsMenu::CreditsMenu(SDL_Renderer* rend, Game* g) : Menu("CreditsMenu", rend, g) {

	AssetsManager& AM = AssetsManager::getInstance();
	tex = AM.GetTexture("Buttons/DEFAULT.png");
	quitTex = AM.GetTexture("Buttons/MAINMENU.png");
}

void CreditsMenu::onEnter()
{
	Menu::onEnter();
}

bool CreditsMenu::handleInput()
{
	InputManager& IM = InputManager::getInstance();

	if (IM.IsKeyReleased(SDLK_SPACE) || IM.IsKeyReleased(SDLK_RETURN) || IM.IsKeyReleased(SDLK_ESCAPE)){
		UIManager::getInstance().popMenu();
		return true;
	}

	int winW = game->windowWidth;
	int winH = game->windowHeight;
	int quitWidth = (int)(winW * 0.34f);
	int quitHeight = (int)(winH * 0.12f);
	int quitX = (int)((winW - quitWidth) / 2);
	int quitY = (int)(winH * 0.825f);

	SDL_Rect quitRect = {quitX, quitY, quitWidth, quitHeight};

	int toggleSize = (int)(winH * 0.08f);
	soundToggleRect = { winW - toggleSize - 20, winH - toggleSize - 20, toggleSize, toggleSize };

	if (IM.IsMouseReleased(1)) {
		if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, quitRect)) {
			UIManager::getInstance().popMenu();
			AudioManager::getInstance().playSound("Button");
			return true;
		}

		if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, soundToggleRect)) {
			AudioManager& AM = AudioManager::getInstance();
			bool newState = !AM.isSoundEnabled();
			AM.setSoundEnabled(newState);
			AM.setMusicEnabled(newState);
			if (newState) {
				AM.playSound("Button");
			}
			return true;
		}
	}
	return false;
}

void CreditsMenu::render()
{
	int winW = game->windowWidth;
	int winH = game->windowHeight;


	int titleWidth = (int)(winW * 0.17f);
	int titleHeight = (int)(winH * 0.12f);
	int titleX = (int)((winW - titleWidth) / 2);
	int titleY = (int)(winH * 0.06f);

	SDL_Rect titleRect = { titleX, titleY, titleWidth, titleHeight };

	SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
	SDL_RenderFillRect(renderer, &titleRect);

	int startX = (int)(winW * 0.3f);
	int spacingX = (int)(winW * 0.14f);
	int startY = (int)(winH * 0.3f);
	int spacingY = (int)(winH * 0.10f);
	int titleButtonWidth = (int)(winW * 0.1f);
	int titleButtonHeight = (int)(winH * 0.07f);
	int buttonWidth = (int)(winW * 0.25f);
	int buttonHeight = (int)(winH * 0.07f);

	if (tex) {
		SDL_RenderCopy(renderer, tex, nullptr, &titleRect);
	}

	SDL_Color titleColor = { 255, 255, 255, 255 };
	int titleFontSize = (int)(winH * 0.06f);
	UIManager::getInstance().renderTitle("CREDITS", (int)(titleX + titleWidth * 0.055f), (int)(titleY + titleHeight * 0.25f), titleColor, titleFontSize);

	for (size_t i = 0; i < titles.size(); ++i)
	{
		SDL_Rect rect = { startX, startY + (int)(spacingY * i), titleButtonWidth, titleButtonHeight };

		SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_RenderCopy(renderer, tex, 0, &rect);
		int subtitleFontSize = (int)(winH * 0.06f);
		UIManager::getInstance().renderTitle(titles[i].c_str(), rect.x + 5, rect.y, { 255, 255, 255, 255 }, subtitleFontSize);
	}

	for (size_t i = 0; i < texts.size(); i++) {
		SDL_Rect rect = { startX + spacingX, startY + (int)(spacingY * i), buttonWidth, buttonHeight };

		SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_RenderCopy(renderer, tex, 0, &rect);
		int textFontSize = (int)(winH * 0.04f);
		UIManager::getInstance().renderText(texts[i].c_str(), rect.x + 15, rect.y + 15, { 255, 255, 255, 255 }, textFontSize);
	}

	int quitWidth = (int)(winW * 0.34f);
	int quitHeight = (int)(winH * 0.12f);
	int quitX = (int)((winW - quitWidth) / 2);
	int quitY = (int)(winH * 0.825f);

	SDL_Rect quitRect = {quitX, quitY, quitWidth, quitHeight};

	SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
	SDL_RenderFillRect(renderer, &quitRect);

	SDL_SetRenderDrawColor(renderer, 150, 180, 255, 255);
	SDL_RenderDrawRect(renderer, &quitRect);
	SDL_RenderCopy(renderer, quitTex, 0, &quitRect);

	int toggleSize = (int)(winH * 0.08f);
	soundToggleRect = { winW - toggleSize - 20, winH - toggleSize - 20, toggleSize, toggleSize };

	AudioManager& AM = AudioManager::getInstance();
	if (AM.isSoundEnabled()) {
		SDL_SetRenderDrawColor(renderer, 80, 200, 120, 255);
	} else {
		SDL_SetRenderDrawColor(renderer, 200, 80, 80, 255);
	}
	SDL_RenderFillRect(renderer, &soundToggleRect);

	SDL_SetRenderDrawColor(renderer, 150, 255, 180, 255);
	SDL_RenderDrawRect(renderer, &soundToggleRect);

	SDL_RenderCopy(renderer, tex, 0, &soundToggleRect);

	int fontSize = (int)(winH * 0.04f);
	const char* text = AM.isSoundEnabled() ? "ON" : "OFF";
	UIManager::getInstance().renderText(text, soundToggleRect.x + toggleSize / 16, soundToggleRect.y + toggleSize / 4, { 255, 255, 255, 255 }, fontSize);
}