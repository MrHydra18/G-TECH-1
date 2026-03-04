#pragma once
#include"InputManager.h"

#define W_WIDTH 960
#define W_HEIGHT 480
#define Window_Pos_X 5
#define Window_Pos_Y 25
#define TARGET_FPS 60
#define TARGET_ELAPSED 1000/TARGET_FPS

class Drawable;

class Window
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Window* window;
	bool WindowOpen;

	Uint64 TotalElapsed;
	int FramCount = 0;

public:

	Window() {}

	void Init();
	void CountTime(Uint64 DeltaTime);
	void DestroyWindow();

	bool IsWindowOpen() const { return WindowOpen; }
	void WindowManager();
	void UpdateWindow();
	void Draw(Drawable* d);

	friend class Sprite;
};

