#pragma once
#include "../src/Globals/hIncludes.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <Globals/hGlobals.h>
#include <Hacks/hacks.h>
#include <Gui/custom_imgui_elements.h>


class Hack_Elements
{
private:
    void GetTriggerBotElements()
    {
        C_Elements::Checkbox("Trigger Bot", &menu_bools::triggerbot);
        if (menu_bools::triggerbot)
        {
            // trigger bot key configuration;
            ImGui::SetNextItemWidth(100.0f);
            C_Elements::InputText(
                "Triggerbot Key Code",
                Input::Input_BGColor,
                Input::Input_TextColor,
                Input::Roundness,
                menu_items::keyCodeStrTB,
                sizeof(menu_items::keyCodeStrTB),
                ImGuiInputTextFlags_CharsHexadecimal
            );
            
            std::stringstream ss(menu_items::keyCodeStrTB);
            ss >> std::hex >> menu_items::keyCode_triggerBot;
            ImGui::Text("Triggerbot Key : %s", KeyCodeToString(menu_items::keyCode_triggerBot));
        }
    }

    void GetRcsElements()
    {
        C_Elements::Checkbox("Recoil Control System (RCS)", &menu_bools::rcs);
        ImGui::SetNextItemWidth(150.0f);
        if (menu_bools::rcs)
            C_Elements::InputFloat(
                "RCS Sensitivity",
                3.5,
                &menu_items::rcs_sesni_input_value
            );
    }

    void GetAimbotElements()
    {
        ImGui::Dummy(ImVec2());
        C_Elements::Checkbox("Aimbot", &menu_bools::aimbot_hack);
        if (menu_bools::aimbot_hack)
        {
            // aimbot key configuration;
            ImGui::SetNextItemWidth(100.0f);          
            C_Elements::InputText(
                "Aimbot Key Code", 
                ImColor(29, 46, 72, 255),
                ImColor(255, 255, 255, 255),
                3.5,
                menu_items::keyCodeStrAimBot, 
                sizeof(menu_items::keyCodeStrAimBot),
                ImGuiInputTextFlags_CharsHexadecimal
            );
            
            std::stringstream sss(menu_items::keyCodeStrAimBot);
            sss >> std::hex >> menu_items::keyCode_AimBot;
            ImGui::Text("Aimbot Key : %s", KeyCodeToString(menu_items::keyCode_AimBot));

            // aimbot settings header configurations;
            ImGui::Dummy(ImVec2());
            C_Elements::BeginCustomizingCollapsingHeader();
            if (ImGui::CollapsingHeader("Aimbot Settings"))
            {
                C_Elements::EndCustomizingCollapsingHeader();
                
                // aim position combo box configuration;
                ImGui::SetNextItemWidth(100.0f);
                if (ImGui::BeginCombo("Aim Position", menu_items::aim_positions[menu_items::aim_positions_index])) // "Select Item" is the label of the combo box
                {
                    for (int n = 0; n < IM_ARRAYSIZE(menu_items::aim_positions); n++)
                    {
                        bool is_selected = (menu_items::aim_positions_index == n);
                        if (ImGui::Selectable(menu_items::aim_positions[n], is_selected))
                            menu_items::aim_positions_index = n;

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                // aim fov configuration;
                C_Elements::SliderFloat("Aimbot Fov", &menu_items::aimbot_fov_slider_value, 0.0f, 360.0f);
                C_Elements::SliderFloat("Smoothness", &Settings::Aimbot::aim_smooth_Factor, 1.f, 0.1f);

                // aim fov circle configuration;
                C_Elements::Checkbox("Show Fov Circle", &menu_items::showCircle);

                if (menu_items::showCircle)
                {                 
                    ImGui::ColorEdit4("Circle Color", (float*)&menu_items::fovCircleColor);
                    C_Elements::SliderFloat("Circle thickness", &menu_items::fov_circle_thickness, 1.5f, 10.0f);

                    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                    draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2,
                        ImGui::GetIO().DisplaySize.y / 2), menu_items::aimbot_fov_slider_value,
                        ImGui::ColorConvertFloat4ToU32(menu_items::fovCircleColor), 100, menu_items::fov_circle_thickness
                    );

                }              
                ImGui::Dummy(ImVec2());
            }
            else
            {
                C_Elements::EndCustomizingCollapsingHeader();
                if (menu_items::showCircle)
                {
                    // aim fov circle configuration;           
                    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                    draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2,
                        ImGui::GetIO().DisplaySize.y / 2), menu_items::aimbot_fov_slider_value,
                        ImGui::ColorConvertFloat4ToU32(menu_items::fovCircleColor), 100, menu_items::fov_circle_thickness
                    );
                }
                ImGui::Dummy(ImVec2());
            }               
        }
    }

    void GetGlowHackElements()
    {
        C_Elements::Checkbox("Player Glow", &menu_bools::glow_hack);
        if (menu_bools::glow_hack)
        {
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::BeginCombo("Glow Color", menu_items::glow_colors_name[menu_items::glow_color_index])) // "Select Item" is the label of the combo box
            {
                for (int n = 0; n < IM_ARRAYSIZE(menu_items::glow_colors_name); n++)
                {
                    bool is_selected = (menu_items::glow_color_index == n);
                    if (ImGui::Selectable(menu_items::glow_colors_name[n], is_selected))
                        menu_items::glow_color_index = n;

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            switch (menu_items::glow_color_index) {
            case 0: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::GREEN; break;
            case 1: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::YELLOW; break;
            case 2: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::BLUE; break;
            case 3: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::RED; break;
            case 4: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::WHITE; break;
            case 5: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::PURPLE; break;
            case 6: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::CYAN; break;
            case 7: Settings::glow_hack::glow_color::CurrentGlowColor = Settings::glow_hack::glow_color::LIGHTBLUE; break;
            default: break;
            }

            ImGui::SetNextItemWidth(50.0f);
            C_Elements::BeginCustomizingCollapsingHeader();
            if (ImGui::CollapsingHeader("Glow Settings"))
            {
                C_Elements::EndCustomizingCollapsingHeader();
                C_Elements::Checkbox("Team Glow", &Settings::glow_hack::glow_cfg::teamGlow);
                C_Elements::Checkbox("Dead Entity Glow", &Settings::glow_hack::glow_cfg::glow_after_entity_is_Dead);
                ImGui::Dummy(ImVec2());
            }
            else
            {
                C_Elements::EndCustomizingCollapsingHeader();
            }
        }
    }

    friend void RenderGuiMenuElements();
};

class Misc_Elements
{
    void GetOffsetsEditorElements()
    {
        ImGui::Text("Offsets");
        C_Elements::InputIntHex("dwLocalPlayerPawn", 3.5, &Offsets::offsets::dwLocalPlayerPawn);
        C_Elements::InputIntHex("dwEntityList", 3.5, &Offsets::offsets::dwEntityList);
        C_Elements::InputIntHex("dwViewAngles", 3.5, &Offsets::offsets::dwViewAngles);
        C_Elements::InputIntHex("dwViewMatrix", 3.5, &Offsets::offsets::dwViewMatrix);
        C_Elements::InputIntHex("dwGameRules", 3.5, &Offsets::offsets::dwGameRules);


        ImGui::Text("Client");
        C_Elements::InputIntHex("m_iTeamNum", 3.5, &Offsets::client_dll::m_iTeamNum);
        C_Elements::InputIntHex("m_iHealth", 3.5, &Offsets::client_dll::m_iHealth);
        C_Elements::InputIntHex("m_hPlayerPawn", 3.5, &Offsets::client_dll::m_hPlayerPawn);
        C_Elements::InputIntHex("m_flFlashBangTime", 3.5, &Offsets::client_dll::m_flFlashBangTime);
        C_Elements::InputIntHex("m_iIDEntIndex", 3.5, &Offsets::client_dll::m_iIDEntIndex);
        C_Elements::InputIntHex("m_iShotsFired", 3.5, &Offsets::client_dll::m_iShotsFired);
        C_Elements::InputIntHex("m_aimPunchAngle", 3.5, &Offsets::client_dll::m_aimPunchAngle);
        C_Elements::InputIntHex("m_vOldOrigin", 3.5, &Offsets::client_dll::m_vOldOrigin);
        C_Elements::InputIntHex("m_vecViewOffset", 3.5, &Offsets::client_dll::m_vecViewOffset);
        C_Elements::InputIntHex("m_Glow", 3.5, &Offsets::client_dll::m_Glow);

        C_Elements::InputIntHex("m_glowColorOverride", 3.5, &Offsets::client_dll::m_glowColorOverride);
        C_Elements::InputIntHex("m_bGlowing", 3.5, &Offsets::client_dll::m_bGlowing);
        C_Elements::InputIntHex("m_entitySpottedState", 3.5, &Offsets::client_dll::m_entitySpottedState);
        C_Elements::InputIntHex("m_bSpotted", 3.5, &Offsets::client_dll::m_bSpotted);
        C_Elements::InputIntHex("m_nBombSite", 3.5, &Offsets::client_dll::m_nBombSite);
        C_Elements::InputIntHex("m_flTimerLength", 3.5, &Offsets::client_dll::m_flTimerLength);

        C_Elements::InputIntHex("m_bBombPlanted", 3.5, &Offsets::client_dll::m_bBombPlanted);
        C_Elements::InputIntHex("m_bBombDropped", 3.5, &Offsets::client_dll::m_bBombDropped);
        C_Elements::InputIntHex("m_bBeingDefused", 3.5, &Offsets::client_dll::m_bBeingDefused);
        C_Elements::InputIntHex("m_pCameraServices", 3.5, &Offsets::client_dll::m_pCameraServices);
        C_Elements::InputIntHex("m_iFOV", 3.5, &Offsets::client_dll::m_iFOV);

        C_Elements::InputIntHex("m_bIsScoped", 3.5, &Offsets::client_dll::m_bIsScoped);
        C_Elements::InputIntHex("m_fFlags", 3.5, &Offsets::client_dll::m_fFlags);
        C_Elements::InputIntHex("m_vecAbsVelocity", 3.5, &Offsets::client_dll::m_vecAbsVelocity);
    }

    bool IsTitleBar = true;
    bool IsNoCollapse = false;
    void GetImGuiStylesOptions()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::SetNextItemWidth(50.0f);

        C_Elements::BeginCustomizingCollapsingHeader();
        if (ImGui::CollapsingHeader("Main Menu"))
        {
            ImGui::SetNextItemWidth(220.0f);
            C_Elements::Checkbox("Enable Titlebar", &IsTitleBar);
            if (IsTitleBar)
            {
                ImGui::ColorEdit4("Title Bar Color", (float*)&TitleBar::TitleBarBG);
                C_Elements::Checkbox("Menu No Collapse", &IsNoCollapse);
            }
            ImGui::Dummy(ImVec2());

        }

        if (ImGui::CollapsingHeader("CheckBox"))
        {
            ImGui::SetNextItemWidth(220.0f);
            ImGui::ColorEdit4("Checkbox Background Color", (float*)&CheckBox_cfg::CheckBoxCheckedBackgroundColor);

            ImGui::SetNextItemWidth(220.0f);
            ImGui::ColorEdit4("Checkmark Color", (float*)&CheckBox_cfg::CheckMarkColor);

            ImGui::SetNextItemWidth(220.f);
            C_Elements::SliderFloat("Checkbox Roundness", &CheckBox_cfg::Roundness, 0, 8);

            static bool IsBorder = false;
            C_Elements::Checkbox("Add Border", &IsBorder);
            if (IsBorder)
            {
                ImGui::SetNextItemWidth(150.f);
                C_Elements::SliderFloat("Border Size", (float*)&CheckBox_cfg::BorderSize, 0, 2);

                ImGui::SetNextItemWidth(220.f);
                ImGui::ColorEdit4("Border Color", (float*)&CheckBox_cfg::BorderColor);
            }
            else
            {
                CheckBox_cfg::BorderSize = 0;
            }
        }
        C_Elements::EndCustomizingCollapsingHeader();
    }

    void GetMenuCustomizerElements()
    {
        if (ImGui::Button("Menu Customizer"))
        {
            menu_bools::show_menu_styler = true;
        }

        if (menu_bools::show_menu_styler)
        {
            ImGui::SetNextWindowSizeConstraints(ImVec2(400, 350), ImVec2(1366, 768));
            ImGui::Begin("Customize Menu");

            GetImGuiStylesOptions();
            if (ImGui::Button("Close"))
            {
                menu_bools::show_menu_styler = false;
            }

        }
    }

    friend void RenderGuiMenuElements();
};

Hack_Elements hack_elements;
Misc_Elements misc_elements;

void RenderGuiMenuElements()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::SetNextWindowSizeConstraints(ImVec2(700, 450), ImVec2(1366, 768));

    C_Elements::CustomizeMenuTitleBar();
    
    ImGui::Begin("Cs2 External Menu");

    hack_elements.GetTriggerBotElements();
    hack_elements.GetRcsElements();
    C_Elements::Checkbox("Bhop", &menu_bools::bhop_hack);
    C_Elements::Checkbox("Antiflash", &menu_bools::antiflash_hack);
    C_Elements::Checkbox("Radar Hack", &menu_bools::radar_hack);
    hack_elements.GetGlowHackElements();
    hack_elements.GetAimbotElements();
    //misc_elements.GetMenuCustomizerElements();
   
    ImGui::End();
}

