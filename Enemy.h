#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Enemy
{

	std::string enemyName;
	std::string enemyFileTextureName;
	sf::Image enemyImage;
	sf::Texture enemyTexture;
	float enemySpeed = 150.f / 1000.f;
	int enemyHeight = 64;
	int enemyWidth = 64;
	float dx = 0.f, dy = 0.f;
	int enemyDirection = 0;
	float activCadr = 0.f;
	sf::Vector2f LastPosition;


public:
	float enemyLife = 2.f;
	sf::Sprite enemySprite;
	Enemy(std::string name, std::string enemyFileTexture, float x, float y);
	void Show(sf::RenderWindow &win, sf::Vector2f playerPosition, float time, int** map);
	void setSprite(float, float);

};

