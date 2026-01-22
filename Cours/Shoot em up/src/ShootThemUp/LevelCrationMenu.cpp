#include "LevelCrationMenu.h"
#include "ConfirmationMenu.h"
#include "LevelManager.h"
#include <filesystem>
#include <fstream>
#include "AudioManager.h"

LevelCrationMenu::LevelCrationMenu(SDL_Renderer* rend, Game* g) : Menu("LevelCrationMenu", rend, g)
{
	AssetsManager& AM = AssetsManager::getInstance();
	bannerTexture = AM.GetTexture("Buttons/DEFAULT.png");
	scrollbarProgress = AM.GetTexture("Buttons/slider.png");
	scrollbarThumb = AM.GetTexture("Buttons/thumb.png");

	InputManager::getInstance().SetKeyDownCB([this](SDL_Keycode key) { OnKeyDown(key); });


	gridData.resize(gridRows * gridCols, 0);


	enemysIcons.clear();
	enemysRect.clear();
	for (const auto& entry : std::filesystem::directory_iterator("../../res/EnemysIcons/")) {
		if (entry.is_regular_file()) {
			std::string filename = "EnemysIcons/" + entry.path().filename().string();
			enemysIcons.push_back(AM.GetTexture(filename));
		}
	}

	bosssIcons.clear();
	bossRect.clear();
	for (const auto& entry : std::filesystem::directory_iterator("../../res/BosssIcons/")) {
		if (entry.is_regular_file()) {
			std::string filename = "BosssIcons/" + entry.path().filename().string();
			bosssIcons.push_back(AM.GetTexture(filename));
		}
	}
	actualString = nullptr;
}

void LevelCrationMenu::onEnter()
{
	std::cout << "[LevelCreationMenu] enter on menu\n";
}

bool LevelCrationMenu::handleInput()
{
	InputManager& IM = InputManager::getInstance();


	if (IM.IsKeyDown(SDLK_ESCAPE)) {
		// si le level a ete save on quit instante
		std::vector<std::string> lvlsName = LevelManager::getInstance().getLevelsName();
		for (int i = 0; i < lvlsName.size(); i++) {
			if (lvlsName[i] == titleString) {
				UIManager::getInstance().popMenu();
				return true;
			}
		}
		//sinon on demande confirmation
		UIManager::getInstance().pushMenu(new ConfirmationMenu(renderer, game, [this] {
			UIManager::getInstance().popMenu();
			UIManager::getInstance().popMenu();
			}));
	}


	int winW = game->windowWidth;
	int winH = game->windowHeight;
	sliderXRect = { 10, winH - 40, winW - 20, 24 };

	if (IM.IsMouseDown(1)) {
		Vector2D mousePos = IM.getMousePos();


		if (!isMouseInRect(mousePos.x, mousePos.y, sliderXRect)) {
			if (isMouseInRect(mousePos.x, mousePos.y, titleRect))
				actualString = &titleString;
			else
				actualString = nullptr;

			for (int i = 0; i < enemysRect.size() && i < 6; i++) {
				if (isMouseInRect(mousePos.x, mousePos.y, enemysRect[i])) {
					selectedEnemy = i + 1;
				}
			}

			for (int i = 0; i < bossRect.size() && i < 6; i++) {
				if (isMouseInRect(mousePos.x, mousePos.y, bossRect[i])) {
					selectedEnemy = i + enemysIcons.size() + 1;
				}
			}
		}
	}


	if (IM.IsMouseHeld(1) && selectedEnemy > 0) {

		Vector2D mousePos = IM.getMousePos();

		// si on slide pas besoins de verif toute les cases
		if (!isMouseInRect(mousePos.x, mousePos.y, sliderXRect)) {
			int gridStartY = winH / 5 + 10;
			int gridHeight = winH - gridStartY - 60;
			int cellSize = gridHeight / gridRows;

			for (int row = 0; row < gridRows; row++) {
				for (int col = scrollX; col < scrollX + 40 && col < gridCols; col++) {
					SDL_Rect cellRect = {
						10 + (col - scrollX) * cellSize,
						gridStartY + row * cellSize,
						cellSize,
						cellSize
					};

					if (isMouseInRect(mousePos.x, mousePos.y, cellRect)) {
						int index = row * gridCols + col;
						gridData[index] = selectedEnemy;
					}
				}
			}
		}
	}

	if (IM.IsMouseDown(3)) {
		Vector2D mousePos = IM.getMousePos();
		// grille
		int winW = game->windowWidth;
		int winH = game->windowHeight;
		int gridStartY = winH / 5 + 10;
		int gridHeight = winH - gridStartY - 60;
		int cellSize = gridHeight / gridRows;

		for (int row = 0; row < gridRows; row++) {
			for (int col = scrollX; col < scrollX + 40 && col < gridCols; col++) {
				SDL_Rect cellRect = {
					10 + (col - scrollX) * cellSize,
					gridStartY + row * cellSize,
					cellSize,
					cellSize
				};

				if (isMouseInRect(mousePos.x, mousePos.y, cellRect)) {
					int index = row * gridCols + col;
					gridData[index] = 0;
				}
			}
		}
	}

	if (IM.IsMouseHeld(3)) {

		Vector2D mousePos = IM.getMousePos();

		// Ne pas peindre si on est sur le slider
		if (!isMouseInRect(mousePos.x, mousePos.y, sliderXRect)) {
			int gridStartY = winH / 5 + 10;
			int gridHeight = winH - gridStartY - 60;
			int cellSize = gridHeight / gridRows;

			for (int row = 0; row < gridRows; row++) {
				for (int col = scrollX; col < scrollX + 40 && col < gridCols; col++) {
					SDL_Rect cellRect = {
						10 + (col - scrollX) * cellSize,
						gridStartY + row * cellSize,
						cellSize,
						cellSize
					};

					if (isMouseInRect(mousePos.x, mousePos.y, cellRect)) {
						int index = row * gridCols + col;
						gridData[index] = 0;
					}
				}
			}
		}
	}




	if (IM.IsMouseDown(1)) {
		Vector2D mousePos = IM.getMousePos();

		// Save
		if (isMouseInRect(mousePos.x, mousePos.y, saveButtonRect)) {

			if (!titleString.empty()) {
				std::string filename = "../../res/levelDatas/" + titleString + ".txt";
				std::ofstream file(filename);

				if (file.is_open()) {
					for (int row = 0; row < gridRows; row++) {
						for (int col = 0; col < gridCols; col++) {
							int index = row * gridCols + col;
							int val = gridData[index];

							if (val == 0)
								file << "-";
							else if (val == 1)
								file << "E";
							else if (val == 2)
								file << "B";
							else if (val == 3)
								file << "L";
							else if (val == 4)
								file << "M";
							else
								file << "-";
						}
						file << "\n";
					}

					file.close();
					AudioManager::getInstance().playSound("Save");
				}
			}
		}
	}




	if (IM.IsMouseDown(1)) {
		Vector2D mousePos = IM.getMousePos();


		int sliderHeight = 24;
		int thumbWidth = 30;
		float ratioX = (float)scrollX / (gridCols - 40);
		int thumbX = (int)(sliderXRect.x + ratioX * (sliderXRect.w - thumbWidth));


		SDL_Rect thumbRect = {
			thumbX - thumbWidth,
			sliderXRect.y - sliderHeight,
			thumbWidth * 2,
			sliderHeight * 2
		};

		if (isMouseInRect(mousePos.x, mousePos.y, thumbRect)) {
			isDraggingSlider = true;
			std::cout << "on drag\n";
		}
	}

	if (IM.IsMouseReleased(1)) {
		isDraggingSlider = false;
	}

	if (isDraggingSlider && IM.IsMouseHeld(1)) {
		Vector2D mousePos = IM.getMousePos();
		int thumbWidth = 30;
		int relativeX = (int)(mousePos.x - sliderXRect.x - (thumbWidth / 2));
		int availableSpace = sliderXRect.w - thumbWidth;
		float scrollRatio = (float)relativeX / availableSpace;

		scrollX = (int)(scrollRatio * (gridCols - 40));

		if (scrollX < 0) scrollX = 0;
		if (scrollX > gridCols - 40) scrollX = gridCols - 40;
	}

	return false;
}


void LevelCrationMenu::OnKeyDown(SDL_Keycode key)
{
	if (!actualString)
		return;

	//suppr
	if (key == SDLK_BACKSPACE && !actualString->empty()) {
		actualString->pop_back();
		return;
	}


	if (actualString == &titleString) {

		if ((key >= SDLK_a && key <= SDLK_z) ||
			(key >= SDLK_0 && key <= SDLK_9) ||
			key == SDLK_UNDERSCORE ||
			key == SDLK_MINUS ||
			key == SDLK_PERIOD ||
			key == SDLK_SPACE) {

			// si on est shift
			InputManager& IM = InputManager::getInstance();
			bool shiftHeld = IM.IsKeyHeld(SDLK_LSHIFT) || IM.IsKeyHeld(SDLK_RSHIFT);

			if (key >= SDLK_a && key <= SDLK_z) {
				//on convertie
				if (shiftHeld) {
					*actualString += (char)(key - 32);
				}
				else {
					*actualString += (char)key;
				}
			}
			else {
				*actualString += (char)key;
			}
		}
	}
}

void LevelCrationMenu::render()
{
	int winW = game->windowWidth;
	int winH = game->windowHeight;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 0);
	SDL_Rect fullscreen = { 0, 0, winW, winH };
	SDL_RenderFillRect(renderer, &fullscreen);

	// bannier moche a changer
	bannerRect = { 0, 0, winW, winH / 5 };
	SDL_RenderCopy(renderer, bannerTexture, 0, &bannerRect);

	int policeSize = winW / 80;

	//name
	titleRect = { winW / 40, winH / 35, winW / 10, winH / 25 };
	SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
	SDL_RenderFillRect(renderer, &titleRect);
	SDL_RenderCopy(renderer, bannerTexture, 0, &titleRect);
	UIManager::getInstance().renderText((titleString != "" ? titleString.c_str() : "Level Name"), titleRect.x + titleRect.w / 16, titleRect.y + titleRect.h / 8, { 255, 255, 255, 255 }, policeSize);

	// Enemys
	enemysRect.clear();
	int btnSize = winW / 30;
	int btnStartX = winW / 6;
	int btnStartY = winH / 35;

	for (int i = 0; i < 6 && i < enemysIcons.size(); i++) {
		int row = i / 3;
		int col = i % 3;
		SDL_Rect btnRect = { btnStartX + col * (btnSize + 10), btnStartY , btnSize, btnSize };
		enemysRect.push_back(btnRect);


		if (selectedEnemy == i + 1) {
			SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
			SDL_RenderFillRect(renderer, &btnRect);
			SDL_RenderCopy(renderer, bannerTexture, 0, &btnRect);
		}

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderCopy(renderer, bannerTexture, 0, &btnRect);

		if (i < enemysIcons.size()) {
			SDL_RenderCopy(renderer, enemysIcons[i], nullptr, &btnRect);
		}

	}

	//Boss (soon)
	bossRect.clear();

	for (int i = 0; i < bosssIcons.size(); i++) {
		SDL_Rect btnRect = { btnStartX + i * (btnSize + 10), btnStartY + (btnSize + 10), btnSize, btnSize };
		bossRect.push_back(btnRect);


		if (selectedEnemy == i + enemysIcons.size() + 1) {
			SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
			SDL_RenderFillRect(renderer, &btnRect);
			SDL_RenderCopy(renderer, bannerTexture, 0, &btnRect);
		}

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderCopy(renderer, bannerTexture, 0, &btnRect);

		if (i < bosssIcons.size()) {
			SDL_RenderCopy(renderer, bosssIcons[i], nullptr, &btnRect);
		}

	}

	// Save
	saveButtonRect = { winW - btnSize * 2,btnStartY + btnSize / 3, btnSize + btnSize / 2, btnSize };
	SDL_SetRenderDrawColor(renderer, 0, 170, 0, 170);
	SDL_RenderFillRect(renderer, &saveButtonRect);
	SDL_RenderCopy(renderer, bannerTexture, 0, &saveButtonRect);
	UIManager::getInstance().renderText("Save", saveButtonRect.x + saveButtonRect.w / 2 - policeSize, saveButtonRect.y + saveButtonRect.h / 3, { 255, 255, 255, 255 }, policeSize);

	// Grille de level
	int gridStartY = winH / 5 + 10;
	int gridHeight = winH - gridStartY - 60;
	int cellSize = gridHeight / gridRows;

	for (int row = 0; row < gridRows; row++) {
		for (int col = scrollX; col < scrollX + 40 && col < gridCols; col++) {
			SDL_Rect cellRect = {
				10 + (col - scrollX) * cellSize,
				gridStartY + row * cellSize,
				cellSize - 2,
				cellSize - 2
			};

			int index = row * gridCols + col;
			int val = gridData[index];

			if (val == 0) {
				SDL_SetRenderDrawColor(renderer, 50, 50, 50, 160);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 150, 150, 150, 160);
			}
			SDL_RenderFillRect(renderer, &cellRect);

			// rendre ca beau
			SDL_SetRenderDrawColor(renderer, 80, 80, 80, 160);
			SDL_RenderDrawRect(renderer, &cellRect);

			//si jamais on met un enemy
			if (val > 0 && val <= enemysIcons.size()) {
				SDL_RenderCopy(renderer, enemysIcons[val - 1], nullptr, &cellRect);
			}
			if (val > enemysIcons.size() && val <= enemysIcons.size() + bosssIcons.size()) {
				SDL_RenderCopy(renderer, bosssIcons[val - enemysIcons.size() - 1], nullptr, &cellRect);
			}

		}
	}


	int sliderHeight = 24;
	sliderXRect = { 10, winH - 40, winW - 20, sliderHeight };


	int thumbWidth = 30;
	float ratioX = (float)scrollX / (gridCols - 40);
	int thumbX = (int)(sliderXRect.x + ratioX * (sliderXRect.w - thumbWidth));


	int arrowSize = sliderHeight;
	SDL_Rect leftArrow = { sliderXRect.x - arrowSize, sliderXRect.y, arrowSize, arrowSize };
	SDL_Rect rightArrow = { sliderXRect.x + sliderXRect.w, sliderXRect.y, arrowSize, arrowSize };
	SDL_RenderCopyEx(renderer, scrollbarThumb, 0, &leftArrow, 270, 0, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, scrollbarThumb, 0, &rightArrow, 90, 0, SDL_FLIP_NONE);


	for (int i = sliderXRect.x; i < sliderXRect.x + sliderXRect.w; i += sliderHeight) {
		SDL_Rect sprogressRect = { 0, 0, 0, 0 };
		if (i > thumbX)
			sprogressRect = { 64, 0, 16, 16 };
		else if (i + 6 > thumbX)
			sprogressRect = { 48, 0, 16, 16 };
		else if (i + 12 > thumbX)
			sprogressRect = { 32, 0, 16, 16 };
		else if (i + 18 > thumbX)
			sprogressRect = { 16, 0, 16, 16 };
		else
			sprogressRect = { 0, 0, 16, 16 };

		SDL_Rect progressRect = { i, sliderXRect.y, sliderHeight, sliderHeight };
		SDL_Rect destRect = { i, sliderXRect.y, 16, sliderHeight };
		SDL_RenderCopyEx(renderer, scrollbarProgress, &sprogressRect, &destRect, 90, 0, SDL_FLIP_NONE);
	}


	SDL_Rect thumbTop = { thumbX, sliderXRect.y - sliderHeight + 6, thumbWidth, sliderHeight };
	SDL_Rect thumbBottom = { thumbX, sliderXRect.y + sliderHeight - 6, thumbWidth, sliderHeight };
	SDL_RenderCopy(renderer, scrollbarThumb, nullptr, &thumbTop);
	SDL_RenderCopyEx(renderer, scrollbarThumb, nullptr, &thumbBottom, 0, 0, SDL_FLIP_VERTICAL);

}
