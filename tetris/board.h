#include <SFML/Graphics.hpp>
using namespace sf;

class Board :public Drawable
{
public:
	Board(float weight, float height);
	
private:
	RectangleShape shape;
	void draw(RenderTarget& target, RenderStates state) const override;
	
};

