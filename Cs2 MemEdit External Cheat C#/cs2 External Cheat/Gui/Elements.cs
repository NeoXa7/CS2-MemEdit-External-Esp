using Globals;
using ImGuiNET;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Menu_Elements
{
    public static class Elements
    {
        public static void VisualsTab()
        {
            if (ImGui.BeginTabItem("Visuals"))
            {
                ImGui.Text("Safe to Use No Detection");
                ImGui.Checkbox("Enable ESP", ref Menu_Bools.enableEsp);
                if (Menu_Bools.enableEsp)
                {
                    ImGui.Checkbox("Draw Box", ref Menu_Bools.enableBoxEsp);
                    ImGui.Checkbox("Draw Lines", ref Menu_Bools.enableLineEsp);
                    ImGui.Checkbox("Draw Names", ref Menu_Bools.enableNameEsp);
                    ImGui.Checkbox("Draw Health Bar", ref Menu_Bools.enableHealthBarEsp);
                    ImGui.Checkbox("Draw Bones", ref Menu_Bools.enableBoneEsp);
                    ImGui.Checkbox("Enable Team ESP", ref Menu_Bools.enableTeamEsp);

                    if (ImGui.CollapsingHeader("ESP Settings"))
                    {
                        ImGui.ColorEdit4("Enemy Box Color", ref CheatsConfigurations.enemyBoxColor);
                        ImGui.ColorEdit4("Enemy Lines Color", ref CheatsConfigurations.enemyLinesColor);                      
                        ImGui.ColorEdit4("Bone Color", ref CheatsConfigurations.boneColor);
                        if (Menu_Bools.enableTeamEsp)
                        {
                            ImGui.ColorEdit4("Team Box Color", ref CheatsConfigurations.teamBoxColor);
                            ImGui.ColorEdit4("Team Lines Color", ref CheatsConfigurations.teamLinesColor);
                        }
                    }
                }

                ImGui.EndTabItem();
            }
        }

        public static void SkillsTab()
        {           
            if (ImGui.BeginTabItem("Skills"))
            {
                ImGui.Text("Safe to Use No Detection");
                ImGui.Checkbox("JumpShot", ref Menu_Bools.enableJumpShot);
                if(Menu_Bools.enableJumpShot)
                {
                     ImGui.InputInt("Jump Shot KeyCode", ref CheatsConfigurations.jumpShotKeyCode);
                }
                
                ImGui.Checkbox("Triggerbot", ref Menu_Bools.enableTriggerBot);
                if (Menu_Bools.enableTriggerBot)
                {
                    ImGui.InputInt("Triggerbot KeyCode", ref CheatsConfigurations.triggerBotKeyCode);
                }
                ImGui.EndTabItem();
            }
        }

        public static void MiscTab()
        {
            if (ImGui.BeginTabItem("Miscs"))
            {
                ImGui.Text("This cheats writes memory #UNSAFE to use");
                ImGui.Checkbox("Radar Hack ", ref Menu_Bools.enableRadar);
                ImGui.Checkbox("Anti FlashBang", ref Menu_Bools.enableAntiFlash);
                ImGui.EndTabItem();
            }
        }
    }
}
