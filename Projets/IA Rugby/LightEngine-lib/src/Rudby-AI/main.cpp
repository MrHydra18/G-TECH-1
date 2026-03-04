#include "RugbyScene.h"
#include "GameManager.h"

#include <fstream>
#include <sstream>
#include <string>

int main()
{

	// default
	unsigned int width = 1280;
	unsigned int height = 720;
	int fps = 60;
	std::string title = "RugbyGame";
	sf::Color color(25, 72, 140);

	std::ifstream file("../../../res/Settings.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key;
			iss >> key;

			if (key == "width:") iss >> width;
			else if (key == "height:") iss >> height;
			else if (key == "fps:") iss >> fps;
			else if (key == "title:") std::getline(iss >> std::ws, title);
			else if (key == "color:") {
				int r, g, b;
				iss >> r >> g >> b;
				color = sf::Color(r, g, b);
			}
		}
	}

	GameManager* hinstance = GameManager::Get();

	hinstance->CreateWindow(width, height, title.c_str(), fps, color);

	hinstance->LaunchScene<RugbyScene>();

	return 0;
}
