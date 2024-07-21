#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Cell.h"

using namespace sf;
using namespace std;

class TetrisBlock 
{
public:
	

	virtual void spawnCells() = 0;
	virtual void createShape() = 0;


	virtual void checkUnderCells() = 0;
	virtual void moveDownCells() = 0;

	virtual void drawCells() = 0;

	virtual vector<Cell> getTabCells() = 0;
	virtual void checkUnderControl() = 0;


	virtual void movement_X() = 0;
	virtual void rotate() = 0; 
};


