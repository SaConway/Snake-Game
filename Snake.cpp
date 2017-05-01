#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "Utilities.h"

const int HEAD_OF_SNAKE = 0;

//---------------------------

Snake::Snake(sf::Texture & texture)
{
	m_body[HEAD_OF_SNAKE]._sprite.setTexture(texture);
	m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 120, 0, 30, PIC_SIZE });
	m_body[HEAD_OF_SNAKE]._sprite.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
	m_body[HEAD_OF_SNAKE]._direction = LEFT;

	m_soundBuffer.loadFromFile("EatSound.ogg");
}

//---------------------------

void Snake::draw(sf::RenderWindow & w)
{
	// Head of snake
	switch (m_body[HEAD_OF_SNAKE]._direction)
	{
	case UP:
		m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 180, 0, 30, PIC_SIZE });
		break;

	case RIGHT:
		m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 150, 0, PIC_SIZE, 30 });
		break;

	case LEFT:
		m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 120, 0, PIC_SIZE, 30 });
		break;

	case DOWN:
		m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 210, 0, 30, PIC_SIZE });
	}

	w.draw(m_body[HEAD_OF_SNAKE]._sprite);


	// Body of snake
	for (int i = 1; i < m_length; ++i)
	{
		if (m_body[i]._direction == UP || m_body[i]._direction == DOWN)
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 90, 0, 30, PIC_SIZE });
		else
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 60, 0, PIC_SIZE, 30 });

		//////////////////////////////////////////////

		if (m_body[i - 1]._direction == RIGHT && m_body[i]._direction == UP ||
			m_body[i - 1]._direction == DOWN && m_body[i]._direction == LEFT)
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 240, 0, 30, PIC_SIZE });

		else if (m_body[i - 1]._direction == LEFT && m_body[i]._direction == UP ||
			m_body[i - 1]._direction == DOWN && m_body[i]._direction == RIGHT)
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 270, 0, 30, PIC_SIZE });

		else if (m_body[i - 1]._direction == RIGHT && m_body[i]._direction == DOWN ||
			m_body[i - 1]._direction == UP && m_body[i]._direction == LEFT)
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 300, 0, 30, PIC_SIZE });

		else if (m_body[i - 1]._direction == UP && m_body[i]._direction == RIGHT ||
			m_body[i - 1]._direction == LEFT && m_body[i]._direction == DOWN)
			m_body[i]._sprite.setTextureRect(sf::IntRect{ 330, 0, 30, PIC_SIZE });

		w.draw(m_body[i]._sprite);
	}
}

//---------------------------

// status value : 0 = Game Over, 1 = Succeded move, 2 = Succeed move + ate fruit

int Snake::move(Fruit & f, sf::Vector2f & v, eDirection & direction)
{
	sf::Vector2f newPos = v + m_body[0]._sprite.getPosition();

	if (newPos.x < 0 || newPos.y < 0 || newPos.x >= WIDTH || newPos.y >= HEIGHT)
		return 0;			// game over

							// Check for collision with tail
	for (int i = 0; i < m_length; ++i)
		if (newPos == m_body[i]._sprite.getPosition())
			return 0;		// game over

	int status = 1;
	// Check for collision with fruit
	if (newPos == f.get())
	{
		m_eatSound.setBuffer(m_soundBuffer);
		m_eatSound.play();
		f.update(*this);
		m_length++;
		status = 2;
	}
	if (m_length > 1)
		updateTail();

	m_body[HEAD_OF_SNAKE]._direction = direction;
	m_body[HEAD_OF_SNAKE]._sprite.move(v);
	return status;
}

//---------------------------

void Snake::updateTail()
{
	bodyStatus prev = m_body[1];
	m_body[1]._sprite = m_body[HEAD_OF_SNAKE]._sprite;
	m_body[1]._direction = m_body[HEAD_OF_SNAKE]._direction;

	for (int i = 2; i < m_length; ++i)
	{
		bodyStatus prev2 = m_body[i];
		m_body[i] = prev;
		prev = prev2;
	}
}