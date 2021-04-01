#include "Texture2D.h"
#define _TEXTURE2D_H
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{

}

bool Texture2D::LoadFromFile(std::string path)
{

}

void Texture2D::Free()
{

}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{

}

int Texture2D::GetWidth() {return m_width;}
int Texture2D::GetHeight() {return  m_height;}


//tutorial 5 task 9