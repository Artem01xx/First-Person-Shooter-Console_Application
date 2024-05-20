#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <windows.h>
#include "CharacterMovement.h"
#include "Enemy.h"
#include "ProjectileManager.h"

namespace ScreenParams {
	const int screenWidth = 120;
	const int screenHeight = 40;
}

namespace PlayerCoord {
	float playerX = 8.0f;
	float playerY = 8.0f;
	float playerA = 0.0f;
	float fov = 3.14159 / 4.0f; // (Field Of View)
	int score = 0;
}

namespace MapParams {
	const int mapHeight = 16;
	const int mapWidth = 16;
}

namespace ClassDefinition {
	Enemy enemy;
	ProjectileManager projectileManager;
	Controller controller;
}

const float depth = 16.0f; // Max Depth Of Vision

int main() {
	//Create Screen Buffer
	wchar_t* screen = new wchar_t[ScreenParams::screenWidth * ScreenParams::screenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWriten = 0;

	//Drawing Map
	std::wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#.......########";
	map += L"#..............#";
	map += L"#......##......#";
	map += L"#......T#......#";
	map += L"#..............#";
	map += L"###............#";
	map += L"##.............#";
	map += L"#......T#..# ###";
	map += L"#......#.......#";
	map += L"#......#.......#";
	map += L"#..............#";
	map += L"#......T########";
	map += L"#..............#";
	map += L"################";

	
	// Taking Current Time
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	//Main Loop
	while (true) {
		// Calculate Difference From Last Frame
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> dElipsedTime = tp2 - tp1;
		tp1 = tp2;
		float elapsedTime = dElipsedTime.count();
		// Updating Player Position
		ClassDefinition::controller.UpdatePlayerPosition(elapsedTime, map, PlayerCoord::playerA, PlayerCoord::playerX, PlayerCoord::playerY, MapParams::mapWidth);

		// Shoot (Right Mouse Button)
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
			ClassDefinition::projectileManager.AddProjectile(PlayerCoord::playerX, PlayerCoord::playerY, PlayerCoord::playerA);
		}
		ClassDefinition::projectileManager.UpdateProjectile(elapsedTime, map, MapParams::mapWidth, MapParams::mapHeight, PlayerCoord::score);

		for (int i = 0; i < ScreenParams::screenWidth; i++) {
			// Calculating Ray For Each Column Of Screen
			float rayAngle = (PlayerCoord::playerA - PlayerCoord::fov / 2.0f) + ((float)i / (float)ScreenParams::screenWidth) * PlayerCoord::fov;
			float distanceToWall = 0.0f;
			bool bHitWall = false;
			bool bHitBoundary = false;

			float eyeX = sinf(rayAngle);
			float eyeY = cosf(rayAngle);
			// Ray Trace
			while (bHitWall == false && distanceToWall < depth) {
				distanceToWall += 0.1;

				float testX = (int)(PlayerCoord::playerX + eyeX * distanceToWall);
				float testY = (int)(PlayerCoord::playerY + eyeY * distanceToWall);

				if (testX < 0 || testX >= MapParams::mapWidth || testY < 0 || testY >= MapParams::mapHeight) {
					bHitWall = true;
					distanceToWall = depth;
				}
				else {
					if (map[testY * MapParams::mapWidth + testX] == '#') {
						bHitWall = true;
						std::vector<std::pair<float, float>> p; // Distance, Dot

						for (int tx = 0; tx < 2; tx++) {
							for (int ty = 0; ty < 2; ty++) {
								float vy = (float)testY + ty - PlayerCoord::playerY;
								float vx = (float)testX + tx - PlayerCoord::playerX;
								float d = sqrt(vx * vx + vy * vy);
								float dot = (eyeX * vx / d) + (eyeY * vy / d);
								p.push_back({ d, dot });
							}
						}
						std::sort(p.begin(), p.end(), [](const std::pair<float, float>& left, const std::pair<float, float>& right)
						{return left.first < right.first; });
						float bound = 0.01;
						if (acos(p.at(0).second) < bound) bHitBoundary = true;
						if (acos(p.at(1).second) < bound) bHitBoundary = true;
					}
				}
			}
			int nCelling = (float)(ScreenParams::screenHeight / 2.0f) - ScreenParams::screenHeight / (float)distanceToWall;
			int nFloor = ScreenParams::screenHeight - nCelling;

			short shade = ' ';
			// Changing Color Where Distance Is
			if (distanceToWall <= depth / 4.0f)		shade = 0x2588;  // Close
			else if (distanceToWall < depth / 3.0f) shade = 0x2593;
			else if (distanceToWall < depth / 2.0f) shade = 0x2592;
			else if (distanceToWall < depth)	    shade = 0x2591;
			else									shade = ' ';     // Far Away
			if (bHitBoundary == true) shade = ' ';

			for (int j = 0; j < ScreenParams::screenHeight; j++) {
				if (j < nCelling) {
					screen[j * ScreenParams::screenWidth + i] = ' ';
				}
				else if (j >= nCelling && j < nFloor) {
					screen[j * ScreenParams::screenWidth + i] = shade;
				}
				else {
					float floor = 1.0f - (((float)j - ScreenParams::screenHeight / 2.0f) / ((float)ScreenParams::screenHeight / 2.0f));
					if (floor < 0.25f)      shade = '#';
					else if (floor < 0.5f)  shade = 'x';
					else if (floor < 0.75f) shade = '.';
					else if (floor < 0.9f)  shade = '_';
					else				   shade = ' ';
					screen[j * ScreenParams::screenWidth + i] = shade;
				}
			}
		}
		// Display Stats
		swprintf_s(screen, 50, L"X=%3.2f, Y=%3.2f, A=%3.2f, FPS=%3.2f, SCORE=%d", PlayerCoord::playerX, PlayerCoord::playerY, PlayerCoord::playerA, 1.0f / elapsedTime, PlayerCoord::score);
	
		// Display Map
		for (int nx = 0; nx < MapParams::mapWidth; nx++) {
			for (int ny = 0; ny < MapParams::mapHeight; ny++) {
				screen[(ny + 1) * ScreenParams::screenWidth + nx] = map[ny * MapParams::mapWidth + nx];
			}
		}
		// Player Position
		screen[((int)PlayerCoord::playerY + 1) * ScreenParams::screenWidth + (int)PlayerCoord::playerX] = 'P';
		ClassDefinition::projectileManager.RenderProjectile(screen, ScreenParams::screenWidth, ScreenParams::screenHeight);
		// Enemy Position
		ClassDefinition::enemy.RenderEnemy(map, MapParams::mapWidth);

		screen[ScreenParams::screenWidth * ScreenParams::screenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, ScreenParams::screenWidth * ScreenParams::screenHeight, { 0, 0 }, &dwBytesWriten);
	}

	delete[] screen;
	return 0;
}