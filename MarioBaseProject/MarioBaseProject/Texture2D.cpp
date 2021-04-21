#include "Texture2D.h"
#define _TEXTURE2D_H
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;

}
Texture2D::~Texture2D()
{
	Free();
	m_renderer = nullptr;
}


bool Texture2D::LoadFromFile(std::string path)
{
	//frees up memory for current texture.
	Free();

	//returned from createtexturefromsurface function.

	//loads the image, img load allows to load files of different types.
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//colour key the image to be transparent
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));

	}

	//create the texture from pixels on surface
	m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
	if (m_texture == nullptr)
	{
		cout << "Unable to create texture from surface. Error: " << SDL_GetError();
	}

	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError;
		m_width = p_surface->w;
		m_height = p_surface->h;

	}

	//remove loaded surface now that the texture is there
	SDL_FreeSurface(p_surface);
	//returns texture
	return m_texture != nullptr;
}

void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		m_width = 0;
		m_height = 0;
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

	}

}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture
	SDL_Rect renderLocation = {new_position.x, new_position.y, m_width, m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);


}

//int Texture2D::GetWidth() {return m_width;}
//int Texture2D::GetHeight() {return  m_height;}


