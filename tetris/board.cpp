#include "Board.h"


Board::Board(float weight, float height) {
	shape.setSize(Vector2f(weight, height));
	shape.setFillColor(Color(128, 128, 128));
	shape.setOutlineThickness(4.f);
	shape.setOutlineColor(Color::White);
}

void Board::draw(RenderTarget& target, RenderStates state) const {
	target.draw(shape, state);
}
