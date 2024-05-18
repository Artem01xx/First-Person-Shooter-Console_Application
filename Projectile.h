#pragma once
#include<vector>

class Projectile
{
public:
	Projectile(float posX, float posY, float angle);
	void Update(float elapsedTime);
private:
	float posX, posY, angle;
	bool isActive;
	const float speed = 5.0f;
};
