#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}

	initialise();
}

Game::~Game()
{
}
void Game::initialise()
{
	m_playerDot = new Dot(false);
	m_enemyDot = new Dot(true);
	m_client = new Client();
	m_client->run();
	m_client->sendMessage("Hello");
	m_playerDot->Init(m_renderer);
	m_enemyDot->Init(m_renderer);

	
}


void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!exit) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update();
		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{


	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			
			m_playerDot->handleEvent(event);
			m_enemyDot->handleEvent(event);


			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
		}
	}
}

void Game::update()
{
	
	m_playerDot->move(1200, 700);
	m_enemyDot->move(1200, 700);
	m_client->receive();
	
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	m_playerDot->render(m_renderer);
	m_enemyDot->render(m_renderer);

	SDL_RenderPresent(m_renderer);

}


