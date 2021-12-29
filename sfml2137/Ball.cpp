#include "Ball.h"

using namespace sf;

Ball::Ball(float x, float y, float rad, Color color)
{
	shape.setPosition(x, y);
	shape.setRadius(rad);
	shape.setFillColor(color);
	shape.setOrigin(rad, rad);
}

void Ball::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}