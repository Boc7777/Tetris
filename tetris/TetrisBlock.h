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
	// ---------------- metody wbudowane ----------------	
	void spawnCells();
	void drawCells();
	void checkUnderControl();
	void moveDownCells();
	void movement_X();
	void checkUnderCells();
	void deleteCellFromTab(int index);

	bool borderChecker(Vector2f position);
	bool colisionChecker(vector<Vector2f> cells_to_check, vector<TetrisBlock*> blocks_tab);
	bool getBlocktoDelete();

	// ---------------- metody indywidualne  ----------------	
	virtual void createShape() = 0;
	virtual void rotate() = 0;


	// ---------------- getery i setery ----------------
	virtual RenderWindow* getWindow() = 0;
	virtual vector<TetrisBlock*> getTabBloks() = 0;
	virtual vector<Cell>& getTabCells() = 0;
	virtual float getCellSize() = 0;
	virtual void setBlockUnderControl(bool _bool) = 0;
	virtual Color getColor() = 0;

	virtual Vector2f& GetBlockPosition() = 0;
	virtual void setBlockPosition(Vector2f position) = 0;
	

};


