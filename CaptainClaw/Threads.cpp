#include <Windows.h>
#include <thread>
#include "Render.h"
extern int level;
extern Thornsinv Thorn[100];
extern int gameOverFlag, xx, yy;



DWORD WINAPI killThread(LPVOID lpParameter)
{
    while (true)
    {
        if (level == 2)
        {
            int num = rand() % 90;
            while (Thorn[num].y >= 480)
            {
                Thorn[num].y--;
                //Thorn collision
                if (Thorn[num].y - 55 <= yy + 75 && Thorn[num].x + 16 >= xx-16 && Thorn[num].x + 16 <= xx+16) {
                    gameOverFlag = 1;
                    Sleep(1000);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        }
    }
}

HANDLE hThread = CreateThread(NULL, 0, killThread, NULL, 0, NULL);