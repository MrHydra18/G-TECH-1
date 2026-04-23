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
		}


	}
	return true;
}