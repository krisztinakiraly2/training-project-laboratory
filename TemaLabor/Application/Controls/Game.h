/*
 * Game.h
 *
 *  Created on: Nov 28, 2023
 *      Author: krisz
 */

#ifndef GAME_H_
#define GAME_H_

#include "BasicControls.h"
#include "Player.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define size 4


typedef struct
{
	uint8_t		NeedToDraw;
	int16_t		Distance;
	char* 		Map;
	Pixel		Position;
	Pixel		Size;
	Color		Color;
	Player 		Player;
	bool		Winner;		// false: Player1, true: Player2
	bool		GameWon;	// Someone won the game
	bool 		MapFull;	//	Its a draw
} Game;

void InitGame(Game* g);

void DrawMap(Game* g);

void fillMapEmpty(char* map);

void fillMapSet(char* map);

bool checkDown(char * map, bool player);

bool checkRight(char * map, bool player);

bool checkDiagonalRight(char * map, bool player);

bool checkDiagonalLeft(char * map, bool player);

void checkWin(Game* g);

void DrawGame(Game* g);

void UpdateGameData(Game* g, Pixel pos);

#endif /* GAME_H_ */
