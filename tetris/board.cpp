#include "Board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>



Board::Board(float weight, float height, float _cell_size, RenderWindow* _window) {
	/*shape.setSize(Vector2f(weight, height));
	shape.setFillColor(Color(128, 128, 128));
	shape.setOutlineThickness(4.f);
	shape.setOutlineColor(Color::White);*/

	texture_board.loadFromFile("background.png");
	shape.setTexture(texture_board);

	texture_rightPanel.loadFromFile("RightPanel.png");
	rightPanel.setTexture(texture_rightPanel);
	

	cell_size = _cell_size;
	window = _window;

	
	font.loadFromFile("czcionka.ttf");

	score_text.setFont(font);
	score_text.setCharacterSize(30);
	score_text.setFillColor(Color::White);
	score_text.setPosition(Vector2f(12.5f * cell_size, 2 * cell_size));
	

	level_text.setFont(font);
	level_text.setCharacterSize(30);
	level_text.setFillColor(Color::White);
	level_text.setPosition(Vector2f(12.5f * cell_size, 5 * cell_size));

}

void Board::draw(RenderTarget& target, RenderStates state) const {
	target.draw(shape, state);
}


void Board::updateData(int _score) {
	score = _score;
	level = score / 100 + 1;
}

void Board::DrawRightPanel() {

	score_text.setString( "SCORE: "+ to_string(score));
	score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
	level_text.setString( "LEVEL: "+ to_string(level));
	level_text.setOrigin(level_text.getLocalBounds().width / 2, level_text.getLocalBounds().height / 2);

	rightPanel.setPosition(Vector2f(10 * cell_size, 0));

	window->draw(rightPanel);
	window->draw(score_text);
	window->draw(level_text);
}

int Board::getLevel() {
	return level;
}
