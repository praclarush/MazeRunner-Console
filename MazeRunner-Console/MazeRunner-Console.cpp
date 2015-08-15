/* ---------------------------------------------------------------------------
**
** File: Bremmer_Project1Final.cpp
** Description: Main Program file for CSPG106 File Project - Game Maze Runner
**
** NOTE: This application requires Windows to run as it uses Window's API's
**
** Author: Nathan Bremmer
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "File.h"
#include "WindowsConsoleCmd.h"
#include "global.h"
#include <conio.h>
#include <ctype.h>

using namespace std;

struct POS
{
	int width;
	int height;
};

struct Level
{
	int height;
	int width;
	char map[MAX_HEIGHT][MAX_WIDTH];
	POS goal;
	POS player;

	/*Level()
	{
	height = 0;
	width = 0;
	goal = 0;
	start = 0;
	}*/
};

map<int, string> files;
Level level;

//Init Global Variables
void init()
{	
	//load maze files
	getFiles(".\\Maps\\*.map", files);
}

//draws the Main Menu
void drawMenu()
{
	ClearScreen();

	cout << string(35, '*') << "\n";
	cout << "* Welcome to Maze Runner\n";
	cout << "* Please select a map file to load\n* q - to quit or r - to refresh the menu\n*\n* Maps: \n";
	for (int i = 1; i <= files.size(); i++)
	{
		cout << "* " << i << " - " << files[i] << "\n";
	}
	cout << string(35, '*') << "\n";
}

//loads the map from the selected file
void loadMap(ifstream& in)
{
	// read maze layout.
	// read width and heigh of maze
	in >> level.height >> level.width;
	in.ignore(100, END_OF_LINE_CHAR);

	for (int row = 1; row <= level.height; row++)
	{
		char ch;
		for (int col = 1; col <= level.width; col++)
		{
			in.get(ch);
			if ((row <= MAX_HEIGHT) && (col <= MAX_WIDTH))
				level.map[row - 1][col - 1] = ch;
		}

		in.ignore(100, END_OF_LINE_CHAR);
	}

	if ((level.width > MAX_WIDTH) || (level.height > MAX_HEIGHT)) {
		cout << "Map too large for window";
		exit(1);
	}
}

//Loads the positions of the start place and goal from the selected file
void loadPositions(ifstream& in)
{
	// load start and goal positions
	// s = start, g = goal
	// first number is hight, second is width
	while (in.peek() != EOF && !in.eof())
	{
		char ch;
		in >> ch;

		if (ch == 's')
		{
			in >> level.player.height >> level.player.width;
			in.ignore(100, END_OF_LINE_CHAR);			
		}
		else if (ch == 'g')
		{
			in >> level.goal.height >> level.goal.width;
		}
	}
}

//sets the positions of the start and goal into the level map
void setPositions()
{
	//sets the start position of the player
	level.map[level.player.height][level.player.width] = PLAYER;

	//sets the goal in the map
	level.map[level.goal.height][level.goal.width] = GOAL;	
}

// Load the selected Map
void LoadLevel(int Map)
{
	ifstream in;
	in.open(".\\Maps\\" + files[Map]);

	if (!in.good())
	{
		cout << "File does not exist. Quitting.\n";
		exit(1);
	}
	loadMap(in);
	loadPositions(in);
	setPositions();
	in.close();
}

// draw the map and instructions on the screen
void drawMap()
{
	ClearScreen();

	//write the instructions
	cout << "You are the '" << PLAYER << "' symbol. Your goal is to reach the end of the maze\n";
	cout << "marked by the '" << GOAL << "' symbol. You can quit at anytime by pressing the ESC key\n";
	cout << "Use the w (up), s (down), a (left) and d (right) to navigate the maze and reach the end";
	cout << endl << endl;


	for (int h = 0; h <= level.height; h++)
	{
		for (int w = 0; w <= level.width; w++)
		{
			cout << level.map[h][w];
		}
		cout << endl;
	}
}

//Main Game Loop
void StartLevel(int Map)
{
	LoadLevel(Map);
	drawMap();


	bool gameOver = false;
	bool quit = false;
	char key;

	do {
		key = _getch();

		switch (key)
		{
		case 'w':
			if (level.map[level.player.height - 1][level.player.width] == ' ')
			{
				level.map[level.player.height][level.player.width] = ' ';
				level.player.height--;
				level.map[level.player.height][level.player.width] = '*';
			}
			else if (level.map[level.player.height - 1][level.player.width] == '#')
				gameOver = true;

			break;
		case 's':
			if (level.map[level.player.height + 1][level.player.width] == ' ')
			{
				level.map[level.player.height][level.player.width] = ' ';
				level.player.height++;
				level.map[level.player.height][level.player.width] = '*';
			}
			else if (level.map[level.player.height + 1][level.player.width] == '#')
				gameOver = true;

			break;
		case 'a':
			if (level.map[level.player.height][level.player.width - 1] == ' ')
			{
				level.map[level.player.height][level.player.width] = ' ';
				level.player.width--;
				level.map[level.player.height][level.player.width] = '*';
			}
			else if (level.map[level.player.height][level.player.width - 1] == '#')
				gameOver = true;

			break;
		case 'd':
			if (level.map[level.player.height][level.player.width + 1] == ' ')
			{
				level.map[level.player.height][level.player.width] = ' ';
				level.player.width++;
				level.map[level.player.height][level.player.width] = '*';
			}
			else if (level.map[level.player.height][level.player.width + 1] == '#')
				gameOver = true;

			break;
		case ESC:
			quit = true; 
			break;
		default:
			break;
		}

		drawMap();
	} while (!gameOver && !quit);

	ClearScreen();

	cout << "GAME OVER! \n";
	if (gameOver)
	{
		cout << "Congratulations! You've solved the map.\n";
	}
	else
	{
		cout << "You decided to quit before finishing the maze. Maybe you should try a easyer level.\n";
	}
	cout << "Press Enter to return to the Main Menu. \n";
	cin.get();
}

int main()
{
	init();

	drawMenu();

	char key;

	do {
		key = _getch();
		
		if (isdigit(key))
		{
			int mapNum = (key - '0') ;

			//add validation here for number range
			if (mapNum != 0 && mapNum <= files.size())
			{
				StartLevel(mapNum);

				drawMenu();
			}			
		}
		else if (key == 'r')
		{
			init();
			drawMenu();
		}
			
	} while (key != 'q');
	
	return 0;
}

