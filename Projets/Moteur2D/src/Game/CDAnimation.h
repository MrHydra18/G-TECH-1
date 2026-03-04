#pragma once
#include "Entity.h"
#include "Lib2D/Sprite.h"

class CDAnimation : public Entity
{
private:
	Sprite* sprite;
	Window* Win;

public:
	CDAnimation() : Entity(0, 0) {}
	void Init(Vector2f Pos, Vector2f Direction, const char* path);
	void Draw(Window*) override;
	void Update() override;

	void ChangeColor(Window* win) override;
};

