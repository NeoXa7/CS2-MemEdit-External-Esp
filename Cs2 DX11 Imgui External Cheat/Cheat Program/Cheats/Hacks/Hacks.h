#pragma once
#include <Memory/hMemory.h>
#include <Inputs/Events.h>
#include <Readers/Game.h>
#include <Readers/Player.h>
#include <Hacks/Config.h>

Game game;
LocalPlayer player;

namespace Cheats
{
	namespace Safe_Cheats
	{
		void TriggerBot();
		void StandaloneRCS();
	}

	namespace Risky_Cheats // This namespace Includes cheats that writes memory which may lead to game ban;
	{
		void Bhop();
		void Antiflash();
		void RadarHack();

		namespace ThreadHacks
		{
			void GlowHack(DWORD64 COLOR);
			void Aimbot();

			std::thread glow_thread([] {
				while (Flags::isRunning) {
					if (Flags::enableGlowHack)
					{
						Cheats::Risky_Cheats::ThreadHacks::GlowHack(Config::GlowHack::GlowColor::CurrentGlowColor);
					}			
				}
				});

			std::thread aimbot_thread([] {
				while (Flags::isRunning) {
					if (Flags::enableAimbot)
					{
						if(GetAsyncKeyState(Config::Aimbot::AB_KEYCODE))
							Cheats::Risky_Cheats::ThreadHacks::Aimbot();
					}
				}
				});

			void JoinThread()
			{
				glow_thread.join();
				aimbot_thread.join();
			}
		}		
	}

	void InitializeBasicCheats();
}

// Safe Hacks;

void Cheats::Safe_Cheats::TriggerBot()
{
	if (player.EntityIndex > 0)
	{
		uintptr_t entityListEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * (player.EntityIndex >> 9) + 0x10);
		uintptr_t entity = Memory::ReadMemory<uintptr_t>(entityListEntry + 120 * (player.EntityIndex & 0x1FF));

		int entityTeam = Memory::ReadMemory<int>(entity + Offsets::client_dll::m_iTeamNum);
		int entityHealth = Memory::ReadMemory<int>(entity + Offsets::client_dll::m_iHealth);

		if (entityTeam != player.Team && entityHealth > 0)
		{
			MouseEvents::SimulateLMBClick();
			Sleep(100);
		}
	}
}

void Cheats::Safe_Cheats::StandaloneRCS()
{
	float aimPunch_x = player.AimPunchAngle;
	float aimPunch_y = Memory::ReadMemory<float>(player.localPlayerPawn + player.AimPunchAngle + 0x4);
	if (player.ShotsFired > 1)
	{
		auto delta_x = (aimPunch_x - Config::RCS::oldPunch_x) * -1.0;
		auto delta_y = (aimPunch_y - Config::RCS::oldPunch_y) * -1.0;
		auto mouse_x = int((delta_y * 2.0 / player.Sensitivity) / -0.022);
		auto mouse_y = int((delta_x * 2.0 / player.Sensitivity) / 0.022);

		MouseEvents::SimulateMouseMove(mouse_x, mouse_y);
		Config::RCS::oldPunch_x = aimPunch_x;
		Config::RCS::oldPunch_y = aimPunch_y;
	}
	else
	{
		Config::RCS::oldPunch_x = aimPunch_x; // 0
		Config::RCS::oldPunch_y = aimPunch_y; // 0
	}
}

// Risky Hacks;

void Cheats::Risky_Cheats::Bhop()
{
	if (GetAsyncKeyState(VK_SPACE) < 0)
	{
		Memory::WriteMemory<int>(CS2::clientAddress + Offsets::buttons::dwForceJump, 65537);
		Sleep(10);
		Memory::WriteMemory<int>(CS2::clientAddress + Offsets::buttons::dwForceJump, 256);
	}
}

void Cheats::Risky_Cheats::Antiflash()
{
	float flashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::client_dll::m_flFlashBangTime);
	if (flashDuration > 0)
	{
		Memory::WriteMemory<float>(player.localPlayerPawn + Offsets::client_dll::m_flFlashBangTime, 0);
	}
}

void Cheats::Risky_Cheats::RadarHack()
{
	uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x10);

	for (int i = 1; i < 64; i++)
	{
		if (listEntry == 0)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + i * 0x78);
		if (currentController == 0)
			continue;

		int pawnHandle = Memory::ReadMemory<int>(currentController + Offsets::client_dll::m_hPlayerPawn);
		if (pawnHandle == 0)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
		if (listEntry2 == 0)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (currentPawn == player.localPlayerPawn || currentPawn == 0)
			continue;

		bool isRadarHacked = Memory::ReadMemory<bool>(currentPawn + Offsets::client_dll::m_entitySpottedState + Offsets::client_dll::m_bSpotted);

		if (!isRadarHacked)
		{
			Memory::WriteMemory<bool>(currentPawn + Offsets::client_dll::m_entitySpottedState + Offsets::client_dll::m_bSpotted, true);
		}
	}
}

void Cheats::Risky_Cheats::ThreadHacks::GlowHack(DWORD64 COLOR)
{
	uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x10);
	for (int i = 1; i < 64; i++)
	{
		if (listEntry == 0)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + i * 0x78);
		if (currentController == 0)
			continue;

		int pawnHandle = Memory::ReadMemory<int>(currentController + Offsets::client_dll::m_hPlayerPawn);
		if (pawnHandle == 0)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
		if (listEntry2 == 0)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (currentPawn == player.localPlayerPawn || currentPawn == 0)
			continue;

		if (Config::GlowHack::GlowSettings::TeamGlow == false)
		{
			if (player.Team == Memory::ReadMemory<int>(currentPawn + Offsets::client_dll::m_iTeamNum))
				continue;
		}

		if (Config::GlowHack::GlowSettings::DeadEntityGlow == false)
		{
			if (Memory::ReadMemory<int>(currentPawn + Offsets::client_dll::m_iHealth) <= 0)
				continue;
		}

		DWORD64 GlowColorOverride = currentPawn + Offsets::client_dll::m_Glow + Offsets::client_dll::m_glowColorOverride;
		DWORD64 GlowFunction = currentPawn + Offsets::client_dll::m_Glow + Offsets::client_dll::m_bGlowing;

		Memory::WriteMemory<DWORD64>(GlowColorOverride, COLOR); // 0x800000FF <- RED; 0xFDE484FF <- PINK; 
		Memory::WriteMemory<DWORD64>(GlowFunction, 1);
	}
}

void Cheats::Risky_Cheats::ThreadHacks::Aimbot()
{
	if (!game.EntityList)
		return;

	Vector3 localEyePos = player.vOldOrigin + player.VecViewOffset;
	Vector3 currentAngles = game.ViewAngles;

	float closestDistance = -1;
	Vector3 enemyPos;


	for (int i = 0; i < 64; i++)
	{
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + ((8 * (i & 0x7FF) >> 9) + 16));
		if (!listEntry)
			continue;

		uintptr_t entityController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
		if (!entityController)
			continue;

		int entityControllerPawn = Memory::ReadMemory<int>(entityController + Offsets::client_dll::m_hPlayerPawn);
		if (!entityControllerPawn)
			continue;

		uintptr_t entityPawn = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (entityControllerPawn & 0x1FF));
		if (!entityPawn)
			continue;

		if (player.Team == Memory::ReadMemory<int>(entityPawn + Offsets::client_dll::m_iTeamNum))
			continue;

		if (Memory::ReadMemory<int>(entityPawn + Offsets::client_dll::m_iHealth) <= 0)
			continue;

		Vector3 entityPos = Memory::ReadMemory<Vector3>(entityPawn + Offsets::client_dll::m_vOldOrigin);

		Vector3 EntitiesPenisPosition = Config::Aimbot::SetPenisCoordinates(entityPos, entityPawn);
		Vector3 EntityEyePositions = Config::Aimbot::SetHeadCoordinates(entityPos, entityPawn);

		Vector3 aimPosition = EntityEyePositions;

		if (Config::Aimbot::CurrentAimPosIndex == 0)
		{
			aimPosition = EntityEyePositions;
		}
		else if (Config::Aimbot::CurrentAimPosIndex == 1)
		{
			aimPosition = EntitiesPenisPosition;
		}

		float currentDistance = distance(localEyePos, aimPosition);

		Vector3 targetAngle = (aimPosition - localEyePos).RelativeAngle();

		float angleDiff = targetAngle.AngleDifference(currentAngles);

		if (angleDiff > Config::Aimbot::AimFov / 2)
			continue;

		if (closestDistance == 0) continue;

		if (closestDistance < 0 || currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			enemyPos = aimPosition;
		}
	}

	if (closestDistance >= 0)
	{
		Vector3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();

		Vector3 smoothedAngle = currentAngles + (relativeAngle - currentAngles) * Config::Aimbot::AimSmoothness;

		Memory::WriteMemory<Vector3>(CS2::clientAddress + Offsets::offsets::dwViewAngles, smoothedAngle);
	}
}

void Cheats::InitializeBasicCheats()
{
	if (Flags::enableTriggerbot)
	{
		if (GetAsyncKeyState(Config::TriggerBot::TB_KEYCODE))
			Cheats::Safe_Cheats::TriggerBot();
	}

	if (Flags::enableRCS)
	{
		Cheats::Safe_Cheats::StandaloneRCS();
	}

	if (Flags::enableAntiflash)
	{
		Cheats::Risky_Cheats::Antiflash();
	}

	if (Flags::enableRadarHack)
	{
		Cheats::Risky_Cheats::RadarHack();
	}

	if (Flags::enableBhop)
	{
		Cheats::Risky_Cheats::Bhop();
	}
}