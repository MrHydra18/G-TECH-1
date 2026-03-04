#include <iostream>
#include "main.h"
#include "Engine2D/Application.h"

int main(int argc, char* argv[])
{
	bool isRunning = true;

	std::cout << "Hello, World!\n";
	Application::GetInstance()->Start();
	while(isRunning)
		Application::GetInstance()->Loop(&isRunning);
	
	return 0;
}