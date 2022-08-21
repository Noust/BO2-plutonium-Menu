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
}UserSettings;