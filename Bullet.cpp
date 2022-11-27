#include "Bullet.h"

Bullet::Bullet(std::string name, std::string bulletFileTexture, float x, float y, sf::Vector2f playerPosition, sf::Vector2f lastPos, float timer, int lastSlide)
{
	this->BulletName = name;
	this->BulletFileTextureName = bulletFileTexture;
	this->BulletImage.loadFromFile("images/" + BulletFileTextureName);
	this->BulletTexture.loadFromImage(this->BulletImage);
	this->BulletSprite.setTexture(this->BulletTexture);
	this->BulletSprite.setTextureRect(sf::IntRect(0, 0, this->BulletWidth, this->BulletHeight));
	this->BulletSprite.setOrigin(this->BulletWidth / 2, this->BulletHeight / 2);
	this->BulletSprite.setPosition(x * 64, y * 64);
	BulletSprite.setPosition(playerPosition);
	this->dx = this->BulletSpeed * timer;
	this->dy = this->BulletSpeed * timer;
	if (playerPosition.x - lastPos.x < 0)
	{
		this->dx *= -1;
	}
	if (playerPosition.y - lastPos.y < 0)
	{
		this->dy *= -1;
	}
	if (playerPosition.x - lastPos.x == 0)
	{
		this->dx = 0;
	}
	if (playerPosition.y - lastPos.y == 0)
	{
		this->dy = 0;
	}
	if (playerPosition.y - lastPos.y == 0 && playerPosition.x - lastPos.x == 0)
	{
		switch (lastSlide)
		{
		case 0: {this->dy = this->BulletSpeed * timer; break;}
		case 1: {this->dy = this->BulletSpeed * -timer; break;}
		case 2: {this->dx = this->BulletSpeed * -timer; break;}
		case 3: {this->dx = this->BulletSpeed * timer; break;}
		}
	}


}

float Bullet::Fly(sf::RenderWindow& win, float time, int** map, std::list<Enemy*> enemys, float bossLife, sf::Sprite bossSprite)
{

	this->activCadr += time;



	if (this->activCadr / 100 > 3)
	{
		this->activCadr = 0.f;
	}



	this->BulletSprite.setTextureRect(sf::IntRect((int)(activCadr / 100) * BulletHeight, 0, BulletWidth, BulletHeight));
	this->BulletSprite.move(dx, dy);

	//BulletSprite.getPosition()
	//(index)->enemySprite.getPosition() 

	for (auto index : enemys)
	{
		if (BulletSprite.getPosition().x + 5 >= (index)->enemySprite.getPosition().x - 30 && BulletSprite.getPosition().x + 5 <= (index)->enemySprite.getPosition().x + 30 && BulletSprite.getPosition().y + 5 >= (index)->enemySprite.getPosition().y - 32 && BulletSprite.getPosition().y + 5 <= (index)->enemySprite.getPosition().y + 32)
		{
			BulletLife = 0;
			(index)->enemyLife -= 1;
		}
	}

	if (BulletSprite.getPosition().x + 5 >= bossSprite.getPosition().x - 47 && BulletSprite.getPosition().x + 5 <= bossSprite.getPosition().x + 47*2 && BulletSprite.getPosition().y + 5 >= bossSprite.getPosition().y - 64*2 && BulletSprite.getPosition().y + 5 <= bossSprite.getPosition().y + 64*2)
	{
		BulletLife = 0;
		bossLife -= 1;
		this->bossLifeRem = bossLife;
		std::cout << bossLife << std::endl;
	}

	if ((map[(int)(BulletSprite.getPosition().y + 10) / 64][(int)(BulletSprite.getPosition().x + 10) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BulletSprite.getPosition().y) / 64][(int)(BulletSprite.getPosition().x) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BulletSprite.getPosition().y) / 64][(int)(BulletSprite.getPosition().x + 10) / 64] != '0'))
	{
		BulletLife = 0;
	}
	if ((map[(int)(BulletSprite.getPosition().y + 10) / 64][(int)(BulletSprite.getPosition().x) / 64] != '0'))
	{
		BulletLife = 0;
	}
	
	win.draw(BulletSprite);
	return bossLife;
}