#include <iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;
bool GOver;
const int wid =50; //ширина и высота игрового поля 
const int hei = 20;
int x, y, fx, fy, score, ltail;
int lvl;
int tx[100], ty[100]; //описание коородинат хвоста

enum control {stop = 0, LEFT, RIGHT, UP, DOWN }; //класс управления;
control con;
void set() { //установка стартовых значений
	GOver = false;
	con = stop;
	srand(time(0));
	x = rand() % wid;
	y = rand() % hei;
	fx = rand() % wid;
	fy = rand() % hei;
	score = 0;
	ltail = 0;
}
void dr() {	//прорисовка игрового поля
	system("cls");	//очистка терминала;
	for (int i = 0; i <= wid+1;i++) //прорисовка верхней границы
		cout << "#";
	cout << endl;
	for (int i = 0;i < hei;i++) { //прорисовка боковых границ, фрукта и змейки
		for (int j = 0;j < wid+1;j++) {
			if ((j == 0) || (j == wid))
				cout << "|";
			if (i == y && j == x)
				cout << "o";
			else if (i == fy && j == fx)
				cout << "@";
			else {
				bool wrt = false; //необходимость удлинять хвост
				for (int k = 0; k < ltail;k++)
					if (tx[k] == j && ty[k] == i) {
						wrt = true;
						cout << "*";
					}
				if (!wrt)
				cout << " ";
			}
		}
		cout << endl;
		
	}

	for (int i = 0; i < wid+2;i++) // прорисовки нижний границы
		cout << "#";
	cout << endl;
	cout << "Score: " <<score<< endl; //счетчик очков

}
void contrl() {
	if (_kbhit()) { //управление змейкой с помощью WASD
		switch (_getch()) {
		case 'a':
			con = LEFT;
			break;
		case 'd':
			con = RIGHT;
			break;
		case 's':
			con = DOWN;
			break;
		case 'w':
			con = UP;
			break;
		}
	}
}
void play() {
	int prex = tx[0]; //предыдущие координаты точки хвоста
	int prey = ty[0];
	int prex2, prey2; //пред предыдущие координаты точки хвоста
	tx[0] = x; ty[0] = y; //координаты головы
	for (int i = 1; i < ltail;i++) { //движение хвоста (сдвиг)
		prex2 = tx[i];
		prey2 = ty[i];
		tx[i] = prex;
		ty[i] = prey;
		prex = prex2;
		prey = prey2;

	}

	switch (con) { //движение головы змеи
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;

	}
	if (x > wid || x<0 || y>hei || y < 0) //проверка врезание в стенку
		GOver = true;
	for (int i = 0; i < ltail;i++) { //проверка врезание в хвост
		if (tx[i] == x && ty[i] == y)
			GOver = true;
	}
	if (x == fx && y == fy) { //перемещение фрукта при условии, что он съеден
		score+=lvl;
		ltail++;
		fx = rand() % wid;
		fy = rand() % hei;
	}
}
int main() {
	
	int cont = 1; //запуск новой игры пока cont=1
	while (cont == 1) {
		set();
		cout << "Choose speed: " << endl
			<< "Slow -> 1" << endl
			<< "Middle -> 2" << endl
			<< "Fast -> 3" << endl;
		int speed;
		cin >> lvl; //выбор уровня
		switch (lvl) {
		case 1:
			speed = 250;
			break;
		case 2:
			speed = 150;
			break;
		case 3:
			speed = 75;
			break;
		default: cout << "Error" << endl;
		}
		if (lvl >= 1 && lvl <= 3) { //проверка на допустимость переменной lvl
			while (!GOver) {
				dr();
				contrl();
				play();
				Sleep(speed);
				
			}
			cout << "Game over!!!" << endl;
			cout << "Your score is " << score << endl;
		}
		cout << "Press 1 and ENTER to continue" << endl;
		cin >> cont;
	}
	return 0;
}