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

}

void Block_I::spawnCells() {
	for (int i = 0; i < 4;i++) {
		mini_cells_tab.emplace_back(i * cell_size, 2 * cell_size, cell_size, Color::Yellow);
	}
}

void Block_I::createShape() {
	mini_cells_tab[0].setPosition(Vector2f(cell_size * 5, cell_size * -4));
	mini_cells_tab[1].setPosition(Vector2f(cell_size * 5, cell_size * -3));
	mini_cells_tab[2].setPosition(Vector2f(cell_size * 5, cell_size * -2));
	mini_cells_tab[3].setPosition(Vector2f(cell_size * 5, cell_size * -1));
}


void Block_I::checkUnderCells() {
	for (auto& internal_cell : mini_cells_tab) {
		if (internal_cell.getPosition().y == cell_size * 19) {
			internal_cell.set_underConrol(false);
			checkUnderControl();
		}

		for (TetrisBlock* block : blocks_tab) {
			for (auto& external_cell : block->getTabCells()) {
				
				if (!external_cell.get_underControl() && 
					external_cell.getPosition().y - internal_cell.getPosition().y == cell_size && 
					internal_cell.getPosition().x == external_cell.getPosition().x) 
				{
					internal_cell.set_underConrol(false);
					checkUnderControl();
				}

			}
		}


	}
}


void Block_I::checkUnderControl() {
	for (auto& cell : mini_cells_tab) {
		if (!cell.get_underControl()) {
			for (auto& cell : mini_cells_tab) {
				cell.set_underConrol(false);
			}
		}
	}
}

vector<Cell> Block_I::getTabCells() {
	return mini_cells_tab;
}



void Block_I::moveDownCells() {
	for (auto& cell : mini_cells_tab) {
		cell.moveDown();
	}
}

void Block_I::drawCells() {
	for (auto& cell : mini_cells_tab) {
		window->draw(cell);
	}
}



void Block_I::movement_X(){

	if (Keyboard::isKeyPressed(Keyboard::Key::Left)){
		bool possible_move = true;

		for (auto& cell : mini_cells_tab) {
			if (!cell.get_underControl()) {
				possible_move = false;
			}
		}

		if (possible_move) {
			for (auto& cell : mini_cells_tab) {
				if (cell.getPosition().x == 0) {
					possible_move = false;
				}
			}


			for (auto& cell : mini_cells_tab) {

				for (TetrisBlock* block : blocks_tab) {
					for (auto& external_cell : block->getTabCells()) {
						if (!external_cell.get_underControl() && cell.getPosition().x - external_cell.getPosition().x == cell_size && cell.getPosition().y == external_cell.getPosition().y) {
							possible_move = false;
						}
					}
				}
			}
		}

		if (possible_move) {
			for (auto& cell : mini_cells_tab) {
				cell.moveLeft();
			}
		}

	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		bool possible_move = true;

		for (auto& cell : mini_cells_tab) {
			if (!cell.get_underControl()) {
				possible_move = false;
			}
		}

		if (possible_move) {
			for (auto& cell : mini_cells_tab) {
				if (cell.getPosition().x == 9 * cell_size) {
					possible_move = false;
				}
			}


			for (auto& cell : mini_cells_tab) {

				for (TetrisBlock* block : blocks_tab) {
					for (auto& external_cell : block->getTabCells()) {
						if (!external_cell.get_underControl() && cell.getPosition().x - external_cell.getPosition().x == -cell_size && cell.getPosition().y == external_cell.getPosition().y) {
							possible_move = false;
						}
					}
				}
			}
		}

		if (possible_move) {
			for (auto& cell : mini_cells_tab) {
				cell.moveRight();
			}
		}
	}
}

void Block_I::rotate(){
	
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
	if(!Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		rotate_checker = false;
	}
}