// Includes
#include "template.h"

// Namespace
using namespace AGK;
using namespace std;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution(512, 288);
	agk::SetTextDefaultMinFilter(0);
	agk::SetDefaultMinFilter(0);
	agk::SetTextDefaultMagFilter(0);
	agk::SetDefaultMagFilter(0);
	agk::SetClearColor(0, 200, 255); // light blue
	agk::SetFolder("media/");
	//agk::SetSyncRate(60.0f, 0);

	nTileWidth = 32;
	nTileHeight = 32;

	nLevelWidth = 64;
	nLevelHeight = 18;

	sLevel += "................................................................";
	sLevel += "................................................................";
	sLevel += "................................................................";
	sLevel += "................................................................";
	sLevel += "................................................................";
	sLevel += "................................................................";
	sLevel += ".......................########.................................";
	sLevel += "......###.............###..............#####....................";
	sLevel += "....................###.........................................";
	sLevel += "...................####.........................................";
	sLevel += "gggggggggggggggggggggggggggggggggggg..gggggggggg........gggggggg";
	sLevel += "...................................#..#..............###........";
	sLevel += "........................############..#...........###...........";
	sLevel += "........................#.............#........###..............";
	sLevel += "........................#...................###.................";
	sLevel += "........................#................###....................";
	sLevel += "........................#################.......................";
	sLevel += "................................................................";

	agk::LoadImage(PLAYER_ID, "guitarman.png");
	agk::LoadImage(GRASS_ID, "orange.png");
	agk::LoadImage(WALL_ID, "brimstone.png");
}

int app::Loop(void)
{
	agk::Print((int)(ceil)(agk::ScreenFPS()));

	agk::DeleteAllSprites();

	GetInput();

	float fNewPlayerPosX = 0.0f;
	float fNewPlayerPosY = 0.0f;

	CalculateMovement(&fNewPlayerPosX, &fNewPlayerPosY);

	CalculateCollisions(&fNewPlayerPosX, &fNewPlayerPosY);

	// Apply new position
	fPlayerPosX = fNewPlayerPosX;
	fPlayerPosY = fNewPlayerPosY;

	// Link camera to player position
	fCameraPosX = fPlayerPosX;
	fCameraPosY = fPlayerPosY;

	DrawMap();

	agk::Sync();

	CalculateDelta();

	return 0; // return 1 to close app
}


void app::End(void)
{

}

void app::CalculateDelta()
{
	fOldTime = fNewTime;
	fNewTime = agk::Timer();
	fElapsedTime = fNewTime - fOldTime;
}