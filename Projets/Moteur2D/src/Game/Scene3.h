#pragma once
#include "Engine2D\Scene.h"

class PongPlayer;
class PongPlayer2;
class Circle;


class Scene3 : public Scene
{

private:
	PongPlayer* player1;
	PongPlayer2* player2;
	Circle* ball;


public:
	Scene3(const char* name, float w_Height, float W_Width);
	float srand(int min, int max);	
};

