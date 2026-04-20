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
		}
	}
	return true;
}