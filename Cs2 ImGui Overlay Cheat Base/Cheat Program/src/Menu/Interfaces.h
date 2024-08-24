#pragma once
#include "../src/Globals/hIncludes.h"

#include <ImGui/imgui.h>
#include <Globals/hGlobals.h>
#include <Menu/ImGuiCustomElements.h>

namespace Interface
{
	inline bool checkbox = false;
	inline float inputFloat = 0;
	inline int inputInt = 0;
	inline int hexInt = 0x78;
	inline float sliderFloat = 0;
	inline int sliderInt = 0;

	void RenderMenuElements()
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(700, 450), ImVec2(1366, 768));
		ImGui::Begin("Overlay Menu");

		C_Elements::CenterText("This is an Custom Center Text");
		C_Elements::Checkbox("Custom CheckBox", &checkbox);
		C_Elements::InputFloat("Custom Float Input", 5.0f, &inputFloat);	
		C_Elements::InputInt("Custom Int Input", 5.0f, &inputInt);
		C_Elements::InputIntHex("Custom HexInt Input", 5.0f, &hexInt);
		C_Elements::SliderFloat("Custom Float Slider", &sliderFloat, 0, 10, "%.1f");
		C_Elements::SliderInt("Custom Int Slider", &sliderInt, 0, 20);
		
		ImGui::End();
	}
}

