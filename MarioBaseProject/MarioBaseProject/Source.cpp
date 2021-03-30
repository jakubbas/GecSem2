#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
using namespace std; 
SDL_Window* g_window = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//flag to check if we want to quit
		bool quit = false;
		
		//loops and checks continously until update returns true
		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		return true;
	}

}

void CloseSDL()
{
	//releases memory from window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quits sdl subsystems
	IMG_Quit();
	SDL_Quit();


}

bool Update()
{
	//event handler
	SDL_Event e;

	//gets event (event variable e, determines what the event is)
	SDL_PollEvent(&e);
	//handles events
	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;

	//case SDLK_q:
	//	switch (e.key.keysym.sym)
	//		return true;
	//		break;
	}

	return false;

}