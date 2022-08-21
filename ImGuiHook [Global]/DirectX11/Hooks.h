#pragma once
#include "include.h"
bool hooked = false;
DWORD HookAddr;
DWORD jmpback;

class Entity
{
public:
	Vector3 Pos; //0x0000
	char pad_000C[60]; //0x000C
}; //Size: 0x0048


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