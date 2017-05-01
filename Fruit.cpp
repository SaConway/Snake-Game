#include "Fruit.h"
#include "Snake.h"

//---------------------------

Fruit::Fruit(sf::Texture & texture, const sf::Vector2f & posBoard)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
	m_sprite.setPosition(posBoard);
}

//---------------------------

void Fruit::update(Snake & s)
{
	sf::Vector2f v = chooseRandPos();
	for (; v == s.getBodyPos(0); v = chooseRandPos());

	for (int i = 0; i < s.getTailLength(); )
		if (v == s.getBodyPos(i) || v == s.getBodyPos(0))
		{
			v = chooseRandPos();
			i = 0;
		}
		else i++;

		m_sprite.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
		m_sprite.setPosition(v);
}

//---------------------------

sf::Vector2f Fruit::chooseRandPos() const
{
	return sf::Vector2f{ (float)((rand() % 12) * (float)(PIC_SIZE)), (float)((rand() % 12) * (float)(PIC_SIZE)) };
}
