#include "include.h"
bool WorldToScreen(Vector3 pos, Vector2& posscreen, float matrix[16]) {
	Vector4 CPC;
	CPC.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	CPC.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	CPC.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	CPC.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (CPC.w < 0.1f)
		return false;

	Vector3 N;
	N.x = CPC.x / CPC.w;
	N.y = CPC.y / CPC.w;
	N.z = CPC.z / CPC.w;

	posscreen.x = (1920 / 2 * N.x) + (N.x + 1920 / 2);
	posscreen.y = -(1080 / 2 * N.y) + (N.y + 1080 / 2);
	return true;
}
Vector2 PosToScreen(Vector3 pos) {
	float matrix[16];
	Vector2 Posscreen;
	memcpy(&matrix, (PBYTE*)((DWORD)GetModuleHandleA("plutonium-bootstrapper-win32.exe") + 0x301D4C0), sizeof(matrix));
	if (WorldToScreen(pos, Posscreen, matrix)) {
		return Posscreen;
	}
	return { -1,-1 };
}