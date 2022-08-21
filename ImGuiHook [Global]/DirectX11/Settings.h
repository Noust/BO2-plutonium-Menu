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

	bool DistanceEsp = false;
	ImColor EnemyDistColor = { 255,0,0 };
	ImColor PlayerDistColor = { 0,0,255 };

	float EspDistance = 50.0f;
	bool Aimbot = false;
}UserSettings;