#include <bangtal.h>
using namespace bangtal;

int main() {
	// Scene1 
	auto scene1 = Scene::create("룸1", "Images/RoomEscape/배경-1.png"); //첫화면 만들기
	// Scene2
	auto scene2 = Scene::create("룸2", "Images/RoomEscape/배경-2.png"); //오른쪽방
	// Scene3
	auto scene3 = Scene::create("룸3", "Images/RoomEscape/배경-2.png"); // 왼쪽방
	
	// Scene1의 문 2개 
	auto door1 = Object::create("Images/RoomEscape/문-오른쪽-닫힘.png", scene1, 800, 270); //문1
	auto door2 = Object::create("Images/RoomEscape/문-왼쪽-닫힘.png", scene1, 170, 272); // 문2
	
	// Scene3의 문 1개
	auto door3 = Object::create("Images/RoomEscape/문-오른쪽-열림.png", scene3, 910, 272); //문3 열려있는 상태
	
	// Scene2의 문 2개
	auto door4 = Object::create("Images/RoomEscape/문-왼쪽-열림.png", scene2, 320, 270);
	auto door5 = Object::create("Images/RoomEscape/문-오른쪽-닫힘.png", scene2, 910, 272, false); //숨겨진 문

	//열쇠
	auto key = Object::create("Images/RoomEscape/열쇠.png", scene1, 505, 320);  
	key->setScale(0.2f); // 열쇠크기 작게
	
	// 화분
	auto flowerpot = Object::create("Images/RoomEscape/화분.png", scene1, 450, 320);
	
	// Scene1에서 콜백
	auto door1_open = false, door1_locked = false;
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door1_locked == false) {
			showMessage("문이 잠겨있다!");
		}
		else if (door1_open == true) {
			scene2->enter();
		}
		else if (key->isHanded()){
			showMessage("철커덩");
			door1->setImage("Images/RoomEscape/문-오른쪽-열림.png");
			door1_open = true;
		}
		return true;
		});

	\

	auto door2_open = false, door2_locked = false;
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door2_locked == false) {
			showMessage("문이 잠겨있다!");
		}
		else if (door2_open == true) {
			scene3->enter();
			scene3->setLight(0.3f);
			showMessage("방이 어둡다!");
		}
		else{
			door2->setImage("Images/RoomEscape/문-왼쪽-열림.png");
			door2_open = true;
		}
		return true;
		});
	door2->setOnKeypadCallback([&](ObjectPtr object)->bool {
		door2_locked = true; // 문열어주는거
		showMessage("철커덕");
		return true;
		});

	// 키패드 만들기
	auto keypad = Object::create("Images/RoomEscape/키패드.png", scene1, 150, 420);
	// 키패드 클릭
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("MOUSEACTION");
		showKeypad("CLICKDRAG", door2);

		return true;
		});
	//scene3 왼쪽방문
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		door2->setImage("Images/RoomEscape/문-왼쪽-닫힘.png"); //
		showMessage("저절로 문이 닫혔다! 뭐지??");
		door2_locked = false;
		return true;
		});

	//왼쪽방 스위치 만들기
	auto scene3_button = Object::create("Images/RoomEscape/스위치.png", scene3, 500, 440);
	auto scene3_lighted = false; // 불 꺼진 상태
	auto letter1 = Object::create("Images/RoomEscape/쪽지.png", scene3, 600, 50, false);
	auto letter2 = Object::create("Images/RoomEscape/쪽지.png", scene3, 650, 70, false);
	auto letter3 = Object::create("Images/RoomEscape/쪽지.png", scene3, 700, 30, false);
	letter1->setScale(0.1f);
	letter2->setScale(0.1f);
	letter3->setScale(0.1f);
	//왼쪽방 불켜기
	scene3_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (scene3_lighted == false) { //불꺼진상태에서 켜기
			scene3->setLight(1.0f);
			letter1->show();
			letter2->show();
			letter3->show();
			scene3_lighted = true;
		}
		else { //불켜진상태에서 끄기
			scene3->setLight(0.3f);
			scene3_lighted = false;
			letter1->hide();
			letter2->hide();
			letter3->hide();
		}
		return true;
		});
	//쪽지3개 힌트 만들어주기
	letter1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("진");
		return true;
		});
	letter2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("2");
		return true;
		});
	letter3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("수");
		return true;
		});
	//오른쪽 방 꾸미기 
	//퀴즈
	auto quiz = Object::create("Images/RoomEscape/퀴즈.jpg",scene2, 500, 40);
	quiz->setScale(0.1f);

	//퀴즈 픽
	quiz->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		quiz->pick();
		showMessage("퀴즈의 답에 4를 더하라");
		return true;
		});

	//버튼 4개
	auto scene2_button1 = Object::create("Images/RoomEscape/스위치.png", scene2, 500, 440);
	auto button1_press = false;
	auto scene2_button2 = Object::create("Images/RoomEscape/스위치.png", scene2, 515, 440);
	auto button2_press = false;
	auto scene2_button3 = Object::create("Images/RoomEscape/스위치.png", scene2, 530, 440);
	auto button3_press = false;
	auto scene2_button4 = Object::create("Images/RoomEscape/스위치.png", scene2, 545, 440);
	auto button4_press = false;

	//버튼 4개중에 마지막꺼 눌렀을때 불 꺼짐
	scene2_button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		button1_press = true;
		return true;
		});
	scene2_button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		button2_press = true;
		return true;
		});
	scene2_button3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		button3_press = true;
		return true;
		});
	scene2_button4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (button2_press == true) {
			button4_press = true;
			scene2->setLight(0.3f);
			door5->show();
		}
		return true;
		});
	// scene1로 들어가는 문
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		return true;
		});

	// 나가는문 
	auto door5_open = false;
	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door5_open == true) {
			endGame();
		}
		else {
			showMessage("철커덩");
			door5->setImage("Images/RoomEscape/문-오른쪽-열림.png");
			door5_open = true;
		}
		return true;
		});
	// key callback함수
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		key->pick();
		door1_locked = true;
		showMessage("열쇠를 발견했다.");
		return true;
		});
	auto flowerpot_moved = false;
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool {	
		if(flowerpot_moved==false){
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 550, 320);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 350, 320);
				flowerpot_moved = true;
			}
		}
		else {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 320);
				flowerpot_moved = false;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 450, 320);
				flowerpot_moved = false;
			}
		}
		return true;
	});
	
	startGame(scene1); // 게임시작
	return 0;
}

//왼쪽방에는 스위치를 (끄면- 비밀번호가 보임 )  + 쪽지를 열면 (2진법를 적어라)