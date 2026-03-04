#include "Circle.h"
#include "Lib2D/Window.h"
#include<iostream>
#include "PongPlayer.h"
#include "PongPlayer2.h"

void Circle::Init(Vector2f Pos, Vector2f Direction, const char* path)
{
	Position = Pos;
	sprite = new Sprite(Pos.GetX(), Pos.GetY(), path); 
	sprite->SetDirection(Direction.GetX(), Direction.GetY());
}

void Circle::Draw(Window* win)
{
	sprite->Draw(win);
}

void Circle::Update()
{

	sprite->Move(sprite->GetDirectionX(), sprite->GetDirectionY(), 3);
}

void Circle::ChangeColor(Window* win)
{
	sprite->ChangeColor(win);
}

void Circle::Delet()
{
	sprite->Delet();
	delete sprite;
	sprite = nullptr;
}
