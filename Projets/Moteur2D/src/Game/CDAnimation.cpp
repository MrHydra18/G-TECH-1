#include "CDAnimation.h"

void CDAnimation::Init(Vector2f Pos, Vector2f Direction, const char* path)
{
	Position = Pos;
	sprite = new Sprite(Pos.GetX(), Pos.GetY(), path);
	sprite->SetDirection(Direction.GetX(), Direction.GetY());
}

void CDAnimation::Draw(Window* win)
{
	Win = win;
	sprite->Draw(win);
}

void CDAnimation::ChangeColor(Window* win)
{
	sprite->ChangeColor(win);
}

void CDAnimation::Update()
{	
	if (sprite->Move(sprite->GetDirectionX(), sprite->GetDirectionY(), 3))
		sprite->ChangeColor(Win);
}

