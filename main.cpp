#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#define row 21
#define col 42
#define MAX 50
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define ENTER 5
#define STOP 6
using namespace std;
void border();
int keyControl();
void main_scene();
int menu();
void level_menu();
void start_menu();
void move(int* x, int* y, int count, int score, int level_choice);
int* star();
bool eat(int x, int y, int* star_rand);
bool crash(int* x, int* y, int count);
void game_over(int score);
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

int main() {
    //system("title Dot.Snake");
    //system(" mode  con lines=30   cols=100 ");
    CursorView(0);
    int x[MAX] = { 4, 0, };
    int y[MAX] = { 5, 0, };
    int count = 1;//����
    int score = 0;//����
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
            move(x, y, count, score, level_choice);
        }
        else if (menu_choice == 9) {//���� �� ����
            system("cls");
            border();
            gotoxy(4, 2);
            cout << "Manual : ��(UP), ��(DOWN), ��(RIGHT), ��(LEFT)";
            gotoxy(4, 4);
            cout << "It is a game that increases the length while eating the stars.";
            gotoxy(4, 6);
            cout << "Eating stars speeds up.";
            gotoxy(4, 8);
            cout << "When it hits the wall, it becomes Game Over.";
            gotoxy(4, 10);
            cout << "When it hits the body, it becomes Game Over.";
            gotoxy(4, 12);
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
            //continue;
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

void main_scene() {
    //��ü ��
    border();
    Sleep(200);
    gotoxy(8, 4);
    setcolor(15, 8);
    cout << " �ˢ�    �ˢ�  �ˢˢ�   �ˢˢˢ� ��    ��   �ˢ�   ��    �� �ˢˢˢ�";
    Sleep(200);
    gotoxy(8, 5);
    setcolor(15, 8);
    cout << " ��  �� ��  ��   ��     ��       �ˢ�  ��  ��  ��  ��  ��   ��      ";
    Sleep(200);
    gotoxy(8, 6);
    setcolor(15, 8);
    cout << " ��  �� ��  ��   ��     �ˢˢˢ� �� �� �� �ˢˢˢ� �ˢ�     �ˢˢˢ�";
    Sleep(200);
    gotoxy(8, 7);
    setcolor(15, 8);
    cout << " ��  �� ��  ��   ��           �� ��  �ˢ� ��    �� ��  ��   ��      ";
    Sleep(200);
    gotoxy(8, 8);
    setcolor(15, 8);
    cout << " �ˢ�    �ˢ�    ��     �ˢˢˢ� ��    �� ��    �� ��    �� �ˢˢˢ�";
    Sleep(500);
    gotoxy(29, 8);
    setcolor(15, 8);
    cout << "��";
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

void move(int* x, int* y, int count, int score, int level_choice)
{
    system("cls");
    border();
    gotoxy(x[0], y[0]);
    cout << "��";
    for (int i = 1; i < count; i++) {//�ʱ� ��� �׸���
        gotoxy(x[i], y[i]);
        cout << "��";
    }

    int* star_rand;//star�Լ��� ���� ���� ��ǥ�� �ޱ� ���� �迭
    while (1) {
        star_rand = star();
        if (star_rand[0] == x[0] || star_rand[1] == y[0]) {
            continue;
        }
        else
            break;
    }
    //gotoxy(0, 24);
    //cout << star_rand[0] << "," << star_rand[1];
    int key = 0;//Ű���� �Է� �����¿� �ޱ� ���� ����
    int key_comp = 0;//�� Ű�� �� Ű �̿����� �ʱ�, �� Ű�� �� Ű �̿����� �ʱ� ���� ����
    int save_x = 0;//���� �Ծ��� �� �߰��� �ֱ� ���� ������
    int save_y = 0;
    //int speed = 200;/
    int speed;//Sleep(speed)�� �ӵ� ����

    do {
        if (count == MAX-1) {
            game_over(score);
        }
        save_x = x[count - 1];
        save_y = y[count - 1];
        if (_kbhit()) {//Ű �Է��� ���� ���� ȭ��ǥ �Է¹ް�, �ƴ� �� �ݺ�
            key = keyControl();
        }

        speed = 200 - (count * ((level_choice-3)/2));
        if (speed <= 0) {
            speed = 1;
        }

        //gotoxy(0, 23);
        //cout << key << "," << key_comp;//Ȯ�ο�

        if ((key_comp == UP && key == DOWN) || (key_comp == DOWN && key == UP) //��� ��, �¿� �찡 �̿����� �ʰ� �ϱ� ����
            || (key_comp == RIGHT && key == LEFT) || (key_comp == LEFT && key == RIGHT)) {
            key = key_comp;//�̿��ǰ� ������ key���� �ٲ�� �ٽ� �ٲ��ֱ�
        }

        switch (key) {
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
                count++; score++;
                x[count - 1] = save_x;
                y[count - 1] = save_y;
                while (1) {
                    star_rand = star();
                    if (star_rand[0] == x[0] || star_rand[1] == y[0]) {
                        continue;
                    }
                    else
                        break;
                }//�� �ٽ� ����
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
                count++; score++;
                x[count - 1] = save_x;
                y[count - 1] = save_y;
                while (1) {
                    star_rand = star();
                    if (star_rand[0] == x[0] || star_rand[1] == y[0]) {
                        continue;
                    }
                    else
                        break;
                }//�� �ٽ� ����
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
                count++; score++;
                x[count - 1] = save_x;
                y[count - 1] = save_y;
                while (1) {
                    star_rand = star();
                    if (star_rand[0] == x[0] || star_rand[1] == y[0]) {
                        continue;
                    }
                    else
                        break;
                }//�� �ٽ� ����
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
                count++; score++;
                x[count - 1] = save_x;
                y[count - 1] = save_y;
                while (1) {
                    star_rand = star();
                    if (star_rand[0] == x[0] || star_rand[1] == y[0]) {
                        continue;
                    }
                    else
                        break;
                }//�� �ٽ� ����
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
            key = key_comp;
            //continue;
        }
        if (key != UP && key != DOWN && key != RIGHT && key != LEFT && key != STOP) {
            key = key_comp;
        }
        if (crash(x, y, count)) {
            game_over(score);
            main();
            break;
        }

        gotoxy(2, 22);
        cout << "SCORE : " << score;
        //while (check) {
           //switch (key)
           //{
           //case UP://�� Ű�� ������ ��
           //   key_comp = key;
           //   while (1) {
           //      if (_kbhit()) {
           //         if (_getch() == 80 || _getch() == 77 || _getch() == 75) {
           //            break;
           //         }
           //      }
           //      if (eat(x[count - 1], y[count - 1] - 1, star_rand)) {//�� ĭ ���� ���� �ִµ�, �� Ű�� ������ ���
           //         count++;
           //         /*for (int i = 0; i < count-1; i++) {
           //            x[count - 1 - i] = x[count - 2 - i];
           //            y[count - 1 - i] = y[count - 2 - i];
           //         }*/
           //         for (int i = 0; i < count - 2; i++) {
           //            y[i]++;
           //         }
           //         x[count - 1] = star_rand[0];
           //         y[count - 1] = star_rand[1];
           //         star_rand = star();
           //         //gotoxy(x[count - 1], y[count - 1]);
           //      }
           //      else {
           //         for (int i = count - 1; i >= 0; i--) {
           //            if (y[i] != 0) {
           //               y[i]--;
           //            }
           //            else
           //               break;
           //         }
           //      }
           //      for (int i = count - 1; i >= 0; i--) {
           //         gotoxy(x[i], y[i]);
           //         cout << "��";
           //      }
           //      gotoxy(x[0], y[0] + 1);
           //      cout << "  ";
           //      Sleep(300);
           //   }
           //   break;
           //case DOWN://�� Ű�� ������ ��
           //   key_comp = key;
           //   while (1) {
           //      
           //      if (eat(x[count - 1], y[count - 1] + 1, star_rand)) {//�� ĭ �ؿ� ���� �ִµ�, �� Ű�� ������ ���
           //         count++;
           //         /*for (int i = 0; i < count-1; i++) {
           //            x[count - 1 - i] = x[count - 2 - i];
           //            y[count - 1 - i] = y[count - 2 - i];
           //         }*/
           //         for (int i = 0; i < count - 2; i++) {
           //            y[i]--;
           //         }
           //         x[count - 1] = star_rand[0];
           //         y[count - 1] = star_rand[1];
           //         star_rand = star();
           //         //gotoxy(x[count - 1], y[count - 1]);
           //      }
           //      else {
           //         for (int i = count - 1; i >= 0; i--) {
           //            if (y[i] != 0) {
           //               y[i]++;
           //            }
           //            else
           //               break;
           //         }
           //      }
           //      for (int i = count - 1; i >= 0; i--) {
           //         gotoxy(x[i], y[i]);
           //         cout << "��";
           //      }
           //      gotoxy(x[0], y[0] - 1);
           //      cout << "  ";
           //      Sleep(300);
           //   }
           //   break;
           //case RIGHT://�� Ű�� ������ ��
           //   key_comp = key;
           //   while (!_kbhit()) {
           //      gotoxy(x[count - 1], y[count - 1]);
           //      for (int i = 0; i < count; i++) {
           //         if (x[i] != 0) {
           //            x[i] += 2;
           //         }
           //         else
           //            break;
           //      }
           //      cout << "  ";
           //      for (int i = 0; i < count; i++) {
           //         gotoxy(x[i], y[i]);
           //         cout << "��";
           //      }
           //      Sleep(300);
           //   }
           //   break;
           //case LEFT://�� Ű�� ������ ��
           //   key_comp = key;
           //   while (!_kbhit()) {
           //      gotoxy(x[count - 1], y[count - 1]);
           //      for (int i = 0; i < count; i++) {
           //         if (x[i] != 0) {
           //            x[i] -= 2;
           //         }
           //         else
           //            break;
           //      }
           //      cout << "  ";
           //      for (int i = 0; i < count; i++) {
           //         gotoxy(x[i], y[i]);
           //         cout << "��";
           //      }
           //      Sleep(300);
           //   }
           //   break;
           //}
           //Sleep(1000);
        //}
    } while (1);
}

int keyControl() {//key�Է� �޴� �Լ�(����Ű)
    int temp = _getch();
    //cout << temp;
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
    else
        return 0;
}

int* star() {
    srand((unsigned int)time(NULL));
    int x_rand = (rand() % (col - 2) + 1) * 2;//�������� ������ ���� x��ǥ
    int y_rand = rand() % (row - 2) + 1;//�������� ������ ���� y��ǥ
    static int rand[2];//���� ��ǥ�� �������ֱ� ����
    rand[0] = x_rand;
    rand[1] = y_rand;
    gotoxy(rand[0], rand[1]);
    cout << "��";

    return rand;
}

bool eat(int x, int y, int* star_rand) {
    if (x == star_rand[0] && y == star_rand[1]) {
        //gotoxy(0, 25);
        //cout << "��";
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
    border();
    gotoxy(4, 2);
    cout << "G A M E  O V E R";
    gotoxy(4, 4);
    cout << "SCORE : " << score;
    gotoxy(4, 6);
    cout << "Press [Enter] to Main";
    setcolor(0, 0);
    if (cin.get() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    setcolor(15, 0);
    system("cls");
}