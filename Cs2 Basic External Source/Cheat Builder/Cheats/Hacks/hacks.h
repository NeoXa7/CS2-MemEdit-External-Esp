#pragma once
#include <Memory/hMemory.h>
#include <Maths/hColor.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include "config.h"
#include "reader.h"

using namespace std;
Player player;
Game game;

namespace HACKS
{
	namespace safe_hacks
	{
		void trigger_bot();
		void recoil_control_system();
		void retrieve_bomb_info();
	}

	namespace risky_hacks
	{
		void bhop();
		void antiflash();
		void radar_hack();
		void glow(DWORD64 COLOR);
		void aimbot();		
	}
}

// Safe Hacks (0% ban rate);

void HACKS::safe_hacks::trigger_bot()
{	
	if (player.entityIndex > 0)
	{
		uintptr_t entityListEntry = Memory::ReadMemory<uintptr_t>(game.entityList + 0x8 * (player.entityIndex >> 9) + 0x10);
		uintptr_t entity = Memory::ReadMemory<uintptr_t>(entityListEntry + 120 * (player.entityIndex & 0x1FF));

		int entityTeam = Memory::ReadMemory<int>(entity + Offsets::client_dll::m_iTeamNum);
		int entityHealth = Memory::ReadMemory<int>(entity + Offsets::client_dll::m_iHealth);

		if (entityTeam != player.localPlayerTeam && entityHealth > 0)
		{
			Settings::Trigger_bot::SimulateMouseClick();
			Sleep(100);
		}
	}
}

void HACKS::safe_hacks::recoil_control_system()
{
	float aimPunch_x = player.aimPunchAngle;
	float aimPunch_y = Memory::ReadMemory<float>(player.localPlayerPawn + player.aimPunchAngle + 0x4);
	if (player.shotsFired > 1)
	{
		auto delta_x = (aimPunch_x - Settings::RCS::oldPunch_x) * -1.0;
		auto delta_y = (aimPunch_y - Settings::RCS::oldPunch_y) * -1.0;
		auto mouse_x = int((delta_y * 2.0 / Settings::RCS::sensitivity) / -0.022);
		auto mouse_y = int((delta_x * 2.0 / Settings::RCS::sensitivity) / 0.022);

		Settings::RCS::recoil_control_mouse_event(mouse_x, mouse_y);
		Settings::RCS::oldPunch_x = aimPunch_x;
		Settings::RCS::oldPunch_y = aimPunch_y;
	}
	else
	{
		Settings::RCS::oldPunch_x = aimPunch_x; // 0
		Settings::RCS::oldPunch_y = aimPunch_y; // 0
	}
}

void HACKS::safe_hacks::retrieve_bomb_info()
{
	
	bool isBombPlanted = false;
	//float C4_DetonationTimer = Memory::ReadMemory<float>(game.gameRules + Offsets::client_dll::m_flTimerLength);
	
	if (game.gameRules != 0)
	{
		isBombPlanted = Memory::ReadMemory<bool>(game.gameRules + Offsets::client_dll::m_bBombPlanted);
		if (isBombPlanted)
		{
			for (int i = 0; i < 40; i++)
			{
				isBombPlanted = Memory::ReadMemory<bool>(game.gameRules + Offsets::client_dll::m_bBombPlanted);
				if (!isBombPlanted)
					break;

				isBombPlanted = true;
				cout << "Bomb Planted : True " << '\n';
				

				int plantedSite = Memory::ReadMemory<int>(game.gameRules + Offsets::client_dll::m_nBombSite);
				if (plantedSite > 0)
				{
					cout << "Bomb Planted to Site B\n";

				}
				else
				{
					cout << "Bomb Planted to Site A\n";
				}

				//bool isBombBeingDefused = Memory::ReadMemory<bool>(game.gameRules + Offsets::client_dll::m_bBeingDefused);
			}
		}
	}	
}

// Risky Hacks;

void HACKS::risky_hacks::bhop()
{
	static bool jump = false;
	if (GetAsyncKeyState(Settings::hot_keys::SPACE_BAR) < 0)
	{
		if (!jump)
		{
			Memory::WriteMemory<int>(cs2_process_info::clientAddress + Offsets::buttons::dwForceJump, 65537);
			jump = true;
		}
		if (jump)
		{
			Memory::WriteMemory<int>(cs2_process_info::clientAddress + Offsets::buttons::dwForceJump, 256);
			jump = false;
		}
	}
}

void HACKS::risky_hacks::antiflash()
{	
	float flashDuration = Memory::ReadMemory<float>(player.localPlayerPawn + Offsets::client_dll::m_flFlashBangTime);
	if (flashDuration > 0)
	{
		Memory::WriteMemory<float>(player.localPlayerPawn + Offsets::client_dll::m_flFlashBangTime, 0);
	}
}

void HACKS::risky_hacks::radar_hack()
{
    uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.entityList + 0x10);

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

        uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
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

void HACKS::risky_hacks::glow(DWORD64 COLOR)
{
	uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.entityList + 0x10);
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

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
		if (listEntry2 == 0)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (currentPawn == player.localPlayerPawn || currentPawn == 0)
			continue;

		if (Settings::glow_hack::glow_cfg::teamGlow == false)
		{
			if (player.localPlayerTeam == Memory::ReadMemory<int>(currentPawn + Offsets::client_dll::m_iTeamNum))
				continue;
		}

		if (Settings::glow_hack::glow_cfg::glow_after_entity_is_Dead == false)
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

void HACKS::risky_hacks::aimbot()
{
	if (!game.entityList)
		return;

	Vector3 localEyePos = player.vOldOrigin + player.vecViewOffset;
	Vector3 currentAngles = game.viewAngles;

	float closestDistance = -1;
	Vector3 enemyPos;


	for (int i = 0; i < 64; i++)
	{
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.entityList + ((8 * (i & 0x7FF) >> 9) + 16));
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

		if (player.localPlayerTeam == Memory::ReadMemory<int>(entityPawn + Offsets::client_dll::m_iTeamNum))
			continue;

		if (Memory::ReadMemory<int>(entityPawn + Offsets::client_dll::m_iHealth) <= 0)
			continue;

		Vector3 entityPos = Memory::ReadMemory<Vector3>(entityPawn + Offsets::client_dll::m_vOldOrigin);

		Vector3 entityTorsoPos = Settings::Aimbot::SetTorsoCoordinates(entityPos, entityPawn);
		Vector3 entityEyePos = Settings::Aimbot::SetHeadCoordinates(entityPos, entityPawn);

		float currentDistance = distance(localEyePos, entityEyePos);

		Vector3 targetAngle = (entityEyePos - localEyePos).RelativeAngle();

		float angleDiff = targetAngle.AngleDifference(currentAngles);

		if (angleDiff > Settings::Aimbot::aim_fov / 2)
			continue;

		if (closestDistance == 0) continue;

		if (closestDistance < 0 || currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			enemyPos = entityEyePos;
		}
	}

	if (closestDistance >= 0)
	{
		Vector3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();

		Vector3 smoothedAngle = currentAngles + (relativeAngle - currentAngles) * Settings::Aimbot::aim_smooth_Factor;

		Memory::WriteMemory<Vector3>(cs2_process_info::clientAddress + Offsets::offsets::dwViewAngles, smoothedAngle);
	}
}
