#include <iostream>
#include "ParticleSys.h"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Simple Particles");
	window.setFramerateLimit(60);
	ParticleSys particles;
	particles.init(sf::Vector2u(window.getSize().x/2, window.getSize().y/2));
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
					sf::Vector2f worldPos = window.mapPixelToCoords(clickPosition);
					particles.init(sf::Vector2u(worldPos));
				}
			}
		}
		particles.update();
		window.clear(sf::Color::Black);
		particles.draw(window);
		window.display();
	}
}
