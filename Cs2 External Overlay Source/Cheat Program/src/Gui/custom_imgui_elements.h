#pragma once

#include <ImGui/imgui_internal.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include "elements_config.h"

using namespace Elements_Config;

namespace C_Elements
{
	inline void CenterButtons(vector<string> names, vector<int> index, int& selected_index)
	{
		vector<ImVec2> sizes = {};
		float total_area = 0.0f;

		const auto& style = ImGui::GetStyle();

		for (string& name : names)
		{
			const ImVec2 label_size = ImGui::CalcTextSize(name.c_str(), 0, true);
			ImVec2 size = ImGui::CalcItemSize(ImVec2(), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
			size.x += 35.f;
			size.y += 5.f;

			sizes.push_back(size);
			total_area += size.x;
		}

		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (total_area / 2));
		for (uint32_t i = 0; i < names.size(); i++)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 70);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

			if (selected_index == index[i])
			{
				// Modify selected button color here
				ImGui::PushStyleColor(ImGuiCol_Button, ImColor(24, 24, 26, 255).Value);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(28, 28, 28, 255).Value);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(24, 24, 26, 255).Value);

				if (ImGui::Button(names[i].c_str(), sizes[i]))
					selected_index = index[i];

				ImGui::PopStyleColor(3);
			}
			else
			{
				// Modify unselected button color here
				ImGui::PushStyleColor(ImGuiCol_Button, ImColor(18, 17, 18, 255).Value);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(18, 17, 18, 255).Value);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(19, 19, 18, 255).Value);
				if (ImGui::Button(names[i].c_str(), sizes[i]))
					selected_index = index[i];
			}

			ImGui::PopStyleVar();
			if (i != names.size() - 1)
				ImGui::SameLine();

		}
	}

	inline void CenterText(const char* format, const float y_padding = 0.0f, ImColor color = ImColor(255, 255, 255))
	{
		const ImVec2 text_size = ImGui::CalcTextSize(format);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (text_size.x / 2));


		if (y_padding > 0.0f)
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
		ImGui::TextColored(color, format);
	}

	inline void Checkbox(const char* format, bool* value)
	{
		const auto& style = ImGui::GetStyle();

		// Set the background color based on whether the checkbox is checked
		if (*value)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBox_cfg::CheckBoxCheckedBackgroundColor.Value);       // purple background when checked
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBox_cfg::CheckBoxCheckedBackgroundColor.Value); // Slightly brighter green when hovered
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBox_cfg::CheckBoxCheckedBackgroundColor.Value);  // Even brighter green when active (clicked)
			ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckBox_cfg::CheckMarkColor.Value);
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBox_cfg::CheckBoxNotCheckedBackgroundColor.Value);       // Dark gray background when unchecked
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBox_cfg::CheckBoxNotCheckedBackgroundColor.Value); // Slightly brighter gray when hovered
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBox_cfg::CheckBoxNotCheckedBackgroundColor.Value);  // Even brighter gray when active (clicked)
		}


		// Push additional style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, CheckBox_cfg::BorderSize);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.5f, 1.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, CheckBox_cfg::Roundness); // Set the rounding (adjust 5.0f to your liking)

		// Push the border color
		ImGui::PushStyleColor(ImGuiCol_Border, CheckBox_cfg::BorderColor.Value);

		// Create the checkbox
		ImGui::Checkbox(format, value);

		// Pop the style colors and variables
		ImGui::PopStyleColor(5); // Pop 4 because we pushed 4 style colors (3 for FrameBg states, 1 for Border)
		ImGui::PopStyleVar(3);   // Pop 3 because we added 3 style vars

		// Optional: Dummy element for spacing
		ImGui::Dummy(ImVec2());
	}

	inline void CustomizeMenuTitleBar()
	{
		// Get the current ImGui style
		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();

		// Customize the menu title bar colors
		style.Colors[ImGuiCol_TitleBg] = TitleBar::TitleBarBG; // Background color of the title bar
		style.Colors[ImGuiCol_TitleBgActive] = TitleBar::TitleBarBG; // Background color when the title bar is active (hovered/focused)

	}

	inline void InputText(const char* label, ImColor button_color, ImColor text_color, float roundness, char* buf, size_t buf_size, auto inputTextFlag, ImVec2 size = ImVec2(0, 0))
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Create the custom InputText widget
		ImGui::InputText(label, buf, buf_size, inputTextFlag);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(4); // Pop the 4 style colors
		ImGui::PopStyleVar(2);   // Pop the 2 style variables
	}

	inline void InputFloat(const char* label,float roundness, float* value)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImColor button_color = Input::Input_BGColor;
		ImColor text_color = Input::Input_TextColor;;

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		ImGui::InputFloat(label, value);
	}

	inline void InputInt(const char* label, float roundness, int* value)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImColor button_color = ImColor(29, 46, 72, 255);
		ImColor text_color = ImColor(255, 255, 255, 255);

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Disable step buttons by setting the step to zero
		ImGui::InputInt(label, value);

		// Pop custom style colors and variables
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void InputIntHex(const char* label, float roundness, int* value)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImColor button_color = ImColor(29, 46, 72, 255);
		ImColor text_color = ImColor(255, 255, 255, 255);

		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		// Create a buffer to hold the hexadecimal string
		char hexValue[16];
		snprintf(hexValue, sizeof(hexValue), "0x%X", *value); // Format the integer as hex

		ImGui::SetNextItemWidth(100.0f);
		// Display the hexadecimal value in an input text box
		if (ImGui::InputText(label, hexValue, sizeof(hexValue), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase))
		{
			// Convert the hexadecimal string back to an integer using sscanf_s
			sscanf_s(hexValue, "%x", value);
		}

		// Pop custom style colors and variables
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f")
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Save original style values to restore later
		float originalFrameRounding = style.FrameRounding;
		float originalGrabRounding = style.GrabRounding;
		ImVec4 originalSliderGrab = style.Colors[ImGuiCol_SliderGrab];
		ImVec4 originalSliderGrabActive = style.Colors[ImGuiCol_SliderGrabActive];
		ImVec4 originalFrameBg = style.Colors[ImGuiCol_FrameBg];

		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding

		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(29, 46, 72, 255).Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(29, 46, 72, 255).Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(29, 46, 72, 255).Value); // Background color of the slider track when clicked

		// Create the custom slider widget
		ImGui::SliderFloat(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(3); // Pop the 3 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d")
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Save original style values to restore later
		float originalFrameRounding = style.FrameRounding;
		float originalGrabRounding = style.GrabRounding;
		ImVec4 originalSliderGrab = style.Colors[ImGuiCol_SliderGrab];
		ImVec4 originalSliderGrabActive = style.Colors[ImGuiCol_SliderGrabActive];
		ImVec4 originalFrameBg = style.Colors[ImGuiCol_FrameBg];

		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding

		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(29, 46, 72, 255).Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(29, 46, 72, 255).Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(29, 46, 72, 255).Value); // Background color of the slider track when clicked

		// Create the custom slider widget
		ImGui::SliderInt(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(3); // Pop the 3 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void BeginCustomizingCollapsingHeader(float header_roundess = 3.5f)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4 headerColor = ImColor(25, 47, 73, 255); // Header background color
		ImVec4 headerHoveredColor = ImColor(32, 58, 94, 255); // Header background color when hovered
		ImVec4 headerActiveColor = ImColor(25, 47, 73, 255); // Header background color when clicked
		ImVec4 textColor = ImColor(255, 255, 255, 255); // Text color

		// Draw custom header background
		ImGui::PushStyleColor(ImGuiCol_Header, headerColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, headerHoveredColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, headerActiveColor);
		ImGui::PushStyleColor(ImGuiCol_Text, textColor);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, header_roundess); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.5, 2.5)); // Adjust padding
	}

	inline void EndCustomizingCollapsingHeader()
	{
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(2);
	}

}