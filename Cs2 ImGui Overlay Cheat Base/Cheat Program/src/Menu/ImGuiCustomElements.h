#pragma once

#include <ImGui/imgui_internal.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

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

	inline void Checkbox(const char* format, bool* value, float box_roundness= 5.0f)
	{
		// when checked;
		ImColor CheckBoxCheckedBackgroundColor = ImColor(116, 84, 183, 255);
		ImColor CheckBoxCheckedBackgroundColorHovered = ImColor(116, 84, 183, 255);
		ImColor CheckBoxCheckedBackgroundColorActive = ImColor(116, 84, 183, 255);
		ImColor CheckMarkColor = ImColor(10, 10, 0, 255);

		// when not checked
		ImColor CheckBoxNotCheckedBackgroundColor = ImColor(29, 46, 72, 255);
		ImColor CheckBoxNotCheckedBackgroundColorHovered = ImColor(29, 46, 72, 255);
		ImColor CheckBoxNotCheckedBackgroundColorActive = ImColor(29, 46, 72, 255);

		// Set the background color based on whether the checkbox is checked
		if (*value)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBoxCheckedBackgroundColor.Value);       // purple background when checked
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBoxCheckedBackgroundColor.Value); // Slightly brighter green when hovered
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBoxCheckedBackgroundColor.Value);  // Even brighter green when active (clicked)
			ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor.Value);
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckBoxNotCheckedBackgroundColor.Value);       // Dark gray background when unchecked
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckBoxNotCheckedBackgroundColor.Value); // Slightly brighter gray when hovered
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckBoxNotCheckedBackgroundColor.Value);  // Even brighter gray when active (clicked)
		}


		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.5f, 1.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, box_roundness);

		ImGui::Checkbox(format, value);

		ImGui::PopStyleColor(5);
		ImGui::PopStyleVar(3);

		ImGui::Dummy(ImVec2());
	}

	inline void BeginCustomizingTitleBar(ImColor TitleBarBGColor, ImColor TitleBarTextColor, ImColor MenuCollapsedBGColor = 12)
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, MenuCollapsedBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, TitleBarBGColor.Value);
		ImGui::PushStyleColor(ImGuiCol_Text, TitleBarTextColor.Value);
	}

	inline void EndCustomizingTitleBar()
	{
		ImGui::PopStyleColor(3);
	}

	inline void InputText(const char* label,  float roundness, char* buf, size_t buf_size, auto inputTextFlag, ImVec2 size = ImVec2(0, 0), ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
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

	inline void InputFloat(const char* label, float roundness, float* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();
		// Push custom style variables
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5)); // Adjust padding

		// Push custom style colors
		ImGui::PushStyleColor(ImGuiCol_FrameBg, button_color.Value); // Background color 
		ImGui::PushStyleColor(ImGuiCol_Text, text_color.Value); // Text color

		ImGui::InputFloat(label, value);

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	inline void InputInt(const char* label,  float roundness, int* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();

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

	inline void InputIntHex(const char* label, float roundness, int* value, ImColor button_color = ImColor(29, 46, 72, 255), ImColor text_color = ImColor(255, 255, 255, 255))
	{
		ImGuiStyle& style = ImGui::GetStyle();

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

	inline void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImColor SliderBGColor = ImColor(29, 46, 72, 255), ImColor SliderGrabColor = ImColor(66, 150, 250, 255), ImColor SliderGrabActiveColor = ImColor(70, 160, 250, 255))
	{
		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, SliderBGColor.Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); // Background color of the slider track when clicked
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

		ImGui::SliderFloat(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(5); // Pop the 5 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void SliderInt(const char* label, int* v, int v_min, float v_max, const char* format = "%d", ImColor SliderBGColor = ImColor(29, 46, 72, 255), ImColor SliderGrabColor = ImColor(66, 150, 250, 255), ImColor SliderGrabActiveColor = ImColor(70, 160, 250, 255))
	{
		// Push custom style variables and colors
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.0f); // Adjust frame rounding
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); // Adjust padding
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 50.0f); // Adjust grab rounding

		ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); // Background color of the slider track
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, SliderBGColor.Value); // Background color of the slider track when hovered
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); // Background color of the slider track when clicked
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

		ImGui::SliderInt(label, v, v_min, v_max, format);

		// Pop the custom style colors and variables
		ImGui::PopStyleColor(5); // Pop the 5 style colors
		ImGui::PopStyleVar(3);   // Pop the 2 style variables
	}

	inline void BeginCustomizingCollapsingHeader(float header_roundess = 3.5f, ImVec4 headerColor = ImColor(25, 47, 73, 255), ImVec4 headerTextColor = ImColor(255, 255, 255, 255), ImVec4 headerHoveredColor = ImColor(32, 58, 94, 255), ImVec4 headerActiveColor = ImColor(25, 47, 73, 255))
	{
		// styling custom header 
		ImGui::PushStyleColor(ImGuiCol_Header, headerColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, headerHoveredColor);
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, headerActiveColor);
		ImGui::PushStyleColor(ImGuiCol_Text, headerTextColor);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, header_roundess); // Adjust roundness
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.5, 2.5)); // Adjust padding
	}

	inline void EndCustomizingCollapsingHeader()
	{
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(2);
	}

}