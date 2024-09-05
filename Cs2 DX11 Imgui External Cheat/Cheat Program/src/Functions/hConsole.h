#pragma once
#include <Globals/hIncludes.h>

void CreateConsoleWindow(const wchar_t* title, int Width = 1000, int Height = 600)
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&file, "CONIN$", "r", stdin);   // Redirect stdin
	freopen_s(&file, "CONERR$", "w", stderr); // Redirect stderr

	SetConsoleTitle(title);

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow != NULL)
	{
		MoveWindow(consoleWindow, 100, 100, Width, Height, TRUE);
	}
}

void CreateLogNotification(const std::string& logFileName) {
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	std::cout
		<< " [INFO] "
		<< "Memory Logs have been created at: "
		<< logFileName
		<< " ("
		<< std::put_time(&localTime, "%Y-%m-%d %H:%M:%S")
		<< ")"
		<< std::endl;
}