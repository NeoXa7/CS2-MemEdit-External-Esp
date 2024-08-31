using System.Numerics;
using MemEdit;



namespace Globals
{
    public static class CS2
    {
        private static memEdit memEdit = new memEdit("cs2");

        public static string processName = "cs2";
        public static string moduleName = "client.dll";
        public static int procID = memEdit.GetProcessID(processName);
        public static IntPtr client = memEdit.GetModuleBase(moduleName);
    }

    public static class Menu_Bools
    {
        // visuals;
        public static bool enableEsp = true;
        public static bool enableBoxEsp = true;
        public static bool enableHealthBarEsp = true;
        public static bool enableNameEsp = false;
        public static bool enableLineEsp = false;     
        public static bool enableBoneEsp = false;
        public static bool enableTeamEsp = false;

        // miscs;
        public static bool enableAntiFlash = false;
        public static bool enableRadar = false;

        // skills;
        public static bool enableJumpShot = false;
        public static bool enableTriggerBot = false;
    }

    public static class CheatsConfigurations
    {
        // vector 4 colors
        public static Vector4 enemyBoxColor = new Vector4(1, 1, 1, 1); // default white
        public static Vector4 enemyLinesColor = new Vector4(1, 1, 1, 1); // default white

        public static Vector4 teamBoxColor = new Vector4(0, 0, 0, 1); //  default black
        public static Vector4 teamLinesColor = new Vector4(0, 0, 0, 1); //  default black

        public static Vector4 teamNameColor = new Vector4(0, 183, 0, 1); //  default green
        public static Vector4 enemyNameColor = new Vector4(1, 0, 0, 1); //  default red

        public static Vector4 boneColor = new Vector4(1, 1, 1, 1); // default white

        public static float boneThickness = 4;

        public static int jumpShotKeyCode = 0x12; // Default hotkey
        public static int triggerBotKeyCode = 0xA0; // Default hotkey 
    }

    public static class Offsets
    {
        //buttons.cs
        public static int jump = 0x17CC530;
        public static int dwForceAttack = 0x17CC020;

        //offsets.cs     
        public static int dwEntityList = 0x19684F8;
        public static int dwViewMatrix = 0x19CA480;
        public static int dwLocalPlayerPawn = 0x17D37F0;

        //client.cs
        public static int m_vOldOrigin = 0x1274;
        public static int m_iTeamNum = 0x3C3;
        public static int m_lifeState = 0x328;
        public static int m_hPlayerPawn = 0x7EC;
        public static int m_vecViewOffset = 0xC50;
        public static int m_iszPlayerName = 0x640;
        public static int m_iHealth = 0x324;
        public static int m_modelState = 0x170;
        public static int m_pGameSceneNode = 0x308;
        public static int m_entitySpottedState = 0x2288;
        public static int m_bSpotted = 0x8;
        public static int m_flFlashBangTime = 0x1348;
        public static int m_fFlags = 0x3CC;
        public static int m_vecAbsVelocity = 0x3D0;
        public static int m_iIDEntIndex = 0x13A8; 
    }
}
