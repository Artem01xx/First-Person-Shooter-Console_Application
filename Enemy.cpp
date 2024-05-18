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


void Enemy::RenderEnemy(wchar_t* screen, int screenWidth) {
	for (auto& enemy : enemies) {
		screen[((int)enemy.y + 1) * screenWidth + (int)enemy.x] = symbol;
	}
}