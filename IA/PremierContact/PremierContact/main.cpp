#include"Gun.h"
#include"Timer.h"
#include<conio.h>

int main()
{
	Gun gun = Gun(10, 10, 1000);
    Timer timer;

	bool isPlaying = true;


    while (isPlaying)
    {
        std::cout << "Press S to Shoot, R to reload and Q to quit.\n";
        float start = timer.Start();
        if (_kbhit() == 1)
        {
            int key = _getch();

            if (key == 114 || key == 94)
                gun.Reload();

            if (key == 115 || key == 95)
                gun.Shoot();

            if (key == 113 || key == 81)
                isPlaying = false;
        }

        float end = timer.End();
        float deltaTime = (end - start) / 1000.0f;
        gun.Update(deltaTime);
    }

	return 0;
}