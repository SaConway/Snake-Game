#pragma once

#include "Fruit.h"
#include <SFML/Audio.hpp>
#include "Utilities.h"

//---------------------------

struct bodyStatus
{
	sf::Sprite _sprite;
	eDirection _direction;
};

//---------------------------

class Snake
{
public:
	Snake(sf::Texture & = sf::Texture());
	void draw(sf::RenderWindow &);
	int move(Fruit &, sf::Vector2f &, eDirection &);
	void updateTail();
	int getTailLength() const { return m_length; }
	const sf::Vector2f & getBodyPos(int i) { return m_body[i]._sprite.getPosition(); }

private:
	bodyStatus m_body[100];
	int m_length = 1;
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_eatSound;
};