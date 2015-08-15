/* ---------------------------------------------------------------------------
**
** File: WindowsConsoleCmd.h
** Description: Contains Methods used to manipluate the Console window on
** Windows
**
** NOTE: This implementation requires the use of Window spacific API's
**
** Author: Nathan Bremmer
** -------------------------------------------------------------------------*/

#pragma once

#include "targetver.h"
#include "stdafx.h"

using namespace std;

//Clears the Console and resets the currsor at 0,0
void ClearScreen();

//Pads the proved string out to the specified size with the specified character which is ' ' by default.
string StringPadding(string value, size_t size, char character = ' ');