#include "PongPlayer2.h"
#include "Lib2D/InputManager.h"

void PongPlayer2::init(Vector2f Pos, Vector2f Direction, const char* path)
{
	Position = Pos;
	sprite = new Sprite(Pos.GetX(), Pos.GetY(), path); //define sprite
	sprite->SetDirection(Direction.GetX(), Direction.GetY());
}

void PongPlayer2::Draw(Window* win)
{
	sprite->Draw(win);
}

void PongPlayer2::Update()
{
	if (InputManager::GetInstance()->IsKeyHeld(SDLK_UP))
		sprite->Move(0, -1, 5);
	if (InputManager::GetInstance()->IsKeyHeld(SDLK_DOWN))
		sprite->Move(0, 1, 5);
}

void PongPlayer2::ChangeColor(Window* win)
{
	sprite->ChangeColor(win);
}

void PongPlayer2::Delet()
{
	sprite->Delet();
	delete sprite;
	sprite = nullptr;
}
