using System;
using System.Collections.Concurrent;
using System.Numerics;
using System.Runtime.InteropServices;
using Globals;
using ImGuiNET;
using ClickableTransparentOverlay;
using MemEdit;
using Menu_Elements;
using cs2_External_Cheat.Hacks;



namespace Renderer
{
    public class Renderer : Overlay
    {
        [DllImport("user32.dll")]
        static extern short GetAsyncKeyState(int vKey);

        public Vector2 screenSize = new Vector2(1366, 768);

        // entities copy , using more thread safe methods.
        private ConcurrentQueue<Entity> entities = new ConcurrentQueue<Entity>();
        private Entity localPlayer = new Entity();
        private readonly object entitylock = new object();

        

        //draw list
        ImDrawListPtr drawList;
        protected override void Render()
        {
            ImGui.SetNextWindowSizeConstraints(new Vector2(700, 450), new Vector2(1366, 768));
            ImGui.Begin("CS2 External Cheat By NeoXa7", ImGuiWindowFlags.NoSavedSettings | ImGuiWindowFlags.NoBringToFrontOnFocus);

            if (ImGui.BeginTabBar("Hack Tabs"))
            {
                Elements.VisualsTab();
                Elements.SkillsTab();
                Elements.MiscTab();
                ImGui.EndTabBar();
            }
            
            ImGui.End();

            DrawOverlay(screenSize);
            drawList = ImGui.GetWindowDrawList();
            if (Menu_Bools.enableEsp)
            {
                foreach (var entity in entities)
                {
                    // check if entities are on screen and not teammates unless team ESP is enabled
                    bool isTeammate = localPlayer.team == entity.team;
                    if (EntityonScreen(entity) && (Menu_Bools.enableTeamEsp || !isTeammate))
                    {
                        DrawHealthBar(entity);
                        DrawName(entity, 20);
                        Drawbox(entity);
                        Drawline(entity);
                        DrawBones(entity);
                    }
                }
            }

        }

        
        public bool EntityonScreen(Entity entity)
        {
            if (entity.position2D.X > 0 && entity.position2D.X < screenSize.X && entity.position2D.Y > 0 && entity.position2D.Y < screenSize.Y)
            {
                return true;
            }
            return false;
        }


        // drawing methods

        public void DrawBones(Entity entity)
        {
            if (Menu_Bools.enableBoneEsp)
            {
                uint uintColor = ImGui.ColorConvertFloat4ToU32(CheatsConfigurations.boneColor);

                float currentBoneThickness = CheatsConfigurations.boneThickness / entity.distance;

                drawList.AddLine(entity.bones2d[1], entity.bones2d[2], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[1], entity.bones2d[3], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[1], entity.bones2d[6], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[3], entity.bones2d[4], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[6], entity.bones2d[7], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[4], entity.bones2d[5], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[7], entity.bones2d[8], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[1], entity.bones2d[0], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[0], entity.bones2d[9], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[0], entity.bones2d[11], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[9], entity.bones2d[10], uintColor, currentBoneThickness);
                drawList.AddLine(entity.bones2d[11], entity.bones2d[12], uintColor, currentBoneThickness);
                drawList.AddCircleFilled(entity.bones2d[2], 3 + currentBoneThickness, uintColor);
            }
        }

        public void DrawName(Entity entity, int yOffset)
        {
            if (Menu_Bools.enableNameEsp)
            {
                Vector4 nameColor = localPlayer.team == entity.team ? CheatsConfigurations.teamNameColor : CheatsConfigurations.enemyNameColor;
                Vector2 textPosition = new Vector2(entity.viewPosition2D.X, entity.viewPosition2D.Y - yOffset);
                drawList.AddText(textPosition, ImGui.ColorConvertFloat4ToU32(nameColor), $"{entity.name}");
            }
        }

        public void Drawbox(Entity entity)
        {
            if (Menu_Bools.enableBoxEsp)
            {
                // calcualte box hieght
                float entityHieght = entity.position2D.Y - entity.viewPosition2D.Y;

                Vector2 rectTop = new Vector2(entity.viewPosition2D.X - entityHieght / 2, entity.viewPosition2D.Y);

                Vector2 rectBottom = new Vector2(entity.position2D.X + entityHieght / 2, entity.position2D.Y);

                // get correct color
                Vector4 boxColor = localPlayer.team == entity.team ? CheatsConfigurations.teamBoxColor : CheatsConfigurations.enemyBoxColor;
                Vector4 textColor = localPlayer.team == entity.team ? CheatsConfigurations.teamBoxColor : CheatsConfigurations.enemyBoxColor;

                drawList.AddRect(rectTop, rectBottom, ImGui.ColorConvertFloat4ToU32(boxColor));
            }


        }

        public void Drawline(Entity entity)
        {
            if (Menu_Bools.enableLineEsp)
            {
                Vector4 lineColor = localPlayer.team == entity.team ? CheatsConfigurations.teamLinesColor : CheatsConfigurations.enemyLinesColor;
                drawList.AddLine(new Vector2(screenSize.X / 2, screenSize.Y / 2), entity.position2D, ImGui.ColorConvertFloat4ToU32(lineColor));
            }
        }

        public void DrawHealthBar(Entity entity)
        {
            if (Menu_Bools.enableHealthBarEsp)
            {
                float entityHeight = entity.position2D.Y - entity.viewPosition2D.Y;
                float boxLeft = entity.viewPosition2D.X - entityHeight / 2;
                float boxRight = entity.viewPosition2D.X + entityHeight / 3;

                float barPercentWidth = 0.05f;
                float barPixelWidth = barPercentWidth * (boxRight - boxLeft);
                float barHeight = entityHeight * (entity.health / 100f);

                Vector2 barTop = new Vector2(boxLeft - barPixelWidth, entity.position2D.Y - barHeight);
                Vector2 barBottom = new Vector2(boxLeft, entity.position2D.Y);

                // bar color

                Vector4 barColor = new Vector4(0, 1, 0, 1);
                drawList.AddRectFilled(barTop, barBottom, ImGui.ColorConvertFloat4ToU32(barColor));
            }
        }
        // updateEntities
        public void UpdateEntities(IEnumerable<Entity> newEntities)
        {
            entities = new ConcurrentQueue<Entity>(newEntities);
        }


        // updateLocalPlayer
        public void UpdateLocalPlayer(Entity newEntity)
        {
            lock (entitylock)
            {
                localPlayer = newEntity;
            }
        }


        // get localplayer
        public Entity GetLocalPlayer()
        {
            lock (entitylock)
            {
                return localPlayer;
            }
        }

        void DrawOverlay(Vector2 screenSize) // overlay window
        {
            ImGui.SetNextWindowSize(screenSize);
            ImGui.SetNextWindowPos(new Vector2(0, 0));
            ImGui.Begin("overlay", ImGuiWindowFlags.NoDecoration
                | ImGuiWindowFlags.NoBackground
                | ImGuiWindowFlags.NoBringToFrontOnFocus
                | ImGuiWindowFlags.NoMove
                | ImGuiWindowFlags.NoInputs
                | ImGuiWindowFlags.NoCollapse
                | ImGuiWindowFlags.NoScrollbar
                | ImGuiWindowFlags.NoScrollWithMouse
                );
        }

    }
}