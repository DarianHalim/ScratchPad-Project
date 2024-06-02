#include <iostream>
#include "raylib.h"
#include <vector>
//Set Up

using namespace std;

const int screenHeight = 850;
const int screenWidth = 1500;

// cube creation
int cubeX = 400;
int cubeY = 400;
int cubeHeight = 25;
int cubeWidth = 25;

int cubeSpeedX = 10;
int cubeSpeedY = 10;

bool isActive = false;

Color greenBG = {20, 160, 133, 255};

// chalk creation
Color chalkColor = WHITE;
int chalkSize = 10;

// Stores the drawn brush
Vector2 brushPos = {-100, -100};
vector<Vector2> circlesPositions;

// Stores Erasing Brush
Vector2 eraserPos = {-100, -100};
vector<Vector2> eraserPositions;

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizable Windows
    InitWindow(screenWidth, screenHeight, "My ScratchPad (Don't Forget To Screenshot Before Exiting)");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        // Sync with current windows size
        int currentScreenWidth = GetScreenWidth();
        int currentScreenHeight = GetScreenHeight();

        // Event Handling:  Mouse Drag, Erasing, Drawing, Collision With Border
        // Mouse Drag
        cubeX = GetMouseX() - cubeHeight / 2; // cube width 20/2
        cubeY = GetMouseY() - cubeWidth / 2;  // cube height 40/2

        // Mouse Draw
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            isActive = true;
            brushPos = {GetMousePosition()};      // Update brush position
            circlesPositions.push_back(brushPos); // Store the position of the circle
        }
        else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            isActive = false; // Stop drawing
        }

        // Mouse Erase
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            isActive = true;
            eraserPos = {GetMousePosition()};

            // Check if eraser position overlaps with any chalk marks and remove them, otherwise brush cant draw where eraser has been used
            for (int i = 0; i < circlesPositions.size(); i++)
            {
                // Adjust the radius as needed
                if (CheckCollisionPointCircle(eraserPos, circlesPositions[i], 10))
                {
                    // Adjusts the loop index after erasing an element
                    circlesPositions.erase(circlesPositions.begin() + i);
                    i--;
                }
            }
        }
        else if (IsMouseButtonUp(MOUSE_BUTTON_RIGHT))
        {
            isActive = false; // Stop Erasing
        }

        // Cube Collision Effect
        if (cubeX >= currentScreenWidth - cubeWidth) // Right side Collision
        {
            cubeX = currentScreenWidth - cubeWidth;
            cubeSpeedX = -cubeSpeedX;
        }
        else if (cubeX <= 0) // Left side Collision
        {
            cubeX = 0;
            cubeSpeedX = -cubeSpeedX;
        }

        if (cubeY >= currentScreenHeight - cubeHeight) // Bottom side Collision
        {
            cubeY = currentScreenHeight - cubeHeight;
            cubeSpeedY = -cubeSpeedY;
        }
        else if (cubeY <= 0) // Top side Collision
        {
            cubeY = 0;
            cubeSpeedY = -cubeSpeedY;
        }

        // Drawing Background and Cube
        BeginDrawing();
        ClearBackground(greenBG);
        DrawRectangle(cubeX, cubeY, cubeHeight, cubeWidth, WHITE);

        // Draw Stored Elements functions kept away from function mouseButton, otherwise dissapear after isActive = false;
        //  Draw all stored erasers
        for (const auto &position : eraserPositions)
        {
            DrawCircleV(position, 20, greenBG);
        }

        // Draw all stored circles (chalk effect)
        for (const auto &position : circlesPositions)
        {
            DrawCircleV(position, 10, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
