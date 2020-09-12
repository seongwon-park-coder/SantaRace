﻿#include <bangtal.h>

using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//장면을 생성한다.
	auto scene = Scene::create("산타 레이스","images/background.png" );
	
	auto santaX = 0, santaY = 400;
	auto santa = Object::create("images/santa.png",scene,santaX,santaY);
	santa->setScale(0.4f);

	auto startButton = Object::create("images/start.png", scene, 590, 70);
	startButton->setScale(0.2f);
	auto endButton = Object::create("images/end.png", scene, 590, 20);
	endButton->setScale(0.2f);
	auto playButton = Object::create("images/play.png", scene, 610, 30, false);
	playButton->setScale(0.2f);


	auto timer = Timer::create(10.f);
	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("헉, 선물 배달 실패!!!");

		playButton->hide();		
		startButton->setImage("Images/restart.png");
		startButton->show();
		endButton->show();

		return true;
	});

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();
		playButton->show();

		santaX = 0;
		santa->locate(scene, santaX, santaY);

		timer->set(10.f);
		timer->start();

		return true;
	});
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		endGame();
		return true;
	});

	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction)->bool {
		//산타를 x축으로 30만큼 이동한다.
		santaX = santaX + 30;
		santa->locate(scene, santaX, santaY);

		if (santaX > 1280) {
			showMessage("선물 배달 성공~~~");
			timer->stop();

			playButton->hide();
			startButton->setImage("images/restart.png");
			startButton->show();
			endButton->show();

		}

		return true;
	});


	//게임을 시작한다
	startGame(scene);
	
	return 0;
}