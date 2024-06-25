/*
 * GameWindow.h
 *
 *  Created on: Nov 28, 2023
 *      Author: krisz
 */

#ifndef WINDOWS2_GAMEWINDOW_H_
#define WINDOWS2_GAMEWINDOW_H_

#include "Window.h"
#include "GameDefines.h"

Window* GetGameWindow();
void InitGameWindow();
void GameNewData(int TouchX, int TouchY);

#endif /* WINDOWS2_GAMEWINDOW_H_ */
