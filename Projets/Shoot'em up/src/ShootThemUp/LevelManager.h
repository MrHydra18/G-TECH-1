#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>



struct LevelData {
	size_t columns = 0;
	size_t rows = 0;
	size_t time;
	std::vector<int> Data1D;

	int get(size_t row, size_t col) {
		

		if (row > rows || col >= columns) {
			return -1;
		}
		size_t index = row * columns + col;
		return Data1D[index];
	}
};

class LevelManager {

private:

	std::map<std::string, LevelData> levelsDatas;
public:

	static LevelManager& getInstance() {
		static LevelManager instance;
		return instance;
	}



	std::vector<std::string> getLevelsName() {
		std::vector<std::string> result;

		for (const auto& entry : std::filesystem::directory_iterator("../../res/levelDatas")){
			if (entry.is_regular_file()){
				if (entry.path().extension() == ".txt") {
					result.push_back(entry.path().filename().string());
				}
			}
		}
		return result;
	}

	LevelData* getLevelData(std::string levelName) {
		if (levelsDatas.find(levelName) != levelsDatas.end())
			return &levelsDatas[levelName];
		LevelData level;


		std::string fullPath = "../../res/levelDatas/" + levelName;
		std::ifstream file(fullPath);

		if (!file.is_open()) {
			std::cerr << "Error while opening .txt file at: " << fullPath << "\n";
			return nullptr;
		}

		level.time = 60000;

		std::string line;
		while (std::getline(file, line)) {
			level.rows++;
			if (level.columns == 0)
				level.columns = line.length();

			for (size_t i = 0; i < line.length(); i++) {
				switch (line[i])
				{
				case 'E': // Alan
					level.Data1D.push_back(1);
					break;
				case 'B': // BonBon
					level.Data1D.push_back(2);
					break;
				case 'L': // Lips
					level.Data1D.push_back(3);
					break;
				case 'M': // Mickael
					level.Data1D.push_back(7);
					break;
				default:
					level.Data1D.push_back(0);
					break;
				}
			}
			for (size_t i = 0; i < level.columns - line.length(); i++)
				level.Data1D.push_back(0);
		}
		levelsDatas[levelName] = level;
		return &levelsDatas[levelName];
	}
};