using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Globalization;
using MemEdit;
using System.Numerics;
using Globals;
using cs2_External_Cheat.Maths;
using cs2_External_Cheat.Hacks;
using Risky_Cheats;



// Init MemEdit DLL
memEdit memEdit = new memEdit("cs2");

Console.Title = "CS2 EXTERNAL CHEAT";
Console.ForegroundColor = ConsoleColor.Red;
Console.WriteLine(@"
   ___ ___ ___   _____  _______ ___ ___ _  _   _   _     
  / __/ __|_  ) | __\ \/ /_   _| __| _ \ \| | /_\ | |    
 | (__\__ \/ /  | _| >  <  | | | _||   / .` |/ _ \| |__  
  \___|___/___| |___/_/\_\ |_| |___|_|_\_|\_/_/ \_\____| 
                                                                  
 ______   __  _   _          __  __    _____ 
 | __ ) \ / / | \ | | ___  ___\ \/ /__ |___  |
 |  _ \\ V /  |  \| |/ _ \/ _ \\  // _` | / / 
 | |_) || |   | |\  |  __/ (_) /  \ (_| |/ /  
 |____/ |_|   |_| \_|\___|\___/_/\_\__,_/_/
  
  Last Updated 24th August 2024

");
Console.ResetColor();


if (CS2.procID > 0 && CS2.client > 0)
{
    Console.ForegroundColor = ConsoleColor.Yellow;
    Console.WriteLine($"  CS2 Process ID : {CS2.procID}");
    Console.WriteLine($"  Client Address : {CS2.client}");
    Console.WriteLine("  Cheat Attached!");
    Console.ForegroundColor = ConsoleColor.Blue;
    Console.WriteLine(" ");
}
else
{
    Console.ForegroundColor = ConsoleColor.DarkRed;
    Console.WriteLine($"  {CS2.processName}.exe Not found! Process ID : 0 ");
    Console.WriteLine($"  Client Address : {CS2.client}");
    Console.WriteLine("  Cheat Failed To Attach ");
    Console.WriteLine(" ");
}


// Initializing Renderer;
Renderer.Renderer renderer = new Renderer.Renderer();
Thread renderThread = new Thread(new ThreadStart(renderer.Start().Wait));
renderThread.Start();


// Getting ScreenSize from Renderer;
Vector2 screenSize = renderer.screenSize;

// Storing Entities;
List<Entity> entities = new List<Entity>();
Entity localPlayer = new Entity();


while (true)
{
    // Clearing Entities;
    entities.Clear();

    IntPtr entityList = memEdit.ReadPointer(CS2.client, Offsets.dwEntityList);
    IntPtr listEntry = memEdit.ReadPointer(entityList, 0x10);
    IntPtr localPlayerPawn = memEdit.ReadPointer(CS2.client, Offsets.dwLocalPlayerPawn);
    localPlayer.team = memEdit.ReadInt(localPlayerPawn, Offsets.m_iTeamNum);

    // looping through the entity list;
    for (int i = 0; i < 64; i++)
    {
        IntPtr currentController = memEdit.ReadPointer(listEntry, i * 0x78);
        if (currentController == IntPtr.Zero)
            continue;


        int pawnHandle = memEdit.ReadInt(currentController, Offsets.m_hPlayerPawn);
        if (pawnHandle == 0)
            continue;

        IntPtr listEntry2 = memEdit.ReadPointer(entityList, 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
        if (listEntry2 == IntPtr.Zero)
            continue;

        IntPtr currentPawn = memEdit.ReadPointer(listEntry2, 0x78 * (pawnHandle & 0x1FF));
        if (currentPawn == IntPtr.Zero || currentPawn == localPlayerPawn)
            continue;



        int lifeState = memEdit.ReadInt(currentPawn, Offsets.m_lifeState);
        if (lifeState != 256)
            continue;

        float[] viewMatrix = memEdit.ReadMatrix(CS2.client + Offsets.dwViewMatrix);

        IntPtr sceneNode = memEdit.ReadPointer(currentPawn, Offsets.m_pGameSceneNode);
        IntPtr boneMatrix = memEdit.ReadPointer(sceneNode, Offsets.m_modelState + 0x80);

        // populate entity

        Entity entity = new Entity();

        entity.name = memEdit.ReadString(currentController, Offsets.m_iszPlayerName, 16).Split("\0")[0];
        entity.health = memEdit.ReadInt(currentPawn, Offsets.m_iHealth);
        entity.team = memEdit.ReadInt(currentPawn, Offsets.m_iTeamNum);
        entity.position = memEdit.ReadVec(currentPawn, Offsets.m_vOldOrigin);
        entity.viewOffsets = memEdit.ReadVec(currentPawn, Offsets.m_vecViewOffset);
        entity.position2D = Calculate.WorldToScreen(viewMatrix, entity.position, screenSize);
        entity.viewPosition2D = Calculate.WorldToScreen(viewMatrix, Vector3.Add(entity.position, entity.viewOffsets), screenSize);
        entity.distance = Vector3.Distance(entity.position, localPlayer.position);
        entity.bones = Calculate.ReadBones(boneMatrix, memEdit);
        entity.bones2d = Calculate.ReadBones2d(entity.bones, viewMatrix, screenSize);

        entities.Add(entity);
    }

    Cheats.RadarHack();
    Cheats.AntiFlash();
    Cheats.JumpShot();
    Cheats.Triggerbot();

    renderer.UpdateLocalPlayer(localPlayer);
    renderer.UpdateEntities(entities);
}