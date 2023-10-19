#include "Score.h"

Score::Score(Font* font)
{
	playerScore = 0;
	maxScore = 0;
	this->font = font;
	UpdateScoreText();
}

Score::~Score()
{
	ClearTexture();
	font = nullptr;
}

void Score::AddPlayerScore()
{
	playerScore++;
	if (playerScore > maxScore)
	{
		maxScore = playerScore;
	}
	UpdateScoreText();
}

void Score::ResetScore()
{
	playerScore = 0;
	UpdateScoreText();
}

void Score::RenderScore()
{
	font->RenderTexture(texture, 
						(SCREEN_WIDTH / 2.0f) - (texture->width / 2.0f),
						0);
	font->RenderTexture(maxTexture,
		SCREEN_WIDTH - maxTexture->width - 2.0f,
		0);
}

void Score::ClearTexture()
{
	if (texture != NULL)
	{
		font->ClearTexture(texture);
		texture = nullptr;
	}

	if (maxTexture != NULL)
	{
		font->ClearTexture(maxTexture);
		maxTexture = nullptr;
	}
}

void Score::UpdateScoreText()
{
	scoreText.str("");
	scoreText.clear();
	scoreText << playerScore;

	maxText.str("");
	maxText.clear();
	maxText << "Max score: " << maxScore;

	ClearTexture();
	texture = font->CreateTexture(MEDIUM_FONT, scoreText.str(), { 255, 255, 255 });
	maxTexture = font->CreateTexture(SMALL_FONT, maxText.str(), { 255, 255, 255 });
}
