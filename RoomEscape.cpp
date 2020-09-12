#include <bangtal.h>
using namespace bangtal;

int main() {
	// Scene1 
	auto scene1 = Scene::create("��1", "Images/RoomEscape/���-1.png"); //ùȭ�� �����
	// Scene2
	auto scene2 = Scene::create("��2", "Images/RoomEscape/���-2.png"); //�����ʹ�
	// Scene3
	auto scene3 = Scene::create("��3", "Images/RoomEscape/���-2.png"); // ���ʹ�
	
	// Scene1�� �� 2�� 
	auto door1 = Object::create("Images/RoomEscape/��-������-����.png", scene1, 800, 270); //��1
	auto door2 = Object::create("Images/RoomEscape/��-����-����.png", scene1, 170, 272); // ��2
	
	// Scene3�� �� 1��
	auto door3 = Object::create("Images/RoomEscape/��-������-����.png", scene3, 910, 272); //��3 �����ִ� ����
	
	// Scene2�� �� 2��
	auto door4 = Object::create("Images/RoomEscape/��-����-����.png", scene2, 320, 270);
	auto door5 = Object::create("Images/RoomEscape/��-������-����.png", scene2, 910, 272, false); //������ ��

	//����
	auto key = Object::create("Images/RoomEscape/����.png", scene1, 505, 320);  
	key->setScale(0.2f); // ����ũ�� �۰�
	
	// ȭ��
	auto flowerpot = Object::create("Images/RoomEscape/ȭ��.png", scene1, 450, 320);
	
	// Scene1���� �ݹ�
	auto door1_open = false, door1_locked = false;
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door1_locked == false) {
			showMessage("���� ����ִ�!");
		}
		else if (door1_open == true) {
			scene2->enter();
		}
		else if (key->isHanded()){
			showMessage("öĿ��");
			door1->setImage("Images/RoomEscape/��-������-����.png");
			door1_open = true;
		}
		return true;
		});

	\

	auto door2_open = false, door2_locked = false;
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door2_locked == false) {
			showMessage("���� ����ִ�!");
		}
		else if (door2_open == true) {
			scene3->enter();
			scene3->setLight(0.3f);
			showMessage("���� ��Ӵ�!");
		}
		else{
			door2->setImage("Images/RoomEscape/��-����-����.png");
			door2_open = true;
		}
		return true;
		});
	door2->setOnKeypadCallback([&](ObjectPtr object)->bool {
		door2_locked = true; // �������ִ°�
		showMessage("öĿ��");
		return true;
		});

	// Ű�е� �����
	auto keypad = Object::create("Images/RoomEscape/Ű�е�.png", scene1, 150, 420);
	// Ű�е� Ŭ��
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("MOUSEACTION");
		showKeypad("CLICKDRAG", door2);

		return true;
		});
	//scene3 ���ʹ湮
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		door2->setImage("Images/RoomEscape/��-����-����.png"); //
		showMessage("������ ���� ������! ����??");
		door2_locked = false;
		return true;
		});

	//���ʹ� ����ġ �����
	auto scene3_button = Object::create("Images/RoomEscape/����ġ.png", scene3, 500, 440);
	auto scene3_lighted = false; // �� ���� ����
	auto letter1 = Object::create("Images/RoomEscape/����.png", scene3, 600, 50, false);
	auto letter2 = Object::create("Images/RoomEscape/����.png", scene3, 650, 70, false);
	auto letter3 = Object::create("Images/RoomEscape/����.png", scene3, 700, 30, false);
	letter1->setScale(0.1f);
	letter2->setScale(0.1f);
	letter3->setScale(0.1f);
	//���ʹ� ���ѱ�
	scene3_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (scene3_lighted == false) { //�Ҳ������¿��� �ѱ�
			scene3->setLight(1.0f);
			letter1->show();
			letter2->show();
			letter3->show();
			scene3_lighted = true;
		}
		else { //���������¿��� ����
			scene3->setLight(0.3f);
			scene3_lighted = false;
			letter1->hide();
			letter2->hide();
			letter3->hide();
		}
		return true;
		});
	//����3�� ��Ʈ ������ֱ�
	letter1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("��");
		return true;
		});
	letter2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("2");
		return true;
		});
	letter3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("��");
		return true;
		});
	//������ �� �ٹ̱� 
	//����
	auto quiz = Object::create("Images/RoomEscape/����.jpg",scene2, 500, 40);
	quiz->setScale(0.1f);

	//���� ��
	quiz->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		quiz->pick();
		showMessage("������ �信 4�� ���϶�");
		return true;
		});

	//��ư 4��
	auto scene2_button1 = Object::create("Images/RoomEscape/����ġ.png", scene2, 500, 440);
	auto button1_press = false;
	auto scene2_button2 = Object::create("Images/RoomEscape/����ġ.png", scene2, 515, 440);
	auto button2_press = false;
	auto scene2_button3 = Object::create("Images/RoomEscape/����ġ.png", scene2, 530, 440);
	auto button3_press = false;
	auto scene2_button4 = Object::create("Images/RoomEscape/����ġ.png", scene2, 545, 440);
	auto button4_press = false;

	//��ư 4���߿� �������� �������� �� ����
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
	// scene1�� ���� ��
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene1->enter();
		return true;
		});

	// �����¹� 
	auto door5_open = false;
	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (door5_open == true) {
			endGame();
		}
		else {
			showMessage("öĿ��");
			door5->setImage("Images/RoomEscape/��-������-����.png");
			door5_open = true;
		}
		return true;
		});
	// key callback�Լ�
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		key->pick();
		door1_locked = true;
		showMessage("���踦 �߰��ߴ�.");
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
	
	startGame(scene1); // ���ӽ���
	return 0;
}

//���ʹ濡�� ����ġ�� (����- ��й�ȣ�� ���� )  + ������ ���� (2������ �����)