#include "Platform.h"

Platform::Platform(unsigned int id,
	float xPos, float yPos)
	:GameObject(id, xPos, yPos, 0, MAX_PLATFORM_HEIGHT)
{
	this->xPos = xPos;
	this->yPos = yPos;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	tempRect = { (int)xPos, (int)yPos, 0, MAX_PLATFORM_HEIGHT };
	completed = false;
}

Platform::~Platform()
{
	GameObject::~GameObject();
	completed = false;
}

void Platform::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (completed)
	{
		SDL_RenderFillRect(renderer, &rect);
	}
	else
	{
		SDL_RenderDrawRect(renderer, &tempRect);
	}
}

void Platform::Update(){}

void Platform::OnCollision(SDL_Rect collision)
{
}

void Platform::SetWidth(int x) 
{
	int w = x - tempRect.x;
	w = std::max(-MAX_PLATFORM_WIDTH, std::min(w, MAX_PLATFORM_WIDTH));

	tempRect.w = w;
}

void Platform::SetCompleted(bool completed)
{
	this->completed = completed;
	if (tempRect.w < 0)
	{
		tempRect.x -= abs(tempRect.w);
		tempRect.w = abs(tempRect.w);
	}
	rect = tempRect;
}