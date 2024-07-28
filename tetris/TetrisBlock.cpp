#include "TetrisBlock.h"
#include <iostream>

void TetrisBlock::spawnCells() {
	for (int i = 0; i < 4;i++) {
		 getTabCells().emplace_back(i * getCellSize(), 2 * getCellSize(), getCellSize(), getColor());
	}
}

void TetrisBlock::drawCells() {
	for (auto& cell : getTabCells()) {
		getWindow()->draw(cell);
	}
}

void TetrisBlock::checkUnderControl() {
	for (auto& cell : getTabCells()) {
		if (!cell.get_underControl()) {
			for (auto& cell : getTabCells()) {
				cell.set_underConrol(false);
				setBlockUnderControl(false);
			}
		}
	}
}

void TetrisBlock::moveDownCells() {
	for (auto& cell : getTabCells()) {
		cell.moveDown();
	}
	setBlockPosition(Vector2f(GetBlockPosition().x, GetBlockPosition().y + getCellSize()));
}

void TetrisBlock::movement_X() {

	if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		bool possible_move = true;

		for (auto& cell : getTabCells()) {
			if (!cell.get_underControl()) {
				possible_move = false;
			}
		}

		if (possible_move) {
			for (auto& cell : getTabCells()) {
				if (cell.getPosition().x == 0) {
					possible_move = false;
				}
			}


			for (auto& cell : getTabCells()) {

				for (TetrisBlock* block : getTabBloks()) {
					for (auto& external_cell : block->getTabCells()) {
						if (!external_cell.get_underControl() && cell.getPosition().x - external_cell.getPosition().x == getCellSize() && cell.getPosition().y == external_cell.getPosition().y) {
							possible_move = false;
						}
					}
				}
			}
		}

		if (possible_move) {
			for (auto& cell : getTabCells()) {
				cell.moveLeft();
			}
			setBlockPosition(Vector2f(GetBlockPosition().x - getCellSize(), GetBlockPosition().y));
		}

	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		bool possible_move = true;

		for (auto& cell : getTabCells()) {
			if (!cell.get_underControl()) {
				possible_move = false;
			}
		}

		if (possible_move) {
			for (auto& cell : getTabCells()) {
				if (cell.getPosition().x == 9 * getCellSize()) {
					possible_move = false;
				}
			}


			for (auto& cell : getTabCells()) {

				for (TetrisBlock* block : getTabBloks()) {
					for (auto& external_cell : block->getTabCells()) {
						if (!external_cell.get_underControl() && cell.getPosition().x - external_cell.getPosition().x == -getCellSize() && cell.getPosition().y == external_cell.getPosition().y) {
							possible_move = false;
						}
					}
				}
			}
		}

		if (possible_move) {
			for (auto& cell : getTabCells()) {
				cell.moveRight();
			}
			setBlockPosition(Vector2f(GetBlockPosition().x + getCellSize(), GetBlockPosition().y));
		}
	}
}

void TetrisBlock::checkUnderCells() {
	for (auto& internal_cell : getTabCells()) {
		if (internal_cell.getPosition().y == getCellSize() * 19) {
			internal_cell.set_underConrol(false);
			checkUnderControl();
		}

		for (TetrisBlock* block : getTabBloks()) {
			for (auto& external_cell : block->getTabCells()) {

				if (!external_cell.get_underControl() &&
					external_cell.getPosition().y - internal_cell.getPosition().y == getCellSize() &&
					internal_cell.getPosition().x == external_cell.getPosition().x)
				{
					internal_cell.set_underConrol(false);
					checkUnderControl();
				}

			}
		}


	}
}

void TetrisBlock::deleteCellFromTab(int index) {
	getTabCells()[index].set_toDelete();
}

bool TetrisBlock::borderChecker(Vector2f position) { 
	if (position.x < 0 || position.x > 9 * getCellSize()) {
		return false;
	}
	if (position.y > 19 * getCellSize()) {
		return false;
	}
	return true;
}

bool TetrisBlock::colisionChecker(vector<Vector2f> cells_to_check, vector<TetrisBlock*> blocks_tab)
{
	for (TetrisBlock* block : blocks_tab) {
		for (auto& external_cell : block->getTabCells()) {
			for (auto& blockCheck : cells_to_check) {

				if (external_cell.getPosition() == blockCheck) {
					return false;
				}
			}
		}
	}
	return true;
}

bool TetrisBlock::getBlocktoDelete(){
	return getTabCells().empty();
}