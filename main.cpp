#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
//#define row 21//���� ����
//#define col 42//���� ����
#define MAX 100//snake �ִ� ����
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define ENTER 5
#define STOP 6
#define DASH 7
using namespace std;

enum Color
{
	BLUE = 1,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

void border();
int keyControl();
void main_scene();
int menu();
void level_menu();
void start_menu();
int style_menu();
void move(int* x, int* y, int count, int score, int level_choice, int color);
int* star(int* x, int* y, int count);
bool eat(int x, int y, int* star_rand);
bool crash(int* x, int* y, int count);
void game_over(int score);
int col = 42;
int row = 21;

void CursorView(char show)//Ŀ�� �����
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gotoxy(int x, int y) {//Ŀ�� �̵�
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}
void setcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void border() {//�׵θ� �׷��ִ� �Լ�
	setcolor(15, 0);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
				cout << "��";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
}

int best_score = 0;


int main() {
	CursorView(0);
	int x[MAX] = { 6, 0, };
	int y[MAX] = { 10, 0, };
	int count = 1;//����
	float score = 0;//����
	main_scene();
	setcolor(0, 0);
	if (cin.get() != '\n') {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	int menu_choice = 0;
	int level_choice = 0;
	system("cls");
	do {
		start_menu();
		menu_choice = menu();
		if (menu_choice == 7) {//���� ����
			system("cls");
			border();
			level_menu();//���� �����ϱ�
			level_choice = menu();
			int color = style_menu();
			move(x, y, count, score, level_choice, color);
		}
		else if (menu_choice == 9) {//���� �� ����
			system("cls");
			border();
			gotoxy(4, 2);
			cout << "Manual : ��(UP), ��(DOWN), ��(RIGHT), ��(LEFT), [Space bar](DASH)";
			gotoxy(4, 4);
			cout << "It is a game that increases the length while eating the stars.";
			gotoxy(4, 6);
			cout << "Eating stars speeds up.";
			gotoxy(4, 8);
			cout << "Press the [Space bar] to Dash. But you're score will be lowered";
			gotoxy(4, 10);
			cout << "When it hits the wall, it becomes Game Over.";
			gotoxy(4, 12);
			cout << "When it hits the body, it becomes Game Over.";
			gotoxy(4, 14);
			cout << "Press the [esc] during the game to pause, and press [Enter] to resume.";
			gotoxy(4, 18);
			cout << "Press [Enter] to Return";
			setcolor(0, 0);
			if (cin.get() != '\n') {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			setcolor(15, 0);
			system("cls");
			border();
		}
		else if (menu_choice == 11) {//exit
			system("cls");
			border();
			gotoxy(4, 2);
			cout << "The game ends." << endl;
			Sleep(1000);
			return 0;
		}
	} while (menu_choice != 11);

	return 0;
}

void main_scene() {//����ȭ�� �׸���
	border();
	Sleep(200);
	gotoxy(8, 4);
	setcolor(15, 8);
	cout << " �ˢ�    �ˢ�  �ˢˢ�   �ˢˢˢ� ��    ��   �ˢ�   ��    �� �ˢˢˢ�";
	Sleep(200);
	gotoxy(8, 5);
	setcolor(15, 8);
	cout << " �� ��  ��  ��   ��     ��       �ˢ�  ��  ��  ��  ��  ��   ��      ";
	Sleep(200);
	gotoxy(8, 6);
	setcolor(15, 8);
	cout << " ��  �� ��  ��   ��     �ˢˢˢ� �� �� �� �ˢˢˢ� �ˢ�     �ˢˢˢ�";
	Sleep(200);
	gotoxy(8, 7);
	setcolor(15, 8);
	cout << " �� ��  ��  ��   ��           �� ��  �ˢ� ��    �� ��  ��   ��      ";
	Sleep(200);
	gotoxy(8, 8);
	setcolor(15, 8);
	cout << " �ˢ�    �ˢ�    ��     �ˢˢˢ� ��    �� ��    �� ��    �� �ˢˢˢ�";
	Sleep(400);
	gotoxy(29, 8);
	setcolor(15, 8);
	cout << "��";
	Sleep(400);
	gotoxy(28, 12);
	setcolor(15, 0);
	cout << "<< Press [Enter] to Start >>";
}

void start_menu() {//ù �޴�(���� ���� & ���� �� & ���� ����)
	system("cls");
	border();
	gotoxy(32, 7);
	cout << "> 1. Game Start";
	gotoxy(32, 9);
	cout << "  2. Game Rules";
	gotoxy(32, 11);
	cout << "  3. Exit";
}

void level_menu() {//���� ���� �޴�
	system("cls");
	border();
	gotoxy(32, 7);
	cout << "> 1. Level 1";
	gotoxy(32, 9);
	cout << "  2. Level 2";
	gotoxy(32, 11);
	cout << "  3. Level 3";
}

int menu() {

	int menu_key = 0;
	int menu_x = 32;
	int menu_y = 7;
	do {
		menu_key = keyControl();
		switch (menu_key) {
		case UP:
			if (menu_y > 7) {
				gotoxy(menu_x, menu_y);//�� �ڸ�
				cout << " ";//���� �����
				menu_y -= 2;
				gotoxy(menu_x, menu_y);//�� ĭ ���� �ö󰡱�
				cout << ">";

			}
			else if (menu_y == 7) {
				gotoxy(menu_x, menu_y);
				cout << " ";
				gotoxy(menu_x, 11);
				cout << ">";
				menu_y = 11;
			}
			break;

		case DOWN:
			if (menu_y < 11) {
				gotoxy(menu_x, menu_y);//�� �ڸ�
				cout << " ";//���� �����
				menu_y += 2;
				gotoxy(menu_x, menu_y);//�� ĭ �ؿ� ��������
				cout << ">";
			}
			else if (menu_y == 11) {
				gotoxy(menu_x, menu_y);
				cout << " ";
				gotoxy(menu_x, 7);
				cout << ">";
				menu_y = 7;
			}
			break;
		case ENTER:
			return menu_y;
		}

	} while (menu_key != ENTER);
}

int style_menu() {
	system("cls");
	border();
	gotoxy(4, 2);
	cout << "Choose Color";

	//���
	setcolor(BLUE, 0); gotoxy(16, 7); cout << "> BLUE";
	setcolor(GREEN, 0); gotoxy(35, 7); cout << "  GREEN";
	setcolor(CYAN, 0); gotoxy(54, 7); cout << "  CYAN";
	setcolor(RED, 0); gotoxy(16, 9); cout << "  RED";
	setcolor(MAGENTA, 0); gotoxy(35, 9); cout << "  MAGENTA";
	setcolor(BROWN, 0); gotoxy(54, 9); cout << "  BROWN";
	setcolor(LIGHTGRAY, 0); gotoxy(16, 11); cout << "  LIGHT_GRAY";
	setcolor(DARKGRAY, 0); gotoxy(35, 11); cout << "  DARK_GRAY";
	setcolor(LIGHTBLUE, 0); gotoxy(54, 11); cout << "  LIGHT_BLUE";
	setcolor(LIGHTGREEN, 0); gotoxy(16, 13); cout << "  LIGHT_GREEN";
	setcolor(LIGHTCYAN, 0); gotoxy(35, 13); cout << "  LIGHT_CYAN";
	setcolor(LIGHTRED, 0); gotoxy(54, 13); cout << "  LIGHT_RED";
	setcolor(LIGHTMAGENTA, 0); gotoxy(16, 15); cout << "  LIGHT_MAGENTA";
	setcolor(YELLOW, 0); gotoxy(35, 15); cout << "  YELLOW";
	setcolor(WHITE, 0); gotoxy(54, 15); cout << "  WHITE";

	int style_key;
	int style_x = 16;
	int style_y = 7;
	do {
		style_key = keyControl();
		switch (style_key) {
		case UP:
			if (style_y > 7) {
				gotoxy(style_x, style_y);//�� �ڸ�
				cout << " ";//���� �����
				style_y -= 2;
				gotoxy(style_x, style_y);//�� ĭ ���� �ö󰡱�
				cout << ">";

			}
			else if (style_y == 7) {
				gotoxy(style_x, style_y);
				cout << " ";
				gotoxy(style_x, 15);
				cout << ">";
				style_y = 15;
			}
			break;

		case DOWN:
			if (style_y < 15) {
				gotoxy(style_x, style_y);//�� �ڸ�
				cout << " ";//���� �����
				style_y += 2;
				gotoxy(style_x, style_y);//�� ĭ �ؿ� ��������
				cout << ">";
			}
			else if (style_y == 15) {
				gotoxy(style_x, style_y);
				cout << " ";
				gotoxy(style_x, 7);
				cout << ">";
				style_y = 7;
			}
			break;

		case RIGHT:
			if (style_x < 54) {
				gotoxy(style_x, style_y);//�� �ڸ�
				cout << " ";//���� �����
				style_x += 19;
				gotoxy(style_x, style_y);//�� ĭ ���� �ö󰡱�
				cout << ">";

			}
			else if (style_x == 54) {
				gotoxy(style_x, style_y);
				cout << " ";
				gotoxy(16, style_y);
				cout << ">";
				style_x = 16;
			}
			break;

		case LEFT:
			if (style_x > 16) {
				gotoxy(style_x, style_y);//�� �ڸ�
				cout << " ";//���� �����
				style_x -= 19;
				gotoxy(style_x, style_y);//�� ĭ ���� �ö󰡱�
				cout << ">";

			}
			else if (style_x == 16) {
				gotoxy(style_x, style_y);
				cout << " ";
				gotoxy(54, style_y);
				cout << ">";
				style_x = 54;
			}
			break;
		case ENTER:
			if (style_x == 16 && style_y == 7) return BLUE;
			else if (style_x == 35 && style_y == 7) return GREEN;
			else if (style_x == 54 && style_y == 7) return CYAN;
			else if (style_x == 16 && style_y == 9) return RED;
			else if (style_x == 35 && style_y == 9) return MAGENTA;
			else if (style_x == 54 && style_y == 9) return BROWN;
			else if (style_x == 16 && style_y == 11) return LIGHTGRAY;
			else if (style_x == 35 && style_y == 11) return DARKGRAY;
			else if (style_x == 54 && style_y == 11) return LIGHTBLUE;
			else if (style_x == 16 && style_y == 13) return LIGHTGREEN;
			else if (style_x == 35 && style_y == 13) return LIGHTCYAN;
			else if (style_x == 54 && style_y == 13) return LIGHTRED;
			else if (style_x == 16 && style_y == 15) return LIGHTMAGENTA;
			else if (style_x == 35 && style_y == 15) return YELLOW;
			else return WHITE;
		}
	} while (style_key != ENTER);

	return 0;
}

void move(int* x, int* y, int count, int score, int level_choice, int color)
{
	system("cls");
	border();
	setcolor(color, 0);
	gotoxy(x[0], y[0]);
	cout << "��";
	for (int i = 1; i < count; i++) {//�ʱ� ��� �׸���
		gotoxy(x[i], y[i]);
		cout << "��";
	}

	int* star_rand;//star�Լ��� ���� ���� ��ǥ�� �ޱ� ���� �迭
	star_rand = star(x, y, count);
	setcolor(color, 0);

	int key = 0;//Ű���� �Է� �����¿� �ޱ� ���� ����
	int key_comp = 0;//�� Ű�� �� Ű �̿����� �ʱ�, �� Ű�� �� Ű �̿����� �ʱ� ���� ����
	int save_x = 0;//���� �Ծ��� �� �߰��� �ֱ� ���� ������
	int save_y = 0;
	int speed;//Sleep(speed)�� �ӵ� ����
	int dash_check = 0;//dash üũ
	do {
		if (count == MAX - 1) {//�̱�� ����(------------------------------------------->�ڵ� �����ؾ���)
			game_over(score);
		}
		save_x = x[count - 1];
		save_y = y[count - 1];
		if (_kbhit()) {//Ű �Է��� ���� ���� ȭ��ǥ �Է¹ް�, �ƴ� �� �ݺ�
			key = keyControl();
		}

		if (dash_check > 0)
			speed = 10;
		else
			speed = 200 - (count * ((level_choice - 4)));


		if (speed <= 0) {
			speed = 1;
		}

		if ((key_comp == UP && key == DOWN) || (key_comp == DOWN && key == UP) //��� ��, �¿� �찡 �̿����� �ʰ� �ϱ� ����
			|| (key_comp == RIGHT && key == LEFT) || (key_comp == LEFT && key == RIGHT)) {
			key = key_comp;//�̿��ǰ� ������ key���� �ٲ�� �ٽ� �ٲ��ֱ�
		}
		switch (key) {
		case DASH:
			key = key_comp;
			if (count == 1) {
				dash_check = 0;
			}
			else {
				gotoxy(x[count - 1], y[count - 1]);//������ �κ� �����
				cout << "  ";
				dash_check = 4;
				count--;
				score--;;
			}
			break;
		case UP:
			key_comp = key;
			gotoxy(x[count - 1], y[count - 1]);//������ �κ� �����
			cout << "  ";
			if (count > 1) {//���� ���� Ƚ���� 1 �̻��� ��
				for (int i = 1; i < count; i++) {//0��°�� �ƴ� ������
					x[count - i] = x[count - 1 - i];
					y[count - i] = y[count - 1 - i];
				}
			}
			x[0] = x[0];//x��ǥ�� �״��
			y[0] = y[0] - 1;//y��ǥ�� -1(�� ĭ �ø���)

			if (eat(x[0], y[0], star_rand)) {//�� �Ծ��� ��
				count++; score++; //bomb_count++;
				x[count - 1] = save_x;
				y[count - 1] = save_y;
				star_rand = star(x, y, count);
				setcolor(color, 0);
			}
			gotoxy(x[0], y[0]);
			cout << "��";
			for (int i = 1; i < count; i++) {//�׸���
				gotoxy(x[i], y[i]);
				cout << "��";
			}
			Sleep(speed);
			break;

		case DOWN:
			key_comp = key;
			gotoxy(x[count - 1], y[count - 1]);//������ �κ� �����
			cout << "  ";
			if (count > 1) {//���� ���� Ƚ���� 1 �̻��� ��
				for (int i = 1; i < count; i++) {//0��°�� �ƴ� ������
					x[count - i] = x[count - 1 - i];
					y[count - i] = y[count - 1 - i];
				}
			}
			x[0] = x[0];//x��ǥ�� �״��
			y[0] = y[0] + 1;//y��ǥ�� +1(�� ĭ ������)

			if (eat(x[0], y[0], star_rand)) {//�� �Ծ��� ��
				count++; score++; //bomb_count++;
				x[count - 1] = save_x;
				y[count - 1] = save_y;
				star_rand = star(x, y, count);//�� �ٽ� ����
				setcolor(color, 0);
			}

			gotoxy(x[0], y[0]);
			cout << "��";
			for (int i = 1; i < count; i++) {//�׸���
				gotoxy(x[i], y[i]);
				cout << "��";
			}
			Sleep(speed);
			break;

		case RIGHT:
			key_comp = key;
			gotoxy(x[count - 1], y[count - 1]);//������ �κ� �����
			cout << "  ";
			if (count > 1) {//���� ���� Ƚ���� 1 �̻��� ��
				for (int i = 1; i < count; i++) {//0��°�� �ƴ� ������
					x[count - i] = x[count - 1 - i];
					y[count - i] = y[count - 1 - i];
				}
			}
			x[0] = x[0] + 2;//x��ǥ�� +2(�� ĭ ����������)
			y[0] = y[0];//y��ǥ�� �״��

			if (eat(x[0], y[0], star_rand)) {//�� �Ծ��� ��
				count++; score++; //bomb_count++;
				x[count - 1] = save_x;
				y[count - 1] = save_y;
				star_rand = star(x, y, count);//�� �ٽ� ����
				setcolor(color, 0);
			}

			gotoxy(x[0], y[0]);
			cout << "��";
			for (int i = 1; i < count; i++) {//�׸���
				gotoxy(x[i], y[i]);
				cout << "��";
			}
			Sleep(speed);
			break;

		case LEFT:
			key_comp = key;
			gotoxy(x[count - 1], y[count - 1]);//������ �κ� �����
			cout << "  ";
			if (count > 1) {//���� ���� Ƚ���� 1 �̻��� ��
				for (int i = 1; i < count; i++) {//0��°�� �ƴ� ������
					x[count - i] = x[count - 1 - i];
					y[count - i] = y[count - 1 - i];
				}
			}
			x[0] = x[0] - 2;//x��ǥ�� -2(�� ĭ ��������)
			y[0] = y[0];//y��ǥ�� �״��

			if (eat(x[0], y[0], star_rand)) {//�� �Ծ��� ��
				count++; score++; //bomb_count++;
				x[count - 1] = save_x;
				y[count - 1] = save_y;
				star_rand = star(x, y, count);//�� �ٽ� ����
				setcolor(color, 0);
			}

			gotoxy(x[0], y[0]);
			cout << "��";
			for (int i = 1; i < count; i++) {//�׸���
				gotoxy(x[i], y[i]);
				cout << "��";
			}
			Sleep(speed);
			break;

		case STOP://escŰ�� ������ ���� ��� ����
			gotoxy(2, 23);
			cout << "STOP";
			gotoxy(2, 25);
			cout << "Press [Enter] to Start";
			setcolor(0, 0);
			if (cin.get() != '\n') {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			setcolor(15, 0);
			gotoxy(2, 23);
			cout << "           ";
			gotoxy(2, 25);
			cout << "                          ";
			key = key_comp;//������ ���� ����
			break;
		}
		if (key != UP && key != DOWN && key != RIGHT && key != LEFT && key != STOP) {
			key = key_comp;
		}
		if (crash(x, y, count)) {
			game_over(score);
			main();
			break;
		}
		if (dash_check > 0)
			dash_check--;

		//���� ��¦�̴� ȿ���� �ֱ� ����
		if (x[0] % 4 == 0 && y[0] % 2 == 0) {
			gotoxy(star_rand[0], star_rand[1]);
			cout << "  ";
		}
		else if (x[0] % 4 == 2 && y[0] % 2 == 1) {
			gotoxy(star_rand[0], star_rand[1]);
			cout << "  ";
		}
		else {
			setcolor(YELLOW, 0);
			gotoxy(star_rand[0], star_rand[1]);
			cout << "��";
			setcolor(color, 0);
		}

		//�� �Ʒ��� ���� ����
		setcolor(WHITE, 0);
		gotoxy(2, 22);
		cout << "SCORE : " << score;
		setcolor(color, 0);
	} while (1);
}

int keyControl() {//key�Է� �޴� �Լ�(����Ű)
	int temp = _getch();
	if (temp == 72)
		return UP;
	else if (temp == 80)
		return DOWN;
	else if (temp == 77)
		return RIGHT;
	else if (temp == 75)
		return LEFT;
	else if (temp == '\r')
		return ENTER;
	else if (temp == 27)
		return STOP;
	else if (temp == 32)
		return DASH;
	else
		return 0;
}

int* star(int* x, int* y, int count) {
	int star_check = 1;
	int x_rand, y_rand;
	while (star_check) {
		star_check = 0;
		srand((unsigned int)time(NULL));
		x_rand = (rand() % (col - 2) + 1) * 2;//�������� ������ ���� x��ǥ
		y_rand = rand() % (row - 2) + 1;//�������� ������ ���� y��ǥ
		for (int i = 0; i < count; i++) {
			if (x_rand == x[i] && y_rand == y[i]) {
				star_check++;
			}
		}
	}
	static int rand[2];//���� ��ǥ�� �������ֱ� ����
	rand[0] = x_rand;
	rand[1] = y_rand;
	setcolor(YELLOW, 0);
	gotoxy(rand[0], rand[1]);
	cout << "��";

	return rand;
}

bool eat(int x, int y, int* star_rand) {
	if (x == star_rand[0] && y == star_rand[1]) {
		gotoxy(x, y);
		return true;
	}
	else
		return false;
}

bool crash(int* x, int* y, int count) {
	if (x[0] == 0 || x[0] == 2 * (col - 1) || y[0] == 0 || y[0] == row - 1) {
		return true;
	}
	if (count >= 5) {//���� �ε����°� ���̰� 5�̻��� �� �����ϹǷ�
		for (int i = 1; i < count; i++) {
			if (x[0] == x[i] && y[0] == y[i]) {
				return true;
			}
		}
	}

	return false;
}

void game_over(int score) {
	system("cls");
	col = 42; row = 21;
	border();
	gotoxy(4, 2);
	cout << "G "; Sleep(200);
	cout << "A "; Sleep(200);
	cout << "M "; Sleep(200);
	cout << "E "; Sleep(200);
	cout << "  "; Sleep(200);
	cout << "O "; Sleep(200);
	cout << "V "; Sleep(200);
	cout << "E "; Sleep(200);
	cout << "R "; Sleep(300);
	gotoxy(4, 4);
	if (score > best_score) {
		best_score = score;
		cout << "Congratulations! It's a Best Score!";
	}
	else
		cout << "Try Again...";
	gotoxy(4, 6);
	cout << "Score : " << score;
	gotoxy(4, 8);
	cout << "Best Score : " << best_score;
	gotoxy(4, 10);
	cout << "Press [Enter] to Main";
	setcolor(0, 0);
	if (cin.get() != '\n') {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	setcolor(15, 0);
	system("cls");
}

