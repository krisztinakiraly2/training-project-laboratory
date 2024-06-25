/*
 * MenuWindow.c
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#include "WindowManager.h"
#include "GameWindow.h"
#include <string.h>

Window MenuWindow;

static void GameButtonOnClick(void* args, uint32_t argsN);

Window* GetMenuWindow()
{
	return &MenuWindow;
}

void InitMenuWindow()
{
	//Labels
	MenuWindow.LabelsNum = 1;
	Label* Caption = &MenuWindow.Labels[0];
	Caption->Position.x = DRV_Display_GetXSize()/2;
	Caption->Position.y = 300;
	strcpy(Caption->Label, "Menu");

	//Buttons
	MenuWindow.ButtonsNum = 5;

	Button* GameBtn = &MenuWindow.Buttons[0];
	GameBtn->OnClick = &GameButtonOnClick;
	strcpy(GameBtn->Label.Label, "Start");
	GameBtn->Size.x = 180;
	GameBtn->Size.y = 40;
	GameBtn->Position.x = DRV_Display_GetXSize()/2 - GameBtn->Size.x/2;
	GameBtn->Position.y = 150;

	//Unused controls
	MenuWindow.GameActive = 0;
}

static void GameButtonOnClick(void* args, uint32_t argsN)
{
	SetActiveWindow(GetGameWindow());
}
