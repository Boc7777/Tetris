#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;


class Cell :public Drawable
{
public:
	Cell(float position_x, float position_y, float size, Color color);
	/*~Cell();*/

	bool get_underControl();
	void set_underConrol(bool x);

	void set_toDelete();
	bool get_toDelete() const;

	void moveLeft();
	void moveRight();

	void moveDown();

	Vector2f getPosition();
	void setPosition(Vector2f position);

private:
	RectangleShape shape; 
	bool underControl;
	bool toDelete;

	float cellSize;
	void draw(RenderTarget& target, RenderStates state) const override;
};

