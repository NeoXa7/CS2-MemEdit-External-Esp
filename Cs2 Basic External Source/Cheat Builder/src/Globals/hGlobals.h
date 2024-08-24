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
        inline int dwForceAttack = 0x17CD040;
        inline int dwForceAttack2 = 0x17CD0D0;
        inline int dwForceJump = 0x17CD550;
    }

    namespace client_dll // client_dll (last updated 9 August 2024);
    {
        // entity
        inline int m_iTeamNum = 0x3C3; // uint8
        inline int m_iHealth = 0x324; // int32
        inline int m_hPlayerPawn = 0x7EC; // CHandle<C_CSPlayerPawn>

        // antiflash
        inline int m_flFlashBangTime = 0x1348; // float32

        // trigger bot
        inline int m_iIDEntIndex = 0x13A8; // CEntityIndex
        inline int m_iShotsFired = 0x22B4; // int32

        // aimbot
        inline int m_aimPunchAngle = 0x14CC; // QAngle
        inline int m_vOldOrigin = 0x1274; // Vector
        inline int m_vecViewOffset = 0xC50; // CNetworkViewOffsetVector

        // glow
        inline int m_Glow = 0xBA0; // CGlowProperty
        inline int m_glowColorOverride = 0x40; // Color
        inline int m_bGlowing = 0x51; // bool

        // radar
        inline int m_entitySpottedState = 0x10F8;
        inline int m_bSpotted = 0x8; // bool

        // get c4 info;
        inline int m_nBombSite = 0xED4; // int32
        inline int m_flTimerLength = 0xF08; // float32
        inline int m_bBombPlanted = 0x9A5; // bool
        inline int m_bBombDropped = 0x9A4; // bool
        inline int m_bBeingDefused = 0xF0C; // bool

        // fov;
        inline int m_pCameraServices = 0x1130; // CPlayer_CameraServices*
        inline int m_iFOV = 0x210; // uint32
        inline int m_bIsScoped = 0x22A0; // bool

        // jumpshot;
        inline int m_fFlags = 0x63; // uint8
        inline int m_vecAbsVelocity = 0x3D0; // Vector
    }

    namespace offsets // offsets (last updated 9 August 2024);
    {

        inline int dwEntityList = 0x19684F8;
        inline int dwLocalPlayerPawn = 0x17D37F0;
        inline int dwViewAngles = 0x19D98E8;
        inline int dwViewMatrix = 0x19CA480;
        inline int dwPlantedC4 = 0x19CEEC8;
        inline int dwGameRules = 0x19C54E8;
    }
}

