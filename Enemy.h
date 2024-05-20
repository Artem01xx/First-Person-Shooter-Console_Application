#pragma once
#include <vector>
#include <string>

// CURR CLASS IS NOT USED
class Enemy
{
public:
	Enemy(float x, float y, char symbol);
	Enemy();
	void InitializeEnemies(float x, float y, char symbol);
	void RenderEnemy(std::wstring& map, int mapWidth);
private:
	float x, y;
	char symbol;
	std::vector<Enemy> enemies;
};

