#include "BulletParticle.h"

BulletParticle::BulletParticle(std::string name, std::string bulletParticleFileTexture, sf::Vector2f BulletPosition, int startX, int startY, int x, int y)
{
	this->BulletParticleName = name;
	this->BulletParticleFileTextureName = bulletParticleFileTexture;
	this->BulletParticleImage.loadFromFile("images/" + BulletParticleFileTextureName);
	this->BulletParticleTexture.loadFromImage(this->BulletParticleImage);
	this->BulletParticleSprite.setTexture(this->BulletParticleTexture);
	this->BulletParticleH = y;
	this->BulletParticleW = x;
	this->BulletParticleSprite.setTextureRect(sf::IntRect(startX, startY, x, y));
	this->BulletParticleSprite.setOrigin(this->BulletParticleW / 2, this->BulletParticleH / 2);
	this->BulletParticleSprite.setPosition(BulletPosition);
	this->startY = startY;
	this->startX = startX;



}

void BulletParticle::Activ(sf::RenderWindow& win, float time, int** map)
{

	this->activCadr += time;
	this->checkCadr += time;



	if (this->activCadr / 200 > 5)
	{
		this->activCadr = 0.f;
	}
	if (this->checkCadr / 40 >= 1)
	{

		this->BulletParticleLife--;
		this->checkCadr = 0;
	}



	this->BulletParticleSprite.setTextureRect(sf::IntRect(((int)(activCadr / 40) * BulletParticleW) + startX, startY, BulletParticleW, BulletParticleH));
	

	win.draw(BulletParticleSprite);
}
