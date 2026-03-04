#pragma once
#include "Entity.h"
#include "Lib2D/Sprite.h"

class PongPlayer : public Entity
{
protected:
	Sprite* sprite;
public:
	PongPlayer() : Entity(0, 0) {}
	void init(Vector2f Pos, Vector2f Direction, const char* path);
	void Draw(Window*) override;
	void Update() override;
	void Delet() override;
	void ChangeColor(Window* win) override;
};

