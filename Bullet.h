#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <list>
#include "Enemy.h"
#include <iostream>

class Bullet
{

	std::string BulletName;
	std::string BulletFileTextureName;
	sf::Image BulletImage;
	sf::Texture BulletTexture;
	float BulletSpeed = 1000.f / 1000.f;
	int BulletHeight = 10;
	int BulletWidth = 10;
	float dx = 0.f, dy = 0.f;
	int BulletDirection = 0;
	float activCadr = 0.f;

	sf::Vector2f LastPosition;


public:
	sf::Sprite BulletSprite;
	float bossLifeRem = 50;
	int BulletLife = 1;
	Bullet(std::string name, std::string bulletFileTexture, float x, float y, sf::Vector2f playerPosition, sf::Vector2f lastPos, float timer, int lastSlide);
	float Fly(sf::RenderWindow& win, float time, int** map, std::list<Enemy*> enemys, float bossLife, sf::Sprite bossSprite);
};