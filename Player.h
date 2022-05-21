#pragma once
#include <SFML/Graphics.hpp>
#include "TmxLevel.h"
#include <iostream>
#include <vector>

class Player{
private:
	float x, y, dx, dy, height, width, speed, moveSpeed, timer;
	sf::Image image; sf::Texture texture; sf::View view;
	std::vector<TmxObject>obj; std::vector<TmxObject>objDop; std::vector<TmxObject>objDialog; std::vector<TmxObject>objDop2;
	std::vector<TmxObject>objDop3;
	float currentFrame;
	bool PlayerStop1, PlayerStop2, PlayerStop3, life;
	bool ActivationInterectivMark; bool ActivationTutorialWindow;
	bool switchDialog;
	int HP, counter;
	enum class direction {
		left,
		right,
		up,
		down,
		stay
	};
	sf::Font font;
	sf::Text HPText;
	sf::Text missionText;
	sf::Text missionDopText;
public:
	bool SwitchLevel; bool Door2; bool Door3;
	direction playerDirection;
	sf::Sprite sprite;
	Player(sf::String F, TmxLevel lvl, float Speed, float X, float Y, float H, float W);
	void Move(float time);
	void Animation(float time);
	void update(float time, int Numberlevel, bool _StopPlayer);
	void Collision(int NumberLevel, float time, sf::FloatRect enemyWeakRect, sf::FloatRect enemyHeavyRect,
		sf::FloatRect slime1Rect, sf::FloatRect slime2Rect);
	void DrawFeature(sf::RenderWindow& window, int NumberLevel, float spawnRobbers, bool DopQuest); // выводит характеристики персонажа
	sf::FloatRect getRect();
	float getX();
	float getY();
	float getHeight();
	float getWigth();
	bool getActivationMark();
	bool getActivationTutrialWindow();
	bool getTrade();
	bool getLife();
	void setPlayerStop1(bool _stop1);
	void setPlayerStop2(bool _stop2);
	void setActivationTutorialWindow(bool _ActivationTutorialWindow);
	void setMomeSpeed(float _MoveSpeed);
};

////////////////////////////////////////////////////////// класс для стрелы ////////////////////////////////////////////////////

class Arrow {
private:
	float x, y, h, w, speed, distance, dX, dY;
	float dx, dy, CoordMouseX, CoordMouseY, timer, collisionTimer;
	float rotation; //переменная для поворота спрайта в сторону курсора
	int direction;
	bool collActivationTimer;
	sf::Image image; sf::Texture texture;
	sf::Image indicatorImage; sf::Texture indicatorTexture;
	std::vector<TmxObject> obj;
public:
	sf::Sprite sprite; sf::Sprite indicatorSprite;
	bool life;
	Arrow(TmxLevel lvl, float _x, float _y, float H, float W);
	void update(sf::RenderWindow& window, float time, sf::Vector2f pos, sf::Vector2f PlayerCoord);
	void Direction();
	void Collision(float time);
	void Rotation(sf::Vector2f pos);
	void ArrowIndicator(sf::Vector2f PlayerCoord, sf::RenderWindow& window);
	sf::FloatRect getRect();
	void setLife(bool Life);
	void setCoordMouse(float coordX, float coordY);
};