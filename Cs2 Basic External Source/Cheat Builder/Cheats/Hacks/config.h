#pragma once
#include "reader.h"

Color color;
extern Player player;
namespace Settings
{
	namespace hot_keys
	{
		int SPACE_BAR = VK_SPACE; //0x20
		int MOUSE_XB1 = VK_XBUTTON1; //0x05
		int MOUSE_XB2 = VK_XBUTTON2; //0x06
		int LEFT_SHIFT = VK_LSHIFT; // 0x06
	}

	namespace Aimbot
	{
		int key = hot_keys::MOUSE_XB2;
		float aim_fov = 10.0f; // Field of view in degrees, adjust this value as needed
		float aim_smooth_Factor = 0.5f; // Adjust this value to change smoothness, lower is smoother

		Vector3 SetTorsoCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			Vector3 entityTorsoPos = entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::client_dll::m_vecViewOffset) * 0.5;
			return entityTorsoPos;
		}

		Vector3 SetHeadCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			Vector3 entityEyePos = entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::client_dll::m_vecViewOffset);
			return entityEyePos;
		}

		void SimulateMouseMove(float deltaX, float deltaY)
		{
			// Convert the angle difference to screen pixels
			int moveX = static_cast<int>((deltaX / 2.41) * 100); // Adjust scaling factor as needed
			int moveY = static_cast<int>((-deltaY / 2.41) * 100); // Invert Y-axis

			// Use Windows API to simulate mouse movement
			mouse_event(MOUSEEVENTF_MOVE, moveX, moveY, 0, 0);
		}

	}

	namespace glow_hack
	{
		namespace glow_color
		{
			DWORD64 WHITE = color.convertToARGB(Color(253, 228, 132, 255));
			DWORD64 BLUE = color.convertToARGB(Color(128, 0, 0, 255));
			DWORD64 RED = color.convertToARGB(Color(0, 0, 255, 255));
			DWORD64 PURPLE = color.convertToARGB(Color(128, 0, 128, 255));
			DWORD64 GREEN = color.convertToARGB(Color(0, 255, 0, 255));
			DWORD64 CYAN = color.convertToARGB(Color(255, 255, 0, 255));
			DWORD64 LIGHTBLUE = color.convertToARGB(Color(0, 0, 0, 255));
			DWORD64 YELLOW = color.convertToARGB(Color::fromHSV(180.0f, 1.0f, 1.0f));
		}

		namespace glow_cfg
		{
			bool teamGlow = false;
			bool glow_after_entity_is_Dead = false;
		}

	}

	namespace Trigger_bot
	{
		int FIRE_KEY = hot_keys::LEFT_SHIFT;
		void SimulateMouseClick()
		{
			INPUT input = { 0 };
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &input, sizeof(INPUT));

			ZeroMemory(&input, sizeof(INPUT));
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(INPUT));
		}
	}

	namespace RCS
	{
		float sensitivity = 2.41;	
		float oldPunch_x = 0.0f;
		float oldPunch_y = 0.0f;

		void recoil_control_mouse_event(int dx, int dy) {
			INPUT input = { 0 };

			// Move mouse horizontally
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			input.mi.dx = dx;
			input.mi.dy = dy;
			input.mi.dwExtraInfo = 0;
			SendInput(1, &input, sizeof(INPUT));
		}
	}
}