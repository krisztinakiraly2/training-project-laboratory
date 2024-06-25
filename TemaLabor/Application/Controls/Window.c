/*
 * Window.c
 *
 *  Created on: 2016 okt. 30
 *      Author: Nagy �kos
 */

#include <Window.h>

static uint8_t IsDrawRequired(Window* w);

/*
 * Window
 */

void InitWindow(Window* w)
{
	w->NeedToDraw = 1;

	for (uint32_t i = 0; i < w->LabelsNum; ++i)
		InitLabel(&w->Labels[i]);

	for (uint32_t i = 0; i < w->ButtonsNum; ++i)
		InitButton(&w->Buttons[i]);

	if (w->GameActive > 0)
		InitGame(&w->Game);
}

uint8_t IsDrawRequired(Window* w)
{
	if (w->NeedToDraw)
		return 1;

	for (uint32_t i = 0; i < w->LabelsNum; ++i)
		w->NeedToDraw |= w->Labels[i].NeedToDraw;
	for (uint32_t i = 0; i < w->ButtonsNum; ++i)
		w->NeedToDraw |= w->Buttons[i].NeedToDraw;
	if (w->GameActive > 0)
		w->NeedToDraw |= w->Game.NeedToDraw;

	return w->NeedToDraw;
}

uint8_t DrawWindow(Window* w)
{
	IsDrawRequired(w);
	if (w->NeedToDraw == 0)
		return 0;

	w->DrawInProgress = 1;
	DRV_Display_Clear();

	for (uint32_t i = 0; i < w->LabelsNum; ++i)
		DrawLabel(&w->Labels[i]);

	for (uint32_t i = 0; i < w->ButtonsNum; ++i)
		DrawButton(&w->Buttons[i]);

	if (w->GameActive > 0)
		DrawGame(&w->Game);

	w->NeedToDraw = 0;
	w->DrawInProgress = 0;
	return 1;
}

