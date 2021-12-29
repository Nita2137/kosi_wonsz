#include "Square.h"

using namespace sf;

Square::Square(float x, float y, Vector2f size, Color color, String txtPath)
{
	shape.setPosition(x, y);
	//shape.setSize(size);
	//shape.setFillColor(color);
	//shape.setOrigin(size.x/2, size.y/2);
	if (!txt.loadFromFile(txtPath)) {}
	shape.setTexture(txt);
	shape.setOrigin(txt.getSize().x / 2, txt.getSize().y / 2);
}

void Square::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}