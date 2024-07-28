#include "Cell.h"
#include <iostream>

using namespace std;

Cell::Cell(float position_x, float position_y, float size, Color color){
	shape.setPosition(Vector2f(position_x, position_y));

	if (color == Color::Blue) {
		texture.loadFromFile("Blocks\\blue_cell.png");
	}
	else if (color == Color::Green) {
		texture.loadFromFile("Blocks\\green_cell.png");
	}
	else if (color == Color::Red) {
		texture.loadFromFile("Blocks\\red_cell.png");
	}
	else if (color == Color::Yellow) {
		texture.loadFromFile("Blocks\\yellow_cell.png");
	}
	else if (color == Color::Cyan) {
		texture.loadFromFile("Blocks\\orange_cell.png");
	}
	else if (color == Color::Magenta) {
		texture.loadFromFile("Blocks\\purple_cell.png");
	}
	else if (color == Color::Black) {
		texture.loadFromFile("Blocks\\darkBlue_cell.png");
	}
	
	underControl = true;
	cellSize = size;
	toDelete = false;

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


void Cell::set_toDelete() {
	toDelete = true;
}

bool Cell::get_toDelete() const {
	return toDelete;
}


void Cell::moveDown() {
	shape.setTexture(texture);
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


