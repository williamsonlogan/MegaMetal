// Includes
#include "template.h"

// Namespace
using namespace AGK;
using namespace std;

void app::DrawMap()
{
	//Draw Level
	int nVisibleTilesX = agk::GetVirtualWidth() / nTileWidth;
	int nVisibleTilesY = agk::GetVirtualHeight() / nTileHeight;

	// Calculate Top-Leftmost visible tile
	float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
	float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

	// Clamp camera to game boundaries
	if (fOffsetX < 0) fOffsetX = 0;
	if (fOffsetY < 0) fOffsetY = 0;
	if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
	if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

	// Get offsets for smooth movement
	float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
	float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

	// Draw visible tile map
	for (int x = -1; x < nVisibleTilesX + 1; x++)
	{
		for (int y = -1; y < nVisibleTilesY + 1; y++)
		{
			char sTileID = GetTile(x + fOffsetX, y + fOffsetY);
			switch (sTileID)
			{
			case '.':
				break;
			case '#':
				agk::SetSpritePosition(agk::CreateSprite(WALL_ID), x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
				break;
			case 'g':
				agk::SetSpritePosition(agk::CreateSprite(GRASS_ID), x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
				break;
			}
		}
	}

	int playerID = agk::CreateSprite(PLAYER_ID);
	agk::SetSpritePosition(playerID, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);

	if (bFlipped)
	{
		agk::SetSpriteFlip(playerID, 1, 0);
	}
	else
	{
		agk::SetSpriteFlip(playerID, 0, 0);
	}
}