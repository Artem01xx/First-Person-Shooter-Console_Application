#pragma once
#include<vector>

struct Projectile
{
	Projectile(float posX, float posY, float angle);
	void Update(float elapsedTime);
	bool isActive;
	float posX, posY, angle;
	float speed = 15.0f;
};
