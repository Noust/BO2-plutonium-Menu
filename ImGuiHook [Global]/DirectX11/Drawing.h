#pragma once
#include "include.h"
void DrawLine(Vector2 pos1, Vector2 pos2, ImColor color, int thickness);
void DrawRect(Vector2 pos, float heigth, float width, int thickness, ImColor color);
void DrawChar(Vector2 pos, const char* text, ImColor color, float divide);
void Draw3dBoxes(int index, ImColor color, int thickness);
void DrawFilledRect(Vector2 pos, float heigth, float Width, ImColor color);
void DrawCircle(Vector2 pos, ImColor color, float radius, int thickness);