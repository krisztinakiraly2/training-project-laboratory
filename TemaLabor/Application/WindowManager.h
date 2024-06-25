/*
 * WindowManager.h
 *
 *  Created on: 2016 okt. 21
 *      Author: Nagy �kos
 */

#ifndef WINDOWMANAGER_WINDOWMANAGER_H_
#define WINDOWMANAGER_WINDOWMANAGER_H_

#include "Window.h"

typedef struct
{
	int32_t Data;
} DataPacket;

void InitWindowManager(void);
void SetActiveWindow(Window* w);
void HandleTouch(int TouchX, int TouchY);
void HandleNewData();
uint8_t HandleDraw(void);

/**
 * Passes a null-terminated string console
 * @param str the string to draw
 */
void HandleString(char* str);

/**
 * Passes an int32 to the line chart
 * @param data the number
 */
void HandleGame();

#endif /* WINDOWMANAGER_WINDOWMANAGER_H_ */
