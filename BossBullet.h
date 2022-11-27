#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class BossBullet
{

	std::string BossBulletName;
	std::string BossBulletFileTextureName;
	sf::Image BossBulletImage;
	sf::Texture BossBulletTexture;
	float BossBulletSpeed = 1000.f / 1000.f;
	int BossBulletHeight = 10;
	int BossBulletWidth = 10;
	float dx = 0.f, dy = 0.f;
	int BossBulletDirection = 0;
	float activCadr = 0.f;

	sf::Vector2f LastPosition;


public:
	sf::Sprite BossBulletSprite;
	int BulletLife = 1;
	float LifeRem = 6;
	BossBullet(std::string name, std::string bulletFileTexture, sf::Vector2f BossPosition, sf::Vector2f playerPosition);
	float Launch(sf::RenderWindow& win, int** map, float playerLife, sf::Sprite playerSprite);
};