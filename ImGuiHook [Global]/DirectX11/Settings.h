#pragma once
#include "include.h"

class settings {
public:
	int MenuWindow = 0;
	bool ESP = false;
	ImColor EnemyBoxColor = { 255,255,255 };
	ImColor PlayerBoxColor = { 255,255,255 };
	int bocthickness = 0;
	float boxWidth = 0.5f;
	float EspDistance = 200.0f;
	bool Aimbot = false;
}UserSettings;