#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{

}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump)
			{
				Jump();
			}
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		case SDLK_w:
			m_can_jump = false;
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);

}
