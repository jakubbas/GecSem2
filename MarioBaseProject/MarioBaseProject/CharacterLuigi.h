#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
#include "Character.h"
class CharacterLuigi : public Character
{
protected:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterLuigi();

};

#endif