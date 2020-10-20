// PersonalSnakeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string> // to use strings, must include this library
#include <iostream>
#include <conio.h>
#include<Windows.h>
#include<ctime>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[30], tailY[30];
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
char map[height][width] = {};

void loadMapArray();
void Draw();
void Input();
void Logic();
void makeTopBot(int i);

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = 1+rand() % width;
	fruitY = 1+rand() % height;
	score = 0;
	srand(time(0));
}
int main()
{
	Setup();
	while (!gameOver)
	{
		loadMapArray();
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
}

void loadMapArray()
{
	makeTopBot(0);
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == y && j == x)
			{
				map[i][j] = 'O';
			}
			else if (i == fruitY && j == fruitX)
			{
				map[i][j] = 'F';
			}
			else if (j == 0 || j == width - 1)// negative 2 because of first and last are walls
			{
				map[i][j] = '#';
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					map[i][j] = ' ';
				}
			}
			
		}
		cout << endl;
	}
	makeTopBot(height);
	cout << endl;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < height + 1; i++)    //This loops on the rows.
	{
		for (int j = 0; j < width; j++) //This loops on the columns
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "Score: " << score;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch()) 
		{
			case 'w':
				dir = UP;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;
	for (int i = 1; i <= nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) 
	{
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
	}

	if (x > width-2 || x < 1 || y > height-1 || y < 1)
	{
		gameOver = true;
		cout << "\nYOU HAVE LOST THE GAME" << endl;
	}
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			cout << "\nYOU HAVE LOST THE GAME"<<endl;
			gameOver = true;
		}
	}
	if (score == 100)
	{
		gameOver = true;
		cout << "\nYOU HAVE WON"<<endl;
	}
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = 1+rand() % (width-1);
		fruitY = 1+rand() % (height-1);
		nTail++;
	}
}

void makeTopBot(int i)
{
	for (int j = 0; j < width; j++)
	{
		map[i][j] = '#';
	}
	cout << endl;
}