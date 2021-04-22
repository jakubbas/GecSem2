#include "GameScreenLevel1.h"
#define _GAMESCREENLEVEL1_H
#include <iostream>
#include "Texture2D.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "Collisions.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete character1;
	delete character2;
	character1 = nullptr;
	character2 = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	character1->Render();
	character2->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//updates character
	character1->Update(deltaTime, e);
	character2->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(character1, character2))
	{
		//cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(character1->GetCollisionBox() , character2-> GetCollisionBox()))
	{
		//cout << "Box hit!" << endl;
	}

}

bool GameScreenLevel1::SetUpLevel()
{
	//load the texture
	//set up player character

	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture." << std::endl;
		return false;
	}

	character1 = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	character2 = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330));


}