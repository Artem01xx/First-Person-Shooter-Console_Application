#include "Enemy.h"

Enemy::Enemy()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->angle = 0.0f;
}

Enemy::Enemy(float x, float y, float angle) {
	this->x = x;
	this->y = y;
	this->angle = angle;
}

void Enemy::InitializeEnemies(float x, float y, float angle) {
	enemies.push_back({ x, y, angle });
}

void Enemy::UpdateEnemyPosition(float elapsedTime, const std::wstring& map, int mapWidth) {
	for (auto& enemy : enemies)
	{
		enemy.x += cosf(enemy.angle) * 2.0f * elapsedTime;
		enemy.y += sinf(enemy.angle) * 2.0f * elapsedTime;

		if (map[(int)enemy.y * mapWidth + (int)enemy.x] == '#') {
			enemy.x -= cosf(enemy.angle) * 2.0f * elapsedTime;
			enemy.y -= sinf(enemy.angle) * 2.0f * elapsedTime;
			enemy.angle += 3.14159f / 2.0f;
		}
	}
}

void Enemy::RenderEnemy(wchar_t* screen, int screenWidth)
{
	for (auto& enemy : enemies) {
		screen[((int)enemy.y + 1) * screenWidth + (int)enemy.x] = 'E';
	}
}