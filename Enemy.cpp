#include "Enemy.h"

Enemy::Enemy(float x, float y, char symbol) {
	this->x = x;
	this->y = y;
	this->symbol = symbol;
}

Enemy::Enemy() {
	this->x = 1.0f;
	this->y = 1.0f;
	this->symbol = 'T';
}

void Enemy::InitializeEnemies(float x, float y, char symbol) {
	enemies.push_back({ x, y, symbol });
}


void Enemy::RenderEnemy(std::wstring& map, int mapWidth) {
	for (auto& enemy : enemies) {
		map[(int)enemy.y * mapWidth + (int)enemy.x] = symbol;
	}
}