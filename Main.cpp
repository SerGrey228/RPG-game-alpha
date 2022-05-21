#include <SFML/Graphics.hpp>
#include <iostream> 
#include <fstream>
#include <string>
#include "TmxLevel.h"
#include "Player.h"
#include "NPC.h"
#include "GameView.h"

using namespace sf;

class Menu {
private:
	bool isMenu;
	int NumMenu;
	Texture menuTexture, exitTexture, continueTexture, GameOverTexture;
public:
	Sprite menuSprite, exitSprite, continueSprite, GameOverSprite;
	Menu() {
		isMenu = false; NumMenu = 0;
		menuTexture.loadFromFile("images/Menu.png");
		exitTexture.loadFromFile("images/Menu.png");
		continueTexture.loadFromFile("images/Menu.png");
		GameOverTexture.loadFromFile("images/Menu.png");
		menuSprite.setTexture(menuTexture);
		exitSprite.setTexture(exitTexture);
		continueSprite.setTexture(continueTexture);
		GameOverSprite.setTexture(GameOverTexture);
		menuSprite.setTextureRect(IntRect(0, 57, 302, 218));
		continueSprite.setTextureRect(IntRect(1, 33, 62, 16));
		exitSprite.setTextureRect(IntRect(1, 18, 30, 13));
		GameOverSprite.setTextureRect(IntRect(127, 1, 154, 33));
	}
};

////////////////////////////////////////////////////////////////////////////////////////

void LevelSwitching(int& NumberLevel, TmxLevel& lvl) {
	if (NumberLevel == 1) { lvl.LoadFromFile("levels/Level1.tmx"); }
	if (NumberLevel == 2) { lvl.LoadFromFile("levels/Level2.tmx"); }
	if (NumberLevel == 3) { lvl.LoadFromFile("levels/Level3.tmx"); }
	if (NumberLevel == 4) { lvl.LoadFromFile("levels/Level4.tmx"); }
	if (NumberLevel == 5) { lvl.LoadFromFile("levels/Level5.tmx"); }
}

bool StartGame(RenderWindow& window, int& NumberLevel, bool &spawnRobbers, bool &DopQuest) {
	float timerEnemy = 0; // таймер для отключения спавна разбойников
	sf::Texture textureMenu;
	sf::Sprite spriteMenu;
	textureMenu.loadFromFile("images/DialogWindow.png");
	spriteMenu.setTexture(textureMenu);
	spriteMenu.setTextureRect(sf::IntRect(7, 170, 285, 267));

	Clock clock;
	window.setFramerateLimit(30);

	TmxLevel lvl;
	LevelSwitching(NumberLevel, lvl);

	sf::Vector2f setCoordPlayerLvl;
	if (NumberLevel == 1) { setCoordPlayerLvl.x = 60, setCoordPlayerLvl.y = 100; }
	if (NumberLevel == 2) { setCoordPlayerLvl.x = 70, setCoordPlayerLvl.y = 100; }
	if (NumberLevel == 3) { setCoordPlayerLvl.x = 60, setCoordPlayerLvl.y = 230; }
	if (NumberLevel == 4) { setCoordPlayerLvl.x = 90, setCoordPlayerLvl.y = 120; }
	if (NumberLevel == 5) { setCoordPlayerLvl.x = 40, setCoordPlayerLvl.y = 230; }

	Menu menu;
	Player player("Archer.png", lvl, 0.1, setCoordPlayerLvl.x, setCoordPlayerLvl.y, 30, 28);
	Medallion medallion(400, 100, 18, 22);
	EnemyWeak enemyWeak("Robber.png", 300, 400, 25, 31);
	EnemyHeavy enemyHeavy("Robber.png", 100, 400, 25, 31);
	Slime1 slime1("Slime.png", 400, 200, 24, 31);
	Slime2 slime2("Slime.png", 400, 300, 24, 31);
	OldMan old("Old man", 352, 124, 32, 32);
	Tradesman tradesman(50, 50, 36, 32);
	Arrow arrow(lvl, 32, 32, 31, 6);
	GameView view;
	Tutorial tutorial;
	InteractionMark interectivMark;

	while (window.isOpen()) {
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		Vector2f PlayerCoord; //x и y координаты персонажа в векторной форме
		PlayerCoord.x = player.getX(); PlayerCoord.y = player.getY();

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					if (!arrow.life) {
						arrow.setCoordMouse(pos.x, pos.y);
						arrow.setLife(true);
					}
				}
			}
		}

		if (NumberLevel == 4 && spawnRobbers == true) {
			enemyWeak.update(window, time, PlayerCoord, arrow.getRect());
			enemyHeavy.update(window, time, PlayerCoord, arrow.getRect());
		}
		if (NumberLevel == 5) {
			slime1.update(window, time, PlayerCoord, arrow.getRect());
			slime2.update(window, time, PlayerCoord, arrow.getRect());
		}
		medallion.medallionQuest(player.getRect());
		tradesman.Animation(time);
		player.update(time, NumberLevel, tradesman.StopPlayer);
		player.Collision(NumberLevel, time, enemyWeak.getRect(), enemyHeavy.getRect(), slime1.getRect(), slime2.getRect());
		arrow.update(window, time, pos, PlayerCoord);
		arrow.Collision(time);
		view.RenderDialogWindow(NumberLevel, window, player.getX(), player.getY(), time);
		tradesman.RenderDialogWindow(NumberLevel, window, player.getTrade(), time);
		if (tradesman.getDialogConsoleOpen() == true) { 
			DopQuest = true;
		}
		else if (medallion.getLife() == false) {
			DopQuest = false;
		}
		tutorial.QuestionMarkAnimation(time);
		tutorial.TutprialWindow(player.getActivationTutrialWindow(), PlayerCoord, window); //открывает окно обучения
		player.setPlayerStop1(view.StopPlayer);	//останавливает персонажа, когда открыто диалоговое окно
		player.setPlayerStop2(tutorial.getActivationWindow());  //останавливает персонажа, когда открыто окно обучения
		player.setActivationTutorialWindow(tutorial.getActivationWindow());
		interectivMark.ActivationMark(player.getActivationMark(), player.getX(), player.getY());

		if (enemyWeak.life == false && enemyHeavy.life == false) { //отключает спавн разбойников, когда таймер больше 2 сек.
			timerEnemy += time;
			if (timerEnemy > 2000) {
				spawnRobbers = false;
			}
		}

		//////////перемещение по уровням//////////

		if (view.counterDialogs == 1) { NumberLevel = 2; return true; }
		if (player.SwitchLevel == true && NumberLevel == 2 && !player.Door2) { NumberLevel = 3; return true; }
		if (player.SwitchLevel == true && NumberLevel == 3) { NumberLevel = 2; return true; }
		if (player.SwitchLevel == true && NumberLevel == 2 && player.Door2) { NumberLevel = 4; return true; }
		if (player.SwitchLevel == true && NumberLevel == 4 && player.Door2) { NumberLevel = 2; return true; }
		if (player.SwitchLevel == true && NumberLevel == 4 && player.Door3) { NumberLevel = 5; return true; }
		if (player.SwitchLevel == true && NumberLevel == 5 && player.Door3) { NumberLevel = 4; return true; }


		if (Keyboard::isKeyPressed(Keyboard::N)) { NumberLevel++; return true; }//новый уровень
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; } //перезагружаем игру
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; } //выходим из игры

		//////////отрисовка//////////

		window.clear();

		lvl.Draw(window);
		view.DialogConsole(window, player.getX(), player.getY());
		tradesman.DialogConsole(window, PlayerCoord);
		if (NumberLevel == 5 && medallion.getLife() == true) { window.draw(medallion.sprite); }
		if (NumberLevel == 5) {
			window.draw(slime1.sprite);
			window.draw(slime2.sprite);
		}
		if (NumberLevel == 4 && spawnRobbers == true) {
			window.draw(enemyWeak.sprite);
			window.draw(enemyHeavy.sprite);
			enemyHeavy.Massage(window);
		}
		window.draw(arrow.sprite); 
		player.DrawFeature(window, NumberLevel, spawnRobbers, DopQuest);
		arrow.ArrowIndicator(PlayerCoord, window);
		if (NumberLevel == 1) {
			window.draw(old.sprite);
			window.draw(tutorial.questionMarkSprite);
			window.draw(tutorial.tutorialMarkSprite);
		}
		if (player.getActivationMark()) { window.draw(interectivMark.spriteMark); }
		window.draw(player.sprite);
		if (NumberLevel == 3) {
			window.draw(tradesman.sprite);
		}
		if (NumberLevel == 1) { window.draw(tutorial.tutuorialWindowSprite); window.draw(tutorial.closeBattomSprite); }
		if (player.getLife() == false) {
			spriteMenu.setPosition(PlayerCoord.x - 100, PlayerCoord.y - 150);
			player.setMomeSpeed(0);
			window.draw(spriteMenu);
		}
		window.display();
	}
}

void GameRunning(RenderWindow& window, int NumberLevel, bool spawnRobbers, bool &DopQuest) { //функция перезагружает игру
	if (StartGame(window, NumberLevel, spawnRobbers, DopQuest)) {
		GameRunning(window, NumberLevel, spawnRobbers, DopQuest);	//рекурсия
	}
}

int main()
{
	int NumberLevel = 1;
	bool spawnRobbers = true;
	bool DopQuest = false;
	RenderWindow window(VideoMode(1000, 1000), "Game!");
	GameRunning(window, NumberLevel, spawnRobbers, DopQuest);
	return 0;
}