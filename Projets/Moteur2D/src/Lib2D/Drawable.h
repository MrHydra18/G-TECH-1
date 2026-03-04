#pragma once

class Window;

class Drawable
{
public:
	virtual void Draw(Window*) = 0;
	virtual void ChangeColor(Window*) = 0;
};
