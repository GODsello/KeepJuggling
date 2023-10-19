#pragma once

#include <string>
#include <sstream>

#include "Font/Font.h";

class Score
{
public:
	Score(Font* font);
	~Score();

	/*
		Adds 1 to the left player score
	*/
	void AddPlayerScore();

	/*
		Sets both scores to zero
	*/
	void ResetScore();

	/*
		Renders score text texture
	*/
	void RenderScore();

	unsigned int GetPlayerScore() { return playerScore; }


private:
	/*
		Destroys font and texture
	*/
	void ClearTexture();

	/*
		Updates score texture to new value
	*/
	void UpdateScoreText();

	unsigned int playerScore;
	unsigned int maxScore;

	Font* font;
	LTexture* texture;
	LTexture* maxTexture;

	std::ostringstream scoreText;
	std::ostringstream maxText;
};

