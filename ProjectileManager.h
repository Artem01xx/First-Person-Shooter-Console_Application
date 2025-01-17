#pragma once
#include <vector>
#include <string>
#include "Projectile.h"

class ProjectileManager
{
public:
	void AddProjectile(float x, float y, float angle);
	void UpdateProjectile(float elapsedTime, std::wstring& map, int mapWidth, int mapHeight, int& score);
	void RenderProjectile(wchar_t* screen, int screenWidth, int screenHeight);
private:
	std::vector<Projectile> projectiles;
};
