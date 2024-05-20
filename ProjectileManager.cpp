#include "ProjectileManager.h"

void ProjectileManager::AddProjectile(float x, float y, float angle){
	projectiles.clear();
	projectiles.push_back(Projectile(x, y, angle));
}

void ProjectileManager::UpdateProjectile(float elapsedTime, std::wstring& map, int mapWidth, int mapHeight, int& score){
	for (auto& projectile : projectiles) {
		projectile.Update(elapsedTime);

		if (map[(int)projectile.posY * mapWidth + (int)projectile.posX] == 'T') {
			map[(int)projectile.posY * mapWidth + (int)projectile.posX] = 'X'; 
			score++;
			projectile.isActive = false; 
		}

		if (projectile.isActive && (projectile.posX < 0 || projectile.posX >= mapWidth || projectile.posY < 0 || projectile.posY >= mapHeight ||
			map[(int)projectile.posY * mapWidth + (int)projectile.posX] == '#')) {
			projectile.isActive = false;
		}
	}
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& proj) {return !proj.isActive; }), projectiles.end());
}

void ProjectileManager::RenderProjectile(wchar_t* screen, int screenWidth, int screenHeight){
	for (auto& projectile : projectiles) {
		if (projectile.isActive && projectile.posX >= 0 && projectile.posX < screenWidth && projectile.posY >= 0 && projectile.posY < screenHeight) {
			screen[((int)projectile.posY + 1) * screenWidth + (int)projectile.posX] = 'B';
		}
	}
}
