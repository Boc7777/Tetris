#include <SFML/Graphics.hpp>
#include <vector>
#include "TetrisBlock.h"

using namespace sf;

class Board :public Drawable
{
public:
	Board(float _cell_size, RenderWindow* _window);
	void updateData(int _score);
	void DrawRightPanel();
	int getLevel();
	void DrawGameOver();
	
private:
	RenderWindow* window;

	Sprite shape; 
	Texture texture_board;
	Sprite rightPanel;
	Texture texture_rightPanel;
	Sprite gameover;
	Texture texture_gameover;
	
	Text score_text;
	Text level_text;
	Font font;

	float cell_size;
	int score;
	int level;

	void draw(RenderTarget& target, RenderStates state) const override;
};

