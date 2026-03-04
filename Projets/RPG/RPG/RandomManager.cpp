#include "RandomManager.h"
#include <cstdlib> 
#include <ctime> 

int RandomManager::GenerateRandomNumber(int min, int max)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
    return min + rand() % (max + 1 - min);
}