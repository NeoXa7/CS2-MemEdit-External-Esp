#pragma once

#include <Gui/custom_imgui_elements.h>

namespace Elements_Config
{
	namespace CheckBox_cfg
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

		ImColor BorderColor = ImColor(10, 10, 0, 255);

		float BorderSize = 0;
		float Roundness = 5.0f;
	}

	namespace TitleBar
	{
		ImColor TitleBarBG = ImColor(116, 84, 183, 255);
	}

	namespace Input
	{
		ImColor Input_BGColor = ImColor(29, 46, 72, 255);
		ImColor Input_TextColor = ImColor(255, 255, 255, 255);
		float Roundness = 3.5;
	}
	
}