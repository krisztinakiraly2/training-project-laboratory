/*
 * Window.h
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy �kos
 */

#ifndef CONTROLS_WINDOW_H_
#define CONTROLS_WINDOW_H_

#include <BasicControls.h>
#include "Game.h"

typedef struct
{
	Button		Buttons[2];
	uint32_t	ButtonsNum;
	Label		Labels[2];
	uint32_t	LabelsNum;
	uint8_t		NeedToDraw;
	uint8_t		DrawInProgress;
	Game 		Game;
	uint8_t 	GameActive;
} Window;

void	InitWindow(Window* w);
uint8_t DrawWindow(Window* w);

#endif /* CONTROLS_WINDOW_H_ */
