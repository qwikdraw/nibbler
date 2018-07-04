#include "Sfml.hpp"

extern "C" IGraphic	*load(glm::ivec2 mapsize)
{
	return new Sfml(mapsize);
}

Sfml::Sfml(glm::ivec2 mapsize) : _mapsize(mapsize)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	_window = new sf::RenderWindow(sf::VideoMode(1600, 1600), "Sfml", sf::Style::Default, settings);
	_square = sf::RectangleShape(sf::Vector2f(20, 20));
}

void	Sfml::Draw(glm::ivec2 pos, char c)
{
	if (c == ' ')
		return;
	if (c == 'O')
		_square.setFillColor(sf::Color(100, 250, 50));
	else if (c == '#')
		_square.setFillColor(sf::Color(250, 100, 50));
	else if (c == '@')
		_square.setFillColor(sf::Color(250, 250, 0));
	_square.setPosition(pos.x * 20, pos.y * 20);
	_window->draw(_square);
}

void	Sfml::Display(void)
{
	_window->display();
	_window->clear();
}

struct Input	Sfml::Input(void)
{
	struct Input out = {false, false, false, false, false, false, false, false};
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)	
			out.close = true;
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
				out.up = true;
			if (event.key.code == sf::Keyboard::Down)
				out.down = true;
			if (event.key.code == sf::Keyboard::Left)
				out.left = true;
			if (event.key.code == sf::Keyboard::Right)
				out.right = true;
			if (event.key.code == sf::Keyboard::Escape)
				out.close = true;
			if (event.key.code == sf::Keyboard::Num1)
				out.one = true;
			if (event.key.code == sf::Keyboard::Num2)
				out.two = true;
		}
	}
	(void)_mapsize;
	return out;
}

void	Sfml::Destroy(void)
{
	_window->close();
	delete _window;
	delete this;
}
