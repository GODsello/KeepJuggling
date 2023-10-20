#pragma once

#include "../GameObject/GameObject.h"
#include "../Constants.h"
#include "../Score.h"

class Platform : public GameObject
{
public:
	Platform(unsigned int id,
		float xPos, float yPos);
	~Platform();

	void Render(SDL_Renderer* renderer);
	void Update();

	void OnCollision(SDL_Rect collision);

	void SetWidth(int x);
	void SetCompleted(bool completed);

private:
	bool completed;
	SDL_Rect tempRect;
};

