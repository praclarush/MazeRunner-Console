/* ---------------------------------------------------------------------------
**
** File: WindowsConsoleCmd.h
** Description: Contains Methods used to manipluate the Console window on
** Windows
**
** NOTE: This implementation requires the use of Window spacific API's
**
** Source = http://support.microsoft.com/kb/99261
** 
** Author: Nathan Bremmer with help from Microsoft
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "WindowsConsoleCmd.h"
using namespace std;

//Clears the Console and resets the currsor at 0,0
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

//Pads the proved string out to the specified size with the specified character which is ' ' by default.
string StringPadding(string value, size_t size, char character)
{
	value.resize(size, character);
	return value;
}