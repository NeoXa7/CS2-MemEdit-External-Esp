#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class Player
{
public:
	uintptr_t localPlayerPawn;
	int localPlayerTeam;
	int localPlayerHealth;

	uint32_t shotsFired;
	float aimPunchAngle;
	
	Vector3 vOldOrigin;
	Vector3 vecViewOffset;
	int m_hPlayerPawn;
	float playerSensitivity;
	int entityIndex;

	void Initialize() {
		localPlayerPawn = Memory::ReadMemory<uintptr_t>(cs2_process_info::clientAddress + Offsets::offsets::dwLocalPlayerPawn);
		localPlayerTeam = Memory::ReadMemory<int>(localPlayerPawn + Offsets::client_dll::m_iTeamNum);	
		localPlayerHealth = Memory::ReadMemory<int>(localPlayerPawn + Offsets::client_dll::m_iHealth);

		shotsFired = Memory::ReadMemory<uint32_t>(localPlayerPawn + Offsets::client_dll::m_iShotsFired);
		aimPunchAngle = Memory::ReadMemory<float>(localPlayerPawn + Offsets::client_dll::m_aimPunchAngle);
		
		vOldOrigin = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::client_dll::m_vOldOrigin);
		vecViewOffset = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::client_dll::m_vecViewOffset);
		m_hPlayerPawn = Memory::ReadMemory<int>(localPlayerPawn + Offsets::client_dll::m_hPlayerPawn);
		entityIndex = Memory::ReadMemory<int>(localPlayerPawn + Offsets::client_dll::m_iIDEntIndex);
		
	}
};

class Game
{
public:
	uintptr_t entityList;
	Vector3 viewAngles;
	uintptr_t gameRules;
	
	void Initialize()
	{
		entityList = Memory::ReadMemory<uintptr_t>(cs2_process_info::clientAddress + Offsets::offsets::dwEntityList);
		viewAngles = Memory::ReadMemory<Vector3>(cs2_process_info::clientAddress + Offsets::offsets::dwViewAngles);
		gameRules = Memory::ReadMemory<uintptr_t>(cs2_process_info::clientAddress + Offsets::offsets::dwGameRules);		
	}
};