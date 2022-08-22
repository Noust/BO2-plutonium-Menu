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
	char pad_0030[384]; //0x0030
	int32_t Team1; //0x01B0
	char pad_0380[40]; //0x0380
}; //Size: 0x03A8



Entity* ents[255];
Entity* entsptr;
Entity* local;
DWORD localAddr;

__declspec(naked) void GetEnts() {
	__asm {
		mov[entsptr], eax
		movss xmm2, [eax + 0x04]
		jmp[jmpback]
	}
}

__declspec(naked) void GetLocal() {
	__asm {
		mov[localAddr], ebx
		subss xmm0, [ebx + 0x04]
		jmp[jmpback1]
	}
}