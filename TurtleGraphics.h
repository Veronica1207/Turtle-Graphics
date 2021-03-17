// Assignment 6 Solution: TurtleGraphics.h
// Declaration of class TurtleGraphics.
// Member functions are defined in TurtleGraphics.cpp.
// Author: Bob Langelaan 
// Date: June 05, 2019

#pragma once
#include <array>

// Define some enum types that will be used in solution

enum class CMDS : unsigned short { PEN_UP = 1, PEN_DWN = 2, TURN_RIGHT = 3, TURN_LEFT = 4, MOVE = 5, DISPLAY = 6, END_OF_DATA = 9 };
enum class Directions : unsigned short { NORTH, EAST, SOUTH, WEST };

class TurtleGraphics
{
private:
	const static size_t NROWS = 22;  // number of rows in floor
	const static size_t NCOLS = 70;  // number of colums in floor

	const static int STARTING_ROW = 0;    // row that turtle will start in
	const static int STARTING_COL = 0;    // column that turtle will start in

	const static Directions STARTING_DIRECTION = Directions::SOUTH; // direction 
	                      // that turtle will be facing at the start

	const static bool STARTING_PEN_POSITION = false; // Pen will be up when 
	                            // program starts
                                // false means pen up, true means pen down

	void displayFloor() const;  // will display floor on the screen

	std::array <std::array <bool, NCOLS>, NROWS> m_Floor;   // floor on which turtle will draw

	bool currentPenPosition;
	Directions currentDirection;
	int currentRow;
	int currentColumn;

public:
	const static int ARRAY_SIZE = 250;

	TurtleGraphics(void); //ctor will init. floor to all "true" values, 
	                      //     as well as initialization of other data members
	void processTurtleMoves( const std::array< int, ARRAY_SIZE> &);  // will process
	                   // the commands contained in array "commands"	

	void moveIt(int numberOfMoves);		//move through the floor in different directions 
										//				and change array values, when pen is down

	void turnRight();	//turn right from the current direction 

	void turnLeft();	//turn left fromt he current direction

	bool getCurrentPenPosition() const;	//accessor for the current pen position

	Directions getCurrentDirection() const;		//accessor for the currentDirection

	int getCurrentRow() const;		//accessor for the current row

	int getCurrentColumn() const;	//accessor for the current column

	void setCurrentPenPosition(bool newPenPosition);	//modifier for the current pen position

	void setCurrentDirection(Directions newDirection);		//modifier for the current direction

	void setCurrentRow(int newRow);		//modifier for the current row

	void setCurrentColumn(int column);	//modifier for the current column

};


