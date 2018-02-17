// Includes
#include "template.h"

// Namespace
using namespace AGK;
using namespace std;

void app::GetInput()
{
	//Handle Input

	if (agk::GetRawKeyState(16))
	{
		bSprintToggle = true;
	}
	else
	{
		bSprintToggle = false;
	}

	if (agk::GetRawKeyState(65)) // Left
	{
		fPlayerVelX += (1 + bSprintToggle) * (bPlayerOnGround ? -35.0f : -10.0f) * fElapsedTime;
		if (!bFlipped)
		{
			bFlipped = true;
		}
	}
	if (agk::GetRawKeyState(68)) // Right
	{
		fPlayerVelX += (1 + bSprintToggle) * (bPlayerOnGround ? 35.0f : 10.0f) * fElapsedTime;
		if (bFlipped)
		{
			bFlipped = false;
		}
	}

	if (agk::GetRawKeyPressed(32))
	{
		if (fPlayerVelY == 0)
		{
			fPlayerVelY = -9.0f;
		}
	}
}

void app::CalculateMovement(float *fNewPosX, float *fNewPosY)
{
	// Gravity
	fPlayerVelY += 20.0f * fElapsedTime;

	// Drag
	if (bPlayerOnGround)
	{
		fPlayerVelX += -10.0f * fPlayerVelX * fElapsedTime;
		if (fabs(fPlayerVelX) < 0.01f)
			fPlayerVelX = 0.0f;
	}
	else
	{
		fPlayerVelX += -3.0f * fPlayerVelX * fElapsedTime;
		if (fabs(fPlayerVelX) < 0.01f)
			fPlayerVelX = 0.0f;
	}

	// Clamp velocities
	if (fPlayerVelX > 10.0f)
		fPlayerVelX = 10.0f;

	if (fPlayerVelX < -10.0f)
		fPlayerVelX = -10.0f;

	if (fPlayerVelY > 100.0f)
		fPlayerVelY = 100.0f;

	if (fPlayerVelY < -100.0f)
		fPlayerVelY = -100.0f;

	// Calculate potential new position
	*fNewPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
	*fNewPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;
}

void app::CalculateCollisions(float *fNewPlayerPosX, float *fNewPlayerPosY)
{
	for (auto obj : vObjects)
	{
		for (auto other_obj : vObjects)
		{

		}
	}

	// Check for pickups!
	if (GetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY + 0.0f) == 'o')
		SetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY + 0.0f, '.');

	if (GetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY + 1.0f) == 'o')
		SetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY + 1.0f, '.');

	if (GetTile(*fNewPlayerPosX + 1.0f, *fNewPlayerPosY + 0.0f) == 'o')
		SetTile(*fNewPlayerPosX + 1.0f, *fNewPlayerPosY + 0.0f, '.');

	if (GetTile(*fNewPlayerPosX + 1.0f, *fNewPlayerPosY + 1.0f) == 'o')
		SetTile(*fNewPlayerPosX + 1.0f, *fNewPlayerPosY + 1.0f, '.');

	// Check for Collision
	if (fPlayerVelX <= 0) // Moving Left
	{
		if (GetTile(*fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) != '.' || GetTile(*fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) != '.')
		{
			*fNewPlayerPosX = (int)*fNewPlayerPosX + 1;
			fPlayerVelX = 0;
		}
	}
	else // Moving Right
	{
		if (GetTile(*fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) != '.' || GetTile(*fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) != '.')
		{
			*fNewPlayerPosX = (int)*fNewPlayerPosX;
			fPlayerVelX = 0;

		}
	}

	bPlayerOnGround = false;
	if (fPlayerVelY <= 0) // Moving Up
	{
		if (GetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY) != '.' || GetTile(*fNewPlayerPosX + 0.9f, *fNewPlayerPosY) != '.')
		{
			*fNewPlayerPosY = (int)*fNewPlayerPosY + 1;
			fPlayerVelY = 0;
		}
	}
	else // Moving Down
	{
		if (GetTile(*fNewPlayerPosX + 0.0f, *fNewPlayerPosY + 1.0f) != '.' || GetTile(*fNewPlayerPosX + 0.9f, *fNewPlayerPosY + 1.0f) != '.')
		{
			*fNewPlayerPosY = (int)*fNewPlayerPosY;
			fPlayerVelY = 0;
			bPlayerOnGround = true; // Player has a solid surface underfoot
		}
	}
}