#define RAYGUI_IMPLEMENTATION

#include "include/raylib.h"
#include "include/raygui.h"
#include <time.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    int currentScreen = 0;
    int histogram[10];
    int i, j, temp;
    bool sorted = false;

    for (i = 0; i < 10; i++)
    {
        histogram[i] = GetRandomValue(10, 200);
    }

    SetTargetFPS(5);  // Lower the FPS to slow down the animations
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(GRAY);

        if (currentScreen == 0)
        {
            if (GuiButton((Rectangle){ 320, 200, 150, 50 }, "Go to next screen")) 
            {
                currentScreen = 1;
                for (i = 0; i < 10; i++)
                {
                    histogram[i] = GetRandomValue(10, 200);
                }
            }
            if (GuiButton((Rectangle){ 320, 260, 150, 50 }, "Exit")) CloseWindow();
        }
        else if (currentScreen == 1)
        {
            if (GuiButton((Rectangle){ 320, 200, 150, 50 }, "Go to previous screen")) currentScreen = 0;

            if (!sorted)
            {
                for (i = 0; i < 10; i++)
                {
                    for (j = 0; j < 10 - i - 1; j++)
                    {
                        if (histogram[j] > histogram[j + 1])
                        {
                            temp = histogram[j];
                            histogram[j] = histogram[j + 1];
                            histogram[j + 1] = temp;
                            sorted = true;
                            break;
                        }
                    }
                    if (sorted) break;
                }
            }

            for (j = 0; j < 10; j++)
            {
                if (sorted && j == i)
                {
                    DrawRectangle(70 + 70 * j, 450 - histogram[j], 50, histogram[j], RED);
                }
                else
                {
                    DrawRectangle(70 + 70 * j, 450 - histogram[j], 50, histogram[j], DARKGRAY);
                }
            }

            if (sorted) sorted = false;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}