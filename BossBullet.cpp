#include "BossBullet.h"

BossBullet::BossBullet(std::string name, std::string bulletFileTexture, sf::Vector2f BossPosition, sf::Vector2f playerPosition)
{
	this->BossBulletName = name;
	this->BossBulletFileTextureName = bulletFileTexture;
	this->BossBulletImage.loadFromFile("images/" + BossBulletFileTextureName);
	this->BossBulletTexture.loadFromImage(this->BossBulletImage);
	this->BossBulletSprite.setTexture(this->BossBulletTexture);
	this->BossBulletSprite.setTextureRect(sf::IntRect(0, 0, this->BossBulletWidth, this->BossBulletHeight));
	this->BossBulletSprite.setOrigin(this->BossBulletWidth / 2, this->BossBulletHeight / 2);
	this->BossBulletSprite.setPosition(BossPosition);
	this->dx = (playerPosition.x - this->BossBulletSprite.getPosition().x) / 100;
	this->dy = (playerPosition.y - this->BossBulletSprite.getPosition().y) / 100;
}

float BossBullet::Launch(sf::RenderWindow& win, int** map, float playerLife, sf::Sprite playerSprite)
{

	this->BossBulletSprite.move(dx, dy);


	if (BossBulletSprite.getPosition().x + 5 >= playerSprite.getPosition().x - 30 && BossBulletSprite.getPosition().x + 5 <= playerSprite.getPosition().x + 30 && BossBulletSprite.getPosition().y + 5 >= playerSprite.getPosition().y - 32 && BossBulletSprite.getPosition().y + 5 <= playerSprite.getPosition().y + 32)
	{
		BulletLife = 0;
		//this->LifeRem -= 1;
	}

	if ((map[(int)(BossBulletSprite.getPosition().y + 10) / 64][(int)(BossBulletSprite.getPosition().x + 10) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BossBulletSprite.getPosition().y) / 64][(int)(BossBulletSprite.getPosition().x) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BossBulletSprite.getPosition().y) / 64][(int)(BossBulletSprite.getPosition().x + 10) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BossBulletSprite.getPosition().y + 10) / 64][(int)(BossBulletSprite.getPosition().x) / 64] != '0'))
	{
		BulletLife = 0;
	}

	win.draw(BossBulletSprite);
	return LifeRem;
}
