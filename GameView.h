#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class GameView {
private:
	sf::Image imageDialogWindow; sf::Texture textureDialogWindow; sf::Sprite DialogWindow;
	sf::View view;
	sf::Text ContinueText;
	sf::Font font; sf::Text dialogText1; sf::Text dialogText2; sf::Text dialogText3;
	bool oldManDialog; bool dialogConsoleOpen;
	float distance; float timer; //таймер для переключения диалога
	int counter; //для взаимодействия со строками в диалогах
public:
	int counterDialogs; //счетчик всех диалогов с дедом(не больше одного)
	bool StopPlayer;
	GameView();
	void RenderDialogWindow(int NumberLevel, sf::RenderWindow& window, float PlayerX, float PlayerY, float time);
	void DialogConsole(sf::RenderWindow& window, float PlayerX, float PlayerY);
	void ActivationDialog(float PlayerX, float PlayerY);
	void OldManDialog(float PlayerX, float PlayerY, float time);
	bool NextLevel() { return true; };
};

class InteractionMark {
private:
	bool MarkSwitching;
	sf::Image imageMark; sf::Texture textureMark;
public:
	sf::Sprite spriteMark;
	InteractionMark();
	void ActivationMark(bool _activationMark, float X, float Y);
};