#pragma once
#include "include.h"
bool hooked = false;
DWORD HookAddr;
DWORD jmpback;
DWORD jmpback1;
DWORD HookAddr1;

class Entity
{
public:
	Vector3 Pos; //0x0000
	char pad_000C[32]; //0x000C
	float Check1; //0x002C
	char pad_0034[20]; //0x0034
}; //Size: 0x0048


Entity* ents[255];
Entity* entsptr;
Entity* local;
DWORD localAddr;

__declspec(naked) void GetEnts() {
	__asm {
		mov[entsptr], eax
		movss xmm2, [eax + 0x04]
		movss[esp], xmm0
		movss xmm0, [eax + 0x08]
		jmp[jmpback]
	}
}

__declspec(naked) void GetLocal() {
	__asm {
		mov[localAddr], ebx
		subss xmm0, [ebx + 0x04]
		movss[esp + 0x18], xmm0
		movss xmm0, [edi + 0x34]
		jmp[jmpback1]
	}
}