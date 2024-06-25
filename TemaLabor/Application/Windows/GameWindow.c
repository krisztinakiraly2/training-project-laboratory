/*
 * GameWindow.c
 *
 *  Created on: Nov 28, 2023
 *      Author: krisz
 */

#include "GameWindow.h"
#include "MenuWindow.h"
#include "WindowManager.h"
#include "drawing.h"
#include "touch.h"
#include <string.h>

Window GameWindow;

static void MenuButtonOnClick(void* args, uint32_t argsN);
static void ClearButtonOnClick(void* args, uint32_t argsN);

Window* GetGameWindow()
{
	return &GameWindow;
}

void InitGameWindow()
{
	DRV_Display_Clear();

	//Buttons
	GameWindow.ButtonsNum = 2;
	Button* MenuBtn = &GameWindow.Buttons[0];
	MenuBtn->OnClick = &MenuButtonOnClick;
	strcpy(MenuBtn->Label.Label, "Menu");
	MenuBtn->Size.x = 70;
	MenuBtn->Size.y = 30;
	MenuBtn->Position.x = 10;
	MenuBtn->Position.y = 10;

	Button* ClearBtn = &GameWindow.Buttons[1];
	ClearBtn->OnClick = &ClearButtonOnClick;
	strcpy(ClearBtn->Label.Label, "Clear");
	ClearBtn->Size.x = 70;
	ClearBtn->Size.y = 30;
	ClearBtn->Position.x = 10*2 + MenuBtn->Size.x;
	ClearBtn->Position.y = 10;

	// Labels
	GameWindow.LabelsNum = 1;
	Label* Caption = &GameWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 290;
	strcpy(Caption->Label, " ");

	// Game
	GameWindow.GameActive = 1;
	Game* g = &GameWindow.Game;
	int16_t extrapadding = 30;
	g->Position.x = 30;
	g->Position.y = 50 + extrapadding;
	g->Distance = (MAX_SCREEN_Y - g->Position.x - 2*PADDING_Y+15)/size;
	g->Size.y = MAX_SCREEN_X-PADDING_X;
	g->Size.x = MAX_SCREEN_Y-PADDING_Y;
	g->Color.blue=0;
	g->Color.green=0;
	g->Color.red=0;
}


static void MenuButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetMenuWindow());
}

static void ClearButtonOnClick(void* args, uint32_t argsN)
{
	Window* myW = GetGameWindow();
	InitGame(&myW->Game);
	strcpy(myW->Labels[0].Label," ");
}

void GameNewData(int TouchX, int TouchY)
{
	Game* g = &GameWindow.Game;
	Pixel pos;
	pos.x = TouchX;
	pos.y = TouchY;
	if(!g->GameWon)
		UpdateGameData(g, pos);
}
