#pragma once

class Entity
{
public:
	Entity();
	~Entity();
private:
	string sTag;
	int iImage;

	float fPosX = 0.0f;
	float fPosY = 0.0f;
	
	float fVelX = 0.0f;
	float fVelY = 0.0f;

	bool bFlipped = false;
};
