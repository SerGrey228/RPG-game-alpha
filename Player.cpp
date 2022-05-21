#include "Player.h"

Player::Player(sf::String F, TmxLevel lvl, float Speed, float X, float Y, float H, float W) {
	dx = 0; dy = 0; speed = 0; moveSpeed = Speed; currentFrame = 0; HP = 150; timer = 0;
	obj = lvl.GetAllObjects("solid"); objDop = lvl.GetAllObjects("door1"); objDop2 = lvl.GetAllObjects("door2");
	objDop3 = lvl.GetAllObjects("door3");
	objDialog = lvl.GetAllObjects("dialog");
	sf::String File = F; 
	x = X, y = Y, height = H, width = W;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(1, 98, 30, 32));
	PlayerStop1 = false; PlayerStop2 = false; PlayerStop3 = false; life = true; switchDialog = false;
	ActivationInterectivMark = false; SwitchLevel = false; ActivationTutorialWindow = false; Door2 = false; Door3 = false;

	font.loadFromFile("fonts/time.ttf");

	HPText.setFont(font);
	HPText.setCharacterSize(24);
	HPText.setScale(0.5, 0.5);

	missionText.setFont(font);
	missionText.setCharacterSize(24);
	missionText.setScale(0.5, 0.5);
	missionText.setFillColor(sf::Color::Yellow);

	missionDopText.setFont(font);
	missionDopText.setCharacterSize(24);
	missionDopText.setScale(0.5, 0.5);
}

void Player::setMomeSpeed(float _MoveSpeed) {
	moveSpeed = _MoveSpeed;
}

void Player::Move(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerDirection = direction::left;
		speed = moveSpeed; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerDirection = direction::right; 
		speed = moveSpeed; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerDirection = direction::up; 
		speed = moveSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerDirection = direction::down; 
		speed = moveSpeed;
	}
	else if (speed == 0) {
		playerDirection = direction::stay;
	}
	Animation(time);
}

void Player::Animation(float time) {
	if (playerDirection == direction::left) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 192, 27, 32));
	}
	if (playerDirection == direction::right) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 96, 27, 31));
	}
	if (playerDirection == direction::up) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(29 * int(currentFrame), 385, 29, 30));
	}
	if (playerDirection == direction::down) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(27 * int(currentFrame), 289, 27, 30));
	}
	if (playerDirection == direction::stay) {
		switch (playerDirection) {
			case direction::up: 
				sprite.setTextureRect(sf::IntRect(0, 385, 29, 30)); 
				break;
			case direction::left: 
				sprite.setTextureRect(sf::IntRect(0, 192, 27, 31)); 
				break;
			case direction::down: 
				sprite.setTextureRect(sf::IntRect(0, 289, 27, 30)); 
				break;
			case direction::right: 
				sprite.setTextureRect(sf::IntRect(0, 97, 28, 32)); 
				break;
		}
	}
}

void Player::update(float time, int NumberLevel, bool _StopPlayer) {
	if (!PlayerStop1 && !PlayerStop2 && !_StopPlayer) { Move(time); }
	switch (playerDirection) {
		case direction::right: 
			dx = speed; 
			dy = 0; 
			break;
		case direction::left: 
			dx = -speed; 
			dy = 0; 
			break;
		case direction::down: 
			dx = 0; 
			dy = speed; 
			break;
		case direction::up: 
			dx = 0; 
			dy = -speed; 
			break;
		case direction::stay: 
			dx = 0; 
			dy = 0; 
			break;
	}
	x += dx * time;
	y += dy * time;
	speed = 0;

	if (HP <= 0) { life = false; std::cout << life; }
	timer -= time;
	if (timer > 0) {
		sprite.setColor(sf::Color::Red);
	}
	else {
		sprite.setColor(sf::Color::White);
	}
	sprite.setPosition(x, y);
	ActivationInterectivMark = false; 
	Door2 = false;
	Door3 = false;
}

void Player::Collision(int NumberLevel, float time, sf::FloatRect enemyWeakRect, sf::FloatRect enemyHeavyRect, 
	sf::FloatRect slime1Rect, sf::FloatRect slime2Rect) {
	for (int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			if (obj[i].name == "solid") {
				if (dy > 0) { y = obj[i].rect.top - height; }
				if (dy < 0) { y = obj[i].rect.top + obj[i].rect.height; }
				if (dx > 0) { x = obj[i].rect.left - width; }
				if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}
	for (int i = 0; i < objDop.size(); i++) {
		if (getRect().intersects(objDop[i].rect)) {
			if (objDop[i].name == "door1" && NumberLevel == 2 || NumberLevel == 3) {
				ActivationInterectivMark = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					SwitchLevel = true;
				}
			}
		}
	}
	for (int i = 0; i < objDop2.size(); i++) {
		if (getRect().intersects(objDop2[i].rect)) {
			if (objDop2[i].name == "door2" && NumberLevel == 2 || NumberLevel == 4) {
				ActivationInterectivMark = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					SwitchLevel = true;
					Door2 = true;
				}
			}
		}
	}
	for (int i = 0; i < objDop3.size(); i++) {
		if (getRect().intersects(objDop3[i].rect)) {
			if (objDop3[i].name == "door3" && NumberLevel == 4 || NumberLevel == 5) {
				ActivationInterectivMark = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					SwitchLevel = true;
					Door3 = true;
				}
			}
		}
	}
	for (int i = 0; i < objDialog.size(); i++) {
		if (getRect().intersects(objDialog[i].rect)) {
			if (objDialog[i].name == "dialog" && NumberLevel == 1) {
				ActivationInterectivMark = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					ActivationTutorialWindow = true;
				}
			}
			if (objDialog[i].name == "dialog" && NumberLevel == 3) {
				ActivationInterectivMark = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					switchDialog = true;
				}
			}
		}
	}
	if (NumberLevel == 4) {
		if (getRect().intersects(enemyWeakRect) || getRect().intersects(enemyHeavyRect)) {
			while (counter == 0) {
				timer = 1000;
				HP = HP - 50;
				counter++;
			}
		}
		else {
			counter = 0;
		}
	}
	if (NumberLevel == 5) {
		if (getRect().intersects(slime1Rect) || getRect().intersects(slime2Rect)) {
			while (counter == 0) {
				timer = 1000;
				HP = HP - 50;
				counter++;
			}
		}
		else {
			counter = 0;
		}
	}
}

void Player::DrawFeature(sf::RenderWindow& window, int NumberLevel, float spawnRobbers, bool DopQuest) {
	HPText.setString("HP: " + std::to_string(HP));
	HPText.setPosition(x - 180, y - 150);
	missionText.setString("mission: kill the robbers.");
	missionText.setPosition(x - 180, y - 190);
	missionDopText.setString("additional mission: find the medallion.");
	missionDopText.setPosition(x - 180, y - 170);

	window.draw(HPText);
	if (!(NumberLevel == 1) && spawnRobbers == true) { window.draw(missionText); }
	if (DopQuest) { window.draw(missionDopText); }
}

sf::FloatRect Player::getRect() {
	return sf::FloatRect(x, y, width, height);
}
float Player::getX() { return x; }
float Player::getY() { return y; }
float Player::getHeight() { return height; }
float Player::getWigth() { return width; }
bool Player::getActivationMark() { return ActivationInterectivMark; }
bool Player::getActivationTutrialWindow() { return ActivationTutorialWindow; }
bool Player::getTrade() { return switchDialog; }
void Player::setPlayerStop1(bool _stop1) { PlayerStop1 = _stop1; }
void Player::setPlayerStop2(bool _stop2) { PlayerStop2 = _stop2; }
void Player::setActivationTutorialWindow(bool _ActivationTutorialWindow) {
	ActivationTutorialWindow = _ActivationTutorialWindow;
}
bool Player::getLife() { return life; }
////////////////////////////////////////////////////////// класс для стрелы ////////////////////////////////////////////////////


Arrow::Arrow(TmxLevel lvl, float _x, float _y, float H, float W) {
	x = _x; y = _y; h = H; w = W;
	dX = 0; dY = 0; CoordMouseX = 0, CoordMouseY = 0; speed = 0.2, timer = 2000;
	collActivationTimer = false, life = false; collisionTimer = false;
	obj = lvl.GetAllObjects("solid");
	image.loadFromFile("images/DialogWindow.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(201, 34, static_cast<int>(h), static_cast<int>(w)));
	sprite.setOrigin(h / 2, w / 2);

	indicatorImage.loadFromFile("images/DialogWindow.png");
	indicatorImage.createMaskFromColor(sf::Color(255, 255, 255));
	indicatorTexture.loadFromImage(indicatorImage);
	indicatorSprite.setTexture(indicatorTexture);
}

void Arrow::update(sf::RenderWindow& window, float time, sf::Vector2f pos, sf::Vector2f PlayerCoord) {
	distance = sqrt((CoordMouseX - x) * (CoordMouseX - x) + (CoordMouseY - y) * (CoordMouseY - y));
	if (life) {
		if (distance > 3) {
			x += speed * time * (CoordMouseX - x) / distance; //идем по иксу с помощью вектора нормали
			y += speed * time * (CoordMouseY - y) / distance;
			sprite.setTextureRect(sf::IntRect(201, 34, static_cast<int>(h), static_cast<int>(w)));
		}
		else {
			Direction();
			timer -= time;
			if (timer <= 0) { life = false; }
		}
		sprite.setPosition(x, y);
	}
	else {
		timer = 2000;
		x = PlayerCoord.x + 12; y = PlayerCoord.y + 12;
		Rotation(pos);
		sprite.setTextureRect(sf::IntRect(201, 34, 1, 1));
		sprite.setPosition(x, y);
	}
	if (collActivationTimer) {
		sprite.setTextureRect(sf::IntRect(201, 34, 0, 0));
		timer -= time;
		if (timer <= 0) { life = false; collActivationTimer = false; }
	}
}

void Arrow::Direction() { //определяет направление выстрела
	if (rotation < -135 && rotation > -180 || rotation > 135 && rotation < 180) { direction = 1; } //лево
	else if (rotation < -45 && rotation > -180) { direction = 3; } //вверх
	else if (rotation > -45 && rotation < 45) { direction = 2; } //право
	else if (rotation > 45 && rotation < 135) { direction = 4; } //вниз

	if (direction == 3 || direction == 4) {
		sprite.setRotation(0);
		sprite.setTextureRect(sf::IntRect(235, 38, 6, 28));
	}
	if (direction == 1) {
		sprite.setRotation(0);
		sprite.setTextureRect(sf::IntRect(218, 41, 17, 27));
	}
	if (direction == 2) {
		sprite.setRotation(0);
		sprite.setTextureRect(sf::IntRect(201, 41, 17, 27));
	}
}

void Arrow::Collision(float time) {
	for (int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			if (obj[i].name == "solid") {
				collActivationTimer = true;
			}
		}
	}
}

void Arrow::Rotation(sf::Vector2f pos) { //поворот страйта в сторону курсора
	dX = pos.x - x;
	dY = pos.y - y;
	rotation = (static_cast<double>(atan2(dY, dX))) * 180 / 3.14159265;
	sprite.setRotation(rotation);
}

void Arrow::ArrowIndicator(sf::Vector2f PlayerCoord, sf::RenderWindow &window) {
	if (life) {
		indicatorSprite.setTextureRect(sf::IntRect(46, 137, 123, 15));
	}
	else {
		indicatorSprite.setTextureRect(sf::IntRect(45, 151, 120, 15));
	}
	indicatorSprite.setPosition(PlayerCoord.x - 190, PlayerCoord.y + 170);
	window.draw(indicatorSprite);
}

sf::FloatRect Arrow::getRect() { return sf::FloatRect(x, y, w, h); }
void Arrow::setLife(bool Life) { life = Life; }
void Arrow::setCoordMouse(float coordX, float coordY) { CoordMouseX = coordX; CoordMouseY = coordY; }