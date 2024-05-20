#include "CharacterMovement.h"

void Controller::UpdatePlayerPosition(const float elapsedTime,  std::wstring& map, float& angle, float& xPos, float& yPos, int mapWidth)
{
	// Move Left
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		angle -= 2.0f * elapsedTime;
	// Move Right
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		angle += 2.0f * elapsedTime;
	// Move Farward
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
		xPos += sinf(angle) * 5.0f * elapsedTime;
		yPos += cosf(angle) * 5.0f * elapsedTime;
		// Check For Collision
		if (map[(int)yPos * mapWidth + (int)xPos] == '#') {
			xPos -= sinf(angle) * 5.0f * elapsedTime;
			yPos -= cosf(angle) * 5.0f * elapsedTime;
		}
	}
	// Move Backwards
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
		xPos -= sinf(angle) * 5.0f * elapsedTime;
		yPos -= cosf(angle) * 5.0f * elapsedTime;
		// Check Collision
		if (map[(int)yPos * mapWidth + (int)xPos] == '#') {
			xPos += sinf(angle) * 5.0f * elapsedTime;
			yPos += cosf(angle) * 5.0f * elapsedTime;
		}
	}
}
