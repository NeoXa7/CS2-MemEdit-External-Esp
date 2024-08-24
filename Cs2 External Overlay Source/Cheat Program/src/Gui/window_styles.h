#pragma once
#include <ImGui/imgui_internal.h>
#include <Fonts/Roboto/Roboto_Black_Italic.h>
#include <Fonts/Roboto/Roboto_Bold.h>
#include <Fonts/Roboto/Roboto_Regular.h>


namespace Menu
{

	inline bool ApplyStyles()
	{
		// loading fonts;
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		io.LogFilename = nullptr;
		io.IniFilename = nullptr;

		// window styles;
		style.WindowRounding = 5;

		// loading fonts;
		io.Fonts->AddFontFromMemoryTTF(roboto_bold, sizeof(roboto_bold), 15.0f);
		return true;
	}
}