#include "Cell.h"
#include <iostream>

using namespace std;

Cell::Cell(float position_x, float position_y, float size, Color color){
	shape.setPosition(Vector2f(position_x, position_y));
	/*shape.setFillColor(color);
	shape.setSize(Vector2f(size, size));*/
	
	/*shape.setOutlineThickness(1.f);*/
	/*shape.setOutlineColor(Color::Black);*/

	if (color == Color::Green) {
		texture.loadFromFile("Blocks\\green_block.png");
	}
	else if (color == Color::Blue) {
		texture.loadFromFile("Blocks\\blue_block.png");
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


