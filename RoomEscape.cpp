/*
#include <bangtal.h>
using namespace bangtal;

int main() {

	// 장면
	auto scene1 = Scene::create("room 1", "images/room1.jpg");
	auto scene2 = Scene::create("room 2", "images/room2.png");

	// 문
	auto isOpen1 = false;
	auto door1 = Object::create("images/door1_closed.jpg", scene1, 600, 147);
	door1->setScale(0.7f);

	auto door2 = Object::create("images/door2.png", scene2, 150, 165);
	door2->setScale(0.75f);

	auto isOpen3 = false;
	auto door3 = Object::create("images/door3_closed.png", scene2, 910, 180);
	door3->setScale(0.55f);

	// 열쇠
	auto key = Object::create("images/key.png", scene1, 490, 100);
	key->setScale(0.01f);

	// 화분
	auto isMoved = false;
	auto plant = Object::create("images/plant.png", scene1, 450, 100);
	plant->setScale(0.2f);

	// 키패드
	auto locked = true;
	auto keypad = Object::create("images/키패드.png", scene2, 885, 360);

	// 스위치
	auto isLightOn1 = true;
	auto button1 = Object::create("images/스위치.png", scene1, 570, 300);  // room 1에서 힌트 제공을 위한 스위치

	auto isLightOn2 = true;
	auto button2 = Object::create("images/스위치.png", scene2, 880, 380);

	// 힌트
	auto hint = Object::create("images/hint.jpg", scene1, 330, 300, false);
	hint->setScale(0.2f);

	// 암호
	auto password = Object::create("images/암호.png", scene2, 400, 100, false);

	// 옷장
	auto isMoved2 = false;
	auto closet = Object::create("images/closet.png", scene2, 910, 180);
	closet->setScale(0.55f);

	// scene1 

	// switch On/Off ( 힌트 제공을 위한 스위치 )
	button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (isLightOn1) {					// 전등이 켜진 상태
			scene1->setLight(0.2f);
			hint->show();
			isLightOn1 = false;
		}
		else {								// 전등이 꺼진 상태
			scene1->setLight(1.0f);
			hint->hide();
			isLightOn1 = true;
		}

		return true;
		});

	// locate pot
	plant->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (!isMoved) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {			// 화분 왼쪽으로 옮기기
				plant->locate(scene1, 350, 100);
				isMoved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {		// 오른쪽
				plant->locate(scene1, 530, 100);
				isMoved = true;
			}
		}

		return true;
		});

	// pick the key
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		key->pick();
		return true;
		});

	// open door
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (isOpen1)									// 문이 열린 상태 -> room 2로 이동
			scene2->enter();
		else if (key->isHanded()) {						// 문이 닫힌 상태 & 열쇠 O -> 문 열기
			door1->setImage("images/door1_open.jpg");
			isOpen1 = true;
		}
		else {											// 문이 닫힌 상태 & 열쇠 X -> 메세지 띄우기
			showMessage("열쇠가 필요해!!");
		}

		return true;
		});



	// scene 2 

	// back to room 1 (left door)
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		return true;
		});

	// locate closet
	closet->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (!isMoved2) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {			// 왼쪽으로 옮기기
				closet->locate(scene2, 600, 180);
				isMoved2 = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {		// 오른쪽
				closet->locate(scene2, 960, 150);
				isMoved2 = true;
			}
		}

		return true;
		});

	// open right door 
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (locked)										// 잠금 해제 X -> 메시지 띄우기
			showMessage("문이 잠겨있다.");

		else if (isOpen3)								// 문이 열린 상태 & 잠금 해제 O -> 게임종료
			endGame();
		else {											// 문이 닫힌 상태 & 잠금 해제 O -> 문 열기
			door3->setImage("images/door3_open.png");
			isOpen3 = true;
		}

		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)-> bool {
		showMessage("철커덕");
		locked = false;
		return true;
		});

	// keypad 작동
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		showKeypad("BANGTAL", door3);
		return true;
		});

	// switch On/Off
	button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (isLightOn2) {					// 전등이 켜진 상태
			scene2->setLight(0.2f);
			password->show();
			isLightOn2 = false;
		}
		else {								// 전등이 꺼진 상태
			scene2->setLight(1.0f);
			password->hide();
			isLightOn2 = true;
		}

		return true;
		});


	// 게임 시작 
	startGame(scene1);

	return 0;
} 
*/