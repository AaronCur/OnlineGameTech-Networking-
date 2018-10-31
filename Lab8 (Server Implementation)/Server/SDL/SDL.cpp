// SDL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>

#pragma comment(lib,"SDL2.lib") 
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_net.lib")

#include "Application.h"

int main(int argc, char** argv)
{
	Application app;
	app.run();
	system("pause");
	return 0;
}