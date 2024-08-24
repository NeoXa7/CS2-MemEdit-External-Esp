#pragma once
#include <Memory/hProcess.h>

namespace cs2_process_info
{
    inline DWORD procID = ProcessManager::GetProcessID(L"cs2.exe");
    inline uintptr_t clientAddress = ProcessManager::GetModuleBaseAddress(procID, L"client.dll");
    inline uintptr_t engineAddress = ProcessManager::GetModuleBaseAddress(procID, L"engine.dll");
}

namespace Offsets
{
    namespace buttons // buttons (last updated 9 August 2024);
    {
        inline int dwForceAttack = 0x17C7ED0;
        inline int dwForceAttack2 = 0x17C7F60;
        inline int dwForceJump = 0x17C83E0;
    }

    namespace client_dll // client_dll (last updated 9 August 2024);
    {
        inline int m_iTeamNum = 0x3C3; // uint8
        inline int m_iHealth = 0x324; // int32
        inline int m_hPlayerPawn = 0x7DC; // CHandle<C_CSPlayerPawn>

        inline int m_flFlashBangTime = 0x1348; // float32
        inline int m_iIDEntIndex = 0x13A8; // CEntityIndex
        inline int m_iShotsFired = 0x22B4; // int32
        inline int m_aimPunchAngle = 0x14CC; // QAngle
        inline int m_vOldOrigin = 0x1274; // Vector
        inline int m_vecViewOffset = 0xC50; // CNetworkViewOffsetVector
        inline int m_Glow = 0xBA0; // CGlowProperty
        inline int m_glowColorOverride = 0x40; // Color
        inline int m_bGlowing = 0x51; // bool
    }

    namespace offsets // offsets (last updated 9 August 2024);
    {

        inline int dwEntityList = 0x1964198;
        inline int dwLocalPlayerPawn = 0x17CF698;
        inline int dwViewAngles = 0x19D40F8;
        inline int dwViewMatrix = 0x19C6250;
    }
}

