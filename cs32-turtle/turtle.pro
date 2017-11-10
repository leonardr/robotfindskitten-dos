Leonard Richardson
[student ID redacted]
CS31A 2A
Project #4.23 2/24/97
Borland Turbo C++

Description
-----------
This is a simple drawing program based on the programming language LOGO. It
allows the user to control a simulated "mechanical turtle" who walks around
an array, drawing shapes as he does.  When given the proper instructions, the
turtle can make many interesting shapes.

Lessons Learned
---------------
 The array was a real pain to do. If I had written the program spec I would
have put (0,0) at the top left of the screen. However, if you wanted to make
a program that could plot graphs, this array structure would be better. I
crashed my computer a lot trying to get the crop function to work because I
kept messing up the calculations of how big a value could be without
overstepping the array bounds.
 I thought of an interesting thing to do with this program. Suppose the array
size was 18x18 with 324 elements. Each array contains a 1 or a 0, and can
therefore be thought of as a bit. Now, suppose that after executing commands
the program looks through the array, converts every 3 bits into an octal
number, and stores the results in a new array with 108 elements. There are
6 turtle commands besides stop, so this new array can be thought of as
containing 108 new instructions to the turtle! (We can add new commands to
bring the total up to 8, or ignore numbers 7 and 8 unless they follow a 5, in
which case they have meaning) The floor array can be cleared, the turtle
reset, and these new commands issued to it. After they have all been executed,
the program can read the array and begin the process again. The data is also
used as a program! Pretty neat, huh? If it gets put into a loop that displays
the floor after every iteration, it can be kind of like Conway's Life
simulation, only more complex. I think I might try something like this over
spring break.


Pseudocode
----------
Function main()
===============
Initialize floor aray using nested loops
Initialize other variables
Print instructions (using a function call)
Print out the intial settings
Do the following
        Input the next command
        Interpret the command just entered with a switch statement
                1: Change variable pen_status to PEN_UP
                2: "                           " PEN_DOWN
                3: Change variable direction to indicate turning right
                4: "                                           " left
                5: Input the number of spaces to move the turtle
                   Call function move_forward with relevant program data
                6: Call function print_floor
                9: Do nothing (exiting will be handled by the do loop)
                Otherwise, print an error message
        Increment variable step_number
        Output the current settings
While the latest input is not 9 ("Quit")

Function print_floor(const int to_print[][YBOUND+1])
====================================================
Do the following 20 times (counter variable = x)
        Do the following 20 times (counter variable = y)
                Print "*" or " ", depending on contents of floor[x][y]

Function move_forward (int direction, int howmany, int draw, int& x, int& y, int to_move[][YBOUND+1])
=====================================================================================================
Reassign variable howmany to the return value of crop(howmany); this will
 prevent the turtle from moving past the array bounds
Interpret the direction using a switch statement
        Up: If draw mode is on
                All of tomove's subscripts between [x][y] and [x+howmany][y]
                 are set to 1.
            The x value is increased by howmany.
        Down: If draw mode is on
                All of tomove's subscripts between [x-howmany][y] and [x][y]
                 are set to 1.
            The x value is decreased by howmany.
        Left: If draw mode is on
                All of tomove's subscripts between [x][y-howmany] and [x][y]
                 are set to 1.
            The y value is decreased by howmany.
        Right: If draw mode is on
                All of tomove's subscripts between [x][y] and [x][y+howmany]
                 are set to 1.
            The y value is increased by howmany.

Function chop (int x, int y, int how_many_spaces, int direction)
================================================================
Interpret the direction using a switch statement
        Up: If the number of spaces to be moved is greater than the
             difference of 19 and the x
                Output a warning
                Return 19-x (this will take the turtle to the top of the screen)
            Otherwise
                Return the original number of spaces to be moved
        Down: If the number of spaces to be moved is greater than x
                Output a warning
                Return x (this will take the turtle to the bottom of the screen)
            Otherwise
                Return the original number of spaces to be moved
        Left: If the number of spaces to be moved is greater than y
                Output a warning
                Return y (this will take the turtle to the far left of the
                 screen)
            Otherwise
                Return the original number of spaces to be moved
        Right: If the number of spaces to be moved is greater than the
                difference of 19 and y
                Output a warning
                Return 19-x (this will take the turtle to the far right of the
                 screen)
            Otherwise
                Return the original number of spaces to be moved

Function print_instructions()
=============================
Prints program instructions using a huge cout statement.

Testing
-------
The following data tests all functions of the simulator.
5 1 3 5 3 2 4 4 3 4 5 5 3 5 2 1 5 3 2 3 5 20 6 4 5 4 4 1 5 10 2 5 5 4 5 8 4
5 6 4 5 11 5 11 6 9
Here is a sample run using this data:

Welcome to Mechanical Turtle Art. Unlike other turtle art programs you may have
seen, MTA allows you the user to control the turtle. The action takes place on
a 20x20 grid, on which you can move the turtle around. When the turtle's pen is
in the down position, every square it walks over will have an asterisk ("*")
drawn in it. With practice, you can draw elaborate shapes on the grid.

Summary of commands:
--------------------
1: Pen up
2: Pen down
3: Turn right
4: Turn left
5: Move forward. The next input is the number of steps. For example, "5 3" would   move the turtle three spaces forward
6: Print the current grid
9: Stop and exit

Step 0:   Position:  Row:  0  Column:  0;   Direction:     Up;   Pen:  Up
Enter your program: 5 1 3 5 3 2 4 4 3 4 5 5 3 5 2 1 5 3 2 3 5 20 6 4 5 4 4 1 5 10
2 5 5 4 5 8 4 5 6 4 5 11 5 11 6 9
Step 1:   Position:  Row:  1  Column:  0;   Direction:     Up;   Pen:  Up
Step 2:   Position:  Row:  1  Column:  0;   Direction:  Right;   Pen:  Up
Step 3:   Position:  Row:  1  Column:  3;   Direction:  Right;   Pen:  Up
Step 4:   Position:  Row:  1  Column:  3;   Direction:  Right;   Pen:  Down
Step 5:   Position:  Row:  1  Column:  3;   Direction:     Up;   Pen:  Down
Step 6:   Position:  Row:  1  Column:  3;   Direction:   Left;   Pen:  Down
Step 7:   Position:  Row:  1  Column:  3;   Direction:     Up;   Pen:  Down
Step 8:   Position:  Row:  1  Column:  3;   Direction:   Left;   Pen:  Down
Warning: Turtle would have moved off floor. Value cropped.
Step 9:   Position:  Row:  1  Column:  0;   Direction:   Left;   Pen:  Down
Step 10:   Position:  Row:  1  Column:  0;   Direction:     Up;   Pen:  Down
Step 11:   Position:  Row:  3  Column:  0;   Direction:     Up;   Pen:  Down
Step 12:   Position:  Row:  3  Column:  0;   Direction:     Up;   Pen:  Up
Step 13:   Position:  Row:  6  Column:  0;   Direction:     Up;   Pen:  Up
Step 14:   Position:  Row:  6  Column:  0;   Direction:     Up;   Pen:  Down
Step 15:   Position:  Row:  6  Column:  0;   Direction:  Right;   Pen:  Down
Warning: Turtle would have moved off floor. Value cropped.
Step 16:   Position:  Row:  6  Column: 19;   Direction:  Right;   Pen:  Down
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
* * * * * * * * * * * * * * * * * * * * 
                                        
                                        
*                                       
*                                       
* * * *                                 
                                        
Step 17:   Position:  Row:  6  Column: 19;   Direction:  Right;   Pen:  Down
Step 18:   Position:  Row:  6  Column: 19;   Direction:     Up;   Pen:  Down
Step 19:   Position:  Row: 10  Column: 19;   Direction:     Up;   Pen:  Down
Step 20:   Position:  Row: 10  Column: 19;   Direction:   Left;   Pen:  Down
Step 21:   Position:  Row: 10  Column: 19;   Direction:   Left;   Pen:  Up
Step 22:   Position:  Row: 10  Column:  9;   Direction:   Left;   Pen:  Up
Step 23:   Position:  Row: 10  Column:  9;   Direction:   Left;   Pen:  Down
Step 24:   Position:  Row: 10  Column:  4;   Direction:   Left;   Pen:  Down
Step 25:   Position:  Row: 10  Column:  4;   Direction:   Down;   Pen:  Down
Step 26:   Position:  Row:  2  Column:  4;   Direction:   Down;   Pen:  Down
Step 27:   Position:  Row:  2  Column:  4;   Direction:  Right;   Pen:  Down
Step 28:   Position:  Row:  2  Column: 10;   Direction:  Right;   Pen:  Down
Step 29:   Position:  Row:  2  Column: 10;   Direction:     Up;   Pen:  Down
Step 30:   Position:  Row: 13  Column: 10;   Direction:     Up;   Pen:  Down
Warning: Turtle would have moved off floor. Value cropped.
Step 31:   Position:  Row: 19  Column: 10;   Direction:     Up;   Pen:  Down
                    *                   
                    *                   
                    *                   
                    *                   
                    *                   
                    *                   
                    *                   
                    *                   
                    *                   
        * * * * * * *                 * 
        *           *                 * 
        *           *                 * 
        *           *                 * 
* * * * * * * * * * * * * * * * * * * * 
        *           *                   
        *           *                   
*       *           *                   
*       * * * * * * *                   
* * * *                                 
                                        
Step 32:   Position:  Row: 19  Column: 10;   Direction:     Up;   Pen:  Down
Step 33:   Position:  Row: 19  Column: 10;   Direction:     Up;   Pen:  Down

I wrote some other programs to make interesting shapes. The one I find most
interesting is this one (which I formatted to make it clearer what's going on):
2 5 3   3 5 3   3 5 3   3 5 3
3 5 5   3 5 5   3 5 5   3 5 5
3 5 7   3 5 7   3 5 7   3 5 7
3 5 11  3 5 11  3 5 11  3 5 11
3 5 13  3 5 13  3 5 13  3 5 13
3 5 15  3 5 15  3 5 15  3 5 15
3 5 17  3 5 17  3 5 17  3 5 17
3 5 19  3 5 19  3 5 19  3 5 19 6 9
That gives the following output:
* * * * * * * * * * * * * * * * * * * * 
*                                     * 
* * * * * * * * * * * * * * * * * *   * 
*                                 *   * 
* * * * * * * * * * * * * * * *   *   * 
*                             *   *   * 
* * * * * * * * * * * * * *   *   *   * 
*                         *   *   *   * 
* * * * * * * * * * * *   *   *   *   * 
*                     *   *   *   *   * 
* * * * * * * * * *   *   *   *   *   * 
*                 *   *   *   *   *   * 
* * * * * * * *   *   *   *   *   *   * 
*             *   *   *   *   *   *   * 
* * * * * *   *   *   *   *   *   *   * 
*         *   *   *   *   *   *   *   * 
* * * *   *   *   *   *   *   *   *   * 
*     *   *   *   *   *   *   *   *   * 
*     *   *   *   *   *   *   *   *   * 
* * * * * * * * * * * * * * * * * * * * 

Another interesting one is this:
3 5 3  2  4 5 5  3 5 2  3 5 2  3 5 4  3 5 5  3 5 10  3 5 5  3 5 4  3 5 2
3 5 2  3 5 5  3 5 6  6 9
Which gives the following final output:
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
  * * * * * * * * * * *                 
  *                   *                 
  *                   *                 
  *   * * *   * * *   *                 
  *   *   *   *   *   *                 
  * * * * *   * * * * *                 
      *           *                     
      *           *                     
      * * * * * * *                     


And the following commands:
5 6 3 5 5 2 4 5 4 3 3 5 2 4 5 3 4 5 2 3 3 5 4 1 4 5 3 2 5 4 3 3 5 2 3 5 4 4 5
2 4 4 5 4 1 5 4 2 3 5 2 1 5 2 2 5 0 6 9
Give this final output:

                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
          *     *     * * * * *       * 
          *     *         *           * 
          * * * *         *           *
          *     *         *
          *     *     * * * * *       * 
                                        
                                        
                                        
                                        
                                        
                                        

