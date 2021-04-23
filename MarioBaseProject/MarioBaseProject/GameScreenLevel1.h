#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h" //SDL.h gotten from gamescreen
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include <vector>

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
	vector<CharacterKoopa*> m_enemies;
	bool SetUpLevel();
	void DoScreenshake();
	void SetLevelMap();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	PowBlock* m_pow_block;
	LevelMap* m_level_map;
	Character* character1;
	Character* character2;
	Character* koopa;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;


};








#endif //GameScreenLevel1