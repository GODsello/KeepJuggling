#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <string>

#include "Window.h";
#include "GameObject/GameObject.h";
#include "Entities/Ball.h";
#include "Entities/Platform.h"
#include "Score.h";
#include "Menus/Pause.h";
#include "Menus/MainMenu.h";
#include "Constants.h";

class App
{
public:
	App();
	~App();

	/*
		Creates window and initializes systems
	*/
	bool OnInit();

	/*
		Updates entities
	*/
	void OnUpdate();

	/*
		Game loop
	*/
	void OnLoop();

	/*
		Main menu loop
		Returns option selected
	*/
	int OnMainMenuLoop();

	/*
		Check collisions between entities
	*/
	void CheckCollisions();

	/*
		Destroys entities, window and systems
	*/
	void OnShutdown();

	/*
		Handles keyboard events
	*/
	void HandleEvents(SDL_Event event);

	/*
		Resets game state. Sets onePlayer property
	*/
	void ResetState(bool onePlayer);

	/*
		Adds entities to the vector of entities
	*/
	void LoadEntities();

	/*
		Removes entities from the vector of entities
	*/
	void DeleteEntities();

private:
	/*
		Checks if the ball has gone out and in which side
	*/
	bool CheckLoss();

	void GenerateBall();

	Window* window;
	float deltaTime;
	
	Ball* ball;
	Platform* currentPlatform;

	std::vector<GameObject*> entities;
	Score* score;
	Font* font;
	Pause* pauseMenu;
	MainMenu* mainMenu;

	bool hasLoss;
	bool pause;
	bool hasGeneratedBall;
};

