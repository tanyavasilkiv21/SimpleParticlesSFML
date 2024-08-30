#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class ParticleSys
{
	struct Particle
	{
		sf::Vector2f velocity;
		int lifetime = 0;
	};

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Vector2u m_position;
	float m_size = 8;

	void resetParticles(size_t count = 1000, float size = 8)
	{
		m_particles = std::vector<Particle>(count);
		m_vertices = sf::VertexArray(sf::Quads, count * 4);
		m_size = size;

		for (size_t p = 0; p < m_particles.size(); p++)
		{
			resetParticle(p, true);
		}
	}
	void resetParticle(std::size_t index, bool first = false)
	{
		m_vertices[4 * index + 0].position = sf::Vector2f(m_position.x, m_position.y);
		m_vertices[4 * index + 1].position = sf::Vector2f(m_position.x + m_size, m_position.y);
		m_vertices[4 * index + 2].position = sf::Vector2f(m_position.x + m_size, m_position.y + m_size);
		m_vertices[4 * index + 3].position = sf::Vector2f(m_position.x, m_position.y + m_size);

		sf::Color c(rand()%255, 0, 155, 255);
		if (first)
		{
			c = sf::Color(0, 0, 0, 0);
		}
		m_vertices[4 * index + 0].color = c;
		m_vertices[4 * index + 1].color = c;
		m_vertices[4 * index + 2].color = c;
		m_vertices[4 * index + 3].color = c;

		float theta = ((float)rand() / RAND_MAX) * 2 * 3.14;

		float radius = ((float)rand() / RAND_MAX) * 5;

		float rx = radius * cos(theta);
		float ry = radius * sin(theta);

		m_particles[index].velocity = sf::Vector2f(rx, ry);

		
		m_particles[index].lifetime = 30 + rand()% 60;
	}

public:
	ParticleSys()
	{

	}
	void init(sf::Vector2u windowSize)
	{
		m_position = windowSize;
		resetParticles();
	}
	void update()
	{
		for (size_t p = 0; p < m_particles.size(); p++)
		{
			if (m_particles[p].lifetime == 0)
			{
				resetParticle(p);
			}
			else
			{
				m_vertices[4 * p + 0].position += m_particles[p].velocity;
				m_vertices[4 * p + 1].position += m_particles[p].velocity;
				m_vertices[4 * p + 2].position += m_particles[p].velocity;
				m_vertices[4 * p + 3].position += m_particles[p].velocity;
				m_particles[p].lifetime--;
			}
		
		}
	}
	void draw(sf::RenderWindow& window) const
	{
		window.draw(m_vertices);
	}
};

