#include "Enemy.h"

Enemy::Enemy(std::string name, std::string enemyFileTexture, float x, float y)
{
	this->enemyName = name;
	this->enemyFileTextureName = enemyFileTexture;
	this->enemyImage.loadFromFile("images/" + enemyFileTextureName);
	this->enemyTexture.loadFromImage(this->enemyImage);
	this->enemySprite.setTexture(this->enemyTexture);
	this->enemySprite.setTextureRect(sf::IntRect(0, 0, this->enemyWidth, this->enemyHeight));
	this->enemySprite.setOrigin(this->enemyWidth / 2, this->enemyHeight / 2);
	this->enemySprite.setPosition(x * 64, y * 64);
}

void Enemy::Show(sf::RenderWindow& win, sf::Vector2f playerPosition, float time, int** map)
{
	this->dx = this->enemySpeed * time;
	this->dy = this->enemySpeed * time;
	this->activCadr += time;

	this->LastPosition = enemySprite.getPosition();


	if (this->activCadr / 500 > 1)
	{
		this->activCadr = 0.f;
	}

	if (this->enemySprite.getPosition().x >= playerPosition.x)
	{
		dx *= -1;
	}
	if (this->enemySprite.getPosition().y >= playerPosition.y)
	{
		dy *= -1;
	}


	if (this->enemySprite.getPosition().y <= playerPosition.y + 2 && this->enemySprite.getPosition().y >= playerPosition.y - 2)
	{
		dy = 0;
	}
	if (this->enemySprite.getPosition().x <= playerPosition.x + 2 && this->enemySprite.getPosition().x >= playerPosition.x - 2)
	{
		dx = 0;
	}

	if (dx > 0)
	{
		this->enemyDirection = 2;
	}
	if (dx < 0)
	{
		this->enemyDirection = 3;
	}
	if (dy > 0)
	{
		this->enemyDirection = 0;
	}
	if (dy < 0)
	{
		this->enemyDirection = 1;
	}

	this->enemySprite.setTextureRect(sf::IntRect(enemyWidth * enemyDirection, (int)(activCadr / 250) * enemyHeight, enemyWidth, enemyHeight));
	this->enemySprite.move(dx, dy);

	if ((map[(int)(enemySprite.getPosition().y + 32) / 64][(int)(enemySprite.getPosition().x + 30) / 64] != '0') && (map[(int)(enemySprite.getPosition().y - 32) / 64][(int)(enemySprite.getPosition().x + 30) / 64] != '0'))
	{
		enemySprite.setPosition(LastPosition.x, enemySprite.getPosition().y);
	}
	if ((map[(int)(enemySprite.getPosition().y - 32) / 64][(int)(enemySprite.getPosition().x - 30) / 64] != '0') && (map[(int)(enemySprite.getPosition().y + 32) / 64][(int)(enemySprite.getPosition().x - 30) / 64] != '0'))
	{
		enemySprite.setPosition(LastPosition.x, enemySprite.getPosition().y);
	}
	if ((map[(int)(enemySprite.getPosition().y - 32) / 64][(int)(enemySprite.getPosition().x + 30) / 64] != '0') && (map[(int)(enemySprite.getPosition().y - 32) / 64][(int)(enemySprite.getPosition().x - 30) / 64] != '0'))
	{
		enemySprite.setPosition(enemySprite.getPosition().x, LastPosition.y);
	}
	if ((map[(int)(enemySprite.getPosition().y + 32) / 64][(int)(enemySprite.getPosition().x - 30) / 64] != '0') && (map[(int)(enemySprite.getPosition().y + 32) / 64][(int)(enemySprite.getPosition().x + 30) / 64] != '0'))
	{
		enemySprite.setPosition(enemySprite.getPosition().x, LastPosition.y);
	}

	win.draw(enemySprite);
}

void Enemy::setSprite(float x, float y)
{
	enemySprite.setPosition(x, y);
}
