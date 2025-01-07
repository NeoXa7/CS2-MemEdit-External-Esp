using Globals;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using MemEdit;
using System.Runtime.InteropServices;
using Cheat_Configs;



namespace Risky_Cheats
{
    public static class Cheats
    {
        [DllImport("user32.dll")]
        static extern short GetAsyncKeyState(int vKey);

        // Init MemEdit DLL
        public static memEdit memEdit = new memEdit("cs2");

        public static void JumpShot()
        {       
            IntPtr localPlayerPawn = memEdit.ReadPointer(CS2.client, Offsets.dwLocalPlayerPawn);
            int fFlag = memEdit.ReadInt(localPlayerPawn, Offsets.m_fFlags);

            // character constants for Jumpshot
            const int INAIR = 65664;

            // getting vector3 velocity
            Vector3 velocity;

            if (Menu_Bools.enableJumpShot)
            {
                if (fFlag == INAIR && GetAsyncKeyState(CheatsConfigurations.jumpShotKeyCode) < 0)
                {
                    Thread.Sleep(100);
                    velocity = memEdit.ReadVec(localPlayerPawn, Offsets.m_vecAbsVelocity);

                    while (velocity.Z > 18f || velocity.Z < -18f)
                    {
                        velocity = memEdit.ReadVec(localPlayerPawn, Offsets.m_vecAbsVelocity);
                    }

                    // Simulate mouse click
                    Mouse_inputs.SimulateMouseClick();
                    Thread.Sleep(1000);
                }
            }
        }

        public static void RadarHack()
        {
            IntPtr localPlayerPawn = memEdit.ReadPointer(CS2.client, Offsets.dwLocalPlayerPawn);
            IntPtr entityList = memEdit.ReadPointer(CS2.client, Offsets.dwEntityList);
            IntPtr listEntry = memEdit.ReadPointer(entityList, 0x10);

            if (Menu_Bools.enableRadar)
            {
                for (int i = 0; i < 64; i++)
                {
                    if (listEntry == IntPtr.Zero)
                        continue;

                    IntPtr currentController = memEdit.ReadPointer(listEntry, i * 0x78);
                    if (currentController == IntPtr.Zero)
                        continue;

                    int pawnHandle = memEdit.ReadInt(currentController, Offsets.m_hPlayerPawn);
                    if (pawnHandle == 0)
                        continue;

                    IntPtr listEntry2 = memEdit.ReadPointer(entityList, 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
                    IntPtr currentPawn = memEdit.ReadPointer(listEntry2, 0x78 * (pawnHandle & 0x1FF));

                    string name = memEdit.ReadString(currentController, Offsets.m_iszPlayerName, 16);
                    bool spotted = memEdit.ReadBool(currentPawn, Offsets.m_entitySpottedState + Offsets.m_bSpotted);

                    memEdit.WriteBool(currentPawn, Offsets.m_entitySpottedState + Offsets.m_bSpotted, true);

                    string spottedStatus = spotted == true ? "spotted" : " ";

                    //Console.WriteLine($"{name}: {spottedStatus}");

                }
            }
        }

        public static void AntiFlash()
        {
            IntPtr localPlayerPawn = memEdit.ReadPointer(CS2.client, Offsets.dwLocalPlayerPawn);
            float flashDuration = memEdit.ReadFloat(localPlayerPawn, Offsets.m_flFlashBangTime);

            if (Menu_Bools.enableAntiFlash)
            {
                if (flashDuration > 0)
                {
                    memEdit.WriteFloat(localPlayerPawn, Offsets.m_flFlashBangTime, 0);
                }
            }
        }

        public static void Triggerbot()
        {           
            if (Menu_Bools.enableTriggerBot)
            {
                IntPtr localPlayerPawn = memEdit.ReadPointer(CS2.client, Offsets.dwLocalPlayerPawn);
                IntPtr entityList = memEdit.ReadPointer(CS2.client, Offsets.dwEntityList);
                int entityIndex = memEdit.ReadInt(localPlayerPawn, Offsets.m_iIDEntIndex);
                int localPlayerTeam = memEdit.ReadInt(localPlayerPawn, Offsets.m_iTeamNum);

                if (entityIndex > 0 && GetAsyncKeyState(CheatsConfigurations.triggerBotKeyCode) < 0)
                {
                    IntPtr entityListEntry = memEdit.ReadPointer(entityList, 0x8 * (entityIndex >> 9) + 0x10);
                    IntPtr entity = memEdit.ReadPointer(entityListEntry, 120 * (entityIndex & 0x1FF));

                    int entityTeam = memEdit.ReadInt(entity, Offsets.m_iTeamNum);
                    int entityHealth = memEdit.ReadInt(entity, Offsets.m_iHealth);

                    if (entityTeam != localPlayerTeam && entityHealth > 0)
                    {
                        Mouse_inputs.SimulateMouseClick();
                        Thread.Sleep(1);
                    }
                }
            }
        }
    }
}
