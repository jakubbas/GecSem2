#include "CharacterMario.h"
#include "constants.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	if (m_jumping)
	{
		//adjust posititon
		m_position.y -= m_jump_force * deltaTime;
		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force < 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}
}
