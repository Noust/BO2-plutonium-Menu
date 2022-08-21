#include "include.h"

bool ShowMenu = false;
bool ImGui_Initialised = false;
bool alreadyther = false;
char Distances[50];
Vector2 SnapLineBegin = { 1920 / 2,1080 };

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
	style.WindowMinSize = ImVec2(575, 346);
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

DWORD WINAPI InitiateHooks(HMODULE hMod) {
	while (!hooked) {
		char modulename[] = "plutonium-bootstrapper-win32.exe";
		char sig[] = "\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xA1";
		char mask[] = "xx???xx???xx???xx???xx????xx???x";
		char sig1[] = "\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\x00\x00\xF3\x0F";
		char mask1[] = "xx???xx????xx???xx???xx????xx??????xx????xx??????xx";
		HookAddr = FindPattern(modulename, sig, mask);
		HookAddr1 = FindPattern(modulename, sig1, mask1);
		int hooklength = 15;
		int hooklength1 = 16;
		jmpback = HookAddr + hooklength;
		jmpback1 = HookAddr1 + hooklength1;
		if (HookAddr != NULL && HookAddr1 != NULL) {
			Hook((BYTE*)HookAddr, (BYTE*)GetEnts, hooklength);
			Hook((BYTE*)HookAddr1, (BYTE*)GetLocal, hooklength1);
			hooked = true;
		}
	}
	while (!GetAsyncKeyState(VK_DELETE)) {
		Sleep(500);
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
		ImGui::BeginChild("##leftside", ImVec2(150, ImGui::GetContentRegionAvail().y), true);
		if (ImGui::Button("Visuals", ImVec2(ImGui::GetContentRegionAvail().x, 25))) {
			UserSettings.MenuWindow = 0;
		}
		if (ImGui::Button("Weapon", ImVec2(ImGui::GetContentRegionAvail().x, 25))) {
			UserSettings.MenuWindow = 1;
		}
		if (ImGui::Button("Name", ImVec2(ImGui::GetContentRegionAvail().x, 25))) {
			UserSettings.MenuWindow = 2;
		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("##rigth", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		if (UserSettings.MenuWindow == 0) {
			ImGui::Checkbox("Snap Line Esp", &UserSettings.SnapLine);
			if (UserSettings.SnapLine) {
				ImGui::ColorEdit4("Enemy Snap Color", (float*)(&UserSettings.EnemySnapColor));
				ImGui::ColorEdit4("Team Snap Color", (float*)(&UserSettings.PlayerSnapColor));
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
				ImGui::ColorEdit4("Enemies Box Color", (float*)(&UserSettings.EnemyBoxColor));
				ImGui::ColorEdit4("Team Box Color", (float*)(&UserSettings.PlayerBoxColor));
				ImGui::SliderFloat("Box Width", &UserSettings.boxWidth, 0, 1);
				ImGui::SliderInt("Box Thickness", &UserSettings.bocthickness, 0, 10);
				ImGui::Separator();
			}
			ImGui::Checkbox("Distance ESP", &UserSettings.DistanceEsp);
			if (UserSettings.DistanceEsp) {
				ImGui::ColorEdit4("Enemies Distance Color", (float*)(&UserSettings.EnemyDistColor));
				ImGui::ColorEdit4("Team Distance Color", (float*)(&UserSettings.PlayerDistColor));
				ImGui::Separator();
			}
			ImGui::Checkbox("3D Box ESP", &UserSettings.ESP3d);
			if (UserSettings.ESP3d) {
				ImGui::ColorEdit4("Enemies 3D Box Color", (float*)(&UserSettings.Enemy3dColor));
				ImGui::ColorEdit4("Team 3D Box Color", (float*)(&UserSettings.Player3dColor));
				ImGui::SliderInt("3D Box Thickness", &UserSettings.box3dthickness, 0, 10);
				ImGui::Separator();
			}
			ImGui::SliderFloat("ESP Distance", &UserSettings.EspDistance, 1, 80);
		}
		if (UserSettings.MenuWindow == 1) {

		}
		if (UserSettings.MenuWindow == 2) {

		}
		ImGui::EndChild();
		ImGui::End();
	}
	if (hooked) {
		if (UserSettings.ESP || UserSettings.DistanceEsp || UserSettings.ESP3d || UserSettings.SnapLine) {
			for (int i = 0; i < 254; i++) {
				if (ents[i] != 0 && local != 0) {
					Vector3 Lpos = local->Pos;
					if (ents[i]->Check1 != 0) {
						Vector3 pos = ents[i]->Pos;
						if ((Lpos.Distance(pos) / 100) > 0.8f && (Lpos.Distance(pos) / 100) < UserSettings.EspDistance) {
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
								sprintf_s(Distances, 50, "[%0.fm]", Lpos.Distance(pos) / 100);
								if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
									DrawChar(Posscreen1, Distances, UserSettings.EnemyDistColor, 1);
								}
							}
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
	Patch((BYTE*)HookAddr, (BYTE*)"\xF3\x0F\x10\x50\x04\xF3\x0F\x11\x04\x24\xF3\x0F\x10\x40\x08", 15);
	Patch((BYTE*)HookAddr1, (BYTE*)"\xF3\x0F\x5C\x43\x04\xF3\x0F\x11\x44\x24\x18\xF3\x0F\x10\x47\x34", 16);
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
		}
		break;
	default:
		break;
	}
	return TRUE;
}