#ifndef _H_AGK_TEMPLATE_
#define _H_AGK_TEMPLATE_

// Link to GDK libraries
#include "AGK.h"

#include "Entity.h"

#include <iostream>
#include <math.h>

using namespace std;

#define DEVICE_WIDTH 1280
#define DEVICE_HEIGHT 720
#define FULLSCREEN false

#define PLAYER_ID 1
#define GRASS_ID 2
#define WALL_ID 3

// used to make a more unique folder for the write path
#define COMPANY_NAME "My Company"

// Global values for the app
class app
{
public:

	// constructor
	app() { memset(this, 0, sizeof(app)); }

	// main app functions - mike to experiment with a derived class for this..
	void Begin(void);
	int Loop(void);
	void End(void);

	// Utility Lambdas
	char GetTile(int x, int y)
	{
		if (x >= 0 && x < nLevelWidth && y >-0 && y < nLevelHeight)
			return sLevel[y * nLevelWidth + x];
		else
			return ' ';
	};

	void SetTile(int x, int y, char c)
	{
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
			sLevel[y*nLevelWidth + x] = c;
	};

private:
	string sLevel;
	int nLevelWidth;
	int nLevelHeight;

	vector<Entity> vObjects;

	int nTileWidth = 16;
	int nTileHeight = 16;

	float fOldTime = 0.0f;
	float fNewTime = 0.0f;
	float fElapsedTime = 0.0f;

	float fPlayerPosX = 1.0f;
	float fPlayerPosY = 1.0f;

	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

	bool bPlayerOnGround = false;
	bool bSprintToggle = false;
	bool bFlipped = false;

	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	//functions
	void CalculateDelta();
	
	void GetInput();
	void CalculateMovement(float *fNewPosX, float *fNewPosY);
	void CalculateCollisions(float *fNewPlayerPosX, float *fNewPlayerPosY);

	void DrawMap();
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
#undef LoadImage
#endif