#include "Ball.h"

Ball::Ball(unsigned int id,
	float xPos, float yPos, float width, float height, float *deltaTime,
	Score *score)
	:GameObject(id, xPos, yPos, width, height)
{
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;

	this->deltaTime = (*deltaTime / 1000.0f);
	this->gravity = GRAVITY;
	this->score = score;
	this->elapsedTime = 0.0f;

	yVelocity = xVelocity = 0.0f;

	yDir = 0.0f;
	xDir = 0.0f;

	srand((unsigned) std::time(NULL));
}

void Ball::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Ball::Update()
{
	elapsedTime += deltaTime;
	if (elapsedTime > TIME_TO_FALL)
	{
		yVelocity += gravity;

		yPos += yVelocity * deltaTime;
		xPos += xVelocity * deltaTime;

		if (xPos < 0 || xPos + rect.w > SCREEN_WIDTH) {
			xVelocity *= -1.0f;
		}
		if (yPos < 0)
		{
			yVelocity = 0.0f;
			yPos = 1.0f;
		}

		rect.y = yPos;
		rect.x = xPos;
	}
}

void Ball::OnCollision(SDL_Rect collision)
{
	rect.y = collision.y - rect.h - 5.0f;
	yPos = rect.y;
	score->AddPlayerScore();
	yVelocity = (- yVelocity - gravity) * (1.0f + (rand() % 5) / 10.0f);
	xVelocity = (rand() % 600) - 300.0f;
}