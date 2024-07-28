#include "Block_O.h"
#include "iostream"


Block_O::Block_O(float _cell_size, Color _color, RenderWindow* _window, vector<TetrisBlock*> _blocks_tab) {
	blocks_tab = _blocks_tab;
	window = _window;
	cell_size = _cell_size;
	color = _color;
	spawnCells();
	createShape();


}

// ---------------- indywidualne metody ----------------

void Block_O::createShape() {
	mini_cells_tab[0].setPosition(Vector2f(cell_size * 4, cell_size * -2));
	mini_cells_tab[1].setPosition(Vector2f(cell_size * 5, cell_size * -2));
	mini_cells_tab[2].setPosition(Vector2f(cell_size * 4, cell_size * -1));
	mini_cells_tab[3].setPosition(Vector2f(cell_size * 5, cell_size * -1));

	setBlockPosition(mini_cells_tab[0].getPosition());
}

void Block_O::rotate() {

}

 

// ---------------- getery i setery ----------------

RenderWindow* Block_O::getWindow() {
	return window;
}

vector<TetrisBlock*> Block_O::getTabBloks() {
	return blocks_tab;
}

vector<Cell>& Block_O::getTabCells() {
	return mini_cells_tab;
}

float Block_O::getCellSize() {
	return cell_size;
}

void Block_O::setBlockUnderControl(bool _bool) {
	block_under_control = _bool;
}

Color Block_O::getColor() {
	return color;
}

Vector2f& Block_O::GetBlockPosition() {
	return blockPosition;
}

void Block_O::setBlockPosition(Vector2f position) {
	blockPosition = position;
}


