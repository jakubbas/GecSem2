#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H
#include "constants.h"


class LevelMap
{
public:
	LevelMap(int Map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

	int GetTileAt(unsigned int h, unsigned int w);

private:
	int** m_map;
};

#endif // !_LEVELMAP_H
