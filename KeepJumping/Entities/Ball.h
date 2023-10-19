#pragma once

#include <iostream>
#include <vector>

#include "../GameObject/GameObject.h"
#include "../Score.h"
#include "../Constants.h"

class Ball : public GameObject
{
public:
	Ball(unsigned int id,
		float xPos, float yPos, float width, float height, 
		float* deltaTime, Score *score);

	void Render(SDL_Renderer* renderer);
	void Update();

	void OnCollision(SDL_Rect collision);

	float GetXDir() { return xDir; }

private:
	float xDir, yDir;
	float yVelocity, xVelocity;
	float deltaTime;
	float gravity;
	Score* score;

	float elapsedTime;
};

