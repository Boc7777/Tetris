#include "Block_T.h"
#include "iostream"
#include <vector>


Block_T::Block_T(float _cell_size, Color _color, RenderWindow* _window, vector<TetrisBlock*> _blocks_tab) {
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

void Block_T::createShape() {
	mini_cells_tab[0].setPosition(Vector2f(cell_size * 4, cell_size * -2));
	mini_cells_tab[1].setPosition(Vector2f(cell_size * 5, cell_size * -2));
	mini_cells_tab[2].setPosition(Vector2f(cell_size * 6, cell_size * -2));
	mini_cells_tab[3].setPosition(Vector2f(cell_size * 5, cell_size * -1));

	setBlockPosition(mini_cells_tab[0].getPosition());
}

void Block_T::rotate() {
	if (block_under_control) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !rotate_checker) {
			rotate_checker = true;
			rotate_number += 1;
			if (rotate_number > 4) {
				rotate_number = 1;
			}


			//cypek w dó³ 
			if (rotate_number == 1) {
				float main_x = GetBlockPosition().x;
				float main_y = GetBlockPosition().y;
				bool possible_rotate = true;
				
				vector<Vector2f> cells_to_check;

				cells_to_check.push_back( Vector2f(main_x , main_y) );
				cells_to_check.push_back(Vector2f(main_x + cell_size , main_y ));
				cells_to_check.push_back(Vector2f(main_x + 2*cell_size, main_y ));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y + cell_size));

				for (auto& blockCheck : cells_to_check) {
					if (!borderChecker(blockCheck)) {
						possible_rotate = false;
					}
				}
				

				//sprawdzanie czy rotate wchodzi w inne komorki
				if (possible_rotate) {
					possible_rotate = colisionChecker(cells_to_check, blocks_tab);
				}
				

				if (possible_rotate) {
					for (int i = 0; i < 4;i++) {
						getTabCells()[i].setPosition(cells_to_check[i]);
					}
				}
				else {
					rotate_number -= 1;
				}


			}

			//cypek w lewo
			else if (rotate_number == 2) {

				float main_x = GetBlockPosition().x;
				float main_y = GetBlockPosition().y;
				bool possible_rotate = true;

				vector<Vector2f> cells_to_check;

				cells_to_check.push_back(Vector2f(main_x+cell_size, main_y));
				cells_to_check.push_back(Vector2f(main_x, main_y+cell_size));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y+cell_size));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y + 2 * cell_size));

				for (auto& blockCheck : cells_to_check) {
					if (!borderChecker(blockCheck)) {
						possible_rotate = false;
					}
				}


				//sprawdzanie czy rotate wchodzi w inne komorki
				if (possible_rotate) {
					possible_rotate = colisionChecker(cells_to_check, blocks_tab);
				}


				if (possible_rotate) {
					for (int i = 0; i < 4;i++) {
						getTabCells()[i].setPosition(cells_to_check[i]);
					}
				}
				else {
					rotate_number -= 1;
				}

			}

			//cypek w góre
			else if (rotate_number == 3) {
				float main_x = GetBlockPosition().x;
				float main_y = GetBlockPosition().y;
				bool possible_rotate = true;

				vector<Vector2f> cells_to_check;

				cells_to_check.push_back(Vector2f(main_x, main_y+ cell_size));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y + cell_size));
				cells_to_check.push_back(Vector2f(main_x + 2*cell_size, main_y + cell_size));

				for (auto& blockCheck : cells_to_check) {
					if (!borderChecker(blockCheck)) {
						possible_rotate = false;
					}
				}


				//sprawdzanie czy rotate wchodzi w inne komorki
				if (possible_rotate) {
					possible_rotate = colisionChecker(cells_to_check, blocks_tab);
				}


				if (possible_rotate) {
					for (int i = 0; i < 4;i++) {
						getTabCells()[i].setPosition(cells_to_check[i]);
					}
				}
				else {
					rotate_number -= 1;
				}
			}

			//cypek w prawo
			else if (rotate_number == 4) {
				float main_x = GetBlockPosition().x;
				float main_y = GetBlockPosition().y;
				bool possible_rotate = true;

				vector<Vector2f> cells_to_check;

				cells_to_check.push_back(Vector2f(main_x, main_y));
				cells_to_check.push_back(Vector2f(main_x, main_y+cell_size));
				cells_to_check.push_back(Vector2f(main_x + cell_size, main_y + cell_size));
				cells_to_check.push_back(Vector2f(main_x , main_y + 2*cell_size));

				for (auto& blockCheck : cells_to_check) {
					if (!borderChecker(blockCheck)) {
						possible_rotate = false;
					}
				}


				//sprawdzanie czy rotate wchodzi w inne komorki
				if (possible_rotate) {
					possible_rotate = colisionChecker(cells_to_check, blocks_tab);
				}


				if (possible_rotate) {
					for (int i = 0; i < 4;i++) {
						getTabCells()[i].setPosition(cells_to_check[i]);
					}
				}
				else {
					rotate_number -= 1;
				}
			}
		}

		//mechanizm isKeyDown 
		if (!Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			rotate_checker = false;
		}
	}
}
 


// ---------------- getery i setery ----------------

RenderWindow* Block_T::getWindow() {
	return window;
}

vector<TetrisBlock*> Block_T::getTabBloks() {
	return blocks_tab;
}

vector<Cell>& Block_T::getTabCells() {
	return mini_cells_tab;
}

float Block_T::getCellSize() {
	return cell_size;
}

void Block_T::setBlockUnderControl(bool _bool) {
	block_under_control = _bool;
}

Color Block_T::getColor() {
	return color;
}

Vector2f& Block_T::GetBlockPosition() {
	return blockPosition;
}

void Block_T::setBlockPosition(Vector2f position) {
	blockPosition = position;
}
