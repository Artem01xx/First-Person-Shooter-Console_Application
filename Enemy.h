#pragma once
#include <vector>
#include <string>

class Enemy
{
public:
	Enemy(float x, float y, char symbol);
	Enemy();
	void InitializeEnemies(float x, float y, char symbol);
	void RenderEnemy(wchar_t* screen, int screenWidth);
private:
	float x, y;
	char symbol;
	std::vector<Enemy> enemies;
};

