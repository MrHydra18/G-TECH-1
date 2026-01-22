#include "SelectionMenu.h"

SelectionMenu::SelectionMenu(SDL_Renderer* r, Game* g) : Menu("SelectionMenu", r, g)
{
	levels = LevelManager::getInstance().getLevelsName();

	AssetsManager& AM = AssetsManager::getInstance();
	scrollbarBg = AM.GetTexture("Buttons/DEFAULT.png");
	scrollbarProgress = AM.GetTexture("Buttons/slider.png");
	scrollbarThumb = AM.GetTexture("Buttons/thumb.png");
	scrollbarThumbHover = AM.GetTexture("Buttons/thumb.png");
	titleTexture = AM.GetTexture("Buttons/DEFAULT.png");
	buttonTexture = AM.GetTexture("Buttons/DEFAULT.png");
}

int SelectionMenu::getThumbPosition() const
{
	int winH = game->windowHeight;
	int sbY = (int)(winH * sbYPercent);
	int sbH = (int)(winH * sbHPercent);
	int tbH = (int)(winH * tbHPercent);
	int spacing = (int)(winH * spacingPercent);
	int startY = (int)(winH * startYPercent);
	int buttonHeight = (int)(winH * 0.1f);

	int totalContentHeight = (int)(levels.size() * spacing);
	int visibleHeight = winH - startY;
	int calculatedMinY = visibleHeight - totalContentHeight;

	if (calculatedMinY >= 0)
		return sbY;

	float scrollRange = abs(calculatedMinY);
	float scrollProgress = -posY / scrollRange;

	int availableSpace = sbH - tbH;
	int thumbY = (int)(sbY + (availableSpace * scrollProgress));

	return thumbY;
}

void SelectionMenu::onEnter()
{
	Menu::onEnter();
}

bool SelectionMenu::handleInput()
{
	InputManager& input = InputManager::getInstance();
	int winH = game->windowHeight;
	int spacing = (int)(winH * spacingPercent);
	int startY = (int)(winH * startYPercent);

	int totalContentHeight = levels.size() * spacing;
	int visibleHeight = winH - startY;
	int calculatedMinY = visibleHeight - totalContentHeight;

	// Ajuster posY si la fenêtre a été redimensionnée
	if (posY > 0)
		posY = 0;
	if (calculatedMinY < 0 && posY < calculatedMinY)
		posY = calculatedMinY;

	//if (input.IsKeyReleased(SDLK_UP) || input.IsKeyReleased(SDLK_z))
	//{
	//	posY += 40;
	//	if (posY > 0)
	//		posY = 0;
	//	return true;
	//}

	//if (input.IsKeyReleased(SDLK_DOWN) || input.IsKeyReleased(SDLK_s))
	//{
	//	posY -= 40;
	//	if (posY < calculatedMinY)
	//		posY = calculatedMinY;
	//	return true;
	//}

	if (input.IsKeyReleased(SDLK_ESCAPE))
	{
		UIManager::getInstance().popMenu();
		return true;
	}

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int sbX = (int)(game->windowWidth * sbXPercent);
	int sbY = (int)(winH * sbYPercent);
	int sbW = (int)(game->windowWidth * sbWPercent);
	int sbH = (int)(winH * sbHPercent);
	int tbH = (int)(winH * tbHPercent);

	if (input.IsMouseDown(SDL_BUTTON_LEFT))
	{
		int thumbPos = getThumbPosition();
		SDL_Rect thumbClickRect = { sbX - sbW / 2, thumbPos - 7, sbW * 2, tbH };

		if (isMouseInRect(mouseX, mouseY, thumbClickRect))
		{
			isDraggingScrollbar = true;
		}

		for (size_t i = 0; i < buttonRects.size(); i++)
		{
			if (isMouseInRect(mouseX, mouseY, buttonRects[i]))
			{
				selected = i;
				game->setLevel(LevelManager::getInstance().getLevelData(levels[i]));
				UIManager::getInstance().clearMenu();
				return true;
			}
		}
	}

	if (input.IsMouseReleased(SDL_BUTTON_LEFT))
	{
		isDraggingScrollbar = false;
	}

	if (isDraggingScrollbar && input.IsMouseHeld(SDL_BUTTON_LEFT))
	{
		int sbH = (int)(winH * sbHPercent);
		int relativeY = (int)(mouseY - sbY - (tbH / 2));
		int availableSpace = sbH - tbH;
		float scrollRatio = (float)relativeY / availableSpace;

		posY = (int)(-(scrollRatio * abs(calculatedMinY)));

		if (posY > 0)
			posY = 0;
		if (posY < calculatedMinY)
			posY = calculatedMinY;

		return true;
	}

	return false;
}

void SelectionMenu::render()
{
	int winW = game->windowWidth;
	int winH = game->windowHeight;


	int titleWidth = (int)(winW * 0.28f);
	int titleHeight = (int)(winH * 0.11f);
	int titleX = (int)((winW - titleWidth) / 2);
	int titleY = (int)(winH * 0.06f);

	SDL_Rect titleRect = { titleX, titleY, titleWidth, titleHeight };
	SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
	SDL_RenderFillRect(renderer, &titleRect);

	if (titleTexture)
	{
		SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
	}

	SDL_Color titleColor = { 200, 200, 200, 255 };
	int titleFontSize = (int)(winH * 0.06f);
	UIManager::getInstance().renderTitle("SELECT LEVEL", (int)(titleX + titleWidth * 0.055f), (int)(titleY + titleHeight * 0.25f), titleColor, titleFontSize);

	int startY = (int)(winH * startYPercent);
	int spacing = (int)(winH * spacingPercent);
	int buttonWidth = (int)(winW * 0.4375f);
	int buttonHeight = (int)(winH * 0.1f);
	int buttonX = (int)((winW - buttonWidth) / 2);
	int Y = startY + posY;
	buttonRects.clear();

	for (size_t i = 0; i < levels.size(); i++)
	{
		SDL_Rect buttonRect = { buttonX, Y, buttonWidth, buttonHeight };
		buttonRects.push_back(buttonRect);

		if (Y > titleY + titleHeight && Y < winH)
		{

			if (i == selected)
			{
				SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
				SDL_RenderFillRect(renderer, &buttonRect);

				SDL_SetRenderDrawColor(renderer, 150, 180, 255, 255);
				SDL_RenderDrawRect(renderer, &buttonRect);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
				SDL_RenderFillRect(renderer, &buttonRect);

				SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
				SDL_RenderDrawRect(renderer, &buttonRect);
			}

			if (buttonTexture)
			{
				SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
			}

			int textFontSize = (int)(winH * 0.04f);
			UIManager::getInstance().renderText(levels[i].c_str(), buttonRect.x + 20, (int)(buttonRect.y + buttonHeight * 0.29f), { 255, 255, 255, 255 }, textFontSize);
		}
		Y += spacing;
	}


	//scrollBar
	int sbX = (int)(winW * sbXPercent);
	int sbY = (int)(winH * sbYPercent);
	int sbW = (int)(winW * sbWPercent);
	int sbH = (int)(winH * sbHPercent);
	int tbH = (int)(winH * tbHPercent);

	int thumbPos = getThumbPosition() - 16;
	thumbPos += 16;
	SDL_Rect upRect = { sbX, sbY - sbW, sbW, sbW };
	SDL_Rect downRect = { sbX,(int)(sbY * 1.10f + sbH), sbW, sbW };
	SDL_RenderCopy(renderer, scrollbarThumb, 0, &upRect);
	SDL_RenderCopyEx(renderer, scrollbarThumb, 0, &downRect, 0, 0, SDL_FLIP_VERTICAL);
	for (int i = sbY; i < sbY + sbH; i += 16) {
		SDL_Rect sprogressRect = { 0, 0, 0, 0 };
		if (i > thumbPos)
			sprogressRect = { 64,0 , 16, 16 };
		else if (i + 4 > thumbPos)
			sprogressRect = { 48, 0, 16, 16 };
		else if (i + 8 > thumbPos)
			sprogressRect = { 32, 0, 16, 16 };
		else if (i + 8 > thumbPos)
			sprogressRect = { 16, 0, 16, 16 };
		else
			sprogressRect = { 0, 0, 16, 16 };
		SDL_Rect progressRect = { sbX, i, sbW, 16 };

		SDL_RenderCopyEx(renderer, scrollbarProgress, &sprogressRect, &progressRect, 0, 0, SDL_FLIP_VERTICAL);
	}
	SDL_Rect thumbRect = { sbX + sbW - 4, thumbPos - 7, sbW, tbH };
	SDL_Rect thumbRectDown = { sbX - sbW + 6, thumbPos - 7, sbW, tbH };
	SDL_RenderCopyEx(renderer, scrollbarThumbHover, nullptr, &thumbRect, 90, 0, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, scrollbarThumbHover, nullptr, &thumbRectDown, 270, 0, SDL_FLIP_NONE);
}
