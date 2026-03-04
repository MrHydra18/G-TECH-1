
#include "MainMenu.h"
#include "PauseMenu.h"
#include "AudioManager.h"

MainMenu::MainMenu(SDL_Renderer* rend, Game* g) : Menu("Main Menu", rend, g) {

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

void MainMenu::onEnter()
{
	std::cout << "[MainMenu] Entering Main Menu\n";
	game->setState(GameState::MainMenu);
	selected = 0;
}

bool MainMenu::handleInput()
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

void MainMenu::render()
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
	UIManager::getInstance().renderTitle("Shoot'em Up", (int)(titleX + titleWidth * 0.04f), (int)(titleY + titleHeight * 0.13f), titleColor, titleFontSize);


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
		if (i == 1) {
			UIManager::getInstance().renderText("Create Level", startX + buttonWidth * 0.03f, startY + (int)(i * spacing) + buttonHeight / 16, titleColor, textFontSize - 5);
		}
		if (i == 3) {
			UIManager::getInstance().renderText("Shop", startX + buttonWidth /3.5, startY + (int)(i * spacing) + buttonHeight / 16, titleColor, textFontSize);
		}

		SDL_Rect innerRect = { rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4 };
		SDL_SetRenderDrawColor(renderer, 60, 60, 70, 255);
		
	}
}



void MainMenu::executeOption()
{
	switch (selected) {
	case 0: 
		UIManager::getInstance().pushMenu(new SelectionMenu(renderer, game));
		AudioManager::getInstance().playSound("Button");
		break;
	case 1:
		UIManager::getInstance().pushMenu(new LevelCrationMenu(renderer, game));
		AudioManager::getInstance().playSound("Button");
		
		break;
	case 2: // CREDITS
		UIManager::getInstance().pushMenu(new CreditsMenu(renderer, game));
		AudioManager::getInstance().playSound("Button");
		
		break;
	case 3: // SHOP
		UIManager::getInstance().pushMenu(new ShopMenu(renderer, game));
		AudioManager::getInstance().playSound("Button");

		
		break;
	case 4: // QUIT
		AudioManager::getInstance().playSound("Confirmation");
		game->quit();
		
		break;
	}
}
