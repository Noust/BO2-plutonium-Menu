#pragma once
#include "include.h"

class settings {
public:

	int MenuWindow = 0;

	bool ESP = false;
	ImColor EnemyBoxColor = { 255,0,0 };
	int bocthickness = 0;
	float boxWidth = 0.5f;

	bool FilledESP = false;
	ImColor EnemyFilledColor = { 0,0,0,80 };
	float FilledWidth = 0.5f;

	bool SnapLine = false;
	int ThicknessSnap = 0;
	ImColor EnemySnapColor = { 255,0,0 };
	bool top = false;
	bool bottom = true;

	bool ESP3d = false;
	ImColor Enemy3dColor = { 255,0,0 };
	int box3dthickness = 0;

	bool DistanceEsp = false;
	ImColor EnemyDistColor = { 255,0,0 };

	float EspDistance = 50.0f;
	bool Aimbot = false;
	bool HeadTarget = false;
	bool StomachTarget = true;
	int AimbotFov = 1920;
	bool ShowFov = false;
	int FovThickness = 0;
	ImColor FovColor = { 255,255,255 };
	bool ShowTarget = false;
	int TargetThickness = 0;
	ImColor TargetColor = { 255,0,0 };
	bool FilledCircle = false;
	ImColor FilledCircleColor = { 0,0,0,80 };
	int AimbotSleep = 1;

	bool SAimbot = false;
	bool SHeadTarget = false;
	bool SStomachTarget = true;
	int SAimbotFov = 1920;
	bool SShowFov = false;
	int SFovThickness = 0;
	ImColor SFovColor = { 255,255,255 };
	bool SShowTarget = false;
	int STargetThickness = 0;
	ImColor STargetColor = { 255,0,0 };
	bool SFilledCircle = false;
	ImColor SFilledCircleColor = { 0,0,0,80 };

	bool nightmode = false;
	ImColor FilledCircleColorBlack = { 0,0,0,90 };
	bool fullbrigthness = false;
	ImColor FilledCircleColorWhite = { 255,255,255,80 };
}UserSettings;