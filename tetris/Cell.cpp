#include "Cell.h"
#include <iostream>

using namespace std;

Cell::Cell(float position_x, float position_y, float size, Color color){
	shape.setPosition(Vector2f(position_x, position_y));
	shape.setFillColor(color);
	shape.setSize(Vector2f(size, size));
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(Color::White);
	underControl = true;
	cellSize = size;
	possibleMove_Left = true;
	possibleMove_Right = true;
}


void Cell::draw(RenderTarget& target, RenderStates state) const {
	target.draw(shape, state);
}


bool Cell::get_underControl() {
	return underControl;
}

void Cell::set_underConrol(bool x) {
	underControl = x;
}


//void Cell::Move_X() {
//	
//	if (underControl) {
//
//		if (Keyboard::isKeyPressed(Keyboard::Key::A) && shape.getPosition().x > 0 && possibleMove_Left) {
//			moveLeft();
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::Key::D) && shape.getPosition().x < cellSize*9 && possibleMove_Right) {
//			moveRight();
//		}
//	}
//}

void Cell::moveDown() {

	if (underControl) {
		shape.setPosition(shape.getPosition().x, shape.getPosition().y + cellSize);
	}
}

void Cell::moveLeft() {
	shape.setPosition(shape.getPosition().x - cellSize, shape.getPosition().y );
}

void Cell::moveRight() {
	shape.setPosition(shape.getPosition().x + cellSize, shape.getPosition().y );
}



Vector2f Cell::getPosition() {
	return shape.getPosition();
}

void Cell::setPosition(Vector2f position){
	shape.setPosition(position);
}




//void Cell::Check_under(vector<Cell> cells_tab) {
//	if (underControl) {
//		for (auto& cell : cells_tab) {
//			if (!cell.get_underControl() && cell.getPosition().y-shape.getPosition().y==cellSize && cell.getPosition().x == shape.getPosition().x){
//				underControl = false;
//			}
//		}
//	}
//
//}

//void Cell::Check_X(vector<Cell> cells_tab) {
//	if (underControl) {
//		possibleMove_Left = true;
//		possibleMove_Right = true;
//		for (auto& cell : cells_tab) {
//
//			if (!cell.get_underControl() && cell.getPosition().x - shape.getPosition().x == cellSize && cell.getPosition().y == shape.getPosition().y){
//				possibleMove_Right = false;
//			}
//			if (!cell.get_underControl() && cell.getPosition().x - shape.getPosition().x == -cellSize && cell.getPosition().y == shape.getPosition().y) {
//				possibleMove_Left = false;
//			}
//
//
//		}
//	}
//}

