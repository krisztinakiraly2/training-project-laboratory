/*
 * WindowManager.c
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#include <GameWindow.h>
#include <MenuWindow.h>
#include <SetupWindow.h>
#include <WindowManager.h>
#include "GameWindow.h"

Window* ActiveWindow = 0;

static uint8_t IsInnerPoint(Button* btn, Pixel p);

void InitWindowManager(void)
{
	//Init windows
	InitMenuWindow();
	InitSetupWindow();
	InitGameWindow();

	//Set startup window
	SetActiveWindow(GetSetupWindow());
}

void SetActiveWindow(Window* w)
{
	ActiveWindow = w;

	//Init window
	InitWindow(w);
}

void HandleTouch(int TouchX, int TouchY)
{
	Pixel p;
	p.x = TouchX;
	p.y = TouchY;
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		for (uint32_t i = 0; i < ActiveWindow->ButtonsNum; ++i)
		{
			if (IsInnerPoint(&ActiveWindow->Buttons[i], p))
			{
				ActiveWindow->Buttons[i].OnClick(0,0);
				break;
			}
		}
	}
}

uint8_t IsInnerPoint(Button* btn, Pixel p)
{
	if ((p.x < btn->Position.x) || ((btn->Position.x + btn->Size.x) < p.x))
		return 0;

	if ((p.y < btn->Position.y) || ((btn->Position.y + btn->Size.y) < p.y))
		return 0;

	return 1;
}

void HandleGame()
{
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->GameActive > 0)
			DrawWindow(ActiveWindow);

		Window* myW = GetGameWindow();
		if(myW->Game.GameWon)
		{
			if(!(myW->Game.Winner))
				strcpy(myW->Labels[0].Label,"Player 1 won");
			else
				strcpy(myW->Labels[0].Label,"Player 2 won");

			myW->Game.NeedToDraw = true;
		}

		if(myW->Game.MapFull)
			strcpy(myW->Labels[0].Label,"It's a draw");
	}
}

void HandleNewData(int TouchX, int TouchY)
{
	if ((ActiveWindow != 0) && (!ActiveWindow->DrawInProgress))
	{
		if (ActiveWindow->GameActive > 0)
		{
			GameNewData(TouchX, TouchY);
		}
	}
}

uint8_t HandleDraw(void)
{
	if (ActiveWindow != 0)
	{
		return DrawWindow(ActiveWindow);
	}
	return 0;
}
