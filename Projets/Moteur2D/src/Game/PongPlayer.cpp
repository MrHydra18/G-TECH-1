#include "PongPlayer.h"
#include "Lib2D/InputManager.h"

void PongPlayer::init(Vector2f Pos, Vector2f Direction, const char* path)
{
	Position = Pos;
	sprite = new Sprite(Pos.GetX(), Pos.GetY(), path); //define sprite
	sprite->SetDirection(Direction.GetX(), Direction.GetY());
}

void PongPlayer::Draw(Window* win)
{
	sprite->Draw(win);
}

void PongPlayer::Update()
{
	if (InputManager::GetInstance()->IsKeyHeld(SDLK_z))
		sprite->Move(0, -1, 5);
	if (InputManager::GetInstance()->IsKeyHeld(SDLK_s))
		sprite->Move(0, 1, 5);
}

void PongPlayer::ChangeColor(Window* win)
{
	sprite->ChangeColor(win);
}

void PongPlayer::Delet()
{
	sprite->Delet();
	delete sprite;
	sprite = nullptr;
}
