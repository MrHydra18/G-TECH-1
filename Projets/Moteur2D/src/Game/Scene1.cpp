#include "Scene1.h"
#include "TestRectangle.h"

Scene1::Scene1(const char* name) : Scene(name)
{
	const char* path = "../../src/Game/image2_2.png";
	int NbEntity = srand(15, 65);

	for (int i = 0; i <= NbEntity; i++)
		NewEntity<TestRectangle>()->init({ srand(0, 960),srand(0, 480) }, { srand(-1, 1), srand(-1, 1) }, path);
}

float Scene1::srand(int min, int max)
{
	float r = min + (rand() % (max - min + 1));
	if (r == 0)
		return 1;

	return r;
}
