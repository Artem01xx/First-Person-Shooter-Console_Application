#include "Projectile.h"


Projectile::Projectile(float posX, float posY, float angle) {
	this->posX = posX;
	this->posY = posY;
	this->angle = angle;
	this->isActive = true;
}

void Projectile::Update(float elapsedTime) {
	posX += sinf(angle) * elapsedTime * speed;
	posY += cosf(angle) * elapsedTime * speed;
}
