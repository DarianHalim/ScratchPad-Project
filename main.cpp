#include <iostream>
#include "raylib.h"
#include <vector>
#include <stack>

// for camera
#include "rlgl.h"
#include "raymath.h"

// Set Up

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

// Stroe chalk history for undo
stack<vector<Vector2>> undoStack;

void saveToUndoStack()
{
    undoStack.push(circlesPositions);
}

void clearUndoStack()
{
    while (!undoStack.empty())
    {
        undoStack.pop();
    }
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Resizable Windows
    InitWindow(screenWidth, screenHeight, "My ScratchPad (Don't Forget To Screenshot Before Exiting)");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    bool drawingChanged = false;
    bool erasingChanged = false;

    // Main game loop
    while (WindowShouldClose() == false)
    {
        // Event Handling:  Mouse Drag, Erasing, Drawing, Collision With Border and Cuve Posisi

        // calcualte mouse coor position
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // Mouse Drag
        cubeX = mouseWorldPos.x - cubeHeight / 2; // cube width 20/2
        cubeY = mouseWorldPos.y - cubeWidth / 2;  // cube height 40/2

        // Camera Zoom In MouseWheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get world point under mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // set offset position for mouse
            camera.offset = GetMousePosition();

            // set target for camera to map world space point
            camera.target = mouseWorldPos;

            // zoom increment number
            float scaleFactor = 1.0f + (0.25f * fabs(wheel)); // fabs from CMath
            if (wheel < 0)
                scaleFactor = 1.0f / scaleFactor;
            camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
        }

        // Mouse Draw
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {

            if (!drawingChanged)
            {
                saveToUndoStack(); // Save state before making changes
                drawingChanged = true;
            }

            brushPos = mouseWorldPos;             // Update brush position
            circlesPositions.push_back(brushPos); // Store the position of the circle
        }
        else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            drawingChanged = false; // Stop drawing
        }

        // Mouse Erase
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if (!erasingChanged)
            {
                saveToUndoStack(); // Save state before making changes
                erasingChanged = true;
            }

            eraserPos = mouseWorldPos;

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

        // Undo
      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z))
        {
            if (!undoStack.empty())
            {
                circlesPositions = undoStack.top();
                undoStack.pop();
            }
        }

        // Drawing Background and Cube
        BeginDrawing();
        BeginMode2D(camera);
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