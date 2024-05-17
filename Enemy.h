#pragma once
#include <vector>
#include <string>

class Enemy
{
public:
	Enemy(float x, float y, float angle);
	Enemy();
	void InitializeEnemies(float x, float y, float angle);
	void UpdateEnemyPosition(float elapsedTime, const std::wstring& map, int mapWidth);
	void RenderEnemy(wchar_t* screen, int screenWidth);
private:
	float x;
	float y;
	float angle;
	std::vector<Enemy> enemies;
};

//Rep