#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Square : public Drawable
{
public:
	Square(float x, float y, Vector2f size, Color color, String txtPath);
	Square() = delete;
	~Square() = default;
private:
	Sprite shape;
	Texture txt;
	void draw(RenderTarget& target, RenderStates state) const override;
};

