#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TetrisBlock.h"

using namespace sf;
using namespace std;

class Block_I :public TetrisBlock
{
public:
	Block_I(float _cell_size, Color _color, RenderWindow* _window, vector<TetrisBlock*> blocks_tab);

	
	void createShape() override;
   	void rotate() override;


	RenderWindow* getWindow() override;
    vector<TetrisBlock*> getTabBloks() override;
	vector<Cell>& getTabCells() override;
	float getCellSize() override;
	void setBlockUnderControl(bool _bool) override;
	Color getColor() override;
	Vector2f& GetBlockPosition() override;
	void setBlockPosition(Vector2f position) override;

private:
	RectangleShape shape;
	RenderWindow* window;
	
	vector<TetrisBlock*> blocks_tab;
	vector<Cell> mini_cells_tab;

	Vector2f blockPosition;

	string type;
	float cell_size;
	Color color;

	bool rotate_checker;
	int rotate_number;

	bool block_under_control;
};

