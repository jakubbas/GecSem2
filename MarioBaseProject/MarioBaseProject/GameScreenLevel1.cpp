#include "GameScreenLevel1.h"
#define _GAMESCREENLEVEL1_H
#include <iostream>
#include "Texture2D.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete character1;
	delete character2;
	character1 = nullptr;
	character2 = nullptr;
	delete m_renderer;
	m_renderer = nullptr;
	delete m_level_map;
	m_level_map = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	character1->Render();
	character2->Render();
	m_pow_block->Render(); // potential issue?
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	/*
	* do the screen shake if required
	*/
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}


	//updates character
	character1->Update(deltaTime, e);
	character2->Update(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePowBlock();

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
	SetLevelMap();

	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture." << std::endl;
		return false;
	}

	character1 = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	character2 = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);


	m_pow_block = new PowBlock(m_renderer, m_level_map); //this

	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } 
	};

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), character1->GetCollisionBox()))
	{
		if (m_pow_block != nullptr)
		{
			//collided while jumping
			if (character1->isJumping() == true)
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				character1->CancelJump();
			}

		}
	}

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), character2->GetCollisionBox()))
	{
		if (m_pow_block != nullptr)
		{
			//collided while jumping
			if (character2->isJumping())
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				character2->CancelJump();
			}

		}
	}

}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (unsigned int i = 0; i < m_enemies.size();i++)
	{
		if (m_enemies[i]->GetAlive())
		{
			m_enemies[i]->TakeDamage();
		}
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], character1))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
					}

				}

				if (Collisions::Instance()->Circle(m_enemies[i], character2))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill luigi
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, Vector2D(64, 330), FACING_RIGHT, KOOPA_SPEED); //SOMETHING BROKEN HERE
}
