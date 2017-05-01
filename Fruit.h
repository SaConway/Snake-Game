#pragma once

#include "Utilities.h"
#include <SFML/Graphics.hpp>

//---------------------------

class Snake;

class Fruit
{
public:
	Fruit(sf::Texture & = sf::Texture(), const sf::Vector2f & = { 0, 0 });
	void draw(sf::RenderWindow & w) const { w.draw(m_sprite); }
	void update(Snake &);
	sf::Vector2f chooseRandPos() const;
	const sf::Vector2f & get() { return m_sprite.getPosition(); }

private:
	sf::Sprite m_sprite;
};