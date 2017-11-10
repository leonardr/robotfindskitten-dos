//This program simulates the movements of a mechanical turtle with a pen in
//its mouth in response to input from the keyboard. It can be used to draw
//nifty shapes.

#include <iomanip.h>
#include <iostream.h>
#include <stdlib.h>

//Constants
//---------

//These constants pertain to direction. They are arranged the way they are
//so that turning around is easy to do.
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;
char* direction_name[4] = {"Up","Right","Down","Left"};

//These constants pertain to the pen.
const int P_UP = 0;
const int P_DOWN = 1;

//These constants pertain to commands.
const int PEN_UP = 1;
const int PEN_DOWN = 2;
const int TURN_RIGHT = 3;
const int TURN_LEFT  = 4;
const int MOVE = 5;
const int PRINT = 6;
const int STOP = 9;

//These constants pertain to arrays. Be sure not to confuse XBOUND and YBOUND,
//which are 19, with the number of elements in each row or column, which is
//20.
const int XBOUND = 19;
const int YBOUND = 19;

//Function prototypes
int chop(int, int, int, int);
void move_forward(int, int, int, int&, int&, int[][XBOUND+1]);
void print_instructions();
void print_floor(const int[][YBOUND+1]);
void print_status();

void main()
{
	//Variable declaration
	//--------------------

	//Important stuff
	int pos_x = 0;
	int pos_y = 0;
	int current_command = 0;
	int direction = UP;
	int spaces = 0;
	int pen_status = P_UP;
	int step_number = 0;

	//Not-very-important stuff
	int counter1 = 0;
	int counter2 = 0;

	//And the oh-so-important floor array.
				int floor[XBOUND+1][YBOUND+1];

	//We now initialize floor.
        for (counter1 = 0; counter1 <= XBOUND; counter1++)
	{
                for (counter2 = 0; counter2 <= YBOUND; counter2++)
		{
			floor[counter1][counter2] = 0;
		}
	}

	print_instructions();

	//First, we print out the initial settings.
	cout << "Step " << step_number <<":   Position:  Row: " << setw(2) << pos_x
			 << "  Column: " << setw(2) << pos_y << ";   Direction:  " << setw(5)
			 << direction_name[direction-1] << ";   Pen:  " << (pen_status == P_UP ? "Up" : "Down") << "\n"
			 << "Enter your program:";
	do
	{
		cin >> current_command;

		switch (current_command)
		{
			case PEN_UP:
				pen_status = P_UP;
				break;

			case PEN_DOWN:
				pen_status = P_DOWN;
				break;

			case TURN_RIGHT:
				//The constants were set so that this would work. For your edification,
				//here's what happens:

				// Before       After
				// ----------------------
				// 1 (up)       2 (right)
				// 2 (right)    3 (down)
				// 3 (down)     4 (left)
				// 4 (left)     1 (up)
				direction = (direction % 4) + 1; //Look, an actual line of code!
				break;

				case TURN_LEFT:
				//This doesn't work nearly as well as turning right. I don't think
				// there's an equivalent mathematical expression that doesn't require
				//evaluating the 1 value seperately. Again, here's a chart.

				// Before       After
				// ----------------------
				// 1 (up)       4 (left)
				// 2 (right)    1 (up)
				// 3 (down)     2 (right)
				// 4 (left)     3 (down)

				direction = (direction == 1 ? 4 : (direction - 1));
				break;

			case MOVE:
				cin >> spaces;
				move_forward (direction, spaces, pen_status, pos_x, pos_y, floor);
				break;

			case PRINT:
				print_floor(floor);
				break;

			case STOP:
				break;

			default:
				cout << "Unknown command " << current_command << " entered; skipped.\n";
		}
	step_number++;
	cout << "Step " << step_number <<":   Position:  Row: " << setw(2) << pos_x
			 << "  Column: " << setw(2) << pos_y << ";   Direction:  " << setw(5)
			 << direction_name[direction-1] << ";   Pen:  " << (pen_status == P_UP ? "Up" : "Down") << "\n";

	} while (current_command != STOP);
}

void print_floor(const int to_print[][YBOUND+1])
{
        int x = YBOUND;
	int y = 0;
        for (x = YBOUND; x >= 0; x--)
	{
                for (y = 0; y <= YBOUND; y++)
		{
			cout << (to_print[x][y] == 1 ? "*" : " ") << " ";
		}
		cout << "\n";
	}
	return;
}

void move_forward(int direction, int howmany, int draw, int& x, int& y, int to_move[][YBOUND+1])
{
	int counter = 0;
	//First, we need to make sure that howmany is sufficiently small to allow
	//the move. The chop function ensures that we don't go off the edges of the
	//array.
	howmany = chop(x, y, howmany, direction);
	switch (direction)
	{
		case UP :
			//We only want to set the values if the pen is down.
			if (draw == P_DOWN)
			{
				for (counter = 0; counter <= howmany; counter++)
				{
					to_move[x+counter][y] = 1;
				}
			}

			//Regardless of whether we drew, we want to change the turtle's
			//x-coordinate.
			x += howmany;
			break;

		//Same sort of thing for the other three directions.
		case DOWN :
			if (draw == P_DOWN)
			{
				for (counter = 0; counter <= howmany; counter++)
				{
					to_move[x-counter][y] = 1;
				}
			}
			x -= howmany;
			break;

			case LEFT:
			if (draw == P_DOWN)
			{
				for (counter = 0; counter <= howmany; counter++)
				{
					to_move[x][y-counter] = 1;
				}
			}
			y -= howmany;
			break;

			case RIGHT:
			if (draw == P_DOWN)
			{
				for (counter = 0; counter <= howmany; counter++)
				{
					to_move[x][y+counter] = 1;
				}
			}
			y += howmany;
			break;
	default :
		cout << "Error: Invalid direction code passed to move_forward.\n";
	}
	return;
}

int chop(int x, int y, int how_many_spaces, int direction)
{
	//This function checks to see whether or not the turtle is in danger of
	//moving off the edge of the array, given how many spaces the user told it
	//to move. If such a danger exists, it changes the variable how_many_spaces
	//to move the turtle to the edge of the array. Otherwise, the return value
	//is the same as the passed value.
	char* warning = "Warning: Turtle would have moved off floor. Value cropped.\n";

	switch (direction)
	{
		case UP :
                        if (how_many_spaces > (XBOUND-x))
			{
				cout << warning;
                                return (XBOUND-x);
			}
			else
				return how_many_spaces;
		case DOWN :
			if (how_many_spaces > x)
			{
				cout << warning;
				return (x);
			}
			else
				return how_many_spaces;
		case LEFT :
			if (how_many_spaces > y)
			{
				cout << warning;
				return y;
			}
			else
				return how_many_spaces;
		case RIGHT :
                        if (how_many_spaces > (YBOUND-y))
			{
				cout << warning;
                                return (YBOUND-y);
			}
			else
				return how_many_spaces;
	}
}

void print_instructions()
{
	cout << "Welcome to Mechanical Turtle Art. Unlike other turtle art programs you may have\n"
			 << "seen, MTA allows you the user to control the turtle. The action takes place on\n"
                         << "a " << XBOUND+1 << "x" << YBOUND+1 << "grid, on which you can move the turtle around. When the turtle's pen is\n"
			 << "in the down position, every square it walks over will have an asterisk (\"*\")\n"
			 << "drawn in it. With practice, you can draw elaborate shapes on the grid.\n\n"
			 << "Summary of commands:\n"
			 << "--------------------\n"
			 << "1: Pen up\n"
			 << "2: Pen down\n"
			 << "3: Turn right\n"
			 << "4: Turn left\n"
			 << "5: Move forward. The next input is the number of steps. For example, \"5 3\" would"
			 << "   move the turtle three spaces forward\n"
			 << "6: Print the current grid\n"
			 << "9: Stop and exit\n\n";

}