#pragma once
#include <string>
#include <Windows.h>

void UpdatePlayerPosition(const float elapsedTime, const std::wstring& map, float& angle, float& xPos, float& yPos, int mapWidth);
