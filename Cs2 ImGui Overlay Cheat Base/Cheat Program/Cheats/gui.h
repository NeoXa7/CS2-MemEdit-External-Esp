#pragma once
#include "../src/Globals/hIncludes.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <Globals/hGlobals.h>



void RenderItems()
{
	ImGui::Begin("Overlay Menu");
	ImGui::Button("button1");
	ImGui::Checkbox("CheckBox", &globals::antiflash);
	ImGui::End();
}