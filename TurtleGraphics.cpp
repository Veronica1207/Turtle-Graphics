// Assignment 6 Solution: TurtleGraphics.cpp
// Class TurtleGraphics.
// Author: Veronica Logvinenko, A01208105
// Date: 2021-02-27

#include <iostream>
#include "TurtleGraphics.h"

using namespace std;

//ctor will init. floor to all "true" values, 
//     as well as initialization of other data members
TurtleGraphics::TurtleGraphics()
	:currentPenPosition(TurtleGraphics::STARTING_PEN_POSITION), currentDirection(TurtleGraphics::STARTING_DIRECTION), currentRow(TurtleGraphics::STARTING_ROW), currentColumn(TurtleGraphics::STARTING_COL)
{
	for (auto &row : m_Floor)
	{
		for (auto &floorPosition : row)
		{
			floorPosition = { true };
		}
	}
}

//accessor for the current pen position
bool TurtleGraphics::getCurrentPenPosition() const
{
	return currentPenPosition;
}

//accessor for the currentDirection
Directions TurtleGraphics::getCurrentDirection() const
{
	return currentDirection;
}

//accessor for the current row
int TurtleGraphics::getCurrentRow() const
{
	return currentRow;
}

//accessor for the current column
int TurtleGraphics::getCurrentColumn() const
{
	return currentColumn;
}

//modifier for the current pen position
void TurtleGraphics::setCurrentPenPosition(bool newPenPosition)
{
	currentPenPosition = newPenPosition;
}

//modifier for the current direction
void TurtleGraphics::setCurrentDirection(Directions newDirection)
{
	currentDirection = newDirection;
}

//modifier for the current row
void TurtleGraphics::setCurrentRow(int newRow)
{
	if (newRow >= 0 && newRow < TurtleGraphics::NROWS)
	{
		currentRow = newRow;
	}
}

//modifier for the current column
void TurtleGraphics::setCurrentColumn(int newColumn)
{
	if (newColumn >= 0 && newColumn < TurtleGraphics::NCOLS)
	{
		currentColumn = newColumn;
	}
	
}


// will process
// the commands contained in array "commands"
void TurtleGraphics::processTurtleMoves(const array< int, TurtleGraphics::ARRAY_SIZE>& commands)
{
	bool exit = false;

	for (int i = 0; i < commands.size(); ++i)
	{
		if (exit != true) 
		{
			switch (static_cast <CMDS> (commands[i]))
			{
			case CMDS::PEN_UP:
				setCurrentPenPosition(false);
				break;

			case CMDS::PEN_DWN:
				setCurrentPenPosition(true);
				break;

			case CMDS::TURN_RIGHT:
				turnRight();
				break;

			case CMDS::TURN_LEFT:
				turnLeft();
				break;

			case CMDS::MOVE:
				moveIt(commands[i + 1]);
				i++;
				break;

			case CMDS::DISPLAY:
				displayFloor();
				break;

			case CMDS::END_OF_DATA:
				exit = true;
				break;

			default:
				cout << "\nSomething went wrong: switch statement in the processTurtleMoves(const int commands[]) function." << endl;
			}
		} 
	}

}

// will display floor on the screen
void TurtleGraphics::displayFloor() const
{
	for (auto const &row : m_Floor)
	{
		for (auto const &floorPosition : row)
		{
			if (floorPosition == true) {
				cout << " ";
			}
			else {
				cout << "*";
			}
		}
	}
}

//will move through the floor in different directions 
//and change m_Floor array values when pen is down
void TurtleGraphics::moveIt(int numberOfMoves)
{
	switch (getCurrentDirection()) {
	case Directions::NORTH:
		
		if (getCurrentRow() - numberOfMoves >= 0)		//if the number to move is within the floor
		{
			for (int i = getCurrentRow(); i > getCurrentRow() - numberOfMoves; --i)
			{
				if (getCurrentPenPosition() == true) // if pen is down
				{ 
					m_Floor[i][getCurrentColumn()] = { false };
				}
			}
			setCurrentRow(getCurrentRow() - numberOfMoves);
		}
		else 
		{
			for (int i = getCurrentRow(); i > 0; --i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[i][getCurrentColumn()] = { false };
				}
			}
			setCurrentRow(0);
		}

		break;

	case Directions::SOUTH:

		if (getCurrentRow() + numberOfMoves <= TurtleGraphics::NROWS)
		{
			for (int i = getCurrentRow(); i < getCurrentRow() + numberOfMoves; ++i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[i][getCurrentColumn()] = { false };
				}
			}
			setCurrentRow(getCurrentRow() + numberOfMoves);
		}
		else 
		{
			for (int i = getCurrentRow(); i < TurtleGraphics::NROWS - getCurrentRow(); ++i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[i][getCurrentColumn()] = { false };
				}
			}
			setCurrentRow(TurtleGraphics::NROWS-1);
		}
		
		break;

	case Directions::EAST:
		
		if (getCurrentColumn() + numberOfMoves <= TurtleGraphics::NCOLS)
		{
			for (int i = getCurrentColumn(); i < getCurrentColumn() + numberOfMoves; ++i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[getCurrentRow()][i] = { false };
				}
			}
			setCurrentColumn(getCurrentColumn() + numberOfMoves);
		}
		else
		{
			for (int i = getCurrentColumn(); i < TurtleGraphics::NCOLS - getCurrentColumn(); ++i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[getCurrentRow()][i] = { false };
				}
			}
			setCurrentColumn(TurtleGraphics::NCOLS-1);
		}
				
		break;

	case Directions::WEST:
		
		if (getCurrentColumn() - numberOfMoves >= 0)
		{
			for (int i = getCurrentColumn(); i > getCurrentColumn() - numberOfMoves; --i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[getCurrentRow()][i] = { false };
				}
			}
			setCurrentColumn(getCurrentColumn() - numberOfMoves);
		}
		else
		{
			for (int i = getCurrentColumn(); i > 0; --i)
			{
				if (getCurrentPenPosition() == true)
				{
					m_Floor[getCurrentRow()][i] = { false };
				}
			}
			setCurrentColumn(0);
		}

		break;

	default:
		cout << "Something went wrong: switch statement in the moveIt() function." << endl;
	}
}

//turn right from the current direction 
void TurtleGraphics::turnRight()
{
	switch (getCurrentDirection()) {
	case Directions::NORTH:
		setCurrentDirection(Directions::EAST);
		break;

	case Directions::EAST:
		setCurrentDirection(Directions::SOUTH);
		break;

	case Directions::SOUTH:
		setCurrentDirection(Directions::WEST);
		break;

	case Directions::WEST:
		setCurrentDirection(Directions::NORTH);
		break;

	default:
		cout << "Something went wrong: switch statement in the turnRight() function." << endl;
	}
}

//turn left fromt he current direction
void TurtleGraphics::turnLeft()
{
	switch (getCurrentDirection()) {
	case Directions::NORTH:
		setCurrentDirection(Directions::WEST);
		break;

	case Directions::EAST:
		setCurrentDirection(Directions::NORTH);
		break;

	case Directions::SOUTH:
		setCurrentDirection(Directions::EAST);
		break;

	case Directions::WEST:
		setCurrentDirection(Directions::SOUTH);
		break;

	default:
		cout << "Something went wrong: switch statement in the turnLeft() function." << endl;
	}
}

