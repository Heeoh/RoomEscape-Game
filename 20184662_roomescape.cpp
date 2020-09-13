#include <bangtal.h>
using namespace bangtal;


bool movePuzzle(ObjectPtr object, int* location, int direction, MouseAction action, ScenePtr inCloset) {
	int x = *location / 1000;					// p1의 좌표 찾기
	int y = *location - (x * 1000);

	if (action == MouseAction::MOUSE_DRAG_LEFT && direction == 1) {
		object->locate(inCloset, x - 120, y);
		*location = (x - 120) * 1000 + y;
		return true;
	}
	else if (action == MouseAction::MOUSE_DRAG_RIGHT && direction == 2) {
		object->locate(inCloset, x + 120, y);
		*location = (x + 120) * 1000 + y;
		return true;
	}
	else if (action == MouseAction::MOUSE_DRAG_DOWN && direction == 4) {
		object->locate(inCloset, x, y - 150);
		*location = x * 1000 + (y - 150);
		return true;
	}
	else if (action == MouseAction::MOUSE_DRAG_UP && direction == 8) {
		object->locate(inCloset, x, y + 150);
		*location = x * 1000 + (y + 150);
		return true;
	}
	return false;
}

void check_blank(int direction[], int b) {
	for (int i = 0; i < 10; i++)
		direction[i] = 0;
	switch (b) {
	case 1:
		direction[2] = 1, direction[4] = 8;
		break;
	case 2:
		direction[1] = 2, direction[3] = 1, direction[5] = 8;
		break;
	case 3:
		direction[2] = 2, direction[6] = 8;
		break;
	case 4:
		direction[1] = 4, direction[5] = 1, direction[7] = 8;
		break;
	case 5:
		direction[2] = 4, direction[4] = 2, direction[6] = 1, direction[8] = 8;
		break;
	case 6:
		direction[3] = 4, direction[5] = 2, direction[9] = 8;
		break;
	case 7:
		direction[4] = 4, direction[8] = 1;
		break;
	case 8:
		direction[5] = 4, direction[7] = 2, direction[9] = 1;
		break;
	case 9:
		direction[6] = 4, direction[8] = 2;
		break;
	default:
		break;
	}
}


int main(){

	// 장면
	auto scene1 = Scene::create("room 1", "images/room2.png");
	auto inCloset = Scene::create("closet", "images/inCloset.jpg");
	auto attic = Scene::create("attic", "images/attic.png");
	auto scene2 = Scene::create("room 2", "images/room2.png");

/* room 1 */
	auto isOpen1 = false;
	auto door1 = Object::create("images/door3_closed.png", scene1, 910, 180);
	door1->setScale(0.55f);

	auto locked = true;
	auto keypad = Object::create("images/키패드.png", scene1, 885, 360);

	auto closet = Object::create("images/closet.png", scene1, 150, 140);
	closet->setScale(0.5f);

	// door1
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (locked)										// 문이 닫힌 상태 & 잠금해제 X -> 메세지 띄우기
			showMessage("잠겨있어. 비밀번호가 필요해!! \n옷장을 열어볼까?");
		else if (isOpen1) {								// 문이 열린 상태 -> room 2로 이동
			scene2->enter();
		}
		else {											
			door1->setImage("images/door3_open.png");	// 문이 닫힌 상태 & 잠금해제 O -> 문 열기
			isOpen1 = true;
		}

		return true;
	});

	door1->setOnKeypadCallback([&](ObjectPtr object)-> bool {
		showMessage("철커덕");
		locked = false;
		return true;
	});

	// keypad 작동
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		showKeypad("LIBRA", door1);
		return true;
	});

	// closet
	closet->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (action == MouseAction::MOUSE_CLICK)
			inCloset->enter();

		return true;
	});


	
/* in Closet */
	auto backButton = Object::create("images/home.png", inCloset, 1150, 10);
	backButton->setScale(0.3f);

	auto isAtticOpen = false;
	auto atticDoor = Object::create("images/atticDoor.jpg", inCloset, 200, 150);
	atticDoor->setScale(0.6f);

	auto board = Object::create("images/board.png", inCloset, 697, 140);
	board->setScale(0.3f);

	auto puzzle1 = Object::create("images/puzzle1.png", inCloset, 710, 450);
	puzzle1->setScale(0.3f);
	auto puzzle2 = Object::create("images/puzzle2.png", inCloset, 830, 450);
	puzzle2->setScale(0.3f);
	auto puzzle3 = Object::create("images/puzzle3.png", inCloset, 950, 450);
	puzzle3->setScale(0.3f);
	auto puzzle4 = Object::create("images/puzzle4.png", inCloset, 710, 300);
	puzzle4->setScale(0.3f);
	auto puzzle5 = Object::create("images/puzzle5.png", inCloset, 830, 300);
	puzzle5->setScale(0.3f);
	auto puzzle6 = Object::create("images/puzzle6.png", inCloset, 950, 300);
	puzzle6->setScale(0.3f);
	auto puzzle7 = Object::create("images/puzzle7.png", inCloset, 710, 150);
	puzzle7->setScale(0.3f);
	auto puzzle8 = Object::create("images/puzzle8.png", inCloset, 830, 150);
	puzzle8->setScale(0.3f);
	auto puzzle9 = Object::create("images/puzzle9.png", inCloset, 1100, 300);
	puzzle9->setScale(0.3f);
	

	int puzzleNum[10] = { 9, 1, 2, 3, 4, 5, 6, 7, 8, 0 };		// 해당 위치에 있는 퍼즐 number, 0 == blank
	int direction[10] = { 0, 0, 0, 0, 0, 0, 4, 0, 2, 0 };		// blank위치로 옮길 수 있는 방향, 0 == 옮길 수 X, 1-Left 2-Right 4-Down 8-Up
	int location[10] = { 0, 710450, 830450, 950450, 710300, 830300, 950300, 710150, 830150, 0 }; // puzzle 의 x y 좌표, x*1000 + y

	int answer[10] = { 9, 1, 5, 2, 7, 4, 3, 8, 6, 0 };
	auto ready = false;
	auto complete = false;		// 9개의 퍼즐 모두 완성


	// puzzle game
	puzzle1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 1 || i < 10)   i++;  // p1의 현재 위치 찾기
		if (movePuzzle(puzzle1, &(location[1]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 1, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);			
		}

		return true;
	});

	puzzle2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 2 && i < 10)   i++;  // p2의 현재 위치 찾기
		if (movePuzzle(puzzle2, &(location[2]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 2, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}

		return true;
		});

	puzzle3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 3 && i < 10)   i++;  // p3의 현재 위치 찾기
		if (movePuzzle(puzzle3, &(location[3]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 3, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}

		return true;
		});

	puzzle4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 4 && i < 10)   i++;  // p4의 현재 위치 찾기
		if (movePuzzle(puzzle4, &(location[4]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 4, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}

		return true;
		});

	puzzle5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 5 && i < 10)   i++;  // p5의 현재 위치 찾기
		if (movePuzzle(puzzle5, &(location[5]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 5, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}

		return true;
		});

	puzzle6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 6 && i < 10)   i++;  // p6의 현재 위치 찾기
		if (movePuzzle(puzzle6, &(location[6]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 6, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}


		return true;
		});

	puzzle7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 7 && i < 10)   i++;  // p7의 현재 위치 찾기
		if (movePuzzle(puzzle7, &(location[7]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 7, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}


		return true;
		});

	puzzle8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		int i = 1;
		while (puzzleNum[i] != 8 && i < 10)   i++;  // p8의 현재 위치 찾기
		if (movePuzzle(puzzle8, &(location[8]), direction[i], action, inCloset)) {

			puzzleNum[puzzleNum[0]] = 8, puzzleNum[i] = 0, puzzleNum[0] = i;  // puzzleNum[] 수정
			check_blank(direction, i);
		}

		return true;
	});

	puzzle9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		for (int j = 0; j < 10; j++) {
			if (puzzleNum[j] != answer[j]) break;
			else if (j == 9 && puzzleNum[j] == answer[j]) ready = true;
			else continue;
		}
		if (ready) {
			puzzle9->locate(inCloset, 950, 150);
			complete = true;
		}
		return true;
	});


	atticDoor->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (action == MouseAction::MOUSE_CLICK) {
			if (!complete)
				showMessage("퍼즐을 풀어야 해!!");
			else if (isAtticOpen == false) {
				atticDoor->setImage("images/ladder.jpg");
				atticDoor->locate(inCloset, 200, 100);
				isAtticOpen = true;
			}
			else {
				attic->enter();
			}
		}

		return true;
	});

	backButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (action == MouseAction::MOUSE_CLICK)
			scene1->enter();
		return true;
	});

/* attic */
	auto isLightOn = true;
	auto button = Object::create("images/스위치.png", attic, 1050, 400);  // attic 에서 힌트 제공을 위한 스위치

	auto hint = Object::create("images/hint.png", attic, 320, 200, false);
	hint->setScale(0.05f);

	auto door_a = Object::create("images/door_BackToRoom1.png", attic, 250, 50);
	door_a->setScale(0.3f);

	// switch
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (isLightOn) {					// 전등이 켜진 상태
			attic->setLight(0.2f);
			hint->show();
			isLightOn = false;
		}
		else {								// 전등이 꺼진 상태
			attic->setLight(1.0f);
			hint->hide();
			isLightOn = true;
		}

		return true;
	});

	// door in attic, back to room 1
	door_a->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		return true;
	});


/* room 2 */
	auto door2 = Object::create("images/door2.png", scene2, 150, 165);
	door2->setScale(0.75f);

	auto isOpen3 = false;
	auto door3 = Object::create("images/door3_closed.png", scene2, 910, 180);
	door3->setScale(0.55f);

	auto locked2 = true;
	auto keypad2 = Object::create("images/키패드.png", scene2, 885, 360);

	auto memoboard = Object::create("images/memoboard.png", scene2, 600, 350);
	memoboard->setScale(0.4f);

	auto tornMemo1 = Object::create("images/tornMemo1.png", scene2, 620, 360, false);
	tornMemo1->setScale(0.05f);

	auto tornMemo2 = Object::create("images/tornMemo2.png", scene2, 720, 340, false);
	tornMemo2->setScale(0.05f);

	auto memo = Object::create("images/memo.png", scene2, 720, 340);
	memo->setScale(0.04f);

	auto isMoved = false;
	auto picture = Object::create("images/picture.png", scene2, 700, 300);
	picture->setScale(0.4f);


	// back to room 1 (left door)
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		return true;
	});

	// open right door 
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (locked2)										// 문이 닫힌 상태 & 잠금해제 X -> 메세지 띄우기
			showMessage("잠겨있어. 비밀번호가 필요해!!");
		else if (isOpen3) {								// 문이 열린 상태 -> room 2로 이동
			endGame();
		}
		else {
			door3->setImage("images/door3_open.png");	// 문이 닫힌 상태 & 잠금해제 O -> 문 열기
			isOpen3 = true;
		}

		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)-> bool {
		showMessage("철커덕");
		locked2 = false;
		return true;
	});

	// keypad 작동
	keypad2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		showKeypad("EARTH", door3);
		return true;
	});

	picture->setOnMouseCallback([&](ObjectPtr onject, int x, int y, MouseAction action)-> bool {
		if (!isMoved) {
			if (action == MouseAction::MOUSE_DRAG_UP)
				picture->locate(scene2, 700, 400);
		}

		return true;
	});

	tornMemo1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		tornMemo1->pick();
		return true;
	});

	tornMemo2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		tornMemo2->pick();
		return true;
	});

	memo->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		memo->pick();
		return true;
	});





	/* 게임 시작 */
	startGame(scene1);

	return 0;
}