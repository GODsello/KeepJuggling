#pragma once

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 768;

const unsigned int BALL_ID = 0;
const unsigned int PLATFORM_ID = 1;

const int MAX_PLATFORM_WIDTH = 150;
const int MAX_PLATFORM_HEIGHT = 20;

const float GRAVITY = 5.0f;

const float TIME_TO_FALL = 1.0f;

const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

struct {
	float width = 20.0f;
	float height = 20.0f;
} ballConstants;

struct {
	float width = 20.0f;
	float height = 150.0f;
} playerConstants;

enum {
	SMALL_FONT = 28,
	MEDIUM_FONT = 36,
	BIG_FONT = 48
};

enum {
	MAIN_ONE_PLAYER,
	MAIN_QUIT,
};

enum {
	RESUME,
	QUIT,
};