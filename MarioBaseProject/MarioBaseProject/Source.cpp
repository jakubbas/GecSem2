#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std; 
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Uint32 g_old_time;
GameScreenManager* game_screen_manager;
//SDL_Texture* g_texture = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
//Texture2D* g_texture = nullptr;
//void FreeTexture(); tutorial 5 9bi

int angle = 0;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time 
		g_old_time = SDL_GetTicks();
		//flag to check if we want to quit
		bool quit = false;
		
		//loops and checks continously until update returns true
		while (!quit)
		{
			Render();
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
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);



		if (g_renderer != nullptr)
		{
			//init png load
			//stating that you allow loading png files
			int imageFlags = IMG_INIT_PNG;

			//returns these flags, if its not then the error appears
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}

		else
		{

			//if it isnt 0
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		//Load the background texture
		//g_texture = new Texture2D(g_renderer);

		//if (!g_texture->LoadFromFile("Images/test.bmp"))
		//{
		//	return false;
		//}



		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		return true;
	}
	///// tutorial 5 10b
}

void CloseSDL()
{
	//releases memory from window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quits sdl subsystems
	IMG_Quit();
	SDL_Quit();
	//clear texture
	//FreeTexture(); tutorial5 9bi
	//release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	delete game_screen_manager;
	game_screen_manager = nullptr;
	//delete g_texture;
	//g_texture = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
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

	}

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		}
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

	g_old_time = new_time;


	return false;


}

void Render()
{
	//sets colour for the renderer then clears window.
	//SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(g_renderer);
	// holds positional data, in this case top left, and then fills the size of the window. can change size by changing values.
	//SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//renders to the screen. sets size, angle for rotation, and flag to tell whether to flip or not.
	//param - renderer, texture, source rect, destination rect, angle, SDL_Point for centre of texture, SDL_RendererFlip flag, in this case doesnt flip.

	//SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, angle, NULL, SDL_FLIP_NONE);
	//updates the screen

	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0XFF, 0XFF);
	SDL_RenderClear(g_renderer);

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);
	game_screen_manager->Render();

	SDL_RenderPresent(g_renderer);


}

//SDL_Texture* LoadTextureFromFile(string path)
//{
//	//frees up memory for current texture.
//	FreeTexture();
//
//	//returned from createtexturefromsurface function.
//	SDL_Texture* p_texture = nullptr;
//
//	//loads the image, img load allows to load files of different types.
//	SDL_Surface* p_surface = IMG_Load(path.c_str());
//	if (p_surface != nullptr)
//	{
//
//	}
//
//	//create the texture from pixels on surface
//	p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
//	if (p_texture == nullptr)
//	{
//		cout << "Unable to create texture from surface. Error: " << SDL_GetError();
//	}
//
//	else
//	{
//		cout << "Unable to create texture from surface. Error: " << IMG_GetError;
//	}
//
//	//remove loaded surface now that the texture is there
//	SDL_FreeSurface(p_surface);
//	//returns texture
//	return p_texture;
//}

//void FreeTexture()   tutorial 5 9bi
//{
//	if (g_texture != nullptr)
//	{
//		SDL_DestroyTexture(g_texture);
//		g_texture = nullptr;
//	}
//}
