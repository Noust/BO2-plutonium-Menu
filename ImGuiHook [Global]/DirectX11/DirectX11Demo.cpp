#include "include.h"

bool ShowMenu = false;
bool ImGui_Initialised = false;
bool alreadyther = false;

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

DWORD WINAPI InitiateHooks(HMODULE hMod) {
	while (!hooked) {
		char modulename[] = "plutonium-bootstrapper-win32.exe";
		char sig[] = "\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\xF3\x0F\x00\x00\x00\x00\xF3\x0F\x00\x00\x00\xA1";
		char mask[] = "xx???xx???xx???xx???xx????xx???x";
		HookAddr = FindPattern(modulename, sig, mask);
		int hooklength = 15;
		jmpback = HookAddr + hooklength;
		if (HookAddr != NULL) {
			Hook((BYTE*)HookAddr, (BYTE*)GetEnts, hooklength);
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
		Sleep(10);
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
			ImGui::Checkbox("Box ESP", &UserSettings.ESP);
			if (UserSettings.ESP) {
				ImGui::ColorEdit4("Enemies Box Color", (float*)(&UserSettings.EnemyBoxColor));
				ImGui::ColorEdit4("Team Box Color", (float*)(&UserSettings.PlayerBoxColor));
				ImGui::SliderFloat("Box Width", &UserSettings.boxWidth, 0, 1);
				ImGui::SliderInt("Box Thickness", &UserSettings.bocthickness, 0, 10);
				ImGui::Separator();
			}
		}
		if (UserSettings.MenuWindow == 1) {

		}
		if (UserSettings.MenuWindow == 2) {

		}
		ImGui::EndChild();
		ImGui::End();
	}
	if (hooked) {
		if (UserSettings.ESP) {
			for (int i = 0; i < 254; i++) {
				if (ents[i] != 0) {
					Vector3 pos = ents[i]->Pos;
					Vector2 Posscreen = PosToScreen(pos);
					if (Posscreen.x > 0 && Posscreen.y > 0 && Posscreen.x < 1920 && Posscreen.y < 1080) {
						DrawLine({ 1920 / 2, 1080 }, Posscreen, ImColor(155, 155, 155), 1);
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