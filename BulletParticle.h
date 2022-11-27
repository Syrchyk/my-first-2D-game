#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
class BulletParticle
{

	std::string BulletParticleName;
	std::string BulletParticleFileTextureName;
	sf::Image BulletParticleImage;
	sf::Texture BulletParticleTexture;
	float BulletParticleSpeed = 1000.f / 1000.f;
	int BulletParticleH = 8;
	int BulletParticleW = 8;
	int startY = 0;
	int startX = 0;
	float dx = 0.f, dy = 0.f;
	int BulletParticleDirection = 0;
	float activCadr = 0.f;
	float checkCadr = 0.f;
	sf::Vector2f LastPosition;


public:
	sf::Sprite BulletParticleSprite;
	int BulletParticleLife = 5;
	BulletParticle(std::string name, std::string bulletParticleFileTexture, sf::Vector2f BulletPosition, int startX, int startY, int x, int y);
	void Activ(sf::RenderWindow& win, float time, int** map);
};