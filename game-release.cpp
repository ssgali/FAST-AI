//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
// #include<sys/wait.h>
// #include<stdlib.h>
// #include<stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void display_boundries();
void display_boundries_2();
void show_stats();
void big_food();
void draw_food();
void reset_file();
void check_file();
void move_snake();
void draw_snake();
void hurdles();
bool squares();
void end_condition(bool end = false);
void end_condition_2();
bool check();
void set_food(int l, int m = 5);
void reset();
void level_1();
void level_2();
void level_3();

//    GLOBAL VARIABLES
int square_x[4] = {23, 5, 15, 15}, square_y[4] = {15, 15, 23, 5};
int food_time[5] = {0, 0, 0, 0, 0};
int big_food_time = 0;
int hurdle_length = 0;
bool resume = false;
bool difficulty = false;
bool flag = false; // hurdle checking
int hurdle_time = 0;
double startx = 320, starty = 400;
int snake_len = 2;
int snake_len_x[270] = {12, 11};
int snake_len_y[270] = {13, 13};
bool easy = true, med = false, hard = false;
bool move_p[4] = {false, true, false, false}, start_game = false, win = false, stats = false;
int y = 300;
int x = 300;
int i = 13, j = 13;
int temp2 = 12;
int temp1 = 13;
int score = 0;
bool game_end = false;
bool edit = true;
float nav_bar = 17;
int hurdles_x[2], hurdles_y[2];
int food_x[6], food_y[6];

void SetCanvasSize(int width, int height)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
/*
 * Main Canvas drawing function.
 * */

void Display()
{
  if (stats == true)
    show_stats();
  if (start_game == true && easy == true) // Initializing Game
  {
    resume = true;
    if (game_end)
    {
      resume = false;
      usleep(5000000);
      start_game = false;
    }
    // Storing Value of Head
    temp2 = j;
    temp1 = i;
    level_1();
    draw_food();
    DrawString(4, 26, "Score = " + to_string(score), colors[MISTY_ROSE]);
    if (score >= 250)
    {
      easy = false;
      med = true;
      hard = false;
      for (int len = 0; len < snake_len; len++)
      {
        snake_len_x[len] = 0;
        snake_len_y[len] = 0;
      }
      snake_len = 2;
    }
  }
  else if (start_game == true && med == true)
  {
    resume = true;
    if (game_end)
    {
      resume = false;
      usleep(5000000);
      start_game = false;
    }
    // Storing Value of Head
    temp2 = j;
    temp1 = i;
    level_2();
    draw_food();
    DrawString(4, 26, "Score = " + to_string(score), colors[MISTY_ROSE]);
    if (score >= 500)
    {
      easy = false;
      med = false;
      hard = true;
      for (int len = 0; len < snake_len; len++)
      {
        snake_len_x[len] = 0;
        snake_len_y[len] = 0;
      }
      snake_len = 2;
    }
  }
  else if (start_game == true && hard == true)
  {
    resume = true;
    if (game_end)
    {
      resume = false;
      usleep(5000000);
      start_game = false;
    }
    // Storing Value of Head
    temp2 = j;
    temp1 = i;
    level_3();
    draw_food();
    DrawString(4, 26, "Score = " + to_string(score), colors[MISTY_ROSE]);
  }
  // Menu

  if (start_game == false && stats == false)
  {
    glClearColor(0.54 /*Red Component*/, 0.71 /*Green Component*/,
                 0.36 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);                                 // Update the colors
    // DrawLine( 0 , 700 ,  1366 , 700 , 2 , colors[GREEN]);
    DrawRoundRect(11, nav_bar + 0.5, 6, 2, colors[GRAY], 0.4);
    DrawString(12, 18, "Start Game", colors[MISTY_ROSE]);
    DrawString(12, 16, "Resume", colors[MISTY_ROSE]);
    DrawString(12, 14, "Difficulty", colors[MISTY_ROSE]);
    DrawString(12, 12, "High Score", colors[MISTY_ROSE]);
    DrawString(12, 10, "Exit", colors[MISTY_ROSE]);
  }
  if (difficulty == true)
  {
    glClearColor(0.54 /*Red Component*/, 0.71 /*Green Component*/,
                 0.36 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);                                 // Update the colors
    // DrawLine( 0 , 700 ,  1366 , 700 , 2 , colors[GREEN]);
    DrawRoundRect(11, nav_bar + 0.5, 6, 2, colors[GRAY], 0.4);
    DrawString(12, 16, "Easy", colors[MISTY_ROSE]);
    DrawString(12, 14, "Medium", colors[MISTY_ROSE]);
    DrawString(12, 12, "Hard", colors[MISTY_ROSE]);
  }
  glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arrow)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
  if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
  {
    if (move_p[3] == false)
    {
      for (int m = 0; m < 4; m++)
        if (m == 2)
          move_p[m] = true;
        else
          move_p[m] = false;
    }
  }
  else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
  {
    if (move_p[2] == false)
    {
      for (int m = 0; m < 4; m++)
        if (m == 3)
          move_p[m] = true;
        else
          move_p[m] = false;
    }
  }
  else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
  {
    if (start_game == true)
    {
      if (move_p[1] == false)
      {
        for (int m = 0; m < 4; m++)
          if (m == 0)
            move_p[m] = true;
          else
            move_p[m] = false;
      }
    }
    else if (difficulty == true)
    {
      if (nav_bar < 15)
        nav_bar = nav_bar + 2;
    }
    else
    {
      if (nav_bar < 17)
        nav_bar = nav_bar + 2;
    }
  }
  else if (key == GLUT_KEY_DOWN) /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
  {
    if (start_game == true)
    {
      if (move_p[0] == false)
      {
        for (int m = 0; m < 4; m++)
          if (m == 1)
            move_p[m] = true;
          else
            move_p[m] = false;
      }
    }
    else if (difficulty == true)
    {
      if (nav_bar > 11)
        nav_bar = nav_bar - 2;
    }
    else
    {
      if (nav_bar > 9)
        nav_bar = nav_bar - 2;
    }
  }
  /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
   * this function*/
  glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
  if (key == KEY_ESC /* Escape key ASCII*/)
  {
    start_game = false;
    stats = false;
    difficulty = false;
  }
  if (key == 'R' || key == 'r')
  {
    if (stats == true && start_game == false)
      reset_file();
  }
  if (key == 13 && start_game == false && stats == false)
  {
    if (nav_bar == 17)
    {
      game_end = false;
      stats = false;
      start_game = true;
      reset();
    }
    else if (nav_bar == 15 && resume == true)
    {
      stats = false;
      start_game = true;
    }
    else if (nav_bar == 13)
    {
      stats = false;
      difficulty = true;
      start_game = false;
    }
    else if (nav_bar == 11)
    {
      stats = true;
      start_game = false;
    }
    else if (nav_bar == 9)
      exit(1);
  }
  if (key == 13 && difficulty == true)
  {
    if (nav_bar == 15)
    {
      easy = true;
      med = false;
      hard = false;
    }
    else if (nav_bar == 13)
    {
      easy = false;
      med = true;
      hard = false;
    }
    else if (nav_bar == 11)
    {
      easy = false;
      med = false;
      hard = true;
    }
    resume = false;
    start_game = false;
    reset();
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

  // implement your functionality here
  for (int q = 0; q < 5; q++)
  {
    if (food_time[q] == 150)
    {
      set_food(q, q);
      food_time[q] = 0;
    }
  }
  if (big_food_time == 600)
  {
    big_food();
  }
  if (med == true && hurdle_time == 350)
  {
    hurdle_time = 50;
  }
  hurdle_time++;
  glutPostRedisplay();
  if (start_game == true)
  {
    for (int q = 0; q < 5; q++)
    {
      food_time[q]++;
    }
    big_food_time++;
  }
  // once again we tell the library to call our Timer function after next 1000/FPS
  glutTimerFunc((500.0 / FPS), Timer, m);
}

/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{
  int width = 768, height = 768; // i have set my window size to be 800 x 600
  InitRandomizer();              // seed the random number generator...
  glutInit(&argc, argv);         // initialize the graphics library...

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
  glutInitWindowPosition(50, 50);               // set the initial position of our window
  glutInitWindowSize(width, height);            // set the size of our window
  glutCreateWindow("PF's Snake Game");          // set the title of our game window
  SetCanvasSize(width / 27, height / 27);       // set the number of pixels...
                                                // Register your functions to the library,
                                                // you are telling the library names of function to call for different tasks.
  glutDisplayFunc(Display);                     // tell library which function to call for drawing Canvas.
  glutSpecialFunc(NonPrintableKeys);            // tell library which function to call for non-printable ASCII characters
  glutKeyboardFunc(PrintableKeys);              // tell library which function to call for printable ASCII characters
                                                // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
  glutTimerFunc(1.0 / FPS, Timer, 0);
  // glutTimerFunc((2000.0 / FPS), Timer, m);
  //  Display();
  //  now handle the control to library and it will call our registered functions when
  //  it deems necessary...
  glutMainLoop();
  return 1;
}
void level_1()
{
  glClearColor(0.233, 0.150, 0.122, 0);
  glClear(GL_COLOR_BUFFER_BIT); // Update the colors
  // Moving Condition
  move_snake();
  // End Game Condition
  end_condition();
  //  Draw Snake
  draw_snake();
  // Boundries of Game
  display_boundries();
}
void level_3()
{
  glClearColor(0.678, 0.450, 0.322, 0);
  glClear(GL_COLOR_BUFFER_BIT); // Update the colors
  // Moving Condition
  move_snake();
  //
  bool see = squares();
  // End Game Condition
  end_condition(see);
  //  Draw Snake
  draw_snake();
  // Boundries of Game
  display_boundries();
}
bool squares()
{
  for (int t = 0; t < 4; t++)
  {
    for (int x_axis = -4; x_axis < 4; x_axis++)
    {
      if (j == square_x[t] + x_axis && i == square_y[t])
        return true;
    }
    for (int y_axis = -4; y_axis < 4; y_axis++)
    {
      if (j == square_x[t] && i == square_y[t] + y_axis)
        return true;
    }
  }
  if (j == 14 && i == 14)
    return true;
  return false;
}
void level_2()
{
  glClearColor(0.76, 0.21, 0.999, 0);
  glClear(GL_COLOR_BUFFER_BIT); // Update the colors
  // Moving Condition
  move_snake();
  // End Game Condition
  end_condition_2();
  //  Draw Snake
  draw_snake();
  // hurdles();
  //  Boundries of Game
  display_boundries_2();
  if (hurdle_time % 300 == 0)
    hurdles();
  for (int i = 0; i < hurdle_length; i++)
    if (flag)
      DrawSquare(hurdles_x[0] + i, hurdles_y[0], 2, colors[BLACK]);
    else
      DrawSquare(hurdles_x[0], hurdles_y[0] + i, 2, colors[BLACK]);
}
void hurdles()
{
  bool loop_end;
  do
  {
    loop_end = false;
    if (rand() % 2)
    {
      flag = true;
      do
      {
        hurdles_x[0] = GetRandInRange(4, 20);
        hurdles_x[1] = GetRandInRange(4, 20);
        hurdle_length = abs(hurdles_x[0] - hurdles_x[1]);
        if (hurdle_length < 11 && 6 < hurdle_length)
          break;
      } while (true);
      hurdles_y[0] = GetRandInRange(4, 20);
      hurdles_y[1] = hurdles_y[0];
      for (int q = 0; q < snake_len; q++)
      {
        for (int i = 0; i < hurdle_length; i++)
        {
          if (snake_len_x[q] == hurdles_x[0] + i && snake_len_y[q] == hurdles_y[0])
          {
            loop_end = true;
            break;
          }
          if (food_x[6] == hurdles_x[0] + i && food_y[6] == hurdles_y[0])
          {
            loop_end = true;
            break;
          }
          for (int p = 0; p < 5; p++)
          {
            if (food_x[p] == hurdles_x[0] + i && food_y[p] == hurdles_y[0])
            {
              loop_end = true;
              break;
            }
          }
          if (food_x[6] == hurdles_x[0] && food_y[6] == hurdles_y[0] + i)
          {
            loop_end = true;
            break;
          }
        }
      }
    }
    else
    {
      flag = false;
      do
      {
        hurdles_y[0] = GetRandInRange(4, 20);
        hurdles_y[1] = GetRandInRange(4, 20);
        hurdle_length = abs(hurdles_y[0] - hurdles_y[1]);
        if (hurdle_length < 11 && 6 < hurdle_length)
          break;
      } while (true);
      hurdles_x[0] = GetRandInRange(4, 20);
      hurdles_x[1] = hurdles_x[0];
      for (int q = 0; q < snake_len; q++)
      {
        for (int i = 0; i < hurdle_length; i++)
        {
          if (snake_len_x[q] == hurdles_x[0] && snake_len_y[q] == hurdles_y[0] + i)
          {
            loop_end = true;
            break;
          }
          if (food_x[6] == hurdles_x[0] && food_y[6] == hurdles_y[0] + i)
          {
            loop_end = true;
            break;
          }
          for (int p = 0; p < 5; p++)
          {
            if (food_x[p] == hurdles_x[0] + i && food_y[p] == hurdles_y[0])
            {
              loop_end = true;
              break;
            }
          }
          if (food_x[6] == hurdles_x[0] + i && food_y[6] == hurdles_y[0])
          {
            loop_end = true;
            break;
          }
        }
      }
    }
  } while (loop_end);
  // DrawLine(hurdles_x[0], hurdles_y[1],hurdles_x[0], hurdles_y[2], 10, colors[BLACK]);
  // DrawLine(hurdles_x[0], hurdles_y[2],abs(hurdles_x[0]-5), hurdles_y[2], 10, colors[BLACK]);
}
void draw_snake()
{
  DrawCircle(j + 0.5, i + 0.5, 0.5, colors[YELLOW]);
  for (int p = 0; p < snake_len; p++)
  {
    swap(temp2, snake_len_x[p]);
    swap(temp1, snake_len_y[p]);
    DrawSquare(snake_len_x[p], snake_len_y[p], 2, colors[GREEN]);
  }
}
void end_condition(bool end)
{
  if (j < 0 || j > 27)
  {
    if (i > 11 && i < 18)
      j = (j >= 28) ? 0 : 27;
    else
      end = true;
  }
  if (i < 0 || i > 27)
  {
    if (j > 11 && j < 18)
      i = (i >= 28) ? 0 : 27;
    else
      end = true;
  }
  for (int q = 0; q < snake_len; q++)
  {
    if ((snake_len_y[q] == i && snake_len_x[q] == j))
    {
      end = true;
      break;
    }
  }
  if (end)
  {
    if (edit)
    {
      win = check();
      edit = false;
    }
    game_end = true;
  }
}
void end_condition_2()
{
  bool end = false;
  if (j < 0 || j > 27 || i < 0 || i > 27)
    end = true;
  for (int q = 0; q < snake_len; q++)
  {
    if ((snake_len_y[q] == i && snake_len_x[q] == j))
    {
      end = true;
      break;
    }
  }
  for (int hl = 0; hl < hurdle_length; hl++)
  {
    if (flag)
    {
      if (j == hurdles_x[0] + hl && i == hurdles_y[0])
      {
        end = true;
        break;
      }
    }
    else
    {
      if (j == hurdles_x[0] && i == hurdles_y[0] + hl)
      {
        end = true;
        break;
      }
    }
  }
  if (end)
  {
    if (edit)
    {
      win = check();
      edit = false;
    }
    game_end = true;
  }
}
void move_snake()
{
  if (game_end != true)
  {
    if (move_p[0])
      i++;
    else if (move_p[1])
      i--;
    else if (move_p[2])
      j--;
    else if (move_p[3])
      j++;
  }
  else
  {
    DrawCircle(j + 0.40, i + 0.35, 0.4, colors[YELLOW]);
  }
}
void display_boundries()
{
  DrawLine(28, 0, 28, 12, 10, colors[MISTY_ROSE]);
  DrawLine(0, 0, 0, 12, 10, colors[MISTY_ROSE]);
  DrawLine(0, 28, 0, 18, 10, colors[MISTY_ROSE]);
  DrawLine(28, 28, 28, 18, 10, colors[MISTY_ROSE]);
  DrawLine(28, 0, 18, 0, 10, colors[MISTY_ROSE]);
  DrawLine(28, 28, 18, 28, 10, colors[MISTY_ROSE]);
  DrawLine(0, 28, 12, 28, 10, colors[MISTY_ROSE]);
  DrawLine(0, 0, 12, 0, 10, colors[MISTY_ROSE]);
  DrawLine(28, 28, 18, 28, 10, colors[MISTY_ROSE]);
  DrawLine(0, 28, 12, 28, 10, colors[MISTY_ROSE]);
  if (hard == true)
  {
    for (int t = 0; t < 4; t++)
    {
      for (int x_axis = -4; x_axis < 4; x_axis++)
      {
        DrawSquare(square_x[t] + x_axis, square_y[t], 2, colors[BLACK]);
      }
      for (int y_axis = -4; y_axis < 4; y_axis++)
      {
        DrawSquare(square_x[t], square_y[t] + y_axis, 2, colors[BLACK]);
      }
    }
    DrawSquare(14, 14, 2, colors[BLACK]);
  }
}
void display_boundries_2()
{
  DrawLine(0, 0, 0, 28, 10, colors[MISTY_ROSE]);
  DrawLine(0, 0, 28, 0, 10, colors[MISTY_ROSE]);
  DrawLine(28, 28, 0, 28, 10, colors[MISTY_ROSE]);
  DrawLine(28, 28, 28, 0, 10, colors[MISTY_ROSE]);
}
void show_stats()
{
  glClearColor(0.23, 0.45, 0.3, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  DrawString(8, 4, "Press R or r to reset Score", colors[MISTY_ROSE]);
  string h_score = "";
  ifstream file;
  file.open("hs.txt");
  int l = 0;
  getline(file, h_score);
  if (h_score == "")
  {
    reset_file();
  }
  else
  {
    while (!(file.eof()))
    {
      DrawString(8, 20 - l, h_score, colors[BLUE]);
      l = l + 5;
      getline(file, h_score);
    }
  }
  file.close();
}
void reset_file()
{
  ofstream file1;
  file1.open("hs.txt");
  for (int p = 0; p < 3; p++)
    file1 << to_string(p + 1) + " Score is 0 by NONE\n";
  file1.close();
}
void check_file()
{
  ifstream file;
  file.open("hs.txt");
  string data;
  getline(file, data);
  if (data == "")
    reset_file();
  file.close();
}
void big_food()
{
  bool go = false;
  do
  {
    go = false;
    food_x[6] = rand() % 26 + 2;
    food_y[6] = rand() % 26 + 2;
    for (int q = 0; q < 5; q++)
      if (food_x[q] == food_x[6] || food_y[q] == food_y[6])
        go = true;
    for (int k = 0; k < snake_len; k++)
      if ((snake_len_x[k] == food_x[6] && snake_len_y[k] == food_y[6]))
        go = true;
  } while (go);
}
void reset()
{
  if (med == true)
  {
    hurdles();
  }
  i = 13, j = 13;
  score = 0;
  for (int len = 0; len < snake_len; len++)
  {
    snake_len_x[len] = 0;
    snake_len_y[len] = 0;
  }
  snake_len = 2;
  food_x[6] = -5;
  food_y[6] = -5;
  big_food_time = 0;
  hurdle_time = 0;
  edit = true;
  for (int l = 0; l < 5; l++)
  {
    food_time[l] = 0;
    set_food(l, l);
  }
  check_file();
}
void draw_food()
{
  for (int z = 0; z < 5; z++)
    DrawCircle(food_x[z] + 0.5, food_y[z] + 0.5, 0.5, colors[RED]);
  for (int z = 0; z < 5; z++)
  {
    if (j == food_x[z] && i == food_y[z])
    {
      set_food(z);
      score += 5;
      snake_len++;
      food_time[z] = 0;
    }
  }
  DrawCircle(food_x[6] + 1, food_y[6] + 1, 1, colors[BLANCHED_ALMOND]);
  if (((j == food_x[6] + 1 && i == food_y[6] + 1)) || (j == food_x[6] && i == food_y[6]) || (j == food_x[6] && i == food_y[6] + 1) || (j == food_x[6] + 1 && i == food_y[6]))
  {
    score = score + 20;
    snake_len++;
    food_x[6] = -5;
    food_y[6] = -5;
    big_food_time = 0;
  }
  else if (big_food_time == 750)
  {
    food_x[6] = -5;
    food_y[6] = -5;
    big_food_time = 0;
  }
}
bool check()
{
  DrawString(20, 25, "Game Over!", colors[BLUE]);
  DrawString(20, 23, "Your score is " + to_string(score), colors[BLACK]);
  ifstream file;
  string h[3];
  string num = "";
  int count = 0;
  char c;
  int a[3] = {70, 60, 23};
  file.open("hs.txt");
  while (count < 3)
  {
    getline(file, h[count]);
    h[count] = h[count].substr(2);
    long unsigned int len = 1;
    c = h[count][len];
    while (c != 'b')
    {
      if (isdigit(c))
        num = num + c;
      len++;
      c = h[count][len];
    }
    if (num != "")
      a[count] = stoi(num);
    num = "";
    count++;
  }
  file.close();
  int temp_score = score;
  bool val = false;
  ofstream file1;
  file1.open("hs.txt");
  string name;
  for (int ind = 0; ind < 3; ind++)
  {
    if (a[ind] < temp_score)
    {
      DrawString(5, 10, "You Have Set a New Record of " + to_string(score) + "! Congratulations", colors[BLUE]);
      cout << "Enter your name to save the progress!\n";
      getline(cin, name);
      string temp_arr = " Score is " + to_string(temp_score) + " by " + name;
      for (int w = ind; w < 3; w++)
      {
        swap(h[w], temp_arr);
      }
      val = true;
      break;
    }
  }
  for (int g = 0; g < 3; g++)
    file1 << to_string(g + 1) + " " + h[g] + "\n";
  file1.close();
  return val;
}
void set_food(int l, int m)
{
  bool go = false;
  do
  {
    go = false;
    food_x[l] = rand() % 27 + 1;
    food_y[l] = rand() % 27 + 1;
    if (hard == true)
    {
      for (int t = 0; t < 4; t++)
      {
        for (int x_axis = -4; x_axis < 4; x_axis++)
        {
          if (food_x[l] == square_x[t] + x_axis && food_y[l] == square_y[t])
            go = true;
        }
        for (int y_axis = -4; y_axis < 4; y_axis++)
        {
          if (food_x[l] == square_x[t] && food_y[l] == square_y[t] + y_axis)
            go = true;
        }
      }
      if (food_x[l] == 14 && food_y[l] == 14)
        go = true;
    }
    for (int q = 0; q < m; q++)
      if ((food_x[q] == food_x[l] || food_y[q] == food_y[l]) && (q != l))
      {
        go = true;
        break;
      }
    for (int q = 0; q < 5; q++)
    {
      if ((abs(food_x[q] - food_x[l]) == abs(food_y[q] - food_y[l])) && (q != l))
      {
        go = true;
        break;
      }
    }
    for (int k = 0; k < snake_len; k++)
      if ((snake_len_x[k] == food_x[l] && snake_len_y[k] == food_y[l]))
      {
        go = true;
        break;
      }
    if (med == true)
    {
      for (int k = 0; k < hurdle_length; k++)
      {
        if (flag)
        {
          if ((food_x[l] == hurdles_x[0] + k) && food_y[l] == hurdles_y[0])
          {
            go = true;
            break;
          }
        }
        else
        {
          if (food_x[l] == hurdles_x[0] && food_y[l] == hurdles_y[0] + k)
          {
            go = true;
            break;
          }
        }
      }
    }
  } while (go);
}
#endif /* Snake Game */
