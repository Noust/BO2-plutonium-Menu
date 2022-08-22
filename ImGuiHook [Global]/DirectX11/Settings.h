#pragma once
#include "include.h"

class settings {
public:

	int MenuWindow = 0;

	bool ESP = false;
	ImColor EnemyBoxColor = { 255,0,0 };
	ImColor PlayerBoxColor = { 0,0,255 };
	int bocthickness = 0;
	float boxWidth = 0.5f;

	bool FilledESP = false;
	ImColor EnemyFilledColor = { 0,0,0,80 };
	ImColor PlayerFilledColor = { 0,0,0,80 };
	float FilledWidth = 0.5f;

	bool SnapLine = false;
	int ThicknessSnap = 0;
	ImColor EnemySnapColor = { 255,0,0 };
	ImColor PlayerSnapColor = { 0, 0, 255 };
	bool top = false;
	bool bottom = true;

	bool ESP3d = false;
	ImColor Enemy3dColor = { 255,0,0 };
	ImColor Player3dColor = { 0,0,255 };
	int box3dthickness = 0;

	bool DistanceEsp = false;
	ImColor EnemyDistColor = { 255,0,0 };
	ImColor PlayerDistColor = { 0,0,255 };

	float EspDistance = 50.0f;
	bool Aimbot = false;
	int AimbotFov = 1920;
	bool ShowFov = false;
	int FovThickness = 0;
	ImColor FovColor = { 255,255,255 };
	bool ShowTarget = false;
	int TargetThickness = 0;
	ImColor TargetColor = { 255,0,0 };
	int AimbotSleep = 2;
}UserSettings;