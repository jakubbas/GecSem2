#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h" //SDL.h gotten from gamescreen
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"

class Character; 
class Texture2D; //Forward class declaration
class PowBlock;
class GameScreenLevel1 : GameScreen // need to state gamescreen as we are inheriting from it
{
public:
	void UpdatePowBlock();
	Texture2D* m_background_texture;
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override; //override optional, since the compiler knows but its good practice


private:
	bool SetUpLevel();
	void DoScreenshake();
	void SetLevelMap();
	PowBlock* m_pow_block;
	LevelMap* m_level_map;
	Character* character1;
	Character* character2;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;


};








#endif //GameScreenLevel1