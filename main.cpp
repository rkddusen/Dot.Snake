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
void CursorView(char show)//커서 숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gotoxy(int x, int y) {//커서 이동
    COORD posXY = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}
void setcolor(int color, int bgcolor)
{
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void border() {//테두리 그려주는 함수
    setcolor(15, 0);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                cout << "■";
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
    int count = 1;//길이
    int score = 0;//점수
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
        if (menu_choice == 7) {//게임 시작
            system("cls");
            border();
            level_menu();//레벨 선택하기
            level_choice = menu();
            move(x, y, count, score, level_choice);
        }
        else if (menu_choice == 9) {//게임 룰 설명
            system("cls");
            border();
            gotoxy(4, 2);
            cout << "Manual : ↑(UP), ↓(DOWN), →(RIGHT), ←(LEFT)";
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
    //전체 맵
    border();
    Sleep(200);
    gotoxy(8, 4);
    setcolor(15, 8);
    cout << " ▦▦    ▦▦  ▦▦▦   ▦▦▦▦ ▦    ▦   ▦▦   ▦    ▦ ▦▦▦▦";
    Sleep(200);
    gotoxy(8, 5);
    setcolor(15, 8);
    cout << " ▦  ▦ ▦  ▦   ▦     ▦       ▦▦  ▦  ▦  ▦  ▦  ▦   ▦      ";
    Sleep(200);
    gotoxy(8, 6);
    setcolor(15, 8);
    cout << " ▦  ▦ ▦  ▦   ▦     ▦▦▦▦ ▦ ▦ ▦ ▦▦▦▦ ▦▦     ▦▦▦▦";
    Sleep(200);
    gotoxy(8, 7);
    setcolor(15, 8);
    cout << " ▦  ▦ ▦  ▦   ▦           ▦ ▦  ▦▦ ▦    ▦ ▦  ▦   ▦      ";
    Sleep(200);
    gotoxy(8, 8);
    setcolor(15, 8);
    cout << " ▦▦    ▦▦    ▦     ▦▦▦▦ ▦    ▦ ▦    ▦ ▦    ▦ ▦▦▦▦";
    Sleep(500);
    gotoxy(29, 8);
    setcolor(15, 8);
    cout << "⊙";
    gotoxy(28, 12);
    setcolor(15, 0);
    cout << "<< Press [Enter] to Start >>";
}

void start_menu() {//첫 메뉴(게임 시작 & 게임 룰 & 게임 종료)
    system("cls");
    border();
    gotoxy(32, 7);
    cout << "> 1. Game Start";
    gotoxy(32, 9);
    cout << "  2. Game Rules";
    gotoxy(32, 11);
    cout << "  3. Exit";
}

void level_menu() {//레벨 고르는 메뉴
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
                gotoxy(menu_x, menu_y);//그 자리
                cout << " ";//먼저 지우고
                menu_y -= 2;
                gotoxy(menu_x, menu_y);//두 칸 위에 올라가기
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
                gotoxy(menu_x, menu_y);//그 자리
                cout << " ";//먼저 지우고
                menu_y += 2;
                gotoxy(menu_x, menu_y);//두 칸 밑에 내려가기
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
    cout << "◎";
    for (int i = 1; i < count; i++) {//초기 모습 그리기
        gotoxy(x[i], y[i]);
        cout << "◈";
    }

    int* star_rand;//star함수로 부터 별의 좌표를 받기 위한 배열
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
    int key = 0;//키보드 입력 상하좌우 받기 위한 변수
    int key_comp = 0;//상 키와 하 키 이웃하지 않기, 좌 키와 우 키 이웃하지 않기 위한 변수
    int save_x = 0;//별을 먹었을 때 추가해 주기 위해 저장함
    int save_y = 0;
    //int speed = 200;/
    int speed;//Sleep(speed)로 속도 조절

    do {
        if (count == MAX-1) {
            game_over(score);
        }
        save_x = x[count - 1];
        save_y = y[count - 1];
        if (_kbhit()) {//키 입력이 있을 때만 화살표 입력받고, 아닐 땐 반복
            key = keyControl();
        }

        speed = 200 - (count * ((level_choice-3)/2));
        if (speed <= 0) {
            speed = 1;
        }

        //gotoxy(0, 23);
        //cout << key << "," << key_comp;//확인용

        if ((key_comp == UP && key == DOWN) || (key_comp == DOWN && key == UP) //상과 하, 좌와 우가 이웃되지 않게 하기 위해
            || (key_comp == RIGHT && key == LEFT) || (key_comp == LEFT && key == RIGHT)) {
            key = key_comp;//이웃되게 누르면 key값이 바뀌니 다시 바꿔주기
        }

        switch (key) {
        case UP:
            key_comp = key;
            gotoxy(x[count - 1], y[count - 1]);//마지막 부분 지우기
            cout << "  ";
            if (count > 1) {//별을 먹은 횟수가 1 이상일 때
                for (int i = 1; i < count; i++) {//0번째가 아닌 나머지
                    x[count - i] = x[count - 1 - i];
                    y[count - i] = y[count - 1 - i];
                }
            }
            x[0] = x[0];//x좌표는 그대로
            y[0] = y[0] - 1;//y좌표는 -1(한 칸 올리기)

            if (eat(x[0], y[0], star_rand)) {//별 먹었을 때
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
                }//별 다시 랜덤
            }
            gotoxy(x[0], y[0]);
            cout << "◎";
            for (int i = 1; i < count; i++) {//그리기
                gotoxy(x[i], y[i]);
                cout << "◈";
            }
            Sleep(speed);
            break;
        case DOWN:
            key_comp = key;
            gotoxy(x[count - 1], y[count - 1]);//마지막 부분 지우기
            cout << "  ";
            if (count > 1) {//별을 먹은 횟수가 1 이상일 때
                for (int i = 1; i < count; i++) {//0번째가 아닌 나머지
                    x[count - i] = x[count - 1 - i];
                    y[count - i] = y[count - 1 - i];
                }
            }
            x[0] = x[0];//x좌표는 그대로
            y[0] = y[0] + 1;//y좌표는 +1(한 칸 내리기)

            if (eat(x[0], y[0], star_rand)) {//별 먹었을 때
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
                }//별 다시 랜덤
            }

            gotoxy(x[0], y[0]);
            cout << "◎";
            for (int i = 1; i < count; i++) {//그리기
                gotoxy(x[i], y[i]);
                cout << "◈";
            }
            Sleep(speed);
            break;
        case RIGHT:
            key_comp = key;
            gotoxy(x[count - 1], y[count - 1]);//마지막 부분 지우기
            cout << "  ";
            if (count > 1) {//별을 먹은 횟수가 1 이상일 때
                for (int i = 1; i < count; i++) {//0번째가 아닌 나머지
                    x[count - i] = x[count - 1 - i];
                    y[count - i] = y[count - 1 - i];
                }
            }
            x[0] = x[0] + 2;//x좌표는 +2(한 칸 오른쪽으로)
            y[0] = y[0];//y좌표는 그대로

            if (eat(x[0], y[0], star_rand)) {//별 먹었을 때
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
                }//별 다시 랜덤
            }

            gotoxy(x[0], y[0]);
            cout << "◎";
            for (int i = 1; i < count; i++) {//그리기
                gotoxy(x[i], y[i]);
                cout << "◈";
            }
            Sleep(speed);
            break;
        case LEFT:
            key_comp = key;
            gotoxy(x[count - 1], y[count - 1]);//마지막 부분 지우기
            cout << "  ";
            if (count > 1) {//별을 먹은 횟수가 1 이상일 때
                for (int i = 1; i < count; i++) {//0번째가 아닌 나머지
                    x[count - i] = x[count - 1 - i];
                    y[count - i] = y[count - 1 - i];
                }
            }
            x[0] = x[0] - 2;//x좌표는 -2(한 칸 왼쪽으로)
            y[0] = y[0];//y좌표는 그대로

            if (eat(x[0], y[0], star_rand)) {//별 먹었을 때
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
                }//별 다시 랜덤
            }

            gotoxy(x[0], y[0]);
            cout << "◎";
            for (int i = 1; i < count; i++) {//그리기
                gotoxy(x[i], y[i]);
                cout << "◈";
            }
            Sleep(speed);
            break;
        case STOP://esc키를 누르면 게임 잠시 멈춤
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
           //case UP://상 키를 눌렀을 때
           //   key_comp = key;
           //   while (1) {
           //      if (_kbhit()) {
           //         if (_getch() == 80 || _getch() == 77 || _getch() == 75) {
           //            break;
           //         }
           //      }
           //      if (eat(x[count - 1], y[count - 1] - 1, star_rand)) {//한 칸 위에 별이 있는데, 상 키를 눌렀을 경우
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
           //         cout << "＠";
           //      }
           //      gotoxy(x[0], y[0] + 1);
           //      cout << "  ";
           //      Sleep(300);
           //   }
           //   break;
           //case DOWN://하 키를 눌렀을 때
           //   key_comp = key;
           //   while (1) {
           //      
           //      if (eat(x[count - 1], y[count - 1] + 1, star_rand)) {//한 칸 밑에 별이 있는데, 하 키를 눌렀을 경우
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
           //         cout << "＠";
           //      }
           //      gotoxy(x[0], y[0] - 1);
           //      cout << "  ";
           //      Sleep(300);
           //   }
           //   break;
           //case RIGHT://우 키를 눌렀을 때
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
           //         cout << "＠";
           //      }
           //      Sleep(300);
           //   }
           //   break;
           //case LEFT://좌 키를 눌렀을 때
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
           //         cout << "＠";
           //      }
           //      Sleep(300);
           //   }
           //   break;
           //}
           //Sleep(1000);
        //}
    } while (1);
}

int keyControl() {//key입력 받는 함수(방향키)
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
    int x_rand = (rand() % (col - 2) + 1) * 2;//랜덤으로 생성될 별의 x좌표
    int y_rand = rand() % (row - 2) + 1;//랜덤으로 생성될 별의 y좌표
    static int rand[2];//별의 좌표를 리턴해주기 위해
    rand[0] = x_rand;
    rand[1] = y_rand;
    gotoxy(rand[0], rand[1]);
    cout << "☆";

    return rand;
}

bool eat(int x, int y, int* star_rand) {
    if (x == star_rand[0] && y == star_rand[1]) {
        //gotoxy(0, 25);
        //cout << "별";
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
    if (count >= 5) {//몸과 부딪히는건 길이가 5이상일 때 가능하므로
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