#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball : public Drawable
{
public:
	Ball(float x, float y, float rad, Color color);
	Ball() = delete;
	~Ball() = default;
private:
	CircleShape shape;

	void draw(RenderTarget& target, RenderStates state) const override;
};

