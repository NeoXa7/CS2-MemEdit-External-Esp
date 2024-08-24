#pragma once
#include <ImGui/imgui.h>
#include <Fonts/Roboto/Roboto_Bold.h>
#include <D3DX11/DX11Loader.h>
#include <Images/iVisuals.hpp>

namespace ImGui_Resource_Loader
{
	
	inline bool LoadImages(ID3D11Device* device)
	{
		// load images;
		bool example_image = D3DX11_Loader::LoadImageByMemory(device, Visuals, sizeof(Visuals), &D3DX11_Loader::ImageResource);
		if (!example_image)
			return false;
	}


	inline bool LoadStyles()
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