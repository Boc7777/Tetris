#include "Block_I.h"
#include "iostream"


Block_I::Block_I(float _cell_size, Color _color, RenderWindow* _window, vector<TetrisBlock*> _blocks_tab) {
	blocks_tab = _blocks_tab;
	window = _window;
	cell_size = _cell_size;
	color = _color;
	spawnCells();
	createShape();
	
	rotate_checker = false;
	rotate_number = 1;
	block_under_control = true;

}

// ---------------- indywidualne metody ----------------

void Block_I::createShape() {
	mini_cells_tab[0].setPosition(Vector2f(cell_size * 5, cell_size * -4));
	mini_cells_tab[1].setPosition(Vector2f(cell_size * 5, cell_size * -3));
	mini_cells_tab[2].setPosition(Vector2f(cell_size * 5, cell_size * -2));
	mini_cells_tab[3].setPosition(Vector2f(cell_size * 5, cell_size * -1));

	setBlockPosition(mini_cells_tab[0].getPosition());
}

void Block_I::rotate(){
	if (block_under_control) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !rotate_checker) {
			rotate_checker = true;
			rotate_number += 1;
			if (rotate_number > 2) {
				rotate_number = 1;
			}


			//stojacy 
			if (rotate_number == 1) {
				float main_x = mini_cells_tab[0].getPosition().x;
				float main_y = mini_cells_tab[0].getPosition().y;
				bool possible_rotate = true;


				for (int i = 1; i < 4;i++) {

					float actual_y = main_y - i * cell_size;
					float actual_x = main_x;

					//sprawdzanie czy rotate wchodzi w inne komorki
					for (TetrisBlock* block : blocks_tab) {
						for (auto& external_cell : block->getTabCells()) {

							if (actual_y == external_cell.getPosition().y && actual_x == external_cell.getPosition().x) {
								possible_rotate = false;
							}
						}
					}
				}

				if (possible_rotate) {
					for (int i = 1; i < 4;i++) {
						mini_cells_tab[i].setPosition(Vector2f(main_x, main_y - i * cell_size));
					}
				}
				else {
					rotate_number -= 1;
				}


			}

			//lezacy
			else if (rotate_number == 2) {

				float main_x = mini_cells_tab[0].getPosition().x;
				float main_y = mini_cells_tab[0].getPosition().y;
				bool possible_rotate = true;

				for (int i = 1; i < 4;i++) {
					float actual_y = main_y;
					float actual_x = main_x + i * cell_size;

					if (actual_x > cell_size * 9) {
						possible_rotate = false;
					}



					for (TetrisBlock* block : blocks_tab) {
						for (auto& external_cell : block->getTabCells()) {

							if (actual_y == external_cell.getPosition().y && actual_x == external_cell.getPosition().x) {
								possible_rotate = false;
							}
						}
					}
				}





				if (possible_rotate) {
					for (int i = 1; i < 4;i++) {
						mini_cells_tab[i].setPosition(Vector2f(main_x + i * cell_size, main_y));
					}
				}
				else {
					rotate_number -= 1;
				}

			}

		}
		if (!Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			rotate_checker = false;
		}
	}
}



// ---------------- getery i setery ----------------

RenderWindow* Block_I::getWindow() {
	return window;
}

vector<TetrisBlock*> Block_I::getTabBloks() {
	return blocks_tab;
}

vector<Cell>& Block_I::getTabCells() {
	return mini_cells_tab;
}

float Block_I::getCellSize() {
	return cell_size;
}

void Block_I::setBlockUnderControl(bool _bool) {
	block_under_control = _bool;
}

Color Block_I::getColor(){
	return color;
}

Vector2f& Block_I::GetBlockPosition() {
	return blockPosition;
}

void Block_I::setBlockPosition(Vector2f position) {
	blockPosition = position;
}
