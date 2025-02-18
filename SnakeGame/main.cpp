#include <iostream>
#include <windows.h>
#include <stdlib.h>  //older compilers don't have rand() included
#include <conio.h>  //library for output/input in the console.  required to provide input to the game

using namespace std;
bool gameOver;
int tailX[50], tailY[50];
int nTail;
const int width = 20;  //dimension of game screen
const int height = 20;
int x, y, fruitX, fruitY, score;  //location of player and fruit respectively
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Settings() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Visual() {
	system("cls");  //clear screen

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";

			if (i == y && j == x)
				cout << "O";       //print the head of your snake at player location

			else if (i == fruitY && j == fruitX)
				cout << "*";
			else {
				bool printTail = false;

				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						printTail = true;
					}
				}
				if(!printTail)

				cout << " ";

			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}



	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case UP:
		y--;
		break;
	default:
		break;
	}
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	if (x == fruitX && y == fruitY) {
		score++;
		fruitX = rand() % width;	//spawn fruit in another location
		fruitY = rand() % height;
		nTail++;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
}

void Input() {
	if (_kbhit()) {		//keyboard hit  <conio.h>  console input/output
		switch (_getch()) {   //get character
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameOver = true;
		}
	}
}

	int main() {

		Settings();

		while (!gameOver) {
			Visual();
			Input();
			Logic();
			Sleep(40);  //slow our game refresh for 10 ms, this is from windows.h library 
		}

		return 0;
	}