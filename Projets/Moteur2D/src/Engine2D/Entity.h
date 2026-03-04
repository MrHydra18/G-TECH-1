#pragma once
#include "Lib2D/Transformable.h"
#include "Lib2D/Drawable.h"

class Entity : public Transformable, public Drawable
{
	// une nouvelle class erite de entity et doit redefinire chaque virtual

public:
	Entity(float PosX, float PosY) : Transformable(PosX, PosY) {}
	virtual void Update();
	virtual void Draw(Window* win);
	virtual void Delet();

	void ChangeColor(Window* win) override;
};

