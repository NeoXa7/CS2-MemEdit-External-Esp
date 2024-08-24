#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

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