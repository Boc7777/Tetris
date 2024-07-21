#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;


class Cell :public Drawable
{
public:
	Cell(float position_x, float position_y, float size, Color color);

	bool get_underControl();
	void set_underConrol(bool x);

	/*void Move_X();*/
	void moveLeft();
	void moveRight();

	void moveDown();
	
	/*void Check_under(vector<Cell> cells_tab);*/
	/*void Check_X(vector<Cell> cells_tab);*/

	Vector2f getPosition();
	void setPosition(Vector2f position);

private:
	RectangleShape shape; 
	bool underControl;

	bool possibleMove_Left;
	bool possibleMove_Right;

	float cellSize;
	void draw(RenderTarget& target, RenderStates state) const override;
};

