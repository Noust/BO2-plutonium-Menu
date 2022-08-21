#pragma once
#include "include.h"
DWORD HookAddr;
DWORD jmpback;

class Entity
{
public:
	char pad_0000[4]; //0x0000
	int32_t IsDead; //0x0004
	char pad_0008[32]; //0x0008
	Vector3 Pos; //0x0028
	Vector3 Velocity; //0x0034
	char pad_0040[20]; //0x0040
}; //Size: 0x0054

Entity* ents[255];
Entity* entsptr;

__declspec(naked) void GetEnts() {
	__asm {
		mov[entsptr], eax
		movss xmm2, [eax + 0x04]
		movss[esp], xmm0
		movss xmm0, [eax + 0x08]
		jmp[jmpback]
	}
}