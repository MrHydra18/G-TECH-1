#pragma once
#include "Entity.h"
#include "Lib2D/Sprite.h"

class Window;

class TestRectangle : public Entity
{
private:
	Sprite* sprite; // if a class need a sprit, include like this, and define in init

public:
	TestRectangle() : Entity(0,0) {}
	void init(Vector2f Pos, Vector2f Direction, const char* path);
	void Draw(Window*) override;
	void Update() override;
	void Delet() override;

	void ChangeColor(Window* win) override;
};

