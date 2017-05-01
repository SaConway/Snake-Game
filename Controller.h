#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"
#include "Utilities.h"
#include <fstream>

//---------------------------

class Controller
{
public:
	Controller();
	void run();
	void input();
	void logic();
	void draw();
	void updateScore(int);
	void clean();
	void initText(sf::Text &, std::string &, unsigned int);

private:
	sf::RenderWindow m_window;
	sf::Texture m_texture;
	sf::Texture m_background;
	sf::Texture m_reset;
	sf::Texture m_power;
	sf::Sprite m_sprite;
	sf::Sprite m_spriteReset;
	sf::Sprite m_spritePower;
	sf::Font m_font;
	sf::Text m_text;
	Snake m_snake;
	Fruit m_fruit;
	Menu m_menu;
	eDirection m_direction = STOP;
	bool m_gameOver = false;
	int m_score = 0;
	int m_highScore;
	std::fstream m_file;
};