#include "NPC.h"

Medallion::Medallion(float X, float Y, float H, float W) {
	x = X, y = Y, h = H, w = W;
	life = true;
	image.loadFromFile("images/TileMap.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(231, 230, 16, 22));
	sprite.setPosition(x, y);
}

void Medallion::medallionQuest(sf::FloatRect PlayerRect) {
	if (life) {
		if (getRect().intersects(PlayerRect)) {
			life = false;
		}
	}
}

bool Medallion::getLife() {
	return life;
}

sf::FloatRect Medallion::getRect() { 
	return sf::FloatRect(x, y, w, h);
}

Tradesman::Tradesman(float X, float Y, float H, float W) {
	x = X; y = Y; height = H; width = W;
	currentFrame = 0; counter = 0; counterDialogs = 0; timer = 0;
	StopPlayer = false; tradesmanDialog = false; dialogConsoleOpen = false;
	image.loadFromFile("images/OldMan.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 33, 32, 36));
	sprite.setPosition(x, y);

	imageDialogWindow.loadFromFile("images/DialogWindow.png");
	imageDialogWindow.createMaskFromColor(sf::Color(255, 255, 255));
	textureDialogWindow.loadFromImage(imageDialogWindow);
	DialogWindow.setTexture(textureDialogWindow);
	DialogWindow.setTextureRect(sf::IntRect(2, 7, 196, 125));
	DialogWindow.setPosition(-123, 0);

	font.loadFromFile("fonts/time.ttf");
	ContinueText.setFont(font); ContinueText.setCharacterSize(20); ContinueText.setScale(0.5, 0.5);
	ContinueText.setString("Press Spase to be continue");
	dialogText1.setFont(font); dialogText1.setCharacterSize(22); dialogText1.setScale(0.5, 0.5);
	dialogText2.setFont(font); dialogText2.setCharacterSize(20); dialogText2.setScale(0.5, 0.5);
	dialogText3.setFont(font); dialogText3.setCharacterSize(20); dialogText3.setScale(0.5, 0.5);
}

void Tradesman::RenderDialogWindow(int NumberLevel, sf::RenderWindow& window, bool switchDialog, float time) {
	if (NumberLevel == 3) {
		ActivationDialog(switchDialog);
		if (tradesmanDialog) {
			dialogConsoleOpen = true;
			StopPlayer = true;
			TradesmanDialog(time);
			if (counter > 4) { counterDialogs = 1; } //кол-во переключений диалогов
		}
		else {
			dialogConsoleOpen = false;
			StopPlayer = false;
		}
	}
}

void Tradesman::ActivationDialog(bool switchDialog) { //352, 124 x и y координаты Деда
	if (switchDialog == true && counterDialogs == 0) {
		tradesmanDialog = true;
	}
	else { 
		tradesmanDialog = false;
	}
}

void Tradesman::DialogConsole(sf::RenderWindow& window, sf::Vector2f PlayerCoord) {
	if (dialogConsoleOpen == true) {
		DialogWindow.setPosition(PlayerCoord.x - 28, PlayerCoord.y + 40);
		window.draw(DialogWindow);
		ContinueText.setPosition(PlayerCoord.x + 10, PlayerCoord.y + 130);
		window.draw(ContinueText);
		dialogText1.setPosition(PlayerCoord.x - 10, PlayerCoord.y + 50);
		window.draw(dialogText1);
		dialogText2.setPosition(PlayerCoord.x - 15, PlayerCoord.y + 70);
		window.draw(dialogText2);
		dialogText3.setPosition(PlayerCoord.x - 15, PlayerCoord.y + 82);
		window.draw(dialogText3);
	}
}

void Tradesman::TradesmanDialog(float time) {
	std::ifstream textStream; std::string textBuf;
	textStream.open("Dialogs/OldMan.txt");

	std::vector<std::string> text;
	std::vector<std::string> outputText;

	while (!textStream.eof()) {
		getline(textStream, textBuf);
		text.push_back(textBuf);
	}

	textStream.close();
	char ArrCounter[10] = { '0', '1', '2', '3', '4', '5', '6', '7' };

	textBuf.clear();
	int num = 0;
	for (int i = 0; i < text.size(); i++) {
		textBuf = text[i];
		if (textBuf[0] == ArrCounter[counter]) {
			textBuf.erase(0, 1); //удаление первого символа
			outputText.push_back(textBuf);
		}
	}
	dialogText1.setString(outputText[0]);
	dialogText2.setString(outputText[1]);
	dialogText3.setString(outputText[2]);
	if (timer > 1000) {	 //таймер на 1 секунду между переключением диалога
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			counter++;
			std::cout << counter << std::endl;
			timer = 0;
		}
	}
	timer += time;
}

void Tradesman::Animation(float time) {
	currentFrame += 0.001 * time;
	if (currentFrame > 4) currentFrame -= 4;
	sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 33, 32, 36));
}

bool Tradesman::getDialogConsoleOpen() { return dialogConsoleOpen; }

////////////// OldMan ///////////////

OldMan::OldMan(sf::String Name, float X, float Y, float H, float W) {
	name = Name; x = X; y = Y; height = H; width = W;
	image.loadFromFile("images/OldMan.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setPosition(x, y);
}
float OldMan::getOldX() { return x; }
float OldMan::getOldY() { return y; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tutorial::Tutorial() {
	currentFrame = 0; ActivationWindow = false;
	questionMarkImage.loadFromFile("images/DialogWindow.png");
	questionMarkImage.createMaskFromColor(sf::Color(255, 255, 255));
	queationMarkTexture.loadFromImage(questionMarkImage);
	questionMarkSprite.setTexture(queationMarkTexture);
	questionMarkSprite.setTextureRect(sf::IntRect(0, 134, 15, 24));
	questionMarkSprite.setPosition(110, 23);

	tutorialMarkImage.loadFromFile("images/DialogWindow.png");
	tutorialMarkImage.createMaskFromColor(sf::Color(255, 255, 255));
	tutorialMarkTexture.loadFromImage(questionMarkImage);
	tutorialMarkSprite.setTexture(queationMarkTexture);
	tutorialMarkSprite.setTextureRect(sf::IntRect(217, 7, 34, 23));
	tutorialMarkSprite.setPosition(100, 50);

	tutorialWindowImage.loadFromFile("images/DialogWindow.png");
	//tutorialWindowImage.createMaskFromColor(sf::Color(255, 255, 255));
	tutorialWindowTexture.loadFromImage(tutorialWindowImage);
	tutuorialWindowSprite.setTexture(tutorialWindowTexture);
	tutuorialWindowSprite.setTextureRect(sf::IntRect(299, 6, 358, 339));
	
	closeBattomTexture.loadFromFile("images/DialogWindow.png");
	closeBattomSprite.setTexture(closeBattomTexture);
	closeBattomSprite.setTextureRect(sf::IntRect(659, 7, 15, 15));
}

void Tutorial::QuestionMarkAnimation(float time) {
	currentFrame += 0.002 * time;
	if (currentFrame > 3) currentFrame -= 3;
	questionMarkSprite.setTextureRect(sf::IntRect(15 * int(currentFrame), 134, 15, 24));
}

void Tutorial::TutprialWindow(bool _ActivationWindow, sf::Vector2f PlayerCoord, sf::RenderWindow &window) {
	ActivationWindow = _ActivationWindow; 
	if (ActivationWindow) {
		tutuorialWindowSprite.setPosition(PlayerCoord.x - 180, PlayerCoord.y - 170);
		tutuorialWindowSprite.setTextureRect(sf::IntRect(299, 6, 358, 339));

		closeBattomSprite.setPosition(PlayerCoord.x + 160, PlayerCoord.y - 167);
		closeBattomSprite.setTextureRect(sf::IntRect(659, 7, 15, 15));
		if (sf::IntRect(900, 90, 40, 40).contains(sf::Mouse::getPosition(window))) { //делает кнопку закрытия в обучении красной
			closeBattomSprite.setTextureRect(sf::IntRect(674, 7, 15, 15));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				ActivationWindow = false;
			}
		}
	}
	else {
		tutuorialWindowSprite.setTextureRect(sf::IntRect(299, 6, 1, 1));
		closeBattomSprite.setTextureRect(sf::IntRect(659, 7, 0, 0));
	}
}

bool Tutorial::getActivationWindow() { return ActivationWindow; }

////////// Enemy //////////

Enemy::Enemy(sf::String F, float X, float Y, float H, float W) {
	x = X, y = Y, h = H, w = W;
	dx = 0, dy = 0;
	counter = 0, distance = 0, currentFrame = 0, timer = 0, rotation = 0;
}

////////// EnemyHeavy //////////

EnemyHeavy::EnemyHeavy(sf::String F, float X, float Y, float H, float W) : Enemy(F, X, Y, H, W) {
	sf::String File = F;
	speed = 0.03, HP = 250;
	isMove = false, life = true, timerDamage = false;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 25, 31));

	randNumber = 0; callMessage = false;
	font.loadFromFile("fonts/time.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setScale(0.5, 0.5);
	text.setString("miss");
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
}
void EnemyHeavy::update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect) {
	if (HP <= 0) { life = false; }
	if (life) {
		distance = sqrt((PlayerCoord.x - x) * (PlayerCoord.x - x) + (PlayerCoord.y - y) * (PlayerCoord.y - y));
		if (distance <= 200) isMove = true;
		else isMove = false;

		if (isMove) {
			if (distance > 2) {
				x += speed * time * (PlayerCoord.x - x) / distance;
				y += speed * time * (PlayerCoord.y - y) / distance;
			}
		}
		sprite.setPosition(x, y);
		Collision(ArrowRect);
		Rotation(PlayerCoord, time);
	}
	else {
		sprite.setTextureRect(sf::IntRect(92, 134, 45, 22)); //смерть
	}

	timer -= time;
	if (timer > 0) {
		if (randNumber == 1) {
			callMessage = true;
		}
		else {
			sprite.setColor(sf::Color::Red);
		}
		speed = 0.01;
	}
	else {
		sprite.setColor(sf::Color::White);
		callMessage = false;
		speed = 0.03;
	}
}
void EnemyHeavy::Collision(sf::FloatRect ArrowRect) {
	if (getRect().intersects(ArrowRect)) {
		while (counter == 0) {
			timer = 400;
			randNumber = 1 + std::rand() % 4; //с шансом 1 к 4 урон не проходит
			if (randNumber == 2 || randNumber == 3 || randNumber == 4) {
				HP = HP - 50;
			}
			counter++;
		}
	}
	else {
		counter = 0;
	}
}
void EnemyHeavy::Rotation(sf::Vector2f PlayerCoord, float time) {
	float dX = PlayerCoord.x - x;
	float dY = PlayerCoord.y - y;
	rotation = (static_cast<double>(atan2(dY, dX))) * 180 / 3.14159265;	// направление

	if (rotation < -135 && rotation > -180 || rotation > 135 && rotation < 180) { EnemyWeakDirection = direction::left; }
	else if (rotation < -45 && rotation > -180) { EnemyWeakDirection = direction::up; }
	else if (rotation > -45 && rotation < 45) { EnemyWeakDirection = direction::right; }
	else if (rotation > 45 && rotation < 135) { EnemyWeakDirection = direction::down; }

	Animation(time);
}
void EnemyHeavy::Animation(float time) {
	if (EnemyWeakDirection == direction::down) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(29 * int(currentFrame), 124, 29, 32));
	}
	else if (EnemyWeakDirection == direction::up) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(29 * int(currentFrame), 157, 29, 32));
	}
	else if (EnemyWeakDirection == direction::left) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(23 * int(currentFrame), 222, 23, 31));
	}
	else if (EnemyWeakDirection == direction::right) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(23 * int(currentFrame), 190, 23, 30));
	}
}
void EnemyHeavy::Massage(sf::RenderWindow& window) {
	if (callMessage) {
		text.setPosition(x + 4, y - 12);
		window.draw(text);
	}
}
sf::FloatRect EnemyHeavy::getRect() {
	return sf::FloatRect(x, y, w, h);
}

////////// EnemyWeak //////////

EnemyWeak::EnemyWeak(sf::String F, float X, float Y, float H, float W) : Enemy(F, X, Y, H, W) {
	sf::String File = F;
	speed = 0.05, HP = 200;
	isMove = false, life = true, timerDamage = false;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 25, 31));
}
void EnemyWeak::update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect) {
	if (HP <= 0) { life = false; }
	if (life) {
		distance = sqrt((PlayerCoord.x - x) * (PlayerCoord.x - x) + (PlayerCoord.y - y) * (PlayerCoord.y - y));
		if (distance <= 200) isMove = true;
		else isMove = false;

		if (isMove) {
			if (distance > 2) {
				x += speed * time * (PlayerCoord.x - x) / distance;
				y += speed * time * (PlayerCoord.y - y) / distance;
			}
		}
		sprite.setPosition(x, y);
		Collision(ArrowRect);
		Rotation(PlayerCoord, time);
	}
	else {
		sprite.setTextureRect(sf::IntRect(83, 3, 123, 30)); //смерть
	}

	timer -= time;
	if (timer > 0) {
		sprite.setColor(sf::Color::Red);
		speed = 0.01;
	}
	else {
		sprite.setColor(sf::Color::White);
		speed = 0.05;
	}
}

void EnemyWeak::Collision(sf::FloatRect ArrowRect) {
	if (getRect().intersects(ArrowRect)) {
		while (counter == 0) {
			timer = 400;
			HP = HP - 50;
			counter++;
		}
	}
	else {
		counter = 0;
	}
}

void EnemyWeak::Rotation(sf::Vector2f PlayerCoord, float time) {
	float dX = PlayerCoord.x - x;
	float dY = PlayerCoord.y - y;
	rotation = (static_cast<double>(atan2(dY, dX))) * 180 / 3.14159265;	// направление

	if (rotation < -135 && rotation > -180 || rotation > 135 && rotation < 180) { EnemyWeakDirection = direction::left; }
	else if (rotation < -45 && rotation > -180) { EnemyWeakDirection = direction::up; }
	else if (rotation > -45 && rotation < 45) { EnemyWeakDirection = direction::right; }
	else if (rotation > 45 && rotation < 135) { EnemyWeakDirection = direction::down; }

	Animation(time);
}

void EnemyWeak::Animation(float time) {
	if (EnemyWeakDirection == direction::down) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(26 * int(currentFrame), 0, 26, 30));
	}
	else if (EnemyWeakDirection == direction::up) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(26 * int(currentFrame), 33, 27, 30));
	}
	else if (EnemyWeakDirection == direction::left) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(21 * int(currentFrame), 95, 20, 28));
	}
	else if (EnemyWeakDirection == direction::right) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(22 * int(currentFrame), 65, 21, 28));
	}
}
sf::FloatRect EnemyWeak::getRect() {
	return sf::FloatRect(x, y, w, h);
}

////////// Slime1 //////////

Slime1::Slime1(sf::String F, float X, float Y, float H, float W) : Enemy(F, X, Y, H, W) {
	sf::String File = F;
	speed = 0.02, HP = 150;
	isMove = false, life = true, timerDamage = false;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 31));
}
void Slime1::update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect) {
	if (HP <= 0) { life = false; }
	if (life) {
		distance = sqrt((PlayerCoord.x - x) * (PlayerCoord.x - x) + (PlayerCoord.y - y) * (PlayerCoord.y - y));
		if (distance <= 200) isMove = true;
		else isMove = false;

		if (isMove) {
			if (distance > 2) {
				x += speed * time * (PlayerCoord.x - x) / distance;
				y += speed * time * (PlayerCoord.y - y) / distance;
			}
		}
		sprite.setPosition(x, y);
		Collision(ArrowRect);
		Rotation(PlayerCoord, time);
	}
	else {
		sprite.setTextureRect(sf::IntRect(87, 19, 29, 10)); //смерть
	}

	timer -= time;
	if (timer > 0) {
		sprite.setColor(sf::Color::Red);
		speed = 0.01;
	}
	else {
		sprite.setColor(sf::Color::White);
		speed = 0.05;
	}
}

void Slime1::Collision(sf::FloatRect ArrowRect) {
	if (getRect().intersects(ArrowRect)) {
		while (counter == 0) {
			timer = 400;
			HP = HP - 50;
			counter++;
		}
	}
	else {
		counter = 0;
	}
}

void Slime1::Rotation(sf::Vector2f PlayerCoord, float time) {
	float dX = PlayerCoord.x - x;
	float dY = PlayerCoord.y - y;
	rotation = (static_cast<double>(atan2(dY, dX))) * 180 / 3.14159265;	// направление

	if (rotation < -135 && rotation > -180 || rotation > 135 && rotation < 180) { EnemyWeakDirection = direction::left; }
	else if (rotation < -45 && rotation > -180) { EnemyWeakDirection = direction::up; }
	else if (rotation > -45 && rotation < 45) { EnemyWeakDirection = direction::right; }
	else if (rotation > 45 && rotation < 135) { EnemyWeakDirection = direction::down; }

	Animation(time);
}

void Slime1::Animation(float time) {
	if (EnemyWeakDirection == direction::down) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(25 * int(currentFrame), 0, 25, 31));
	}
	else if (EnemyWeakDirection == direction::up) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(25 * int(currentFrame), 33, 25, 31));
	}
	else if (EnemyWeakDirection == direction::left) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 96, 27, 31));
	}
	else if (EnemyWeakDirection == direction::right) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 64, 27, 31));
	}
}
sf::FloatRect Slime1::getRect() {
	return sf::FloatRect(x, y, w, h);
}

////////// Slime2 //////////

Slime2::Slime2(sf::String F, float X, float Y, float H, float W) : Enemy(F, X, Y, H, W) {
	sf::String File = F;
	speed = 0.025, HP = 150;
	isMove = false, life = true, timerDamage = false;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 31));
}
void Slime2::update(sf::RenderWindow& window, float time, sf::Vector2f PlayerCoord, sf::FloatRect ArrowRect) {
	if (HP <= 0) { life = false; }
	if (life) {
		distance = sqrt((PlayerCoord.x - x) * (PlayerCoord.x - x) + (PlayerCoord.y - y) * (PlayerCoord.y - y));
		if (distance <= 200) isMove = true;
		else isMove = false;

		if (isMove) {
			if (distance > 2) {
				x += speed * time * (PlayerCoord.x - x) / distance;
				y += speed * time * (PlayerCoord.y - y) / distance;
			}
		}
		sprite.setPosition(x, y);
		Collision(ArrowRect);
		Rotation(PlayerCoord, time);
	}
	else {
		sprite.setTextureRect(sf::IntRect(87, 19, 29, 10)); //смерть
	}

	timer -= time;
	if (timer > 0) {
		sprite.setColor(sf::Color::Red);
		speed = 0.01;
	}
	else {
		sprite.setColor(sf::Color::White);
		speed = 0.05;
	}
}

void Slime2::Collision(sf::FloatRect ArrowRect) {
	if (getRect().intersects(ArrowRect)) {
		while (counter == 0) {
			timer = 400;
			HP = HP - 50;
			counter++;
		}
	}
	else {
		counter = 0;
	}
}

void Slime2::Rotation(sf::Vector2f PlayerCoord, float time) {
	float dX = PlayerCoord.x - x;
	float dY = PlayerCoord.y - y;
	rotation = (static_cast<double>(atan2(dY, dX))) * 180 / 3.14159265;	// направление

	if (rotation < -135 && rotation > -180 || rotation > 135 && rotation < 180) { EnemyWeakDirection = direction::left; }
	else if (rotation < -45 && rotation > -180) { EnemyWeakDirection = direction::up; }
	else if (rotation > -45 && rotation < 45) { EnemyWeakDirection = direction::right; }
	else if (rotation > 45 && rotation < 135) { EnemyWeakDirection = direction::down; }

	Animation(time);
}

void Slime2::Animation(float time) {
	if (EnemyWeakDirection == direction::down) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(25 * int(currentFrame), 0, 25, 31));
	}
	else if (EnemyWeakDirection == direction::up) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(25 * int(currentFrame), 33, 25, 31));
	}
	else if (EnemyWeakDirection == direction::left) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 96, 27, 31));
	}
	else if (EnemyWeakDirection == direction::right) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 64, 27, 31));
	}
}
sf::FloatRect Slime2::getRect() {
	return sf::FloatRect(x, y, w, h);
}