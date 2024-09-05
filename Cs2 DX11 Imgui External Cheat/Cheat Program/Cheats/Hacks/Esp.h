#pragma once
#include <ImGui/imgui.h>
#include <Maths/hVector.h>

namespace ESP
{
    inline void DrawBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
    }

    inline void DrawLine(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);
    }

    inline void DrawHealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor color = ImColor(0, 255, 0, 255), float thickness = 2.0f, float barWidth = 7.0f, float offset = 5.0f) {
        float boxHeight = bottomRight.y - topLeft.y;
        float healthHeight = (health / 100.0f) * boxHeight;

        ImVec2 healthTopLeft(topLeft.x - barWidth - offset, bottomRight.y - healthHeight);
        ImVec2 healthBottomRight(topLeft.x - offset, bottomRight.y);

        ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, color, 0.0f, ImDrawFlags_None);
    }

    inline void DrawSkeleton(const std::vector<Vector2>& skeletonPoints, ImU32 color = IM_COL32(255, 255, 255, 255), float thickness = 1.5f) {
        if (skeletonPoints.size() < 15) return;

        // Draw lines between key points to form the skeleton
        DrawLine(skeletonPoints[0], skeletonPoints[1], color, thickness); // Head to Neck
        DrawLine(skeletonPoints[1], skeletonPoints[2], color, thickness); // Neck to Spine

        // Left Arm
        DrawLine(skeletonPoints[1], skeletonPoints[3], color, thickness); // Neck to Left Shoulder
        DrawLine(skeletonPoints[3], skeletonPoints[4], color, thickness); // Left Shoulder to Left Elbow
        DrawLine(skeletonPoints[4], skeletonPoints[5], color, thickness); // Left Elbow to Left Hand

        // Right Arm
        DrawLine(skeletonPoints[1], skeletonPoints[6], color, thickness); // Neck to Right Shoulder
        DrawLine(skeletonPoints[6], skeletonPoints[7], color, thickness); // Right Shoulder to Right Elbow
        DrawLine(skeletonPoints[7], skeletonPoints[8], color, thickness); // Right Elbow to Right Hand

        // Left Leg
        DrawLine(skeletonPoints[2], skeletonPoints[9], color, thickness); // Spine to Left Hip
        DrawLine(skeletonPoints[9], skeletonPoints[10], color, thickness); // Left Hip to Left Knee
        DrawLine(skeletonPoints[10], skeletonPoints[11], color, thickness); // Left Knee to Left Foot

        // Right Leg
        DrawLine(skeletonPoints[2], skeletonPoints[12], color, thickness); // Spine to Right Hip
        DrawLine(skeletonPoints[12], skeletonPoints[13], color, thickness); // Right Hip to Right Knee
        DrawLine(skeletonPoints[13], skeletonPoints[14], color, thickness); // Right Knee to Right Foot
    }

    inline void DrawText(const char* text, const Vector2& position, ImU32 color, bool centered = false)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = ImGui::GetFont(); // Get the current font
        ImVec2 textSize = font->CalcTextSizeA(io.FontGlobalScale, FLT_MAX, 0.0f, text); // Get the size of the text

        if (centered)
        {
            ImVec2 textPos(position.x - textSize.x / 2.0f, position.y - textSize.y / 2.0f);
            ImGui::GetBackgroundDrawList()->AddText(textPos, color, text);
        }
        else
        {
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(position.x, position.y), color, text);
        }
    }

}