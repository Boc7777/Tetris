#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TetrisBlock.h"

using namespace sf;
using namespace std;

class Block_O :public TetrisBlock
{
public:
	Block_O(float _cell_size, Color _color, RenderWindow* _window, vector<TetrisBlock*> blocks_tab);

	void spawnCells() override;
	void createShape() override;
	void drawCells() override;

	void checkUnderCells() override;
	void checkUnderControl() override;
	vector<Cell> getTabCells() override;


	void moveDownCells() override;
	void movement_X() override;
	void rotate() override;

private:
	RectangleShape shape;
	RenderWindow* window;

	vector<TetrisBlock*> blocks_tab;
	vector<Cell> mini_cells_tab;

	string type;
	float cell_size;
	Color color;
};



