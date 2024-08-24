#include "../Cheats/Hacks/hacks.h"

HANDLE Memory::processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, cs2_process_info::procID);

void _cheat_InitProgram()
{
    if (Memory::processHandle == 0) {
        SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // red
        cerr << "processHandle not found Error: " << GetLastError() << endl;
        SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // white
    }

    // your Cheat logic here;
    while (true)
    {
        player.Initialize();
        game.Initialize();

        if (player.localPlayerHealth <= 0)
            continue;

        HACKS::safe_hacks::retrieve_bomb_info();
        if (GetAsyncKeyState(Settings::Trigger_bot::FIRE_KEY))
            HACKS::safe_hacks::trigger_bot();  
        
        HACKS::safe_hacks::recoil_control_system();
        HACKS::risky_hacks::glow(Settings::glow_hack::glow_color::GREEN);        

       if (GetAsyncKeyState(Settings::Aimbot::key))
           HACKS::risky_hacks::aimbot();
    }    
}

int main()
{
    ProcessManager::CheckProcess(cs2_process_info::procID, L"cs2.exe");
    ProcessManager::CheckBaseAddress(cs2_process_info::clientAddress);
    _cheat_InitProgram();
}
