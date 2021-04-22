#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h" //SDL.h gotten from gamescreen
#include "Commons.h"
#include "Character.h"

class Character; 
class Texture2D; //Forward class declaration

class GameScreenLevel1 : GameScreen // need to state gamescreen as we are inheriting from it
{
public:
	Texture2D* m_background_texture;
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override; //override optional, since the compiler knows but its good practice


private:
	bool SetUpLevel();
	Character* my_character;
};








#endif //GameScreenLevel1