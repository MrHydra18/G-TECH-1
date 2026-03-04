
#include "InputManager.h"

bool InputManager::update()
{
	SDL_Event events;
	for (auto& paire : keysStates) {
		if (paire.second.isDown) {
			paire.second.isDown = false;
			paire.second.isHeld = true;
		}
		if (paire.second.isRelease) {
			paire.second.isRelease = false;
			paire.second.isHeld = false;
		}
	}

	for (auto& paire : mouseButtonsStates) {
		if (paire.second.isDown) {
			paire.second.isDown = false;
			paire.second.isHeld = true;
		}
		if (paire.second.isRelease) {
			paire.second.isRelease = false;
			paire.second.isHeld = false;
		}
	}
	while (SDL_PollEvent(&events)) {
		switch (events.type) {

		case SDL_QUIT:
			return false;

		case SDL_WINDOWEVENT:
			if (events.window.event == SDL_WINDOWEVENT_RESIZED) {
				windowResized = true;
				int requestedWidth = events.window.data1;
				int requestedHeight = events.window.data2;

				// Ratio 16:9 (1600/900 = 16/9)
				float targetRatio = 16.0f / 9.0f;
				float currentRatio = (float)requestedWidth / (float)requestedHeight;

				// Ajuster pour maintenir le ratio 16:9
				if (currentRatio > targetRatio) {
					// Trop large, ajuster la largeur
					newWidth = (int)(requestedHeight * targetRatio);
					newHeight = requestedHeight;
				} else {
					// Trop haut, ajuster la hauteur
					newWidth = requestedWidth;
					newHeight = (int)(requestedWidth / targetRatio);
				}

				// Forcer la taille de la fenêtre au ratio correct
				SDL_Window* window = SDL_GetWindowFromID(events.window.windowID);
				if (window) {
					SDL_SetWindowSize(window, newWidth, newHeight);
				}
			}
			break;

		case SDL_KEYDOWN:

			if (keysStates[SDL_GetKeyFromScancode(events.key.keysym.scancode)].isHeld == false)
				keysStates[SDL_GetKeyFromScancode(events.key.keysym.scancode)] = { true, false, false };

			if (m_onKeyDown != nullptr)
				m_onKeyDown(events.key.keysym.sym);

			break;

		case SDL_KEYUP:
			keysStates[SDL_GetKeyFromScancode(events.key.keysym.scancode)] = { false, true, false };
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (mouseButtonsStates[(int)events.button.button].isHeld == false) {
				mouseButtonsStates[(int)events.button.button] = { true, false, false };
				mousePos = { (float)events.button.x, (float)events.button.y };
			}
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonsStates[(int)events.button.button] = { false, true, false };
			break;
		case SDL_MOUSEMOTION:
			mousePos = { (float)events.motion.x, (float)events.motion.y };
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			if (m_onFocusLost != nullptr)
				m_onFocusLost();
		}


	}
	return true;
}
