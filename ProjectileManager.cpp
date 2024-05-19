#include "ProjectileManager.h"

void ProjectileManager::AddProjectile(float x, float y, float angle){
	projectiles.clear();
	projectiles.push_back(Projectile(x, y, angle));
}

void ProjectileManager::UpdateProjectile(float elapsedTime, std::wstring& map, int mapWidth, int MapHeight){
	for (auto& projectile : projectiles) {
		projectile.Update(elapsedTime);
		if (projectile.isActive && (projectile.posX < 0 || projectile.posY >= mapWidth || projectile.posY < 0 || projectile.posY >= MapHeight ||
			map[(int)projectile.posY * mapWidth + (int)projectile.posX] == '#')) {
			projectile.isActive = false;
		}
	}
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile proj) {return !proj.isActive; }), projectiles.end());
}

void ProjectileManager::RenderProjectile(wchar_t* screen, int screenWidth, int screenHeight){
	for (auto& projectile : projectiles) {
		if (projectile.isActive && projectile.posX >= 0 && projectile.posX < screenWidth && projectile.posY >= 0 && projectile.posY < screenHeight) {
			screen[(int)projectile.posY * screenWidth + (int)projectile.posX] = 'B';
		}
	}
}
