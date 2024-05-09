
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cmath> // for basic math functions such as cos, sin, sqrt
class Food;
class Ball;
//Pre Declarations for Composition or Aggregation

class Bricks
{
public:
    int location[2] = {0, 0}; // X and Y coordinates of Brick on screen
    int size[2] = {80, 20};   // Width and Height of Brick
    int score_count = 0;      //  Score to destroy brick
    int color = 0;            // Color of Brick
    Bricks()
    {}

        //Copy Constructor
    Bricks(Bricks &b)
    {
        this->location[0] = b.location[0];
        this->location[1] = b.location[1];
        this->size[0] = b.size[0];
        this->size[1] = b.size[1];
        this->score_count = b.score_count;
        this->color = b.color;
    }
    void print_brick()
    {
        int x = location[0];
        int y = location[1];
        if (color == 0)
            DrawRectangle(x, y, 80, 20, colors[ORANGE]);
        else if (color == 1)
            DrawRectangle(x, y, 80, 20, colors[RED]);
        else if (color == 2)
            DrawRectangle(x, y, 80, 20, colors[BLUE]);
        else if (color == 3)
            DrawRectangle(x, y, 80, 20, colors[VIOLET]);
        else if (color == 4)
            DrawRectangle(x, y, 80, 20, colors[GREEN]);
    }
    //To initialize the brick but not print it
    void make_brick(int x, int y, int size, int color)
    {
        this->color = color;
        this->location[0] = x;
        this->location[1] = y;
        if (color == 0 || color == 4)
            score_count = 1;
        else if (color == 2)
            score_count = 3;
        else
            score_count = 2;
    }
};
class Game
{

    //              Main Class Abstraction and PolyMorphesism
protected:
    int score = 0;
    int h_score = 0;
    int width = 1300;
    int height = 768;
public:
        //Virtual Function
    virtual int get_choice()
    {
        return 0;
    }
    virtual void set_choice(int s)
    {
    }
    virtual void display()
    {
    }
    virtual void set_state(int s)
    {
    }
    virtual int get_state()
    {
        return 0;
    }
    virtual void set_level(int s)
    {
    }
    virtual void simulate_game()
    {
    }
    virtual void set_paddle_x(int s)
    {
    }
    virtual void set_paddle_width(int s)
    {
    }
    virtual int get_paddle_x()
    {
        return 0;
    }
    virtual int get_paddle_width()
    {
        return 0;
    }
    virtual void set_ball_x(float s)
    {
    }
    virtual void set_ball_y(float s)
    {
    }
    virtual void set_ball_color(int s)
    {
    }
    virtual int get_ball_color()
    {
        return 0;
    }
    virtual float get_ball_x()
    {
        return 0;
    }
    virtual float get_ball_y()
    {
        return 0;
    }
    virtual int get_speed()
    {
        return 0;
    }
    virtual void set_speed(int s)
    {
    }
    virtual int get_bricks()
    {
        return 0;
    }
    virtual void set_bricks(int s)
    {
    }
    virtual Bricks *get_all_bricks()
    {
        return nullptr;
    }
    virtual void set_all_bricks(Bricks *p)
    {
    }
    virtual int get_lives()
    {
        return 0;
    }
    virtual void set_lives(int s)
    {
    }
    virtual int get_level()
    {
        return 0;
    }
    virtual void set_score(int s)
    {
    }
    virtual void set_hscore(int s)
    {
    }
    virtual int get_score()
    {
        return 0;
    }
    virtual int get_2paddle_x()
    {
        return 0;
    }
    virtual void set_2paddle_x(int s)
    {
    }
    virtual int get_paddle_width_2()
    {
        return 0;
    }
    virtual void set_paddle_width_2(int s)
    {
    }
    virtual void set_power_up(bool b)
    {
    }
    virtual bool get_power_up()
    {
        return 0;
    }
    virtual Food *get_power_food()
    {
        return nullptr;
    }
    virtual void set_paddle_color(int s)
    {
    }
    virtual void set_paddle2_color(int s)
    {
    }
    virtual int get_property()
    {
        return 0;
    }
    virtual void set_property(int s)
    {
    }
    virtual void effect(Game &game)
    {
    }
    virtual float get_angle()
    {
        return 0;
    }
    virtual void set_angle(float a)
    {
    }
    virtual void set_balls_active(bool a)
    {}
    virtual ~Game()
    {}
};
class Food : public Game
{
private:
    int timer[5] = {12, 12, 12, 12, 12};    //Timer of Each Power Up
    bool active[5] = {0, 0, 0, 0, 0};       // Active Power Bars
    int location[2] = {0, 0};               //  X and Y coordinates of Brick on screen
    int color = 0;                          //  Color of Brick
public:
    Food()
    {}
    Food(int x, int y, int color)
    {
        location[0] = x;
        location[1] = y;
        this->color = color;
    }
    
    //This will print the Power Up on the Map
    void fall(Game &game)
    {
        location[1] -= 3;
        if (location[1] < 0)
        {
            game.set_power_up(0);
            return;
        }
        else if ((location[1] <= 20) && (location[0] >= game.get_paddle_x() && location[0] <= (game.get_paddle_x() + game.get_paddle_width())))
        {
            game.set_property(color);
            active[color] = 1; // activate the Power
            timer[color] = 12; // reseting time
            return;
        }
        if (color == 1)
        {
            DrawRectangle(location[0], location[1], 80, 20, colors[RED]);
        }
        else if (color == 0)
        {
            DrawSquare(location[0], location[1], 40, colors[ORANGE]);
        }
        else if (color == 2)
        {
            DrawCircle(location[0], location[1], 20, colors[BLUE]);
        }
        else if (color == 3)
        {
            DrawSquare(location[0], location[1], 40, colors[VIOLET]);
        }
        else if (color == 4)
        {
            DrawTriangle(location[0], location[1], location[0] + 25, location[1] + 25, location[0] + 50, location[1], colors[GREEN]);
        }
    }
    //Properties of Power Ups
    void effect(Game &game)
    {
        if (active[0])
        {
            // game.set_balls_active(1);
            timer[0] -= 1;
            if (timer[0] == 0)
            {
                timer[0] = 12;
                active[0] = 0;
                reset(0, game);
            }
        }
        if (active[1])
        {
            // inc speed
            game.set_speed(20);
            timer[1] -= 1;
            if (timer[1] == 0)
            {
                timer[1] = 12;
                active[1] = 0;
                reset(1, game);
            }
        }
        if (active[2])
        {
            // dec speed
            game.set_speed(5);
            timer[2] -= 1;
            if (timer[2] == 0)
            {
                timer[2] = 12;
                active[2] = 0;
                reset(2, game);
            }
        }
        if (active[3])
        {
            // dec width
            if (game.get_level() == 3 && game.get_paddle_width() >= 150 && game.get_paddle_width_2() >= 150)
            {
                game.set_paddle_width(game.get_paddle_width() / 2);
                game.set_paddle_width_2(game.get_paddle_width_2() / 2);
            }
            else if (game.get_paddle_width() >= 150)
            {
                game.set_paddle_width(game.get_paddle_width() / 2);
            }
            timer[3] -= 1;
            if (timer[3] == 0)
            {
                timer[3] = 12;
                active[3] = 0;
                reset(3, game);
            }
        }
        if (active[4])
        {
            if (game.get_level() == 3 && game.get_paddle_width() <= 150 && game.get_paddle_width_2() <= 150)
            {
                game.set_paddle_width(game.get_paddle_width() * 2);
                game.set_paddle_width_2(game.get_paddle_width_2() * 2);
            }
            else if (game.get_paddle_width() <= 150)
            {
                game.set_paddle_width(game.get_paddle_width() * 2);
            }
            timer[4] -= 1;
            if (timer[4] == 0)
            {
                timer[4] = 12;
                active[4] = 0;
                reset(4, game);
            }
        }
    }
    //reseting the power ups to Default settings 
    void reset(int num, Game &game)
    {
        if (num == 0)
        {
            // reset balls
            set_balls_active(0);
        }
        if (num == 1)
        {
            // reset inc speed
            game.set_speed(10);
        }
        if (num == 2)
        {
            // reset dec speed
            game.set_speed(10);
        }
        if (num == 3)
        {
            // reset decrease height
            if (game.get_level() == 3)
            {
                game.set_paddle_width(150);
                game.set_paddle_width_2(150);
            }
            else
            {
                game.set_paddle_width(150);
            }
        }
        if (num == 4)
        {
            // inc width
            if (game.get_level() == 3)
            {
                game.set_paddle_width(150);
                game.set_paddle_width_2(150);
            }
            else
            {
                game.set_paddle_width(150);
            }
        }
    }
    //Initializing the Power Up but not yet printing
    void set_cord(int x, int y, int color)
    {
        location[0] = x;
        location[1] = y;
        this->color = color;
    }
};

class Player
{
private:
    int color;
    int location_x, location_y;
    int size[2] = {150, 20}; // Width and Height of Player
public:
    Player(int paddle_x, int width_p, int col, int paddle_y = 0)
    {
        color = col;
        location_x = paddle_x;
        location_y = paddle_y;
        size[0] = width_p;
        if (color == 0)
            DrawRectangle(location_x, location_y, size[0], size[1], colors[ORANGE]);
        else if (color == 1)
            DrawRectangle(location_x, location_y, size[0], size[1], colors[RED]);
        else if (color == 2)
            DrawRectangle(location_x, location_y, size[0], size[1], colors[BLUE]);
        else if (color == 3)
            DrawRectangle(location_x, location_y, size[0], size[1], colors[VIOLET]);
        else if (color == 4)
            DrawRectangle(location_x, location_y, size[0], size[1], colors[GREEN]);
    }
};
class Ball : public Game
{
private:
    float loc_x;
    float loc_y;

public:
    Ball(float x, float y, int color) : loc_x(x), loc_y(y)
    {
        if (color == 0)
            DrawCircle(loc_x, loc_y, 10, colors[ORANGE]);
        else if (color == 1)
            DrawCircle(loc_x, loc_y, 10, colors[RED]);
        else if (color == 2)
            DrawCircle(loc_x, loc_y, 10, colors[BLUE]);
        else if (color == 3)
            DrawCircle(loc_x, loc_y, 10, colors[VIOLET]);
        else if (color == 4)
            DrawCircle(loc_x, loc_y, 10, colors[GREEN]);
    }
    void movement(int speed, Game &game)
    {
            //Direction of Ball
        static bool ball_ud = true;
        static bool ball_lr = true;     
        //Ball Moving upward
        if (ball_ud == true)
        {
            if ((game.get_ball_y() > height - 60) && game.get_level() == 3)     // For third Level Upper Paddle Game Over
            {
                game.set_lives(game.get_lives() - 1);
                if (game.get_lives() == -1)
                    DrawString(500, 500, "Game-Over\n", colors[BLACK]);
                ball_ud = true;
                ball_lr = true;
                game.set_ball_x(600);
                game.set_ball_y(150);
                game.set_angle(0.5);
                game.set_speed(10);
                game.set_power_up(0);
                usleep(40 * 10000);
                return;
            }
            else if ((game.get_ball_y() >= height - 80) && (game.get_ball_x() >= game.get_2paddle_x() && game.get_ball_x() <= (game.get_2paddle_x() + game.get_paddle_width_2())) && game.get_level() == 3)
            {
                //for Third Level Upper Paddle Collision
                //setting angle from the mid formula
                float d_f_c = (game.get_ball_x() - (game.get_2paddle_x() + (game.get_paddle_width_2() / 2)));
                float a = d_f_c / (game.get_paddle_width_2() / 2);
                if (a < 0)
                    a *= -1;
                if (a == 0)
                    a = 0.5;
                game.set_angle(a);
                ball_ud = false;
                if (game.get_ball_x() - game.get_2paddle_x() > ((game.get_paddle_width_2()) / 2))
                    ball_lr = true;
                else
                    ball_lr = false;
                game.set_paddle2_color(game.get_ball_color());
            }
            else if (game.get_ball_y() >= height - 92 && (game.get_level() != 3))   // For Other Levels Upper Bar
                ball_ud = false;
        }
        else        //Ball Moving Downward
        {
            if (game.get_ball_y() <= 0)
            {
                game.set_lives(game.get_lives() - 1);
                if (game.get_lives() == -1)
                    DrawString(500, 500, "Game-Over\n", colors[BLACK]);
                ball_ud = true;
                ball_lr = true;
                game.set_angle(0.5);
                game.set_ball_x(600);
                game.set_ball_y(100);
                game.set_speed(10);
                game.set_power_up(0);
                usleep(40 * 10000);
                return;
            }
            else if ((game.get_ball_y() <= 20) && (game.get_ball_x() >= game.get_paddle_x() && game.get_ball_x() <= (game.get_paddle_x() + game.get_paddle_width())))
            {
                float d_f_c = (game.get_ball_x() - (game.get_paddle_x() + (game.get_paddle_width() / 2)));
                float a = d_f_c / (game.get_paddle_width() / 2);
                if (a < 0)
                    a *= -1;
                if (a == 0)
                    a = 0.5;
                game.set_angle(a);
                ball_ud = true;
                if (game.get_ball_x() - game.get_paddle_x() > ((game.get_paddle_width()) / 2))
                    ball_lr = true;
                else
                    ball_lr = false;
                game.set_paddle_color(game.get_ball_color());
            }
        }
        //For left and Right 
        if (ball_lr == true)
        {
            if (game.get_ball_x() > width - 25)
                ball_lr = false;
        }
        else
        {
            if (game.get_ball_x() - speed < 25)
                ball_lr = true;
        }
        
        //Updating Ball Co-ordinates
        if (ball_lr)
            game.set_ball_x(game.get_ball_x() + speed * (game.get_angle()));
        else
            game.set_ball_x(game.get_ball_x() - speed * (game.get_angle()));

        if (ball_ud)
            game.set_ball_y(game.get_ball_y() + speed * (1 - game.get_angle()));
        else
            game.set_ball_y(game.get_ball_y() - speed * (1 - game.get_angle()));
        
        //Brick b pointer pointing to the dynamic array of Bricks created in the Level 
        Bricks *b = game.get_all_bricks();
        for (int i = 0; i < game.get_bricks(); i++)
        {
            int x = (b[i]).location[0];
            int y = (b[i]).location[1];
            int x1 = (b[i]).size[0];
            int y1 = (b[i]).size[1];
            if ((game.get_ball_x() >= x && game.get_ball_x() <= x + x1) && (game.get_ball_y() >= y && game.get_ball_y() <= y + y1))
            {
                game.set_ball_color((b[i]).color);
                b[i].score_count -= 1;
                // Check if the ball hits the top or bottom side of the brick
                if (game.get_ball_y() >= y && game.get_ball_y() <= y + y1 && ((game.get_ball_x() >= x && game.get_ball_x() <= x + speed) || (game.get_ball_x() <= x + x1 && game.get_ball_x() >= x + x1 - speed)))
                {
                    ball_lr = !ball_lr; // Reverse the horizontal direction
                }
                // Check if the ball hits the left or right side of the brick
                if (game.get_ball_x() >= x && game.get_ball_x() <= x + x1 && ((game.get_ball_y() >= y && game.get_ball_y() <= y + speed) || (game.get_ball_y() <= y + y1 && game.get_ball_y() >= y + y1 - speed)))
                {
                    ball_ud = !ball_ud; // Reverse the vertical direction
                }
                if (b[i].score_count == 0)
                {
                //Updating the Array and Score Respectively
                    if (game.get_power_up() == false && rand()%3 == 1)
                    {
                    //Generating PowerUps 33% chance
                        (*(game.get_power_food())).set_cord(game.get_ball_x(), game.get_ball_y(), b[i].color);
                        game.set_power_up(1);
                    }
                    int tscore = 0;
                    if ((b[i]).color == 0 || (b[i]).color == 4)
                        tscore = 5;
                    else if ((b[i]).color == 2)
                        tscore = 15;
                    else
                        tscore = 10;
                    game.set_score(tscore);
                    Bricks *temp = new Bricks[game.get_bricks() - 1];
                    int tempIndex = 0;
                    for (int j = 0; j < game.get_bricks(); j++)
                    {
                        if (j != i)
                        {
                            temp[tempIndex] = b[j]; // Copy bricks to temp
                            tempIndex++;
                        }
                    }
                    delete[] game.get_all_bricks();         // Delete old array
                    game.set_all_bricks(temp);              // Assign new array
                    game.set_bricks(game.get_bricks() - 1); // Update bricks count
                }
                break;
            }
        }
    }
};

class Walls : public Game
{
public:
    Walls(int s)
    {
        int width = Game::width;
        int height = Game::height + 20;
        if (s != 3)
        {
            DrawRectangle(-1, height - 105, width + 5, 20, colors[RED]); // top
            DrawRectangle(width - 25, 0, 60, height - 95, colors[RED]);  // Right
            DrawRectangle(0, 0, 25, height - 95, colors[RED]);           // Lefts
        }
        else
        {
            DrawRectangle(width - 25, 0, 60, height - 60, colors[RED]); // Right
            DrawRectangle(0, 0, 25, height - 60, colors[RED]);          // Left
        }
    }
};

class menu : public Game
{
protected:
    int choice = 2;
    int height = 1300, width = 700;
    int state = 1;

public:
    menu()
    {
    }
    void display()
    {
    //different states of Menu and At a time only one is visible controling from the main file in keys section
        if (state == 1)
        {
            DrawRectangle(580, (choice * 50) + 420, 150, 50, colors[GREEN]);
            DrawString(600, 530, "Play Game", colors[WHITE]);
            DrawString(600, 480, "High Score", colors[WHITE]);
            DrawString(600, 430, "Exit", colors[WHITE]);
        }
        else if (state == 2)
        {
            DrawRectangle(580, (choice * 50) + 420, 150, 50, colors[GREEN]);
            DrawString(600, 530, "Level 1", colors[WHITE]);
            DrawString(600, 480, "Level 2", colors[WHITE]);
            DrawString(600, 430, "Level 3", colors[WHITE]);
        }
        else if (state == 3)
        {
            fstream file;
            file.open("HighScores.txt");
            string line;
            int height = 0;
            int hs;
            DrawString(500, 650, "---High Scores---", colors[WHITE]);
            while (getline(file, line))
            {
                if (height == 0)
                {
                    if (line == "")
                        hs = 0;
                    else
                        hs = stoi(line);
                }
                DrawString(600, 530 - height, line, colors[WHITE]);
                height += 40;
            }
            if (height == 0)
                DrawString(600, 530 + height, "No High-Score Yet!", colors[WHITE]);
            set_hscore(hs);
            file.close();
        }
        else if (state == 4)
        {
            DrawRectangle(580, (choice * 50) + 420, 150, 50, colors[GREEN]);
            DrawString(600, 530, "Resume", colors[WHITE]);
            DrawString(600, 480, "Main Menu", colors[WHITE]);
            DrawString(600, 430, "Exit", colors[WHITE]);
        }
    }
    int get_choice()
    {
        return choice;
    }
    int get_state()
    {
        return state;
    }
    void set_state(int s)
    {
        state = s;
    }
    void set_choice(int s)
    {
        choice = s;
    }
    ~menu()
    {
    }
};

class gauge
{
public:
    void display(int lives, int score, int hscore)
    {
        if (lives < 0)
            lives = 0;
        DrawString(50, 730, "Ali Rauf", colors[BLACK]);
        DrawString(250, 730, "Score: " + Num2Str(score), colors[BLACK]);
        DrawString(450, 730, "Lives: " + Num2Str(lives), colors[BLACK]);
        DrawString(600, 730, "Highest Score: " + Num2Str(hscore), colors[BLACK]);
        DrawString(950, 730, "Roll No: 23I-0076", colors[BLACK]);
    }
};

class level_1 : public Game
{
private:
    //          General Variables
    Food x;
    int property = -1;
    bool power_up = false;
    int level = 1;
    int lives = 2;
    gauge g;
    //          Bricks of Level 1

    int brick = 5 * 15;
    Bricks *b = new Bricks[brick];

    //          Variables for Paddle

    int paddle_x = 255, paddle_width = 150, paddle_color = 0;

    //          Variables for Ball
    bool balls_active = 0;
    float angle = 0.5;
    int no_of_balls = 1;
    int color = 0;
    float ball_x = 600, ball_y = 100;
    int speed = 10;

public:
    level_1()
    {
        //Intializing Bricks of Level 1(Not Printing them)
        int p = 0;
        for (int i = 1; i < 6; i++)
        {
            for (int j = 1; j < 30; j += 2)
            {
                b[p].make_brick(j * (Game::width / 33) + 25, Game::height - 95 - ((i + 1) * 19), 0, rand() % 5);
                p++;
            }
        }
        file_read();
    }
    
    //For reading High score to display on screen
    void file_read()
    {
        fstream file;
        file.open("HighScores.txt");
        string line;
        int counter = 0;
        int hs = 0; // Initialize highest score variable
        int current_score;

        while (getline(file, line))
        {
            current_score = stoi(line);
            if (counter == 0 || current_score > hs)
            {
                hs = current_score; // Update highest score if current score is higher
            }
            counter++;
        }
        set_hscore(hs);
        file.close();
    }
    void print_bricks()
    {
        for (int i = 0; i < brick; i++)
            b[i].print_brick();
    }
    void simulate_game()
    {
    //getting called time from time
        glClearColor(0, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        Walls w(1);
        g.display(lives, Game::score, Game::h_score);
        if (power_up == true)
            x.fall(*this);
        if (balls_active)
        {
            Ball temp1(ball_x, ball_y, color); // more balls
            Ball temp2(ball_x, ball_y, color);
            temp1.movement(speed, *this);
            temp2.movement(speed, *this);
        }
        print_bricks();
        Player p(paddle_x, paddle_width, paddle_color);
        Ball b(ball_x, ball_y, color);
        b.movement(speed, *this);
    }
    // Functions for Paddle
    void set_paddle_x(int s)
    {
        paddle_x = s;
    }
    void set_paddle_width(int s)
    {
        paddle_width = s;
    }
    int get_paddle_x()
    {
        return paddle_x;
    }
    int get_paddle_width()
    {
        return paddle_width;
    }

    // Functions for Ball
    void set_balls_active(bool a)
    {
        balls_active = a;
    }
    void set_ball_x(float s)
    {
        ball_x = s;
    }
    void set_ball_y(float s)
    {
        ball_y = s;
    }
    void set_ball_color(int s)
    {
        color = s;
    }
    int get_ball_color()
    {
        return color;
    }
    float get_ball_x()
    {
        return ball_x;
    }
    float get_ball_y()
    {
        return ball_y;
    }
    int get_speed()
    {
        return speed;
    }
    void set_speed(int s)
    {
        speed = s;
    }
    float get_angle()
    {
        return angle;
    }
    void set_angle(float a)
    {
        angle = a;
    }
    // Functions For bricks
    int get_bricks()
    {
        return brick;
    }
    void set_bricks(int s)
    {
        brick = s;
    }
    Bricks *get_all_bricks()
    {
        return b;
    }
    void set_all_bricks(Bricks *p)
    {
        b = p;
    }

    // General Function
    void set_score(int s)
    {
        Game::score += s;
    }
    int get_lives()
    {
        return lives;
    }
    void set_lives(int s)
    {
        lives = s;
    }
    int get_level()
    {
        return level;
    }
    void set_hscore(int s)
    {
        Game::h_score = s;
    }
    int get_score()
    {
        return Game::score;
    }
    void set_power_up(bool b)
    {
        power_up = b;
    }
    bool get_power_up()
    {
        return power_up;
    }
    Food *get_power_food()
    {
        return &x;
    }
    void set_paddle_color(int s)
    {
        paddle_color = s;
    }
    int get_property()
    {
        return property;
    }
    void set_property(int s)
    {
        property = s;
    }
    void effect(Game &game)
    {
        x.Food::effect(*this);
    }
    ~level_1()
    {
        if (brick != 0)
            delete[] b;
    }
};
class level_2 : public Game
{
private:
    //          General Variables
    Food x;
    int property = -1;
    bool power_up = false;
    int level = 2;
    int lives = 2;
    gauge g;

    //          Bricks of Level 1

    int brick = 5 * 25;
    Bricks *b = new Bricks[brick];

    //          Variables for Paddle

    int paddle_x = 255, paddle_width = 150, color = 0;

    //          Variables for Ball
    float angle = 0.5;
    int no_of_balls = 1;
    int paddle_color = 0;
    float ball_x = 600, ball_y = 100;
    int speed = 10;

public:
    level_2()
    {
        int p = 0;
        for (int i = 1; i < 6; i++)
        {
            for (int j = 1; j < 26; j++)
            {
                if (i < 4)
                    b[p].make_brick(((((j - 1) % 5)) * 76) + (25 + (((i - 1) * 5 * 77))), (Game::height - 95 - 40) - (((j - 1) / 5) * 20) - ((i - 1) * 5 * 20), 0, rand() % 5);
                else
                    b[p].make_brick(((((j - 1) % 5)) * 76) + (25 + (((5 - i) * 5 * 77))), (Game::height - 95 - 40) - (((j - 1) / 5) * 20) - ((i - 1) * 5 * 20), 0, rand() % 5);
                p++;
            }
        }
        file_read();
    }
    void file_read()
    {
        fstream file;
        file.open("HighScores.txt");
        string line;
        int counter = 0;
        int hs = 0; // Initialize highest score variable
        int current_score;

        while (getline(file, line))
        {
            current_score = stoi(line);
            if (counter == 0 || current_score > hs)
            {
                hs = current_score; // Update highest score if current score is higher
            }
            counter++;
        }
        set_hscore(hs);
        file.close();
    }
    void print_bricks()
    {
        for (int i = 0; i < brick; i++)
            b[i].print_brick();
    }
    void simulate_game()
    {
        glClearColor(0.7, 0.821, 0.9, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        Walls w(2);
        g.display(lives, Game::score, Game::h_score);
        if (power_up == true)
            x.fall(*this);
        print_bricks();
        Player p(paddle_x, paddle_width, paddle_color);
        Ball b(ball_x, ball_y, color);
        b.movement(speed, *this);
    }
    // Functions for Paddle
    void set_paddle_x(int s)
    {
        paddle_x = s;
    }
    void set_paddle_width(int s)
    {
        paddle_width = s;
    }
    int get_paddle_x()
    {
        return paddle_x;
    }
    int get_paddle_width()
    {
        return paddle_width;
    }

    // Functions for Ball
    void set_ball_x(float s)
    {
        ball_x = s;
    }
    void set_ball_y(float s)
    {
        ball_y = s;
    }
    void set_ball_color(int s)
    {
        color = s;
    }
    int get_ball_color()
    {
        return color;
    }
    float get_ball_x()
    {
        return ball_x;
    }
    float get_ball_y()
    {
        return ball_y;
    }
    int get_speed()
    {
        return speed;
    }
    void set_speed(int s)
    {
        speed = s;
    }
    float get_angle()
    {
        return angle;
    }
    void set_angle(float a)
    {
        angle = a;
    }
    // Functions For bricks
    int get_bricks()
    {
        return brick;
    }
    void set_bricks(int s)
    {
        brick = s;
    }
    Bricks *get_all_bricks()
    {
        return b;
    }
    void set_all_bricks(Bricks *p)
    {
        b = p;
    }

    // General Function
    void set_score(int s)
    {
        Game::score += s;
    }
    int get_lives()
    {
        return lives;
    }
    void set_lives(int s)
    {
        lives = s;
    }
    int get_level()
    {
        return level;
    }
    void set_hscore(int s)
    {
        Game::h_score = s;
    }
    int get_score()
    {
        return Game::score;
    }
    void set_power_up(bool b)
    {
        power_up = b;
    }
    bool get_power_up()
    {
        return power_up;
    }
    Food *get_power_food()
    {
        return &x;
    }
    void set_paddle_color(int s)
    {
        paddle_color = s;
    }
    int get_property()
    {
        return property;
    }
    void set_property(int s)
    {
        property = s;
    }
    void effect(Game &game)
    {
        x.Food::effect(*this);
    }
    ~level_2()
    {
        if (brick != 0)
            delete[] b;
    }
};
class level_3 : public Game
{
private:
    //          General Variables
    Food x;
    int property = -1;
    bool power_up = false;
    int level = 3;
    int lives = 2;
    gauge g;
    int count = 0;
    //          Bricks of Level 1

    int brick = 56;
    Bricks *b = new Bricks[brick];

    //          Variables for Paddle

    int paddle_x = 255, paddle_width = 150, color = 0;

    //          Variables for 2nd Paddle

    int paddle_x_2 = 255, paddle_width_2 = 150;
    //          Variables for Ball
    float angle = 0.5;
    int no_of_balls = 1;
    int paddle_color = 0;
    int paddle2_color = 0;
    float ball_x = 650, ball_y = 100;
    int speed = 10;

public:
    level_3()
    {
        helper(1, 9, 9);
        file_read();
    }
    void file_read()
    {
        fstream file;
        file.open("HighScores.txt");
        string line;
        int counter = 0;
        int hs = 0; // Initialize highest score variable
        int current_score;

        while (getline(file, line))
        {
            current_score = stoi(line);
            if (counter == 0 || current_score > hs)
            {
                hs = current_score; // Update highest score if current score is higher
            }
            counter++;
        }
        set_hscore(hs);
        file.close();
    }
    void helper(int col, int rows, int number)
    {
        if (rows == 1 && col == number + 1)
            return;
        else if (col == number + 1)
        {
            helper(1, rows - 1, number);
        }
        else
        {
            if (rows == 1 || rows == number) /// Boundries
            {
                b[count].make_brick(((col * 80) + (Game::width / 31)) + (width / 8), Game::height - (height / 3) - ((rows + 1) * 19), 0, rand() % 5);
                count++;
            }
            else if (rows <= (number / 2) + 1 && ((col > (number / 2 - (rows - 2))) && (col <= (number - (number / 2 - (rows - 2)))))) // Upper half spaces
                /*pass*/;
            else if (rows > (number / 2) + 1 && ((col > (number / 2 - (number - rows - 1))) && (col <= (number - (number / 2 - (number - rows - 1)))))) // Lower half spaces
                /*pass*/;
            else
            {
                b[count].make_brick(((col * 80) + (Game::width / 31)) + (width / 8), Game::height - (height / 3) - ((rows + 1) * 19), 0, rand() % 5);
                count++;
            }
            helper(col + 1, rows, number);
        }
    }
    void print_bricks()
    {
        for (int i = 0; i < brick; i++)
            b[i].print_brick();
    }
    void simulate_game()
    {
        glClearColor(0.5, 0.1, 0.8, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        Walls w(3);
        g.display(lives, Game::score, Game::h_score);
        if (power_up == true)
            x.fall(*this);
        print_bricks();
        Player p(paddle_x, paddle_width, paddle_color);
        Player p2(paddle_x_2, paddle_width_2, paddle2_color, height - 60);
        Ball b(ball_x, ball_y, color);
        b.movement(speed, *this);
    }
    // Functions for Paddle
    void set_paddle_x(int s)
    {
        paddle_x = s;
    }
    void set_paddle_width(int s)
    {
        paddle_width = s;
    }
    int get_paddle_x()
    {
        return paddle_x;
    }
    int get_paddle_width()
    {
        return paddle_width;
    }

    // Functions for Ball
    void set_ball_x(float s)
    {
        ball_x = s;
    }
    void set_ball_y(float s)
    {
        ball_y = s;
    }
    void set_ball_color(int s)
    {
        color = s;
    }
    int get_ball_color()
    {
        return color;
    }
    float get_ball_x()
    {
        return ball_x;
    }
    float get_ball_y()
    {
        return ball_y;
    }
    int get_speed()
    {
        return speed;
    }
    void set_speed(int s)
    {
        speed = s;
    }
    float get_angle()
    {
        return angle;
    }
    void set_angle(float a)
    {
        angle = a;
    }
    // Functions For bricks
    int get_bricks()
    {
        return brick;
    }
    void set_bricks(int s)
    {
        brick = s;
    }
    Bricks *get_all_bricks()
    {
        return b;
    }
    void set_all_bricks(Bricks *p)
    {
        b = p;
    }

    // General Function
    void set_score(int s)
    {
        Game::score += s;
    }
    int get_lives()
    {
        return lives;
    }
    void set_lives(int s)
    {
        lives = s;
    }
    int get_level()
    {
        return level;
    }
    void set_hscore(int s)
    {
        Game::h_score = s;
    }
    int get_score()
    {
        return Game::score;
    }
    int get_2paddle_x()
    {
        return paddle_x_2;
    }
    void set_2paddle_x(int s)
    {
        paddle_x_2 = s;
    }
    int get_paddle_width_2()
    {
        return paddle_width_2;
    }
    void set_paddle_width_2(int s)
    {
        paddle_width_2 = s;
    }
    void set_power_up(bool b)
    {
        power_up = b;
    }
    bool get_power_up()
    {
        return power_up;
    }
    Food *get_power_food()
    {
        return &x;
    }
    void set_paddle_color(int s)
    {
        paddle_color = s;
    }
    void set_paddle2_color(int s)
    {
        paddle2_color = s;
    }
    int get_property()
    {
        return property;
    }
    void set_property(int s)
    {
        property = s;
    }
    void effect(Game &game)
    {
        x.Food::effect(*this);
    }
    ~level_3()
    {
        if (brick != 0)
            delete[] b;
    }
};
