#pragma once
#include <Maths/hColor.h>
#include <Maths/hVector.h>

Color color;

namespace Config
{
	namespace TriggerBot
	{
		inline bool enableHotKey = true;
		inline bool enableTeamCheck = true;
		static int TB_KEYCODE = 0;
		static char TB_Default_KEYCODE_STR[16] = "A0";
	}

	namespace RCS
	{
		float oldPunch_x = 0.0f;
		float oldPunch_y = 0.0f;
	}

	namespace GlowHack
	{
		const char* AvailableColors[] = { "Green", "Yellow", "Blue", "Red", "White", "Purple", "Cyan", "LightBlue" };
		static int CurrentColorIndex = 0;

		namespace GlowColor
		{
			DWORD64 WHITE = color.convertToARGB(Color(253, 228, 132, 255));
			DWORD64 BLUE = color.convertToARGB(Color(128, 0, 0, 255));
			DWORD64 RED = color.convertToARGB(Color(0, 0, 255, 255));
			DWORD64 PURPLE = color.convertToARGB(Color(128, 0, 128, 255));
			DWORD64 GREEN = color.convertToARGB(Color(0, 255, 0, 255));
			DWORD64 CYAN = color.convertToARGB(Color(255, 255, 0, 255));
			DWORD64 LIGHTBLUE = color.convertToARGB(Color(0, 0, 0, 255));
			DWORD64 YELLOW = color.convertToARGB(Color::fromHSV(180.0f, 1.0f, 1.0f));

			DWORD64 CurrentGlowColor = GREEN;
		}

		namespace GlowSettings
		{
			inline bool TeamGlow = false;
			inline bool DeadEntityGlow = false;
		}

	}

	namespace Esp
	{
		inline bool enableEspBoxes = true;
		inline bool enableEspHealthBar = true;
		inline bool enableEspLines = false;
		inline bool enableEspNames = true;
		inline bool enableEspTeam = false;
		inline bool enableEspBones = true;

		ImColor BoxColor = ImColor(255, 255, 255, 255); // Default white;
		ImColor HealthBarColor = ImColor(0, 255, 0, 255); // Default green;
		ImColor LinesColor = ImColor(255, 255, 255, 255); // Default white;
		float LinesThickness = 2.0f;
		float BoxThickness = 1.0f;
	}

	namespace Aimbot
	{
		inline bool enableHotKey = false;
		static int AB_KEYCODE = 0;
		static char AB_Default_KEYCODE_STR[16] = "06";

		const char* AimPositions[] = { "Head", "Penis" };
		static int CurrentAimPosIndex = 0; // Index of the currently selected item

		static float AimFov = 10.f;
		static float AimSmoothness = 1.f;

		static bool ShowFovCircle = false;
		static ImVec4 FovCircleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Default White;
		static float FovCircleThickness = 1.5f;		

		Vector3 SetPenisCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			return entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vecViewOffset) * 0.5;
		}

		Vector3 SetHeadCoordinates(Vector3 entityPosition, uintptr_t entityPawn)
		{
			return entityPosition + Memory::ReadMemory<Vector3>(entityPawn + Offsets::m_vecViewOffset);
		}
	}
}