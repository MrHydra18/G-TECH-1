#include "TestRectangle.h"

void TestRectangle::init(Vector2f Pos, Vector2f Direction, const char* path)
{
	Position = Pos;
	sprite = new Sprite(Pos.GetX(), Pos.GetY(), path); //define sprite
	sprite->SetDirection(Direction.GetX(), Direction.GetY());
}

void TestRectangle::Draw(Window* win)
{
	sprite->Draw(win);
}

void TestRectangle::Update()
{
	sprite->Move(sprite->GetDirectionX(), sprite->GetDirectionY(), 3);
}

void TestRectangle::ChangeColor(Window* win)
{
	sprite->ChangeColor(win);
}

void TestRectangle::Delet()
{
	sprite->Delet();
	delete sprite;
	sprite = nullptr;
}

