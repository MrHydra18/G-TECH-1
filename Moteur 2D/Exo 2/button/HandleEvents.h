#pragma once 
#include<SDL3/SDL.h>

class HandleEvents
{
private:
	
	bool isOpen = true;
	bool mousePress = false;
	float mouseX = 0;
	float mouseY = 0;

public:



	HandleEvents() = default;

	float GetClickX() { return mouseX; }
	float GetClickY() { return mouseY;}
	bool MousePress() { return mousePress; }
	void Events();
};