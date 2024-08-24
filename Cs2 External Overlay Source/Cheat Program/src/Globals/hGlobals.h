#pragma once
#include <Memory/hProcess.h>

namespace menu_items
{
    const char* glow_colors_name[] = { "Green", "Yellow", "Blue", "Red", "White", "Purple", "Cyan", "LightBlue" };
    static int glow_color_index = 0; // Index of the currently selected item

   
    static int keyCode_triggerBot = 0; 
    static char keyCodeStrTB[16] = "A0"; 

    static float rcs_sesni_input_value = 2.41f;

    // aimbot configurations;
    static int keyCode_AimBot = 0;
    static char keyCodeStrAimBot[16] = "06";

    const char* aim_positions[] = { "Head", "Torso" };
    static int aim_positions_index = 0; // Index of the currently selected item

    static float aimbot_fov_slider_value = 10.0f;
    static ImVec4 fovCircleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    static float fov_circle_thickness = 1.5f;
    static bool showCircle = false;

    // c4 configurations;
    bool bombPlanted = false;
    static int C4_Time_Left = -1;
}

namespace menu_bools
{
    bool Running = true;
    // safe hacks
    inline bool triggerbot = true;
    inline bool rcs = true;
    inline bool get_bomb_info = false;

    // risky hacks
    inline bool bhop_hack = false;
    inline bool antiflash_hack = false;
    inline bool radar_hack = false;
    inline bool glow_hack = true;
    inline bool aimbot_hack = true;
    inline bool esp_hack = false;
    inline bool fov_changer_hack = false;
    inline bool open_offsets_editor = false;
    inline bool show_menu_styler = false;
}

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

const char* KeyCodeToString(int keyCode) {
    switch (keyCode) {
        // Function keys
    case 0x70: return "F1";
    case 0x71: return "F2";
    case 0x72: return "F3";
    case 0x73: return "F4";
    case 0x74: return "F5";
    case 0x75: return "F6";
    case 0x76: return "F7";
    case 0x77: return "F8";
    case 0x78: return "F9";
    case 0x79: return "F10";
    case 0x7A: return "F11";
    case 0x7B: return "F12";

        // Control keys
    case 0x01: return "LEFT_MOUSE_BUTTON";
    case 0x02: return "RIGHT_MOUSE_BUTTON";
    case 0x03: return "CONTROL_BREAK";
    case 0x04: return "MIDDLE_MOUSE_BUTTON";
    case 0x05: return "X1_MOUSE_BUTTON";
    case 0x06: return "X2_MOUSE_BUTTON";
    case 0x08: return "BACKSPACE";
    case 0x09: return "TAB";
    case 0x0C: return "CLEAR";
    case 0x0D: return "ENTER";
    case 0x10: return "SHIFT";
    case 0x11: return "CTRL";
    case 0x12: return "ALT";
    case 0x13: return "PAUSE";
    case 0x14: return "CAPS_LOCK";
    case 0x1B: return "ESC";
    case 0x1C: return "CONVERT";
    case 0x1D: return "NONCONVERT";
    case 0x1E: return "ACCEPT";
    case 0x1F: return "MODECHANGE";
    case 0x20: return "SPACE";
    case 0x21: return "PAGE_UP";
    case 0x22: return "PAGE_DOWN";
    case 0x23: return "END";
    case 0x24: return "HOME";
    case 0x25: return "LEFT_ARROW";
    case 0x26: return "UP_ARROW";
    case 0x27: return "RIGHT_ARROW";
    case 0x28: return "DOWN_ARROW";
    case 0x29: return "SELECT";
    case 0x2A: return "PRINT";
    case 0x2B: return "EXECUTE";
    case 0x2C: return "PRINT_SCREEN";
    case 0x2D: return "INSERT";
    case 0x2E: return "DELETE";
    case 0x2F: return "HELP";
    case 0x5B: return "LEFT_WIN";
    case 0x5C: return "RIGHT_WIN";
    case 0x5D: return "APPS";
    case 0x5E: return "POWER";
    case 0x5F: return "SLEEP";

        // Alphanumeric keys
    case 0x30: return "0";
    case 0x31: return "1";
    case 0x32: return "2";
    case 0x33: return "3";
    case 0x34: return "4";
    case 0x35: return "5";
    case 0x36: return "6";
    case 0x37: return "7";
    case 0x38: return "8";
    case 0x39: return "9";
    case 0x41: return "A";
    case 0x42: return "B";
    case 0x43: return "C";
    case 0x44: return "D";
    case 0x45: return "E";
    case 0x46: return "F";
    case 0x47: return "G";
    case 0x48: return "H";
    case 0x49: return "I";
    case 0x4A: return "J";
    case 0x4B: return "K";
    case 0x4C: return "L";
    case 0x4D: return "M";
    case 0x4E: return "N";
    case 0x4F: return "O";
    case 0x50: return "P";
    case 0x51: return "Q";
    case 0x52: return "R";
    case 0x53: return "S";
    case 0x54: return "T";
    case 0x55: return "U";
    case 0x56: return "V";
    case 0x57: return "W";
    case 0x58: return "X";
    case 0x59: return "Y";
    case 0x5A: return "Z";

        // Modifier keys
    case 0xA0: return "LEFT_SHIFT";
    case 0xA1: return "RIGHT_SHIFT";
    case 0xA2: return "LEFT_CTRL";
    case 0xA3: return "RIGHT_CTRL";
    case 0xA4: return "LEFT_ALT";
    case 0xA5: return "RIGHT_ALT";

        // Numeric keypad
    case 0x60: return "NUMPAD0";
    case 0x61: return "NUMPAD1";
    case 0x62: return "NUMPAD2";
    case 0x63: return "NUMPAD3";
    case 0x64: return "NUMPAD4";
    case 0x65: return "NUMPAD5";
    case 0x66: return "NUMPAD6";
    case 0x67: return "NUMPAD7";
    case 0x68: return "NUMPAD8";
    case 0x69: return "NUMPAD9";
    case 0x6A: return "NUMPAD_MULTIPLY";
    case 0x6B: return "NUMPAD_ADD";
    case 0x6C: return "NUMPAD_SEPARATOR";
    case 0x6D: return "NUMPAD_SUBTRACT";
    case 0x6E: return "NUMPAD_DECIMAL";
    case 0x6F: return "NUMPAD_DIVIDE";

        // Other keys
    case 0xBA: return "OEM_1"; // For ';:'
    case 0xBB: return "OEM_PLUS"; // For '=+'
    case 0xBC: return "OEM_COMMA"; // For ',<'
    case 0xBD: return "OEM_MINUS"; // For '-_'
    case 0xBE: return "OEM_PERIOD"; // For '.>'
    case 0xBF: return "OEM_2"; // For '/?'
    case 0xC0: return "OEM_3"; // For '`~'
    case 0xDB: return "OEM_4"; // For '[{'
    case 0xDC: return "OEM_5"; // For '\|'
    case 0xDD: return "OEM_6"; // For '] }'
    case 0xDE: return "OEM_7"; // For '''"

    default: return "Unknown";
    }
}