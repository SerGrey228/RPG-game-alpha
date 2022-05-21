#include "GameView.h"

GameView::GameView() {
	StopPlayer = false; oldManDialog = false; dialogConsoleOpen = false;
	counter = 0; counterDialogs = 0; timer = 0;

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

void GameView::RenderDialogWindow(int NumberLevel, sf::RenderWindow& window, float PlayerX, float PlayerY, float time) {
	view.reset(sf::FloatRect(0, 0, 400, 400));
	view.setCenter(PlayerX, PlayerY);
	window.setView(view);

	if (NumberLevel == 1) {
		ActivationDialog(PlayerX, PlayerY);
		if (oldManDialog) {
			dialogConsoleOpen = true;
			StopPlayer = true;
			OldManDialog(PlayerX, PlayerY, time);
			if (counter > 4) { counterDialogs = 1; } //кол-во переключений диалогов
		}
		else {
			dialogConsoleOpen = false;
			StopPlayer = false;
		}
	}
}

void GameView::ActivationDialog(float PlayerX, float PlayerY) { //352, 124 x и y координаты Деда
	distance = sqrt((PlayerX - 352) * (PlayerX - 352) + (PlayerY - 124) * (PlayerY - 124));
	if (distance <= 100 && counterDialogs == 0) {
		oldManDialog = true;
	}
	else oldManDialog = false;
}

void GameView::DialogConsole(sf::RenderWindow& window, float PlayerX, float PlayerY) {
	if (dialogConsoleOpen == true) {
		DialogWindow.setPosition(PlayerX - 28, PlayerY + 40);
		window.draw(DialogWindow);
		ContinueText.setPosition(PlayerX + 10, PlayerY + 130);
		window.draw(ContinueText);
		dialogText1.setPosition(PlayerX - 10, PlayerY + 50);
		window.draw(dialogText1);
		dialogText2.setPosition(PlayerX - 15, PlayerY + 70);
		window.draw(dialogText2);
		dialogText3.setPosition(PlayerX - 15, PlayerY + 82);
		window.draw(dialogText3);
	}
}

void GameView::OldManDialog(float PlayerX, float PlayerY, float time) {
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
	if (timer > 1000) {		//таймер на 1 секунду между переключением диалога
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {	
			counter++;
			std::cout << counter << std::endl;
			timer = 0;
		}
	}
	timer += time;
}



//////////   //////////

InteractionMark::InteractionMark() {
	MarkSwitching = false;
	imageMark.loadFromFile("images/DialogWindow.png");
	imageMark.createMaskFromColor(sf::Color(255, 255, 255));
	textureMark.loadFromImage(imageMark);
	spriteMark.setTexture(textureMark);
	spriteMark.setTextureRect(sf::IntRect(201, 7, 13, 17));
}

void InteractionMark::ActivationMark(bool _activationMark, float x, float y) {
	MarkSwitching = _activationMark;
	if (MarkSwitching) {
		spriteMark.setPosition(x + 7, y - 20);
	}
}
