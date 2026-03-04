#include "Scene3.h"
#include "Game/PongPlayer.h"
#include "Game/PongPlayer2.h"
#include "Game/Circle.h"

Scene3::Scene3(const char* name, float w_Height, float W_Width) : Scene(name)
{
	const char* path = "../../src/Game/Barre_pong.png";
	const char* pathCircle = "../../src/Game/BalleBlanche.png";

	NewEntity<PongPlayer>()->init({ 100,w_Height / 3 }, { 1,1 }, path);
	NewEntity<PongPlayer2>()->init({ (W_Width - 100),w_Height / 3 }, { 1,1 }, path);

	NewEntity<Circle>()->Init({ W_Width / 2, w_Height / 2 }, { srand(-1, 1), srand(-1, 1) }, pathCircle);
}

float Scene3::srand(int min, int max)
{
	float r = min + (rand() % (max - min + 1));
	if (r == 0)
		return 1;

	return r;
}
