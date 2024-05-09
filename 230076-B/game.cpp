//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
// 										My Header Files 									//
#include "classes.h"
using namespace std;
void NonPrintableKeys(int key, int x, int y);
Game **game = new Game *[2];

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

/*
 * Main Canvas drawing function.
 * */
void GameDisplay()
{
	//  set the background color using function glClearColor.
	//  to change the background play with the red, green and blue values below.
	//  Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (game[1] != nullptr && game[0][0].get_state() != 4)
	{
		// Level Ending Conditions
		if (game[1][0].get_bricks() == 0 && game[1][0].get_level() == 1)
		{
			int s = game[1][0].get_score();
			delete game[1];
			game[1] = new level_2;
			game[1][0].set_score(s);
			usleep(300 * 10000);
		}
		else if (game[1][0].get_bricks() == 0)
		{
			int s = game[1][0].get_score();
			delete game[1];
			game[1] = new level_3;
			game[1][0].set_score(s);
			usleep(300 * 10000);
		}
		else if (game[1][0].get_bricks() == 0 && game[1][0].get_level() == 3)
		{
			int s = game[1][0].get_score();
			delete game[1];
			fstream file;
			file.open("HighScores.txt");
			file << s << endl;
			file.close();
			game[1] = nullptr;
			usleep(300 * 10000);
			game[0][0].set_state(1);
		}
		if (game[1][0].get_lives() > -1)
		{
			game[1][0].simulate_game();
		}
		else
		{
			// Game OVer if Lives equals 0
			fstream file;
			file.open("HighScores.txt", ios::app);
			file<< game[1][0].get_score()<<endl;
			file.close();
			glutPostRedisplay();
			usleep(300 * 10000);
			delete game[1];
			game[1] = nullptr;
			game[0][0].set_state(1);
		}
	}
	if (game[0][0].get_state() != 5)
		game[0][0].display();
	glutPostRedisplay();
	glutSpecialFunc(NonPrintableKeys);
	glutSwapBuffers(); // do not modify this line..
}

void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		if (game[1] != nullptr && game[0][0].get_state() != 4 && game[1][0].get_level() == 3)
		{
			if (game[1][0].get_2paddle_x() - 20 < 20)
				game[1][0].set_2paddle_x(20);
			else
				game[1][0].set_2paddle_x(game[1][0].get_2paddle_x() - 20);
		}
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
		if (game[1] != nullptr && game[0][0].get_state() != 4 && game[1][0].get_level() == 3)
		{
			if (game[1][0].get_2paddle_x() + 20 > 1276 - game[1][0].get_paddle_width_2())
				game[1][0].set_2paddle_x(1276 - game[1][0].get_paddle_width_2());
			else
				game[1][0].set_2paddle_x(game[1][0].get_2paddle_x() + 20);
		}
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
		if (game[0][0].get_choice() < 2)
			game[0][0].set_choice(game[0][0].get_choice() + 1);
	}

	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		if (game[0][0].get_choice() > 0)
			game[0][0].set_choice(game[0][0].get_choice() - 1);
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int x, int y)
{
	// Use to go to the Previous Menu
	// Choice Is basically the Green Bar
	if (key == 27 /* Escape key ASCII*/)
	{
		if (game[0][0].get_state() == 1) // Control is in Main Menu
		{
			delete game[0];
			delete game[1];
			delete[] game;
			exit(1);
		}
		else if (game[0][0].get_state() == 2 || game[0][0].get_state() == 3) // Copntrol is Either in Highscore or level
			game[0][0].set_state(1);
		else if (game[0][0].get_state() == 5)
			game[0][0].set_state(4);
		else if (game[0][0].get_state() == 4)
			game[0][0].set_state(5);
	}
	else if (key == 13 && game[0][0].get_state() == 1)
	{
		if (game[0][0].get_choice() == 0)
		{
			delete game[0];
			delete[] game;
			exit(1); // Exit Called
		}
		else if (game[0][0].get_choice() == 1)
		{
			game[0][0].set_state(3); // HighScore Menu
		}
		else if (game[0][0].get_choice() == 2)
		{
			game[0][0].set_state(2); // Levels Menu
		}
	}
	else if (key == 13 && game[0][0].get_state() == 2)
	{
		if (game[1] != nullptr)
			delete game[1];
		if (game[0][0].get_choice() == 2)
			game[1] = new level_1;
		else if (game[0][0].get_choice() == 1)
			game[1] = new level_2;
		else if (game[0][0].get_choice() == 0)
			game[1] = new level_3;
		else
			game[1] = new level_1;
		game[0][0].set_state(5);
	}
	else if (key == 13 && game[0][0].get_state() == 4)
	{
		if (game[0][0].get_choice() == 2)
			game[0][0].set_state(5);
		else if (game[0][0].get_choice() == 1)
		{
			game[0][0].set_state(1);
			if (game[1] != nullptr)
				delete game[1];
			game[1] = nullptr;
		}
		else if (game[0][0].get_choice() == 0)
		{
			delete game[0];
			if (game[1] != nullptr)
				delete game[1];
			delete[] game;
			game = nullptr;
			exit(1);
		}
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{
	// static int arr[5] = {6, 6, 6, 6,6};
	if (game[1] != nullptr && game[0][0].get_state() != 4)
	{
		Game a;
		game[1][0].effect(a);
	}
	// implement your functionality here
	// glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(500, Timer, 0);
}

void MousePressedAndMoved(int x, int y)
{
	glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	if (game[1] != nullptr && game[0][0].get_state() != 4)
	{
		if (x + 20 > 1276 - game[1][0].get_paddle_width())
			game[1][0].set_paddle_x(1276 - game[1][0].get_paddle_width());
		else if (x - 20 < 20)
			game[1][0].set_paddle_x(25);
		else
			game[1][0].set_paddle_x(x);
	}
	glutPostRedisplay();
}
void MouseClicked(int button, int state, int x, int y)
{
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	int width = 1300, height = 768;				  // i have set my window size to be 800 x 600
	InitRandomizer();							  // seed the random number generator...
	glutInit(&argc, argv);						  // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50);				  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("OOP Project");			  // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...
	game[0] = new menu();
	game[1] = nullptr; // No Level yet
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay);	 // tell library which function to call for drawing Canvas.
									 // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}

#endif /* AsteroidS_CPP_ */