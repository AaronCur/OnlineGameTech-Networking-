#pragma once
#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include "Dot.h"
#include <WS2tcpip.h>
#include "Client.h"
#include <string.h>


using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();
	void initialise();

	Client* m_client;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	Dot* m_playerDot;
	Dot* m_enemyDot;

	std::string s;
	std::string delimiter;
	std::string token;
	bool joined = false;

	LTexture winTexture;
	LTexture loseTexture;


};



#endif // !GAME