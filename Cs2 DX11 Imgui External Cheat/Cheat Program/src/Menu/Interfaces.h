#pragma once
#include <ImGui/imgui.h>
#include <Menu/ImGuiCustomElements.h> 
#include <Globals/hGlobals.h>
#include <Inputs/keycodes.h>
#include <Hacks/Config.h>

class Interfaces
{
private:
	class Skills
	{
	public:
		void GetTriggerBotElements()
		{
			C_Elements::Checkbox("TriggerBot", &Flags::enableTriggerbot);
			if (Flags::enableTriggerbot)
			{
				// trigger bot key configuration;
				ImGui::SetNextItemWidth(100.0f);
				C_Elements::InputText(
					"Triggerbot Key Code",
					3.5f,
					Config::TriggerBot::TB_Default_KEYCODE_STR,
					sizeof(Config::TriggerBot::TB_Default_KEYCODE_STR),
					ImGuiInputTextFlags_CharsHexadecimal
				);

				std::stringstream ss(Config::TriggerBot::TB_Default_KEYCODE_STR);
				ss >> std::hex >> Config::TriggerBot::TB_KEYCODE;
				ImGui::Text("Triggerbot Key : %s", KeyCodeToString(Config::TriggerBot::TB_KEYCODE));
				C_Elements::LeaveLine();
			}
		}

		void GetRCSElements()
		{
			C_Elements::Checkbox("Standalone RCS", &Flags::enableRCS);
		}
	};

	class MemoryCheats
	{
	private:
		void DrawAimFovCircle()
		{
			if (Config::Aimbot::ShowFovCircle)
			{
				ImGui::ColorEdit4("Circle Color", (float*)&Config::Aimbot::FovCircleColor);
				C_Elements::SliderFloat("Circle thickness", &Config::Aimbot::FovCircleThickness, 1.0f, 5.0f, "%.1f");

				ImDrawList* draw_list = ImGui::GetForegroundDrawList();
				draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2,
					ImGui::GetIO().DisplaySize.y / 2), Config::Aimbot::AimFov,
					ImGui::ColorConvertFloat4ToU32(Config::Aimbot::FovCircleColor), 100, Config::Aimbot::FovCircleThickness
				);
			}
		}

	public:
		void GetMiscElements()
		{
			C_Elements::Checkbox("Bhop", &Flags::enableBhop);
			C_Elements::Checkbox("Antiflash", &Flags::enableAntiflash);		
			C_Elements::Checkbox("RadarHack", &Flags::enableRadarHack);
		}

		void GlowHackElements()
		{
			C_Elements::Checkbox("Player Glow", &Flags::enableGlowHack);
			if (Flags::enableGlowHack)
			{
				ImGui::SetNextItemWidth(100.0f);
				if (ImGui::BeginCombo("Glow Color", Config::GlowHack::AvailableColors[Config::GlowHack::CurrentColorIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(Config::GlowHack::AvailableColors); n++)
					{
						bool is_selected = (Config::GlowHack::CurrentColorIndex == n);
						if (ImGui::Selectable(Config::GlowHack::AvailableColors[n], is_selected))
							Config::GlowHack::CurrentColorIndex = n;

						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				switch (Config::GlowHack::CurrentColorIndex) {
				case 0: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::GREEN; break;
				case 1: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::YELLOW; break;
				case 2: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::BLUE; break;
				case 3: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::RED; break;
				case 4: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::WHITE; break;
				case 5: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::PURPLE; break;
				case 6: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::CYAN; break;
				case 7: Config::GlowHack::GlowColor::CurrentGlowColor = Config::GlowHack::GlowColor::LIGHTBLUE; break;
				default: break;
				}

				ImGui::SetNextItemWidth(50.0f);
				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Glow Settings"))
				{
					C_Elements::EndCustomizingCollapsingHeader();
					C_Elements::Checkbox("Team Glow", &Config::GlowHack::GlowSettings::TeamGlow);
					C_Elements::Checkbox("Dead Entity Glow", &Config::GlowHack::GlowSettings::DeadEntityGlow);
					C_Elements::LeaveLine();
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
				}
			}
		}

		void GetAimbotElements()
		{
			C_Elements::Checkbox("Aimbot", &Flags::enableAimbot);
			if (Flags::enableAimbot)
			{
				// trigger bot key configuration;
				ImGui::SetNextItemWidth(100.0f);
				C_Elements::InputText(
					"Aimbot Key Code",
					3.5f,
					Config::Aimbot::AB_Default_KEYCODE_STR,
					sizeof(Config::Aimbot::AB_Default_KEYCODE_STR),
					ImGuiInputTextFlags_CharsHexadecimal
				);

				std::stringstream ss(Config::Aimbot::AB_Default_KEYCODE_STR);
				ss >> std::hex >> Config::Aimbot::AB_KEYCODE;
				ImGui::Text("Aimbot Key : %s", KeyCodeToString(Config::Aimbot::AB_KEYCODE));
				C_Elements::LeaveLine();

				// aimbot settings header configurations;
				C_Elements::BeginCustomizingCollapsingHeader();
				if (ImGui::CollapsingHeader("Aimbot Settings"))
				{
					C_Elements::EndCustomizingCollapsingHeader();

					// aim position combo box configuration;
					ImGui::SetNextItemWidth(100.0f);
					if (ImGui::BeginCombo("Aim Position", Config::Aimbot::AimPositions[Config::Aimbot::CurrentAimPosIndex])) // "Select Item" is the label of the combo box
					{
						for (int n = 0; n < IM_ARRAYSIZE(Config::Aimbot::AimPositions); n++)
						{
							bool is_selected = (Config::Aimbot::CurrentAimPosIndex == n);
							if (ImGui::Selectable(Config::Aimbot::AimPositions[n], is_selected))
								Config::Aimbot::CurrentAimPosIndex = n;

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					// aim fov configuration;
					C_Elements::SliderFloat("Aimbot Fov", &Config::Aimbot::AimFov, 0.0f, 360.0f);
					C_Elements::SliderFloat("Smoothness", &Config::Aimbot::AimSmoothness, 0.1f, 1.0f, "%.1f");

					// aim fov circle configuration;
					C_Elements::Checkbox("Show Fov Circle", &Config::Aimbot::ShowFovCircle);

					DrawAimFovCircle();
					C_Elements::LeaveLine();
				}
				else
				{
					C_Elements::EndCustomizingCollapsingHeader();
					DrawAimFovCircle();
					C_Elements::LeaveLine();
				}
			}
		}
		friend void RenderMenu();
	};

	friend void RenderMenu();
};

void RenderMenu()
{
	Interfaces::MemoryCheats memorycheats;
	Interfaces::Skills skills;

	ImGui::SetNextWindowSizeConstraints(ImVec2(400, 450), ImVec2(1366, 768));
	C_Elements::CustomizeMenuTitleBar();
	ImGui::Begin("Cs2 External Overlay Menu By NeoXa7");
	
	if (ImGui::BeginTabBar("Cheats Type"))
	{
		if (ImGui::BeginTabItem("Skills"))
		{
			C_Elements::LeaveLine();
			ImGui::TextColored(ImVec4(0, 183, 0, 255), "Safe to Use! No Memory Written!");
			skills.GetTriggerBotElements();
			skills.GetRCSElements();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Memory"))
		{
			C_Elements::LeaveLine();
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not Safe to Use! Memory Written!");
			memorycheats.GetMiscElements();
			memorycheats.GlowHackElements();
			memorycheats.GetAimbotElements();
			ImGui::EndTabItem();
		}
		else
		{
			memorycheats.DrawAimFovCircle();
		}

		ImGui::EndTabBar();
	}
	else
	{
		memorycheats.DrawAimFovCircle();
	}

	ImGui::End();
}

