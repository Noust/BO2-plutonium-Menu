#pragma once
#include "include.h"

void Patch(BYTE* addr, BYTE* bytes, unsigned int size);
bool Hook(void* src, void* dst, int len);
MODULEINFO GetModuleInfo(char* szModule);
DWORD64 FindPattern(char* module, char* pattern, char* mask);