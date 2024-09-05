#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class LocalPlayer
{
private:
	uintptr_t DW_Sensitivity;
public:
	uintptr_t localPlayerPawn;
	int Team;
	int Health;

	uint32_t ShotsFired;
	float AimPunchAngle;

	Vector3 vOldOrigin;
	Vector3 VecViewOffset;
	int m_hPlayerPawn;
	int EntityIndex;
	float Sensitivity;
	int fFlag;

	void Initialize() {
		localPlayerPawn = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwLocalPlayerPawn);
		Team = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iTeamNum);
		Health = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iHealth);

		ShotsFired = Memory::ReadMemory<uint32_t>(localPlayerPawn + Offsets::m_iShotsFired);
		AimPunchAngle = Memory::ReadMemory<float>(localPlayerPawn + Offsets::m_aimPunchAngle);

		vOldOrigin = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vOldOrigin);
		VecViewOffset = Memory::ReadMemory<Vector3>(localPlayerPawn + Offsets::m_vecViewOffset);
		m_hPlayerPawn = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_hPlayerPawn);
		EntityIndex = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_iIDEntIndex);

		DW_Sensitivity = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::dwSensitivity);
		Sensitivity = Memory::ReadMemory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity);
		fFlag = Memory::ReadMemory<int>(localPlayerPawn + Offsets::m_fFlags);
	}
}; extern LocalPlayer player;
