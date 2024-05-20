#pragma once
#include <string>
#include <windows.h>
#include "ProjectileManager.h"

class Controller {
public:
	void UpdatePlayerPosition(const float elapsedTime, std::wstring& map, float& angle, float& xPos, float& yPos, int mapWidth);
private:
	ProjectileManager projectileManager;
};
