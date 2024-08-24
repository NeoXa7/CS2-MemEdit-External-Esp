#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <d3d11.h>
#include <Gui/menu_elements.h>
#include <Memory/hMemory.h>
#include <Memory/hProcess.h>
#include <dwmapi.h>
#include <Hacks/hacks.h>
#include <Gui/window_styles.h>


HANDLE Memory::processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, cs2_process_info::procID);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateConsoleWindow()
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
	freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr

	// Set console title
	SetConsoleTitle(L"Debug Console");

	// Optional: Move console window to a specific position
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL)
	{
		MoveWindow(consoleWindow, 100, 100, 800, 600, TRUE); // Position and size
	}

	SetConsoleTextColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
	//std::cout << "Console initialized!" << std::endl; // Test message
}


LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
	{
		return 0L;
	}

	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0L;
	}

	return DefWindowProc(window, message, w_param, l_param);
}


INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
	//CreateConsoleWindow();
	if (cs2_process_info::procID > 0)
	{
		SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Cs2 Process Found With Process ID : " << cs2_process_info::procID << '\n';
		cout << "Client Address : " << cs2_process_info::clientAddress << '\n';	

		SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "===========================================================================>\n";

		player.Initialize();
		cout << "Checking Offsets (Last Updated 22 August 2024) " << '\n';
		cout << "Local Player : " << player.localPlayerPawn << '\n';
		cout << "Local Team : " << player.localPlayerTeam << '\n';
		cout << "Local Player Health : " << player.localPlayerHealth << '\n';
		cout << "Aim Punch Angles : " << player.aimPunchAngle << '\n';
	}
	else
	{
		SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Process ID : " << cs2_process_info::procID << '\n';
		cout << "Open Cs2!\n";
		SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	


	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_procedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"External Overlay Class";
	wc.hIconSm = 0;

	RegisterClassExW(&wc);

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	const HWND window = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_LAYERED,
		wc.lpszClassName,
		L"Cs2 External Overlay",
		WS_POPUP,
		0,
		0,
		screen_width,
		screen_height,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);


	SetLayeredWindowAttributes(window, RGB(0, 0, 0), 255, LWA_COLORKEY);


	{
		RECT client_area{};
		GetClientRect(window, &client_area);

		RECT window_area{};
		GetWindowRect(window, &window_area);

		POINT diff{};
		ClientToScreen(window, &diff);

		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom

		};

		DwmExtendFrameIntoClientArea(window, &margins);

	}

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 60U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = window;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levels[2]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		&level,
		&device_context
	);

	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

	if (back_buffer)
	{
		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
		back_buffer->Release();
	}
	else
	{
		return 1;
	}

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);
	Menu::ApplyStyles();
	
	while (menu_bools::Running)
	{
		// Rendering Items Here;
		player.Initialize();
		game.Initialize();

		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				menu_bools::Running = false;
			}
		}

		if (!menu_bools::Running)
		{
			break;
		}

		
		// Begin a new frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		
		
		RenderGuiMenuElements();
		HACKS::InitializeBasicCheats(); // all hacks;

		ImGui::Render();

		constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swap_chain->Present(0U, 0U);
		
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// Join threads before exiting
	HACKS::CheatsThread::JoinThreads();

	if (swap_chain)
	{
		swap_chain->Release();
	}

	if (device_context)
	{
		device_context->Release();
	}

	if (device)
	{
		device->Release();
	}

	if (render_target_view)
	{
		render_target_view->Release();
	}

	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);

	

	return 0;
}
