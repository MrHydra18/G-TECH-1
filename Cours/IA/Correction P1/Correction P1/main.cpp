#include <chrono>
#include <conio.h>
#include <iostream>

#include "Gun.h"

#define FPS 60
#define TARGET_DT_NS 1000000000 / FPS

bool HandleInput(Gun& gun)
{
	if (_kbhit() == 0)
		return false;

	char input = _getch();

	switch (input)
	{
	case 's':
	{
		gun.Shoot();
		break;
	}
	case 'r':
	{
		gun.Reload();
		break;
	}
	case 'q':
	{
		return true;
		break;
	}
	}

	return false;
}

using Clock = std::chrono::steady_clock;

float GetCapElapsed(Clock::time_point& start) 
{
	while (true) 
	{
		auto duration = Clock::now() - start;
	
		if (duration.count() >= TARGET_DT_NS)
			return duration.count() / 1000000000.f;
	}
}

int main()
{
	Gun gun;

	float dt = 0;

	while (true)
	{
		auto start = Clock::now();

		bool quit = HandleInput(gun);
		if (quit)
			break;

		gun.Update(dt);

		dt = GetCapElapsed(start);
	}

	return 0;
}