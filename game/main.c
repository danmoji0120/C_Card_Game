#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

/*함수모음*/

void Gotoxy(int x, int y) //좌표 
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Cusor() //커서숨기기
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0; // 커서를 보일지 말지 결정(0이면 안보임, 0제외 숫자 값이면 보임)
	cursorInfo.dwSize = 1; // 커서의 크기를 결정 (1~100 사이만 가능)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Square_OutLine(int x, int y) //사각형 생성
{ 

	int i;

	for (i = 0;i <= x*2;i = i + 2) {
		Gotoxy(i, 0);
		printf("■");
	}
	for (i = 1;i <= y-1;i++) {
		Gotoxy(0, i);
		printf("■");
	}
	for (i = 1;i <= y-1;i++) {
		Gotoxy(x*2, i);
		printf("■");
	}
	for (i = 0;i <= x*2;i = i + 2) {
		Gotoxy(i, y);
		printf("■");
	}

}

void Main_Select_Clear() //선택 표시 갱신
{
	Gotoxy(12, 6);
	printf("  ");
	Gotoxy(22, 6);
	printf("  ");
	Gotoxy(34, 6);
	printf("  ");
	Gotoxy(44, 6);
	printf("  ");
	Gotoxy(56, 6);
	printf("  ");
	Gotoxy(66, 6);
	printf("  ");
}

void battle_Select_Clear() //선택 표시 갱신
{
	for (int i = 2;i <= 52;i++) {
		Gotoxy(i, 22);
		printf("  ");
		Gotoxy(i, 29);
		printf("  ");
	}
}

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void Draw_Card(int x, int y, int type, int power)
{
	enum ColorType { RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;

	switch (type)
	{
	case 1: //공격 (빨강)
		for (int i = x; i <= x+6;i += 2) {
			for (int j = y; j <= y+5;j++) {
				Gotoxy(i, j);
				textcolor(RED);
				printf("▩");
			}
		}
		Gotoxy(x + 6, y);
		if (power < 10)
			printf("0%d", power);
		else
			printf("%d", power);
		textcolor(WHITE);
		break;
	case 2: //방어 (파랑)
		for (int i = x; i <= x + 6;i += 2) {
			for (int j = y; j <= y + 5;j++) {
				Gotoxy(i, j);
				textcolor(BLUE);
				printf("▩");
			}
		}
		Gotoxy(x + 6, y);
		if (power < 10)
			printf("0%d", power);
		else
			printf("%d", power);
		textcolor(WHITE);
		break;
	case 3: //치료 (초록)
		for (int i = x; i <= x + 6;i += 2) {
			for (int j = y; j <= y + 5;j++) {
				Gotoxy(i, j);
				textcolor(GREEN);
				printf("▩");
			}
		}
		Gotoxy(x + 6, y);
		if (power < 10)
			printf("0%d", power);
		else
			printf("%d", power);
		textcolor(WHITE);
		break;
	}
}

void Card_Selector()
{
	int select_num = 1;

	Gotoxy(3, 22);
	printf("┌───────┐ ");
	Gotoxy(3, 29);
	printf("└───────┘ ");

	while (1) //입력 및
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1) { //오른쪽
			if (select_num + 1 <= 5) select_num++;
			battle_Select_Clear();

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //왼쪽
			if (select_num - 1 >= 1) select_num--;
			battle_Select_Clear();
		}
		if (GetAsyncKeyState(VK_SPACE) & 1) { //space
			
		}
		switch (select_num) {
		case 1:

			Gotoxy(2, 22);
			printf("┌─────────┐ ");
			Gotoxy(2, 29);
			printf("└─────────┘ ");

			break;
		case 2:
			
			Gotoxy(12, 22);
			printf("┌─────────┐ ");
			Gotoxy(12, 29);
			printf("└─────────┘ ");

			break;
		case 3:
			
			Gotoxy(22, 22);
			printf("┌─────────┐ ");
			Gotoxy(22, 29);
			printf("└─────────┘ ");

			break;
		case 4:
			
			Gotoxy(32, 22);
			printf("┌─────────┐ ");
			Gotoxy(32, 29);
			printf("└─────────┘ ");

			break;
		case 5:
			
			Gotoxy(42, 22);
			printf("┌─────────┐ ");
			Gotoxy(42, 29);
			printf("└─────────┘ ");

			break;
		default:
			break;
		}
	}
}

//화면 출력 사전 정의

int Explanation_Screen();
int Main_Screen();
int battle_Screen();

//화면 출력 함수

int Main_Screen() //메인 화면 출력
{
	int menu_num = 1;

	system("mode con:cols=80 lines=11");        //화면크기
	system("title [danmoji] test_game");    //게임이름

	Square_OutLine(39, 10);

	Gotoxy(35, 3); //메인화면 구성
	printf("테스트게임");

	Gotoxy(14, 6);
	printf("게임시작");

	Gotoxy(36, 6);
	printf("게임설명");

	Gotoxy(58, 6);
	printf("게임종료");

	while (1) //입력 및
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1) { //오른쪽
			if (menu_num + 1 <= 3) menu_num++;
			Main_Select_Clear();

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //왼쪽
			if (menu_num - 1 >= 1) menu_num--;
			Main_Select_Clear();
		}
		if (GetAsyncKeyState(VK_SPACE) & 1) { //space
			if (menu_num == 1) {
				system("cls");
				battle_Screen();
			}
			else if (menu_num == 2) {
				system("cls");
				Explanation_Screen();
				return 0;
				
			}
			else {
				system("cls");
				exit(0);
			}
		}
		switch (menu_num) {
		case 1:
			Gotoxy(12, 6);
			printf("▶");
			Gotoxy(22, 6);
			printf("◀");

			break;
		case 2:
			Gotoxy(34, 6);
			printf("▶");
			Gotoxy(44, 6);
			printf("◀");

			break;
		case 3:
			Gotoxy(56, 6);
			printf("▶");
			Gotoxy(66, 6);
			printf("◀");

			break;
		default:
			break;
		}
	}
}

int Explanation_Screen() //게임 설명 화면 출력
{
	system("mode con:cols=80 lines=31");        //화면크기
	system("title [danmoji] test_game");    //게임이름

	Square_OutLine(39, 30);

	Gotoxy(62,29);
	printf("돌아가려면 ESC..");

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE) & 1) { //esc
			Main_Screen();
			return 0;
		}
	}
}

int battle_Screen() //인게임 시스템
{
	int P_damage, P_Guard, P_Heal, P_Card[2][5], P_HP = 400;
	int E_damage, E_Guard, E_Heal, E_Card[2][5], E_HP = 400;
	int i, j;

	system("mode con:cols=80 lines=31");        //화면크기
	system("title [danmoji] test_game");    //게임이름

	Square_OutLine(39, 30);

	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 21);
		printf("■");
	}
	for (i = 22;i <= 30; i++) {
		Gotoxy(54, i);
		printf("■");
	}

	srand(time(NULL));
	
	for (i = 0;i <= 4;i++) { //[0][i] = power, [1][i] = type
		P_Card[0][i] = rand() % 20 + 1;
		P_Card[1][i] = rand() % 3 + 1; // 1=공격(빨강), 2=방어(파랑), 3=치료(초록)
	}
	for (i = 0;i <= 4;i++) {
		Sleep(500);
		Draw_Card(4+(10*i), 23, P_Card[1][i], P_Card[0][i]);
	}
	Card_Selector();
	
}

/*메인코드*/

void main() {
	Cusor();

	Main_Screen();

}