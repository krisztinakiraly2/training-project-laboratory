/*
 * Game.c
 *
 *  Created on: Nov 28, 2023
 *      Author: krisz
 */

#include "Game.h"

void fillMapEmpty(char* map)
{
	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			*(map+i*size+j) = '.';
		}
	}
}

void InitGame(Game* g)
{
	g->Map = malloc(size*size*sizeof(char));
	fillMapEmpty(g->Map);

	g->Player.Player1 = 'X';
	g->Player.Player2 = 'O';
	g->Player.currentPlayer = false; // Player1 starts
	g->GameWon = false;
	g->Winner = false;
	g->MapFull = false;
}

bool checkDown(char * map, bool player)
{
	int sameInColoumn=0;
	char symb = !player ? 'X' : 'O';
	bool won=false;

	for(int j=0; j<size; ++j)
	{
		for(int i=0; i<size; ++i)
		{
			char first = *(map+j*size+i);
			char second = *(map+j*size+i+1);
			if((first == symb) && (second == first))
				++sameInColoumn;
			else
			{
				if(*(map+j*size+i) == symb)
					++sameInColoumn;

				if(sameInColoumn==4)
				{
					won=true; break;
				}
				else
					sameInColoumn=0;
			}
		}

		if (won) break;
	}

	return won;
}

bool checkRight(char * map, bool player)
{
	int sameInRow=0;
	char symb = !player ? 'X' : 'O';
	bool won=false;

	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			char first = *(map+j*size+i);
			char second = *(map+(j+1)*size+i);

			if(first == symb && second == first)
				++sameInRow;
			else
			{
				if(*(map+j*size+i) == symb)
					++sameInRow;

				if(sameInRow==4)
				{
					won=true; break;
				}
				else
					sameInRow=0;
			}
		}

		if (won) break;
	}

	return won;
}

bool checkDiagonalRight(char * map, bool player)
{
	int sameInDiagonal = 0;
	char symb = !player ? 'X' : 'O';

	for (int16_t i=0; i<size; ++i)
	{
		if(*(map+i*size+i)==symb)
			++sameInDiagonal;
	}

	return (sameInDiagonal==4) ? true : false;
}

bool checkDiagonalLeft(char * map, bool player)
{
	int sameInDiagonal = 0;
	char symb = !player ? 'X' : 'O';

	for (int16_t i=0; i<size; ++i)
	{
		int16_t offset = i*size+size-1-i;
		if(*(map+offset)==symb)
			++sameInDiagonal;
	}

	return (sameInDiagonal==4) ? true : false;
}

bool checkFull(char * map)
{
	bool isFull = true;

	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			if(*(map+j*size+i) == '.')
			{
				isFull = false; break;
			}
		}
		if(!isFull)
			break;
	}

	return isFull;
}

void checkWin(Game* g)
{
	char* map = g->Map;

	if(checkDown(map, false) || checkRight(map, false) || checkDiagonalRight(map, false) ||checkDiagonalLeft(map, false))
	{
		g->Winner=false; g->GameWon=true;
	}

	if(checkDown(map, true) || checkRight(map, true) || checkDiagonalRight(map, true) ||checkDiagonalLeft(map, true))
	{
		g->Winner=true; g->GameWon=true;
	}

	if(checkFull(map))
		g->MapFull = true;
}

void DrawX(Pixel start, int16_t dist)
{
	Color c;
	c.red = 235;
	c.green = 52;
	c.blue = 52;

	Pixel end;
	end.x = start.x + dist;
	end.y = start.y + dist;

	DRV_DrawLine(start, end, c);

	start.y += dist;
	end.y -= dist;
	DRV_DrawLine(start, end, c);
}

void DrawO(Pixel start, int16_t dist)
{
	Pixel center;
	center.x = start.x + dist/2;
	center.y = start.y + dist/2;

	Color c;
	c.red = 55;
	c.green = 184;
	c.blue = 115;

	DRV_DrawCircle(center, dist/2-1, c);
}

void DrawMap(Game* g)
{
	char* map = g->Map;
	int16_t dist = g->Distance;
	Pixel start;
	start.x = g->Position.x;
	start.y = g->Position.y + (size-1) * dist;

	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			char current = *(map+j*size+i);

			if(current == 'X')
				DrawX(start, dist);
			else
			{
				if(current == 'O')
					DrawO(start, dist);
			}

			start.x += dist;
		}
		start.x = g->Position.x;
		start.y -= dist;
	}
}

void DrawGame(Game* g)
{
	Pixel map;
	map.x = g->Position.x;
	map.y = g->Position.y;
	DRV_DrawRectangle(map, g->Size.y, g->Size.y, g->Color);

	Pixel posX, posY;
	posX.y = g->Position.y;
	posY.x = g->Position.x;

	for(int16_t i=1; i<size;++i)
	{
		posX.x = g->Position.x + i * g->Distance;
		DRV_DrawVerticalLine(posX, g->Size.y, g->Color);

		posY.y = g->Position.y + i * g->Distance;
		DRV_DrawHorizontalLine(posY, g->Size.y, g->Color);
	}

	DrawMap(g);

	g->NeedToDraw = false;

	checkWin(g);
}

void UpdateGameData(Game* g, Pixel pos)
{
	g->NeedToDraw = true;

	int16_t x=-1, y=-1;
	int16_t dist = g->Distance;
	int16_t startX = g->Position.x;
	int16_t startY = g->Position.y + size*dist;

	for(int i=0; i<size; ++i)
	{
		if((pos.x >= (startX + i*dist)) && (pos.x < (startX + (i+1)*dist)))
		{
			x=i; break;
		}
	}

	for(int i=0; i<size; ++i)
	{
		int l = (startY - i*dist);
		int r = (startY - (i+1)*dist);
		if(pos.y <= l && pos.y > r)
		{
			y=i; break;
		}
	}

	if(x>=0 && y>=0)
	{
		if(*(g->Map+x*size+y) == '.')
		{
			*(g->Map+x*size+y) = !(g->Player.currentPlayer) ? g->Player.Player1 : g->Player.Player2;
			g->Player.currentPlayer = !g->Player.currentPlayer;
		}
	}
}
