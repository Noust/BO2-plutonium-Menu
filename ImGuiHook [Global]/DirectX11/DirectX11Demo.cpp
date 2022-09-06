#include "include.h"

bool ShowMenu = false;
bool ImGui_Initialised = false;
bool alreadyther = false;
char Distances[50];
Vector2 SnapLineBegin = { 1920 / 2,1080 };
int closest;
Vector2 Diference;
Vector2 Middle = { 1920 / 2, 1080 / 2 };
Vector2 siii;
Vector2 AimbottargetScreen;

void Colors() {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(11, 12);
	style.FramePadding = ImVec2(14, 3);
	style.ItemSpacing = ImVec2(8, 7);
	style.ItemInnerSpacing = ImVec2(12, 6);
	style.WindowRounding = 7.0f;
	style.ChildRounding = 7.0f;
	style.FrameRounding = 12.0f;
	style.ScrollbarRounding = 12.0f;
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 14.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;
	style.WindowMinSize = ImVec2(547, 347);
	style.WindowTitleAlign = { 0.5,0.5f };

	style.Colors[ImGuiCol_TitleBg] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_CheckMark] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_Button] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_Header] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_HeaderActive] = ImColor(87, 35, 100);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(87, 35, 100);
}
//Address of signature = plutonium - bootstrapper - win32.exe + 0x0015F6AB
//"\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xA1", "xx???xx???xx???xx???xx????xx???x"
//"F3 0F ? ? ? F3 0F ? ? ? F3 0F ? ? ? F3 0F ? ? ? F3 0F ? ? ? ? F3 0F ? ? ? A1"

//Address of signature = plutonium - bootstrapper - win32.exe + 0x003953E5
//"\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F", "xx???xx????xx???xx???xx????xx??????xx????xx??????xx"
//"F3 0F ? ? ? F3 0F ? ? ? ? F3 0F ? ? ? F3 0F ? ? ? F3 0F ? ? ? ? F3 0F ? ? ? ? ? ? F3 0F ? ? ? ? F3 0F ? ? ? ? ? ? F3 0F"
int FindClosestEnemy() {
	int closestentity = 0;
	float Finish;
	float Closest = FLT_MAX;
	for (int i = 0; i < 254; i++) {
		if (ents[i] != 0 && local != 0) {
			float Distance = local->Pos.Distance(ents[i]->Pos) / 100; if (Distance > UserSettings.EspDistance || Distance < 0.9f) continue;
			float Check = ents[i]->Check1; if (Check == 0) continue;
			Vector3 pos = ents[i]->Pos;
			pos.z += 57;
			Vector2 Posscreen = PosToScreen(pos);
			Finish = Posscreen.Distance({ 1920 / 2, 1080 / 2 });
			if (Finish < Closest) {
				Closest = Finish;
				closestentity = i;
			}
		}
	}
	return closestentity;
}

DWORD WINAPI InitiateHooks(HMODULE hMod) {
	while (!hooked) {
		char modulename[] = "plutonium-bootstrapper-win32.exe";
		char sig[] = "\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xA1";
		char mask[] = "xx???xx???xx???xx???xx????xx???x";
		char sig1[] = "\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F";
		char mask1[] = "xx???xx????xx???xx???xx????xx??????xx????xx??????xx";
		HookAddr = FindPattern(modulename, sig, mask);
		HookAddr1 = FindPattern(modulename, sig1, mask1);
		int hooklength = 5;
		int hooklength1 = 5;
		jmpback = HookAddr + hooklength;
		jmpback1 = HookAddr1 + hooklength1;
		if (HookAddr != NULL && HookAddr1 != NULL) {
			Hook((void*)HookAddr, GetEnts, hooklength);
			Hook((void*)HookAddr1, GetLocal, hooklength1);
			hooked = true;
		}
	}
	while (!GetAsyncKeyState(VK_DELETE)) {
		if (UserSettings.Aimbot && !ShowMenu) {
			closest = FindClosestEnemy();
			if (ents[closest] != 0 && local != 0) {
				float Distance = local->Pos.Distance(ents[closest]->Pos) / 100;
				if (Distance < UserSettings.EspDistance && Distance > 0.9f && ents[closest]->Check1 != 0) {
					Vector3 pos = ents[closest]->Pos;
					if (UserSettings.HeadTarget)
						pos.z += 57;
					if (UserSettings.StomachTarget)
						pos.z += 40;
					AimbottargetScreen = PosToScreen(pos);
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}
void shoot() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 1920 / 2, 1080 / 2, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 1920 / 2, 1080 / 2, 0, 0);
}

DWORD WINAPI Aimbot(HMODULE hMod) {
	while (!GetAsyncKeyState(VK_DELETE)) {
		if (UserSettings.Aimbot && !ShowMenu) {
			if (GetAsyncKeyState(VK_XBUTTON2) & 1) {
				if (ents[closest] != 0 && local != 0) {
					float Distance = local->Pos.Distance(ents[closest]->Pos) / 100;
					if (Distance < UserSettings.EspDistance && Distance > 0.9f && ents[closest]->Check1 != 0) {
						if (AimbottargetScreen.Distance({ 1920 / 2, 1080 / 2 }) < UserSettings.AimbotFov) {
							SetCursorPos(AimbottargetScreen.x, AimbottargetScreen.y);
							Sleep(3);
							shoot();
							SetCursorPos(siii.x, siii.y);
						}
					}
				}
			}
			else {
				Diference = AimbottargetScreen.Dif(Middle);
				siii = Diference + Middle;
			}
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}

DWORD WINAPI SetEntities(HMODULE hMod) {
	while (!GetAsyncKeyState(VK_DELETE)) {
		alreadyther = false;
		for (int i = 0; i < 254; i++) {
			if (ents[i] == entsptr) {
				alreadyther = true;
				break;
			}
		}
		if (!alreadyther) {
			for (int i = 0; i < 254; i++) {
				if (ents[i] == 0) {
					ents[i] = entsptr;
					break;
				}
			}
		}
		if (localAddr != NULL)
			local = (Entity*)(localAddr);
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}

namespace Process {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	HMODULE Module;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}

namespace DirectX11Interface {
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(Process::WndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!ImGui_Initialised) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX11Interface::Device))){
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			DirectX11Interface::Device->GetImmediateContext(&DirectX11Interface::DeviceContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			pSwapChain->GetDesc(&Desc);
			WindowHwnd = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			DirectX11Interface::Device->CreateRenderTargetView(BackBuffer, NULL, &DirectX11Interface::RenderTargetView);
			BackBuffer->Release();

			ImGui_ImplWin32_Init(WindowHwnd);
			ImGui_ImplDX11_Init(DirectX11Interface::Device, DirectX11Interface::DeviceContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::GetIO().ImeWindowHandle = Process::Hwnd;
			Process::WndProc = (WNDPROC)SetWindowLongPtr(Process::Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			ImGui_Initialised = true;
		}
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) ShowMenu = !ShowMenu;
	Colors();
	ImGui_ImplDX11_NewFrame();//0044219A
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = ShowMenu;
	if (ShowMenu == true) {
		ImGui::Begin("Nova", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::BeginChild("##leftside", ImVec2(ImGui::GetContentRegionAvail().x, 49), true);
		if (ImGui::Button("Visuals", ImVec2(ImGui::GetWindowSize().x / 2.12f, 25))) {
			UserSettings.MenuWindow = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Weapon", ImVec2(ImGui::GetWindowSize().x / 2.12f, 25))) {
			UserSettings.MenuWindow = 1;
		}
		ImGui::EndChild();
		ImGui::BeginChild("##rigth", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		if (UserSettings.MenuWindow == 0) {
			ImGui::Checkbox("Snap Line Esp", &UserSettings.SnapLine);
			if (UserSettings.SnapLine) {
				ImGui::ColorEdit4("Snap Color", (float*)(&UserSettings.EnemySnapColor));
				ImGui::SliderInt("Snap thickness", &UserSettings.ThicknessSnap, 0, 10);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("Snap Line begin place");
				if (ImGui::Button("Bottom Center")) {
					SnapLineBegin = { 1920 / 2,1080 };
				}
				if (ImGui::Button("Center")) {
					SnapLineBegin = { 1920 / 2,1080 / 2 };
				}
				if (ImGui::Button("Top Center")) {
					SnapLineBegin = { 1920 / 2,0 };
				}
				if (ImGui::Button("Center Right")) {
					SnapLineBegin = { 1920,1080 / 2 };
				}
				if (ImGui::Button("Center Left")) {
					SnapLineBegin = { 0,1080 / 2 };
				}
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("Snap Line end place");
				if (ImGui::Button("Top")) {
					UserSettings.bottom = false;
					UserSettings.top = true;
				}
				if (ImGui::Button("Bottom")) {
					UserSettings.bottom = true;
					UserSettings.top = false;
				}
				ImGui::Separator();
			}
			ImGui::Checkbox("Box ESP", &UserSettings.ESP);
			if (UserSettings.ESP) {
				ImGui::ColorEdit4("Box Color", (float*)(&UserSettings.EnemyBoxColor));
				ImGui::SliderFloat("Box Width", &UserSettings.boxWidth, 0, 1);
				ImGui::SliderInt("Box Thickness", &UserSettings.bocthickness, 0, 10);
				ImGui::Separator();
			}
			ImGui::Checkbox("Distance ESP", &UserSettings.DistanceEsp);
			if (UserSettings.DistanceEsp) {
				ImGui::ColorEdit4("Distance Color", (float*)(&UserSettings.EnemyDistColor));
				ImGui::Separator();
			}
			ImGui::Checkbox("3D Box ESP", &UserSettings.ESP3d);
			if (UserSettings.ESP3d) {
				ImGui::ColorEdit4("3D Box Color", (float*)(&UserSettings.Enemy3dColor));
				ImGui::SliderInt("3D Box Thickness", &UserSettings.box3dthickness, 0, 10);
				ImGui::Separator();
			}
			ImGui::Checkbox("Filled Box ESP", &UserSettings.FilledESP);
			if (UserSettings.FilledESP) {
				ImGui::ColorEdit4("Filled Box Color", (float*)(&UserSettings.EnemyFilledColor));
				ImGui::SliderFloat("Filled Box Width", &UserSettings.FilledWidth, 0, 1);
				ImGui::Separator();
			}
			ImGui::Checkbox("Night Mode", &UserSettings.nightmode);
			if (UserSettings.nightmode) {
				UserSettings.fullbrigthness = false;
			}
			ImGui::Checkbox("Full Brightness", &UserSettings.fullbrigthness);
			if (UserSettings.fullbrigthness) {
				UserSettings.nightmode = false;
			}
			ImGui::SliderFloat("ESP Distance", &UserSettings.EspDistance, 1, 80);
		}
		if (UserSettings.MenuWindow == 1) {
			ImGui::Checkbox("Aimbot", &UserSettings.Aimbot);
			if (UserSettings.Aimbot) {
				ImGui::Text("Target");
				if (ImGui::Button("Head")) {
					UserSettings.HeadTarget = true;
					UserSettings.StomachTarget = false;
				}
				if (ImGui::Button("Stomach")) {
					UserSettings.HeadTarget = false;
					UserSettings.StomachTarget = true;
				}
				ImGui::Checkbox("Show Aimbot Fov", &UserSettings.ShowFov);
				if (UserSettings.ShowFov) {
					ImGui::SliderInt("Thickness Fov", &UserSettings.FovThickness, 0, 10);
					ImGui::ColorEdit4("Fov Color", (float*)(&UserSettings.FovColor));
					ImGui::Checkbox("Filled Circle", &UserSettings.FilledCircle);
					if (UserSettings.FilledCircle) {
						ImGui::ColorEdit4("Filled Circle Color", (float*)(&UserSettings.FilledCircleColor));
					}
				}
				ImGui::SliderInt("Aimbot Fov", &UserSettings.AimbotFov, 1, 1920);
				ImGui::Separator();
				ImGui::Checkbox("Show Target", &UserSettings.ShowTarget);
				if (UserSettings.ShowTarget)
				{
					ImGui::SliderInt("Thickness target line", &UserSettings.TargetThickness, 0, 10);
					ImGui::ColorEdit4("Target color", (float*)(&UserSettings.TargetColor));
					ImGui::Separator();
				}
				ImGui::SliderInt("Aimbot Sleep", &UserSettings.AimbotSleep, 1, 100);
				ImGui::Separator();
			}
		}
		if (UserSettings.MenuWindow == 2) {

		}
		ImGui::EndChild();
		ImGui::End();
	}
	if (hooked) {
		if (UserSettings.ESP || UserSettings.DistanceEsp || UserSettings.ESP3d || UserSettings.SnapLine || UserSettings.FilledWidth) {
			for (int i = 0; i < 254; i++) {
				if (ents[i] != 0 && local != 0) {
					if (ents[i]->Check1 != 0) {
						Vector3 pos = ents[i]->Pos;
						if ((local->Pos.Distance(pos) / 100) > 0.8f && (local->Pos.Distance(pos) / 100) < UserSettings.EspDistance) {
							Vector3 pos1 = ents[i]->Pos;
							pos1.z += 64;
							Vector3 pos2 = ents[i]->Pos;
							if (UserSettings.top)
								pos2.z += 64.0f;
							if (UserSettings.bottom)
								pos2.z += 0;
							Vector2 Posscreen = PosToScreen(pos);
							Vector2 Posscreen1 = PosToScreen(pos1);
							Vector2 posscreen2 = PosToScreen(pos2);
							float heigth = Posscreen.y - Posscreen1.y;
							if (UserSettings.ESP) {
								if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
									DrawRect(Posscreen, heigth, heigth * UserSettings.boxWidth, UserSettings.bocthickness, UserSettings.EnemyBoxColor);
								}
							}
							if (UserSettings.ESP3d) {
								if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
									Draw3dBoxes(i, UserSettings.Enemy3dColor, UserSettings.box3dthickness);
								}
							}
							if (UserSettings.SnapLine) {
								if (posscreen2.x > 0 && posscreen2.y > 0 && posscreen2.x < 1920 && posscreen2.y < 1080) {
									DrawLine(SnapLineBegin, posscreen2, UserSettings.EnemySnapColor, UserSettings.ThicknessSnap);
								}
							}
							if (UserSettings.DistanceEsp) {
								sprintf_s(Distances, 50, "[%0.fm]", local->Pos.Distance(pos) / 100);
								if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
									DrawChar(Posscreen1, Distances, UserSettings.EnemyDistColor, 1);
								}
							}
							if (UserSettings.FilledESP) {
								if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
									DrawFilledRect(Posscreen, heigth, heigth * UserSettings.FilledWidth, UserSettings.EnemyFilledColor);
								}
							}
						}
					}
				}
			}
		}
		if (UserSettings.fullbrigthness) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(1920 / 2, 1080 / 2), 1920, UserSettings.FilledCircleColorWhite, 0);
		}
		if (UserSettings.nightmode) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(1920 / 2, 1080 / 2), 1920, UserSettings.FilledCircleColorBlack, 0);
		}
		if (UserSettings.Aimbot) {
			if (UserSettings.ShowFov) {
				DrawCircle({ 1920 / 2, 1080 / 2 }, UserSettings.FovColor, UserSettings.AimbotFov, UserSettings.FovThickness);
				if (UserSettings.FilledCircle) {
					ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(1920 / 2, 1080 / 2), UserSettings.AimbotFov, UserSettings.FilledCircleColor, 0);
				}
			}
			if (UserSettings.ShowTarget) {
				if (ents[closest] != 0 && local != 0) {
					float Distance = local->Pos.Distance(ents[closest]->Pos) / 100;
					if (Distance < UserSettings.EspDistance && Distance > 0.9f && ents[closest]->Check1 != 0) {
						if (AimbottargetScreen.Distance({ 1920 / 2, 1080 / 2 }) < UserSettings.AimbotFov) {
							DrawLine({ 1920 / 2, 1080 / 2 }, AimbottargetScreen, UserSettings.TargetColor, UserSettings.TargetThickness);
						}
					}
				}
			}
		}
	}
	ImGui::EndFrame();
	ImGui::Render();
	DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(HMODULE hMod) {
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetCurrentProcessId() == ForegroundWindowProcessID) {

			Process::ID = GetCurrentProcessId();
			Process::Handle = GetCurrentProcess();
			Process::Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process::Hwnd, &TempRect);
			Process::WindowWidth = TempRect.right - TempRect.left;
			Process::WindowHeight = TempRect.bottom - TempRect.top;

			char TempTitle[MAX_PATH];
			GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
			Process::Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
			Process::ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
			Process::Path = TempPath;

			WindowFocus = true;
		}
	}
	bool InitHook = false;
	while (InitHook == false) {
		if (DirectX11::Init() == true) {
		    CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
			InitHook = true;
		}
	}
	while (!GetAsyncKeyState(VK_DELETE)) {
		Sleep(500);
	}
	Patch((BYTE*)HookAddr, (BYTE*)"\xF3\x0F\x10\x50\x04", 5);
	Patch((BYTE*)HookAddr1, (BYTE*)"\xF3\x0F\x5C\x43\x04", 5);
	ShowMenu = false;
	Sleep(10);
	DisableAll();
	FreeLibraryAndExitThread(hMod, 0);
}

BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
	return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		if (ChecktDirectXVersion(DirectXVersion.D3D11) == true) {
			Process::Module = hModule;
			StartThread(hModule, (LPTHREAD_START_ROUTINE)MainThread);
			StartThread(hModule, (LPTHREAD_START_ROUTINE)InitiateHooks);
			StartThread(hModule, (LPTHREAD_START_ROUTINE)SetEntities);
			StartThread(hModule, (LPTHREAD_START_ROUTINE)Aimbot);
		}
		break;
	default:
		break;
	}
	return TRUE;
}