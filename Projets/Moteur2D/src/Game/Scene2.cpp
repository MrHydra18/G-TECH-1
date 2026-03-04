#include "Scene2.h"
#include "Game/CDAnimation.h"


Scene2::Scene2(const char* name) : Scene(name)
{
	const char* path = "../../src/Game/DVDLogo.png";
	NewEntity<CDAnimation>()->Init({ 100,100 }, { 1,1 }, path);
	
}

