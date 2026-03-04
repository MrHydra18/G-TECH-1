#pragma once
#include "Entity.h"
#include "Lib2D/Sprite.h"

class Circle : public Entity
{
	Sprite* sprite;

public:
	Circle() : Entity(0,0) {}
	void Init(Vector2f Pos, Vector2f direction, const char* path);
	void Draw(Window*) override;
	void Update() override;
	void Delet() override;
	void ChangeColor(Window* win) override;
};

