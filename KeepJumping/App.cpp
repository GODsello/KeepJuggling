#include "App.h"

App::App(){
	window = new Window();
	ball = nullptr;
	deltaTime = 0.0f;
	hasLoss = false;
	score = nullptr;
	pause = false;
	font = nullptr;
	currentPlatform = nullptr;
	hasGeneratedBall = false;
}

App::~App(){
	OnShutdown();
}

bool App::OnInit()
{
	// Create window
	bool result = window->Init("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);

	font = new Font(window->GetRenderer());
	result = font->LoadFont();
	score = new Score(font);
	mainMenu = new MainMenu(font);
	pauseMenu = new Pause(font);

	return result;
}

void App::OnUpdate()
{
	for(GameObject * g : entities)
	{
		g->Update();
	}
}

void App::OnLoop()
{
	bool quit = false;
	
	SDL_Event event;

	while (!quit)
	{
		if (hasLoss)
		{
			LoadEntities();
		}

		float startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				pauseMenu->ResetMenu();
				pause = !pause;
			}
			if (pause)
			{
				int pauseResult = pauseMenu->HandleMenuEvents(&event);
				switch (pauseResult)
				{
				case RESUME:
					pause = false;
					break;
				case QUIT:
					quit = true;
					break;
				default:
					break;
				}
			}
			else
			{
				HandleEvents(event);
			}
		}

		if (!pause)
		{
			OnUpdate();

			CheckCollisions();
		}

		//Clear screen
		SDL_SetRenderDrawColor(window->GetRenderer(), 0x0, 0x00, 0x00, 0x00);
		SDL_RenderClear(window->GetRenderer());

		score->RenderScore();

		for (GameObject* g : entities)
		{
			g->Render(window->GetRenderer());
		}

		if (pause)
		{
			pauseMenu->RenderMenu();
		}

		SDL_RenderPresent(window->GetRenderer());

		if (score->GetPlayerScore() % 10 != 0)
		{
			hasGeneratedBall = false;
		}

		if (score->GetPlayerScore() > 0 && score->GetPlayerScore() % 10 == 0 && !hasGeneratedBall)
		{
			GenerateBall();
			hasGeneratedBall = true;
		}

		hasLoss = CheckLoss();
		if (hasLoss)
		{
			DeleteEntities();
		}
		
		// FPS handle
		deltaTime = (SDL_GetTicks() - startTime);
		if (deltaTime < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - deltaTime);
		}
		deltaTime = (SDL_GetTicks() - startTime);
	}
}

int App::OnMainMenuLoop()
{
	bool stopLoop = false;
	int selected = -1;

	SDL_Event event;

	while (!stopLoop)
	{
		float startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				stopLoop = true;
				selected = MAIN_QUIT;
			}
			if (selected < 0)
			{
				selected = mainMenu->HandleMenuEvents(&event);
				if (selected >= 0)
				{
					stopLoop = true;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(window->GetRenderer(), 0x0, 0x00, 0x00, 0x00);
		SDL_RenderClear(window->GetRenderer());

		mainMenu->RenderMenu();

		SDL_RenderPresent(window->GetRenderer());

		deltaTime = (SDL_GetTicks() - startTime);
		if (deltaTime < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - deltaTime);
		}
		deltaTime = (SDL_GetTicks() - startTime);
	}
	return selected;
}

void App::CheckCollisions()
{
	for (GameObject* entity1 : entities) {
		for (GameObject* entity2 : entities)
		{
			if (entity1->GetId() == entity2->GetId())
			{
				continue;
			}

			if (SDL_HasIntersection(entity1->GetRect(), entity2->GetRect()))
			{
				entity1->OnCollision(*entity2->GetRect());
			}
		}
	}
}

void App::OnShutdown()
{
	entities.clear();

	delete score;
	score = nullptr;

	delete pauseMenu;
	pauseMenu = nullptr;

	delete font;
	font = nullptr;

	delete window;
	window = nullptr;
}

void App::HandleEvents(SDL_Event event)
{
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse, &yMouse);
	if (event.type == SDL_MOUSEBUTTONDOWN && currentPlatform == nullptr) {
		currentPlatform = new Platform(PLATFORM_ID, xMouse, yMouse);
		entities.push_back(currentPlatform);
	}
	else if (event.type == SDL_MOUSEBUTTONUP && currentPlatform != nullptr)
	{
		int idxPlat = 0;
		bool found = false;
		for (; idxPlat < entities.size() && !found; idxPlat++)
		{
			if (entities[idxPlat]->GetId() == PLATFORM_ID)
			{
				found = true;
			}
		}
		if (idxPlat < entities.size())
		{
			entities.erase(entities.begin() + idxPlat - 1);
		}

		currentPlatform->SetWidth(xMouse);
		currentPlatform->SetCompleted(true);
		currentPlatform = nullptr;
	}
	else if (currentPlatform != nullptr)
	{
		currentPlatform->SetWidth(xMouse);
	}
}

void App::ResetState(bool onePlayer)
{
	hasLoss = false;
	pause = false;
	hasGeneratedBall = false;
	score->ResetScore();
}

void App::LoadEntities() {
	GenerateBall();
}

void App::DeleteEntities()
{
	for (GameObject* g : entities) {
		delete g;
	}
	entities.clear();

	ball = nullptr;
}

bool App::CheckLoss() 
{
	for (GameObject* g : entities)
	{
		if (g->GetId() == BALL_ID && g->GetRect()->y > SCREEN_HEIGHT)
		{
			score->ResetScore();
			return true;
		}
	}

	return false;
}

void App::GenerateBall() 
{
	ball = new Ball(BALL_ID,
		SCREEN_WIDTH / 2.0f - ballConstants.width / 2.0f,
		SCREEN_HEIGHT / 2.0f - ballConstants.height / 2.0f,
		ballConstants.width, ballConstants.height,
		&deltaTime, score);
	entities.push_back(ball);
}