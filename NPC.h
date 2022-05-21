#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "TmxLevel.h"

class Medallion {
private:
	float x, y, h, w;
	sf::Image image; sf::Texture texture;
	bool life;
public:
	Medallion(float X, float Y, float H, float W);
	sf::Sprite sprite;
	sf::FloatRect getRect();
	void medallionQuest(sf::FloatRect PlayerRect);
	bool getLife();
};

class Tradesman {
private:
	float x, y, height, width, currentFrame;
	sf::Image image; sf::Texture texture;
	bool tradesmanDialog;
	bool dialogConsoleOpen;
	float timer; //таймер для переключения диалога
	int counter; //для взаимодействия со строками в диалогах

	sf::Image imageDialogWindow; sf::Texture textureDialogWindow; sf::Sprite DialogWindow;
	sf::Text ContinueText;
	sf::Font font; 
	sf::Text dialogText1; sf::Text dialogText2; sf::Text dialogText3;
public:
	bool StopPlayer;
	int counterDialogs; //счетчик всех диалогов с дедом(не больше одного)
	sf::Sprite sprite;
	Tradesman(float X, float Y, float H, float W);
	void RenderDialogWindow(int NumberLevel, sf::RenderWindow& window, bool switchDialog, float time);
	void ActivationDialog(bool switchDialog);
	void TradesmanDialog(float time);
	void DialogConsole(sf::RenderWindow& window, sf::Vector2f PlayerCoord);
	void Animation(float time);
	bool getDialogConsoleOpen();
};

class OldMan {
private:
	float x, y, height, width;
	sf::String name;
	sf::Image image; sf::Texture texture;
public:
	sf::Sprite sprite;
	OldMan(sf::String Name, float X, float Y, float H, float W);
	float getOldX();
	float getOldY();
};

class Tutorial {
private:
	std::vector<TmxObject> obj;
	float currentFrame; bool ActivationWindow;
	sf::Image questionMarkImage; sf::Texture queationMarkTexture;
	sf::Image tutorialMarkImage; sf::Texture tutorialMarkTexture;
	sf::Image tutorialWindowImage; sf::Texture tutorialWindowTexture;
	sf::Texture closeBattomTexture;
public:
	sf::Sprite questionMarkSprite; sf::Sprite tutorialMarkSprite; sf::Sprite tutuorialWindowSprite; sf::Sprite closeBattomSprite;
	Tutorial();
	void QuestionMarkAnimation(float time);
	void TutprialWindow(bool _ActivationWindow, sf::Vector2f PlayerCoord, sf::RenderWindow& window);
	bool getActivationWindow();
};

class Enemy {
public:
	sf::Sprite sprite;
	bool life;
protected:
	float x, y, h, w, speed, dx, dy, distance, rotation, currentFrame, timer;
	bool isMove, timerDamage;
	int HP, counter;
	enum class direction {
		left,
		right,
		up,
		down,
		stay
	};
	direction EnemyWeakDirection;
	sf::Image image;
	sf::Texture texture;
	Enemy(sf::String F, float X, float Y, float H, float W);
};

class EnemyHeavy : public Enemy {
private:
	int randNumber;
	bool callMessage;
	sf::Font font;
	sf::Text text;
public:
	EnemyHeavy(sf::String F, float X, float Y, float H, float W);
	void update(sf:: RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect);
	void Collision(sf::FloatRect ArrowRect);
	void Rotation(sf::Vector2f PlayerCoord, float time);
	void Animation(float time);
	void Massage(sf::RenderWindow& window);
	sf::FloatRect getRect();
};

class EnemyWeak : public Enemy {
public:
	EnemyWeak(sf::String F, float X, float Y, float H, float W);
	void update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect);
	void Collision(sf::FloatRect ArrowRect);
	void Rotation(sf::Vector2f PlayerCoord, float time);
	void Animation(float time);
	sf::FloatRect getRect();
};

class Slime1 : public Enemy {
public:
	Slime1(sf::String F, float X, float Y, float H, float W);
	void update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect);
	void Collision(sf::FloatRect ArrowRect);
	void Rotation(sf::Vector2f PlayerCoord, float time);
	void Animation(float time);
	sf::FloatRect getRect();
};

class Slime2 : public Enemy {
public:
	Slime2(sf::String F, float X, float Y, float H, float W);
	void update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect);
	void Collision(sf::FloatRect ArrowRect);
	void Rotation(sf::Vector2f PlayerCoord, float time);
	void Animation(float time);
	sf::FloatRect getRect();
};