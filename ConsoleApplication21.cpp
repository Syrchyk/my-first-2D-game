#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <math.h>
#include "Enemy.h"
#include "Maps.h"
#include "Bullet.h"
#include "BulletParticle.h"
#include "BossBullet.h"

enum directions { STAND = 0, LEFT, RIGTH, UP, DOWN, JAMP };

void CutScene(sf::RenderWindow& win, sf::Sprite player, sf::Sprite NPC, sf::Text text, sf::RectangleShape backFont, int** map, sf::Sprite mapSprite, int MapW, int MapH, sf::Sprite MomSprite, sf::Sprite OutOfMapSprite, bool isOutOfMap, sf::Vector2f cameraPos, sf::Vector2f cameraSize, sf::View mainCamera)
{
	sf::Clock clock;
	float timer = 0.f;
	float playTime = 0.f;
	float animTime = 0.f;
	bool isCutScene = true;
	float dx;
	float dy;



	NPC.setTextureRect(sf::IntRect(32, 16, 16, 16));
	while (isCutScene)
	{

		backFont.setPosition(NPC.getPosition().x - backFont.getSize().x / 2, NPC.getPosition().y - 75);
		text.setPosition(backFont.getPosition().x + 5, backFont.getPosition().y - 4);

		timer = clock.restart().asMilliseconds();
		playTime += timer;

		if (playTime < 2500)
		{
			animTime += timer;
			if (animTime/300 > 2)
			{
				animTime = 0;
			}
			dx = 0;
			float dy = -(100.f / 1000.f) * timer;
			NPC.setTextureRect(sf::IntRect(((int)animTime / 300 * 16) + 32, 16, 16, 16));
			NPC.move(dx, dy);
		}
		else
		{
			NPC.setTextureRect(sf::IntRect(32, 32, 16, 16));
			text.setString("Mom i miss you");
		}
		if (playTime < 2000)
		{
			dx = 0;
			float dy = -(100.f / 1000.f) * timer;
			player.move(dx, dy);
			player.setTextureRect(sf::IntRect(64, 64*((int)playTime/500), 64, 64));
			mainCamera.setCenter(player.getPosition());
		}
		else
		{
			player.setTextureRect(sf::IntRect(128, 0, 64, 64));
		}
		if (playTime > 5000)
		{
			win.close();
		}

		cameraSize = mainCamera.getSize();
		cameraPos = player.getPosition();
		if (cameraPos.x < cameraSize.x / 2)  cameraPos.x = cameraSize.x / 2;
		if (cameraPos.x > ((MapW - 1) * 64) - cameraSize.x / 2) cameraPos.x = ((MapW - 1) * 64) - cameraSize.x / 2;
		if (cameraPos.y < cameraSize.y / 2)  cameraPos.y = cameraSize.y / 2;
		if (cameraPos.y > ((MapH) * 64) - cameraSize.y / 2) cameraPos.y = ((MapH) * 64) - cameraSize.y / 2;
		mainCamera.setCenter(cameraPos);

		win.setView(mainCamera);
		win.clear();
		for (int y = 0; y < MapH; y++)
			for (int x = 0; x < MapW - 1; x++)
			{
				switch (map[y][x])
				{
				case '1': {mapSprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); break; }
				case '2': {mapSprite.setTextureRect(sf::IntRect(128, 0, 64, 64)); break; }
				case '3': {mapSprite.setTextureRect(sf::IntRect(128, 128, 64, 64)); break; }
				case '4': {mapSprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); break; }
				case '5': {mapSprite.setTextureRect(sf::IntRect(64, 0, 64, 64)); break; }
				case '6': {mapSprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); break; }
				case '7': {mapSprite.setTextureRect(sf::IntRect(64, 128, 64, 64)); break; }
				case '8': {mapSprite.setTextureRect(sf::IntRect(128, 64, 64, 64)); break; }
				case '0': {mapSprite.setTextureRect(sf::IntRect(64, 64, 64, 64)); break; }
				case '<': {mapSprite.setTextureRect(sf::IntRect(192, 64, 64, 64)); break; }
				case '>': {mapSprite.setTextureRect(sf::IntRect(192, 0, 64, 64)); break; }
				case '{': {mapSprite.setTextureRect(sf::IntRect(256, 64, 64, 64)); break; }
				case '}': {mapSprite.setTextureRect(sf::IntRect(256, 0, 64, 64)); break; }
				case 'T': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case 'M': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case 'W': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case ' ': {OutOfMapSprite.setPosition(x * 64.f, y * 64.f);
					win.draw(OutOfMapSprite);
					isOutOfMap = true;
					break; }
				}
				if (!isOutOfMap)
				{
					mapSprite.setPosition(x * 64.f, y * 64.f);
				}
				else
				{
					isOutOfMap = false;
				}
				win.draw(mapSprite);
			}
		win.draw(backFont);
		win.draw(text);
		win.draw(NPC);
		win.draw(player);
		win.draw(MomSprite);
		win.display();
	}
}
int EndGame(sf::RenderWindow& win, sf::Sprite& endHUD, sf::View& camera)
{
	int activeMenuItem = 0;
	int maxMenuItem = 1;
	endHUD.setScale(1.5, 1.5);
	bool isMenu = true;

	while (isMenu)
	{
		sf::Event event;

		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					win.close();
					return 0;
				}
			}
		}
		endHUD.setTextureRect(sf::IntRect(0, 0, 188, 44));
		endHUD.setPosition(camera.getCenter().x - 94, camera.getCenter().y - 44);
		win.draw(endHUD);
		endHUD.setTextureRect(sf::IntRect(0, 44, 188, 44));
		endHUD.setPosition(camera.getCenter().x - 94, camera.getCenter().y +  -22 + 20 + 44);
		win.draw(endHUD);
		win.display();
	}
}

int Menu(sf::RenderWindow &win, sf::Sprite &backMenu, sf::Vector2f &backMenuSize, sf::Sprite &HUD, sf::View &camera)
{
	backMenu.setPosition(camera.getCenter().x - backMenuSize.x * backMenu.getScale().y / 2, camera.getCenter().y - backMenuSize.y * backMenu.getScale().y / 2);
	int activeMenuItem = 0;
	int maxMenuItem = 5;
	HUD.setScale(1.5, 1.5);
	bool isMenu = true;

	while (isMenu)
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					isMenu = false;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					activeMenuItem = (--activeMenuItem < 0) ? maxMenuItem - 1 : activeMenuItem;
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::S)
				{
					activeMenuItem = (++activeMenuItem > maxMenuItem - 1) ? 0 : activeMenuItem;
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					return activeMenuItem;
				}
			}
		}
		win.draw(backMenu);
		for (int i = 0; i < maxMenuItem; i++)
		{
			if (activeMenuItem == i)
			{
				HUD.setTextureRect(sf::IntRect(176, 44 * i, 128, 44));
			}
			else
			{
				HUD.setTextureRect(sf::IntRect(48, 44 * i, 128, 44));
			}
			HUD.setPosition(backMenu.getPosition().x + 20 * 1.5, backMenu.getPosition().y + 20 * 1.5 + (56 * 1.5 * i));
			win.draw(HUD);
		}
		win.display();
	}
}

int main()
{
    srand(time(NULL));
	// створення мапи
	int MapW = 0;
	int MapH = 0;
	int** map = new int* [0];
	map = mapSizeChange(map, sipleSizeMapH, sipleSizeMapW, MapH);
	MapW = sipleSizeMapW;
	MapH = sipleSizeMapH;
	for (int y = 0; y < MapH; y++)
		for (int x = 0; x < MapW - 1; x++)
		{
			map[y][x] = map1[y][x];
		}
	// створення екрану гри
    int screenW = 960;
    int screenH = 640;
    sf::RenderWindow myGame(sf::VideoMode(screenW, screenH), "My game");
    myGame.setFramerateLimit(60);





	//зберігання шляхів до картинок
    std::string fileNameMapImage = "mapa.png";
    std::string fileNamePlayerImage = "player.png";
	std::string fileNameBulletsImage = "bullets.png";
	std::string fileNameHUDImage = "HUD.png";
	std::string fileNameBackMenuImage = "backMenu.png";
	std::string fileOutOfMapImage = "OutOfMap.png";
	std::string fileNameEndHUDImage = "endHUD.png";
	std::string fileNameNPCImage = "mainNPC.png";
	std::string fileNameBossImage = "druid.png";
	std::string fileNameMomImage = "EndGame.png";


	//підгружання і настроювання картинки для фону меню
	sf::Image backMenuImage;
	sf::Texture backMenuTexture;
	sf::Sprite backMenuSprite;
	int backMenuImageH = 308;
	int backMenuImageW = 168;
	sf::Vector2f backMenuSize = { 168, 308 };
	backMenuImage.loadFromFile("images/" + fileNameBackMenuImage);
	backMenuTexture.loadFromImage(backMenuImage);
	backMenuSprite.setTexture(backMenuTexture);
	backMenuSprite.setScale(1.5, 1.5);

	//підгружання і настроювання кнопок для меню і деяких елементів гри
	sf::Image HUDImage;
	sf::Texture HUDTexture;
	sf::Sprite HUDSprite;
	int HUDImageH = 220;
	int HUDImageW = 344;
	HUDImage.loadFromFile("images/" + fileNameHUDImage);
	HUDTexture.loadFromImage(HUDImage);
	HUDSprite.setTexture(HUDTexture);

	sf::Image endHUDImage;
	sf::Texture endHUDTexture;
	sf::Sprite endHUDSprite;
	
	endHUDImage.loadFromFile("images/" + fileNameEndHUDImage);
	endHUDTexture.loadFromImage(endHUDImage);
	endHUDSprite.setTexture(endHUDTexture);
	
	//boss
	sf::Image bossImage;
	sf::Texture bossTexture;
	sf::Sprite bossSprite;
	int bossImageH = 64;
	int bossImageW = 47;
	bool bossactive = false;
	bossImage.loadFromFile("images/" + fileNameBossImage);
	bossTexture.loadFromImage(bossImage);
	bossSprite.setTexture(bossTexture);
	bossSprite.setTextureRect(sf::IntRect(0, 0, bossImageW, bossImageH));
	bossSprite.setPosition(8 * 64, 7 * 64);
	bossSprite.setOrigin(bossImageW / 2.f, bossImageH / 2.f);
	int bossDirection = 0;
	bool bossSpawn = false;
	bool bossEnd = false;
	float bossLife = 10.f;
	bossSprite.scale(4, 4);

	//MOM
	sf::Image MomImage;
	sf::Texture MomTexture;
	sf::Sprite MomSprite;
	int MomImageH = 45;
	int MomImageW = 45;
	MomImage.loadFromFile("images/" + fileNameMomImage);
	MomTexture.loadFromImage(MomImage);
	MomSprite.setTexture(MomTexture);
	MomSprite.setTextureRect(sf::IntRect(0, 0, MomImageW, MomImageH));
	MomSprite.setPosition(8 * 64, 7 * 64);
	MomSprite.setOrigin(MomImageW / 2.f, MomImageH / 2.f);
	MomSprite.scale(4, 4);

	//NPC
	sf::Image NPCImage;
	sf::Texture NPCTexture;
	sf::Sprite NPCSprite;
	int NPCImageH = 16;
	int NPCImageW = 16;
	bool NPCactive = false;
	float NPCSpeed = 350.f / 1000;
	NPCImage.loadFromFile("images/" + fileNameNPCImage);
	NPCTexture.loadFromImage(NPCImage);
	NPCSprite.setTexture(NPCTexture);
	NPCSprite.setTextureRect(sf::IntRect(32, 0, NPCImageW, NPCImageH));
	NPCSprite.setPosition(5*64, 3*64);
	NPCSprite.setOrigin(NPCImageW / 2.f, NPCImageH / 2.f);
	sf::Vector2f LastPositionNPC;
	int NPCDirection = 0;
	NPCSprite.scale(4, 4);
	bool NPCWASD = false;
	bool UseWASD = false;
	bool BossActiv = false;
	bool BossEND = false;
	

	//підгружання і настроювання картинки для гравця і самого гравця
    sf::Image playerImage;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int playerImageH = 64;
    int playerImageW = 64;
    int playerActiveSlide = 0;
	int playerLastActiveSlide = 0;
    int playerAnimationMaxSlide = 4;
    float playerSpeed = 350.f / 1000;
    directions playerDirection = STAND;
    sf::Vector2f playerStartPositionTopLeft = {5*64, 4*64};
    sf::Vector2f playerSlaidStartPositionTopLeft = {0, 0};
	sf::Vector2f LastPosition = {0, 0};
    playerImage.loadFromFile("images/" + fileNamePlayerImage);
    playerTexture.loadFromImage(playerImage);
	playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(64, 0, playerImageW, playerImageH));
    playerSprite.setPosition(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);
    playerSprite.setOrigin(playerImageW / 2.f, playerImageH / 2.f);
	int playerMaxHP = 3;
	float playerHP = 6;


	//підгружання і настроювання картинки для пуль і самих пуль
	sf::Image BulletImage;
	sf::Texture BulletTexture;
	sf::Sprite BulletSprite;
	int BulletActiv = 0;
	int BulletW = 8;
	int BulletH = 8;
	BulletImage.loadFromFile("images/" + fileNameBulletsImage);
	BulletTexture.loadFromImage(BulletImage);
	BulletSprite.setTexture(playerTexture);


	//підгружання і настроювання мапи
    sf::Image mapImage;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	mapImage.loadFromFile("images/" + fileNameMapImage);
	mapTexture.loadFromImage(mapImage);
	mapSprite.setTexture(mapTexture);

	sf::Image OutOfMapImage;
	sf::Texture OutOfMapTexture;
	sf::Sprite OutOfMapSprite;
	OutOfMapImage.loadFromFile("images/" + fileOutOfMapImage);
	OutOfMapTexture.loadFromImage(OutOfMapImage);
	OutOfMapSprite.setTexture(OutOfMapTexture);
	bool isOutOfMap = false;

	//підгружання і настроювання камери
    sf::View mainCamera;
    sf::Vector2f cameraSize;
    sf::Vector2f cameraPos;
    mainCamera.reset(sf::FloatRect(0, 0, screenW, screenH));
    mainCamera.setCenter(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);


	//зберігання шляхів до звуків і музики
	std::string fileNameMusic1 = "mus1.wav";
	std::string fileNameMusic2 = "mus2.wav";
	std::string fileNamerun2 = "run2.wav";
	std::string fileNamerun1 = "run1.wav";
	std::string fileNameBossMus = "BossMus.wav";
	std::string fileNameShoot = "shoot.wav";
	std::string fileNameDeath = "death.wav";

	////підгружання і настроювання музики
	sf::Music mus[3] = {};
	int musPlay = 0;
	mus[0].openFromFile("sounds/" + fileNameMusic1);
	mus[1].openFromFile("sounds/" + fileNameMusic2);
	mus[2].openFromFile("sounds/" + fileNameBossMus);
	mus[0].play();
	mus[0].setVolume(5);
	mus[1].setVolume(5);
	mus[2].setVolume(5);

	//підгружання і настроювання звуків
	sf::Sound ShootS;
	sf::SoundBuffer shoot;
	shoot.loadFromFile("sounds/" + fileNameShoot);
	ShootS.setBuffer(shoot);
	ShootS.setVolume(30);
	sf::Sound deathS;
	sf::SoundBuffer  death;
	death.loadFromFile("sounds/" + fileNameDeath);
	deathS.setBuffer(death);
	deathS.setVolume(80);
	sf::Sound run1S;
	sf::SoundBuffer  run1;
	run1.loadFromFile("sounds/" + fileNamerun1);
	run1S.setBuffer(run1);
	run1S.setVolume(100);
	sf::Sound run2S;
	sf::SoundBuffer  run2;
	run2.loadFromFile("sounds/" + fileNamerun2);
	run2S.setBuffer(run2);
	run2S.setVolume(100);


	// вороги
	std::list<Enemy*> enemys;
	std::list<Bullet*> bullets;
	std::list<BulletParticle*> bulletsParticle;
	std::list<BossBullet*> bossBullet;
	bool bossTriger = false;


	//text
	sf::RectangleShape backFont;
	backFont.setSize(sf::Vector2f(100.f, 25.f));
	backFont.setFillColor(sf::Color::Black);
	backFont.setPosition(NPCSprite.getPosition().x - backFont.getSize().x / 2, NPCSprite.getPosition().y - 75);

	std::string fileNameFont = "mainFont.ttf";

	sf::Font font;
	font.loadFromFile("fonts/" + fileNameFont);
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(25);
	text.setPosition(backFont.getPosition().x-40, backFont.getPosition().y-16.5);
	text.setString("touch E");



	//параметри для самої гри
    sf::Clock clock;
    float timer = 0.f;
	float timerS = 0.f;
    float playerAnimationTimer = 0.f;
    float StouneTimer = 0.f;
	float NPCtimer = 0.f;
	float newEnemy = 0.f;
	float playerdamage = 0.f;
	float NPCsecondT = 0.f;
	float NPCthirdT = 0.f;
    float dx = 0.f;
    float dy = 0.f;
	float nx = 0.f;
	float ny = 0.f;
	float timerRem; 
	bool timerTrue = false;
	float bossShot = 0.f;
	bool bossRoom = false;
	bool GameEnd = true;
	float activCadr = 0.f;


    while (myGame.isOpen())
    {
        sf::Event event;


        while (myGame.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                myGame.close();
            }

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					timerRem = timer;
					mus[musPlay].pause();
					switch (Menu(myGame, backMenuSprite, backMenuSize, HUDSprite, mainCamera))
					{
					case 0: {break;}
					case 1: {break;}
					case 2: {break;}
					case 3: {break;}
					case 4: {myGame.close(); break;}
					}
					mus[musPlay].play();
					timerTrue = true;
					
				}
			}
        }
		backFont.setPosition(NPCSprite.getPosition().x - backFont.getSize().x/2, NPCSprite.getPosition().y - 75);
		text.setPosition(backFont.getPosition().x+5, backFont.getPosition().y-4);

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (!NPCactive)
			{
				NPCactive = true;
				backFont.setSize(sf::Vector2f(200, 25));
				text.setString("Now I follow you");
			}
		}
		LastPositionNPC = NPCSprite.getPosition();
		if (NPCactive)
		{
			NPCsecondT += timer;
			nx = (float)NPCSpeed / 200 * sqrt(pow((NPCSprite.getPosition().x - playerSprite.getPosition().x), 2) + pow((NPCSprite.getPosition().y - playerSprite.getPosition().y), 2)) * (float)timer;
			ny = (float)NPCSpeed / 200 * sqrt(pow((NPCSprite.getPosition().x - playerSprite.getPosition().x), 2) + pow((NPCSprite.getPosition().y - playerSprite.getPosition().y), 2)) * (float)timer;
			if (NPCSprite.getPosition().x >= playerSprite.getPosition().x)
			{
				nx *= -1;
			}
			if (NPCSprite.getPosition().y >= playerSprite.getPosition().y)
			{
				ny *= -1;
			}
			if (NPCSprite.getPosition().y <= playerSprite.getPosition().y + 2 && NPCSprite.getPosition().y >= playerSprite.getPosition().y - 2)
			{
				ny = 0;
			}
			if (NPCSprite.getPosition().x <= playerSprite.getPosition().x + 2 && NPCSprite.getPosition().x >= playerSprite.getPosition().x - 2)
			{
				nx = 0;
			}
			if (nx > 0)
			{
				NPCDirection = 3;
			}
			if (nx < 0)
			{
				NPCDirection = 2;
			}
			if (ny > 0)
			{
				NPCDirection = 0;
			}
			if (ny < 0)
			{
				NPCDirection = 1;
			}
			if (NPCtimer / 500 > 1)
			{
				NPCtimer = 0.f;
			}
			NPCSprite.setTextureRect(sf::IntRect((int)(NPCtimer / 250) * NPCImageH + 32, NPCImageW * NPCDirection, NPCImageW, NPCImageH));
			NPCSprite.move(nx, ny);
			if ((map[(int)(NPCSprite.getPosition().y + 32) / 64][(int)(NPCSprite.getPosition().x + 30) / 64] != '0') && (map[(int)(NPCSprite.getPosition().y - 32) / 64][(int)(NPCSprite.getPosition().x + 30) / 64] != '0'))
			{
				NPCSprite.setPosition(LastPositionNPC.x, NPCSprite.getPosition().y);
			}
			if ((map[(int)(NPCSprite.getPosition().y - 32) / 64][(int)(NPCSprite.getPosition().x - 30) / 64] != '0') && (map[(int)(NPCSprite.getPosition().y + 32) / 64][(int)(NPCSprite.getPosition().x - 30) / 64] != '0'))
			{
				NPCSprite.setPosition(LastPositionNPC.x, NPCSprite.getPosition().y);
			}
			if ((map[(int)(NPCSprite.getPosition().y - 32) / 64][(int)(NPCSprite.getPosition().x + 30) / 64] != '0') && (map[(int)(NPCSprite.getPosition().y - 32) / 64][(int)(NPCSprite.getPosition().x - 30) / 64] != '0'))
			{
				NPCSprite.setPosition(NPCSprite.getPosition().x, LastPositionNPC.y);
			}
			if ((map[(int)(NPCSprite.getPosition().y + 32) / 64][(int)(NPCSprite.getPosition().x - 30) / 64] != '0') && (map[(int)(NPCSprite.getPosition().y + 32) / 64][(int)(NPCSprite.getPosition().x + 30) / 64] != '0'))
			{
				NPCSprite.setPosition(NPCSprite.getPosition().x, LastPositionNPC.y);
			}
			if (NPCsecondT > 3000 && !NPCWASD)
			{
				text.setString("Use   the   WASD");
				NPCWASD = true;
			}
		}


		for (auto index : enemys)
		{
			if (playerdamage >= 1000)
			{
				if (playerSprite.getPosition().x >= (index)->enemySprite.getPosition().x - 30 && playerSprite.getPosition().x <= (index)->enemySprite.getPosition().x + 30 && playerSprite.getPosition().y >= (index)->enemySprite.getPosition().y - 32 && playerSprite.getPosition().y <= (index)->enemySprite.getPosition().y + 32)
				{
					playerHP -= 1;
					playerdamage = 0;
				}
			}
		}

		for (auto index : bullets)
		{
			if ((index)->bossLifeRem < bossLife)
			{
				bossLife = (index)->bossLifeRem;

			}
		}


		std::list<Enemy*> toDeathErase;
		for (auto index : enemys)
		{
			if ((index)->enemyLife == 0)
			{
				toDeathErase.push_back(index);
				bulletsParticle.push_back(new BulletParticle("bulletParticle", "enemySet.png",  (index)->enemySprite.getPosition(), 0, 128, 64, 64));
				deathS.play();
			}
		}
		for (auto index : toDeathErase)
		{
			enemys.remove(index);
			delete index;
		}
		toDeathErase.clear();

		std::list<Bullet*> toErase;
		for (auto index : bullets)
		{
			if ((index)->BulletLife == 0)
			{
				bulletsParticle.push_back(new BulletParticle("bulletParticle", "bullets.png", (index)->BulletSprite.getPosition(), 40, 0, 8, 8));
				toErase.push_back(index);
			}
		}
		if (!toErase.empty())
		{
			for (auto index : toErase)
			{
				bullets.remove(index);
				delete index;
			}
			toErase.clear();
		}

		std::list<BossBullet*> toEraseBoss;
		for (auto index : bossBullet)
		{
			if ((index)->BulletLife == 0)
			{
				toEraseBoss.push_back(index);
			}
		}
		if (!toEraseBoss.empty())
		{
			for (auto index : toEraseBoss)
			{
				bossBullet.remove(index);
				delete index;
			}
			toEraseBoss.clear();
		}

		std::list<BulletParticle*> toEraseParticle;
		for (auto index : bulletsParticle)
		{
			if ((index)->BulletParticleLife == 0)
			{
				toEraseParticle.push_back(index);

			}
		}
		if (!toEraseParticle.empty())
		{
			for (auto index : toEraseParticle)
			{
				bulletsParticle.remove(index);
				delete index;
			}
			toEraseParticle.clear();
		}

		if (playerHP == 0)
		{
			EndGame(myGame, endHUDSprite, mainCamera);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			if ((mus[musPlay].getVolume() + 1) >= 100)
			{
				mus[musPlay].setVolume(100);
			}
			else
			{
				mus[musPlay].setVolume(mus[musPlay].getVolume() + 1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			if ((mus[musPlay].getVolume() - 1) <= 0)
			{
				mus[musPlay].setVolume(0);
			}
			else
			{
				mus[musPlay].setVolume(mus[musPlay].getVolume() - 1);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (musPlay != 2)
			{
				mus[0].play();
				mus[1].stop();
				musPlay = 0;
			}
			else
			{
				mus[0].play();
				mus[2].stop();
				musPlay = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (musPlay != 2)
			{
				mus[1].play();
				mus[0].stop();
				musPlay = 1;
			}
			else
			{
				mus[1].play();
				mus[2].stop();
				musPlay = 1;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (timerS > 300)
			{
				timerS = 0;
			}
			
			if (timerS == 0)
			{
				ShootS.play();
				bullets.push_back(new Bullet("bullet", "bullets.png", playerSprite.getPosition().x, playerSprite.getPosition().y, playerSprite.getPosition(), LastPosition, timer, playerLastActiveSlide));

				timerS = 0;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{

			playerSpeed = 1.f / 1000;
		}
		else
		{
			playerSpeed = 350.f / 1000;
		}
		LastPosition = playerSprite.getPosition();



		timer = clock.restart().asMilliseconds();
		if (timerTrue)
		{
			timer = timerRem;
			timerTrue = false;
		}
		timerS += timer;
		playerAnimationTimer += timer;
		NPCtimer += timer;
		newEnemy += timer;
		playerdamage += timer;
		bossShot += timer;

		
		if (newEnemy > 5000 && GameEnd)
		{
			int x, y;
			if (MapH == bossSizeMapH)
			{
				x = 9;
				y = 5;
			}
			else 
			{
				x = 42;
				y = 22;
			}
			enemys.push_back(new Enemy("enemy", "enemySet.png", x, y));
			newEnemy = 0;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (playerDirection != RIGTH)
			{
				playerDirection = RIGTH;
				playerSlaidStartPositionTopLeft = sf::Vector2f{0, 192};
				playerLastActiveSlide = 3;
			}
			playerActiveSlide = playerAnimationTimer / 125;
			if (playerActiveSlide >= playerAnimationMaxSlide)
			{
				playerAnimationTimer = 0.0;
				playerActiveSlide = 0;
			}
			float dx = playerSpeed * timer;
			float dy = 0.f;
			playerSprite.setTextureRect(sf::IntRect(playerSlaidStartPositionTopLeft.y, (playerSlaidStartPositionTopLeft.x + playerActiveSlide * playerImageW), playerImageW, playerImageH));
			playerSprite.move(dx, dy);
			playerStartPositionTopLeft = playerSprite.getPosition();
			mainCamera.setCenter(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (playerDirection != LEFT)
			{
				playerDirection = LEFT;
				playerSlaidStartPositionTopLeft = sf::Vector2f{0, 128};
				playerLastActiveSlide = 2;
			}
			playerActiveSlide = playerAnimationTimer / 125;
			if (playerActiveSlide >= playerAnimationMaxSlide)
			{
				playerAnimationTimer = 0.0;
				playerActiveSlide = 0;
			}
			float dx = -playerSpeed * timer;
			float dy = 0.f;
			playerSprite.setTextureRect(sf::IntRect(playerSlaidStartPositionTopLeft.y, (playerSlaidStartPositionTopLeft.x + playerActiveSlide * playerImageW), playerImageW, playerImageH));
			playerSprite.move(dx, dy);
			playerStartPositionTopLeft = playerSprite.getPosition();
			mainCamera.setCenter(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (playerDirection != UP)
			{
				playerDirection = UP;
				playerSlaidStartPositionTopLeft = sf::Vector2f{0, 64};
				playerLastActiveSlide = 1;
			}
			playerActiveSlide = playerAnimationTimer / 125;
			if (playerActiveSlide >= playerAnimationMaxSlide)
			{
				playerAnimationTimer = 0.0;
				playerActiveSlide = 0;
			}
			float dx = 0.f;
			float dy = -playerSpeed * timer;
			playerSprite.setTextureRect(sf::IntRect(playerSlaidStartPositionTopLeft.y, (playerSlaidStartPositionTopLeft.x + playerActiveSlide * playerImageW), playerImageW, playerImageH));
			playerSprite.move(dx, dy);
			playerStartPositionTopLeft = playerSprite.getPosition();
			mainCamera.setCenter(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (NPCWASD && !UseWASD)
			{
				text.setString("Use space for shoot");
				UseWASD = true;
			}
			if (playerDirection != DOWN)
			{
				playerDirection = DOWN;
				playerSlaidStartPositionTopLeft = sf::Vector2f{0, 0};
				playerLastActiveSlide = 0;
			}
			playerActiveSlide = playerAnimationTimer / 125;
			if (playerActiveSlide >= playerAnimationMaxSlide)
			{
				playerAnimationTimer = 0.0;
				playerActiveSlide = 0;
			}
			float dx = 0.f;
			float dy = playerSpeed * timer;
			playerSprite.setTextureRect(sf::IntRect(playerSlaidStartPositionTopLeft.y, (playerSlaidStartPositionTopLeft.x + playerActiveSlide * playerImageW), playerImageW, playerImageH));
			playerSprite.move(dx, dy);
			playerStartPositionTopLeft = playerSprite.getPosition();
			mainCamera.setCenter(playerStartPositionTopLeft.x, playerStartPositionTopLeft.y);
		}
		if (playerSprite.getPosition() != LastPosition)
		{
			if (rand() % 2 == 1)
			{
				run1S.play();
			}
			else
			{
				run2S.play();
			}
		}

		if (UseWASD && !BossActiv)
		{
			NPCthirdT += timer;
			if (NPCthirdT > 2000)
			{
				text.setString("Find out my Mom");
			}
			if (playerSprite.getPosition().y > 21 * 64 && playerSprite.getPosition().x > 18 * 64)
			{
				text.setString("Touch  this  cube");
			}
		}
		if (BossActiv && !BossEND)
		{
			text.setString("KILL       HIM");
		}
		if (BossEND)
		{
			text.setString("Continue looking for");
		}
		if (BossEND && playerSprite.getPosition().y < 8*64 && playerSprite.getPosition().x > 41)
		{
			text.setString("It    is    her");
			playerSprite.setPosition(42.5f * 64.f, 7 * 64);
			NPCSprite.setPosition(41.5f * 64.f, 7 * 64);
			myGame.clear();
			for (int y = 0; y < MapH; y++)
				for (int x = 0; x < MapW - 1; x++)
				{
					switch (map[y][x])
					{
					case '1': {mapSprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); break; }
					case '2': {mapSprite.setTextureRect(sf::IntRect(128, 0, 64, 64)); break; }
					case '3': {mapSprite.setTextureRect(sf::IntRect(128, 128, 64, 64)); break; }
					case '4': {mapSprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); break; }
					case '5': {mapSprite.setTextureRect(sf::IntRect(64, 0, 64, 64)); break; }
					case '6': {mapSprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); break; }
					case '7': {mapSprite.setTextureRect(sf::IntRect(64, 128, 64, 64)); break; }
					case '8': {mapSprite.setTextureRect(sf::IntRect(128, 64, 64, 64)); break; }
					case '0': {mapSprite.setTextureRect(sf::IntRect(64, 64, 64, 64)); break; }
					case '<': {mapSprite.setTextureRect(sf::IntRect(192, 64, 64, 64)); break; }
					case '>': {mapSprite.setTextureRect(sf::IntRect(192, 0, 64, 64)); break; }
					case '{': {mapSprite.setTextureRect(sf::IntRect(256, 64, 64, 64)); break; }
					case '}': {mapSprite.setTextureRect(sf::IntRect(256, 0, 64, 64)); break; }
					case 'T': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
					case 'M': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
					case 'W': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
					case ' ': {OutOfMapSprite.setPosition(x * 64.f, y * 64.f);
						myGame.draw(OutOfMapSprite);
						isOutOfMap = true;
						break; }
					}
					if (!isOutOfMap)
					{
						mapSprite.setPosition(x * 64.f, y * 64.f);
					}
					else
					{
						isOutOfMap = false;
					}
					myGame.draw(mapSprite);
				}
			HUDSprite.setScale(1, 1);
			for (int i = 0; i < playerMaxHP; i++)
			{
				if ((playerHP - i * 2) / 2.f >= 1)
				{
					HUDSprite.setTextureRect(sf::IntRect(0, 0, 48, 44));
				}
				else if ((playerHP - i * 2) / 2.f < 1 && (playerHP - i * 2) / 2.f > 0)
				{
					HUDSprite.setTextureRect(sf::IntRect(0, 44, 48, 44));
				}
				else
				{
					HUDSprite.setTextureRect(sf::IntRect(0, 88, 48, 44));
				}
				HUDSprite.setPosition(cameraPos.x - (cameraSize.x / 2 - 4) + i * 52, cameraPos.y - (cameraSize.y / 2 - 4));
				myGame.draw(HUDSprite);
			}
			myGame.draw(backFont);
			myGame.draw(text);
			myGame.draw(NPCSprite);
			myGame.draw(playerSprite);
			if (bossSpawn)
			{
				myGame.draw(bossSprite);
			}
			if (BossEND)
			{
				myGame.draw(MomSprite);
			}
			myGame.display();
			CutScene(myGame, playerSprite, NPCSprite, text, backFont, map, mapSprite, MapW, MapH, MomSprite, OutOfMapSprite, isOutOfMap, cameraPos, cameraSize, mainCamera);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mainCamera.zoom(1.1f);
			cameraSize = mainCamera.getSize();
			if (cameraSize.x > screenW) cameraSize.x = screenW;
			if (cameraSize.y > screenH) cameraSize.y = screenH;
			mainCamera.setSize(cameraSize);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mainCamera.zoom(0.9f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mainCamera.rotate(1.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mainCamera.rotate(-1.f);
		}

		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'T')
		{
			bossRoom = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'T')
		{
			bossRoom = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'T')
		{
			bossRoom = true;
		}
		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'T')
		{
			bossRoom = true;
		}
		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'W')
		{
			bossTriger = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'W')
		{
			bossTriger = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'W')
		{
			bossTriger = true;
		}
		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'W')
		{
			bossTriger = true;
		}
		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'M')
		{
			bossEnd = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'M')
		{
			bossEnd = true;
		}
		if (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] == 'M')
		{
			bossEnd = true;
		}
		if (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] == 'M')
		{
			bossEnd = true;
		}

		if (bossEnd)
		{

			map = mapSizeChange(map, afterBossSizeMapH, afterBossSizeMapW, MapH);
			MapH = afterBossSizeMapH;
			MapW = afterBossSizeMapW;
			for (int y = 0; y < MapH; y++)
			{
				for (int x = 0; x < MapW - 1; x++)
				{
					map[y][x] = map3[y][x];
				}
			}
			playerSprite.setPosition(42 * 64, 20 * 64);
			playerSlaidStartPositionTopLeft = playerSprite.getPosition();
			NPCSprite.setPosition(42 * 64, 20 * 64);
			std::list<Enemy*> toErase;
			for (auto index : enemys)
			{
				toErase.push_back(index);
			}
			for (auto index : toErase)
			{
				enemys.remove(index);
				delete index;
			}
			toErase.empty();
			bossEnd = false;
			GameEnd = false;
			BossEND = true;
			MomSprite.setPosition(38 * 64, 3 * 64);
		}

		if (bossRoom)
		{
			for (int y = 0; y < MapH; y++)
				for (int x = 0; x < MapW - 1; x++)
				{
					map[y][x] = map4[y][x];
				}
			bossRoom = false;
		}

		if (bossTriger == true)
		{
			mus[2].play();
			mus[musPlay].stop();
			musPlay = 2;
			map = mapSizeChange(map, bossSizeMapH, bossSizeMapW, MapH);
			MapW = bossSizeMapW;
			MapH = bossSizeMapH;
			playerSprite.setPosition(64 * 8, 64 * 12);
			NPCSprite.setPosition(MapH * 32, (MapW - 1) * 32);

			for (int y = 0; y < MapH; y++)
				for (int x = 0; x < MapW - 1; x++)
					{
					map[y][x] = map2[y][x];
				}
			std::list<Enemy*> toErase;
			for (auto index : enemys)
			{
				toErase.push_back(index);
			}
			for (auto index : toErase)
			{
				enemys.remove(index);
				delete index;
			}
			toErase.empty();

			BossActiv = true;
			bossSpawn = true;
			bossTriger = false;
		}

		if (BossEND)
		{
			activCadr += timer;
			if (activCadr / 200 > 4)
			{
				activCadr = 0.f;
			}
			MomSprite.setTextureRect(sf::IntRect(((int)(activCadr / 200) * MomImageW), 0, MomImageW, MomImageH));
		}

		if (playerdamage >= 400)
		{
			if (playerSprite.getPosition().x >= bossSprite.getPosition().x - bossImageW / 2 * 4 && playerSprite.getPosition().x <= bossSprite.getPosition().x + bossImageW / 2 * 4 && playerSprite.getPosition().y >= bossSprite.getPosition().y - bossImageH / 2 * 4 && playerSprite.getPosition().y <= bossSprite.getPosition().y + bossImageH / 2 * 4)
			{
				playerHP -= 1;
				playerdamage = 0;
			}
		}

		if (bossSpawn)
		{
			if ((int)bossLife == 0)
			{
				bossSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
				MapH = bossSizeMapH;
				MapW = bossSizeMapW;
				bossSprite.setPosition(50, 50);
				for (int y = 0; y < MapH; y++)
				{
					for (int x = 0; x < MapW - 1; x++)
					{
						map[y][x] = map5[y][x];
					}
				}
				bossSpawn = false;

			}
			if (bossShot > 500)
			{
				bossBullet.push_back(new BossBullet("bullet", "bullets.png", bossSprite.getPosition(), playerSprite.getPosition()));
				bossShot = 0;
				for (auto index : bossBullet)
				{
					if ((index)->LifeRem < playerHP)
					{
						playerHP--;
					}
				}
			}
		}

		if ((map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] != '0') && (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] != '0'))
		{
			playerSprite.setPosition(LastPosition.x, playerSprite.getPosition().y);
		}
		if ((map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] != '0') && (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] != '0'))
		{
			playerSprite.setPosition(LastPosition.x, playerSprite.getPosition().y);
		}
		if ((map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] != '0') && (map[(int)(playerSprite.getPosition().y - 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] != '0'))
		{
			playerSprite.setPosition(playerSprite.getPosition().x, LastPosition.y);
		}
		if ((map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x - 30) / 64] != '0') && (map[(int)(playerSprite.getPosition().y + 32) / 64][(int)(playerSprite.getPosition().x + 30) / 64] != '0'))
		{
			playerSprite.setPosition(playerSprite.getPosition().x, LastPosition.y);
		}


		cameraSize = mainCamera.getSize();
		cameraPos = playerStartPositionTopLeft;
		if (cameraPos.x < cameraSize.x / 2)  cameraPos.x = cameraSize.x / 2;
		if (cameraPos.x > ((MapW - 1) * 64) - cameraSize.x / 2) cameraPos.x = ((MapW - 1) * 64) - cameraSize.x / 2;
		if (cameraPos.y < cameraSize.y / 2)  cameraPos.y = cameraSize.y / 2;
		if (cameraPos.y > ((MapH) * 64) - cameraSize.y / 2) cameraPos.y = ((MapH) * 64) - cameraSize.y / 2;
		mainCamera.setCenter(cameraPos);

		myGame.setView(mainCamera);
        myGame.clear();
        for (int y = 0; y < MapH; y++)
            for (int x = 0; x < MapW - 1; x++)
            {
                switch (map[y][x])
                {
                case '1': {mapSprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); break; }
                case '2': {mapSprite.setTextureRect(sf::IntRect(128, 0, 64, 64)); break; }
                case '3': {mapSprite.setTextureRect(sf::IntRect(128, 128, 64, 64)); break; }
                case '4': {mapSprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); break; }
                case '5': {mapSprite.setTextureRect(sf::IntRect(64, 0, 64, 64)); break; }
                case '6': {mapSprite.setTextureRect(sf::IntRect(0, 64, 64, 64)); break; }
                case '7': {mapSprite.setTextureRect(sf::IntRect(64, 128, 64, 64)); break; }
                case '8': {mapSprite.setTextureRect(sf::IntRect(128, 64, 64, 64)); break; }
                case '0': {mapSprite.setTextureRect(sf::IntRect(64, 64, 64, 64)); break; }
                case '<': {mapSprite.setTextureRect(sf::IntRect(192, 64, 64, 64)); break; }
                case '>': {mapSprite.setTextureRect(sf::IntRect(192, 0, 64, 64)); break; }
                case '{': {mapSprite.setTextureRect(sf::IntRect(256, 64, 64, 64)); break; }
                case '}': {mapSprite.setTextureRect(sf::IntRect(256, 0, 64, 64)); break; }
				case 'T': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case 'M': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case 'W': {mapSprite.setTextureRect(sf::IntRect(256, 128, 64, 64)); break; }
				case ' ': {OutOfMapSprite.setPosition(x * 64.f, y * 64.f);
						   myGame.draw(OutOfMapSprite);
						   isOutOfMap = true;
						   break; }
                }
				if (!isOutOfMap)
				{
					mapSprite.setPosition(x * 64.f, y * 64.f);
				}
				else
				{
					isOutOfMap = false;
				}
                myGame.draw(mapSprite);
            }
		HUDSprite.setScale(1, 1);
		for (int i = 0; i < playerMaxHP; i++)
		{
			if ((playerHP - i * 2) / 2.f >= 1)
			{
				HUDSprite.setTextureRect(sf::IntRect(0, 0, 48, 44));
			}
			else if ((playerHP - i * 2) / 2.f < 1 && (playerHP - i * 2) / 2.f > 0)
			{
				HUDSprite.setTextureRect(sf::IntRect(0, 44, 48, 44));
			}
			else
			{
				HUDSprite.setTextureRect(sf::IntRect(0, 88, 48, 44));
			}
			HUDSprite.setPosition(cameraPos.x - (cameraSize.x / 2 - 4) + i * 52, cameraPos.y - (cameraSize.y / 2 - 4));
			myGame.draw(HUDSprite);
		}
		myGame.draw(backFont);
		myGame.draw(text);
		myGame.draw(NPCSprite);
        myGame.draw(playerSprite);
		if (bossSpawn)
		{
			myGame.draw(bossSprite);
		}
		if (BossEND)
		{
			myGame.draw(MomSprite);
		}

		for (auto index = bossBullet.begin(); index != bossBullet.end(); index++)
		{
 			(*index)->Launch(myGame, map, playerHP, playerSprite);
		}
		for (auto index = bullets.begin(); index != bullets.end(); index++)
		{
			(*index)->Fly(myGame, timer, map, enemys, bossLife, bossSprite);
		}
		for (auto index = enemys.begin(); index != enemys.end(); index++)
		{
			(*index)->Show(myGame, playerSprite.getPosition(), timer, map);
		}
		for (auto index = bulletsParticle.begin(); index != bulletsParticle.end(); index++)
		{
			(*index)->Activ(myGame, timer, map);
		}
        myGame.display();
    }


}



