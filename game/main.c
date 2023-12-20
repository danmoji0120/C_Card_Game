#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#pragma warning(disable:6385)
#pragma warning(disable:4244)
#pragma warning(disable:4101)
 

/*전역변수 선언*/
int P_Card[2][5], P_Select[2]; //P_Select[0] = power, P_Select[1] = cost
int E_Card[2][5], E_Select[2];
int GP_HP, GE_HP, GP_Guard, GE_Guard, GP_FullHP=20, GE_FullHP=20;

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

void win_sound()
{
	Beep(200, 50);
	Sleep(20);
	Beep(300, 50);
	Sleep(20);
	Beep(500, 70);
	Sleep(20);
}

void game_win()
{
	Beep(200, 400);
	Sleep(20);
	Beep(200, 100);
	Sleep(10);
	Beep(200, 100);
	Sleep(10);
	Beep(500, 100);
	Sleep(10);
	Beep(500, 100);
	Sleep(10);
	Beep(500, 100);
	Sleep(10);
	Beep(590, 1100);
	Sleep(100);
}

void game_defeat()
{
	Beep(400, 200);
	Sleep(20);
	Beep(300, 200);
	Sleep(10);
	Beep(200, 200);
	Sleep(10);
	Beep(150, 800);
	Sleep(10);
}

void defeat_sound()
{
	Beep(300, 50);
	Sleep(20);
	Beep(200, 50);
	Sleep(20);
	Beep(100, 70);
	Sleep(20);
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
	int i;
	for (i = 2;i <= 52;i++) {
		Gotoxy(i, 22);
		printf("  ");
		Gotoxy(i, 29);
		printf("  ");
	}
}

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void Draw_Card(int x, int y, int type, int power, BOOL flip)
{
	enum ColorType { RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;
	int i,j;
	switch (type)
	{
	case 1: //공격 (빨강)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
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
		}
		else {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(RED);
					printf("▩");
				}
			}
		}
		textcolor(WHITE);
		break;
	case 2: //방어 (파랑)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
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
		}
		else {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(BLUE);
					printf("▩");
				}
			}
		}
		textcolor(WHITE);
		break;
	case 3: //치료 (초록)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
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
		}
		else {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(GREEN);
					printf("▩");
				}
			}
		}
		textcolor(WHITE);
		break;
	}
}

int Card_Selector()
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
			Beep(200, 50);
		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //왼쪽
			if (select_num - 1 >= 1) select_num--;
			battle_Select_Clear();
			Beep(200, 50);
		}
		if (GetAsyncKeyState(VK_SPACE) & 1) { //space
			battle_Select_Clear();
			Beep(500, 25);
			Sleep(10);
			Beep(200, 25);
			Sleep(100);
			return select_num;
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

void Battle_Display_Update() //배틀화면 ui 표시
{
	enum ColorType { D_RED = 4, RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;


	Gotoxy(56,24);
	printf("                ");
	Gotoxy(56, 24);
	textcolor(D_RED);
	printf("체력: %d/%d", GP_HP, GP_FullHP);

	Gotoxy(2, 3);
	printf("                ");
	Gotoxy(2, 3);
	textcolor(D_RED);
	printf("체력: %d/%d", GE_HP, GE_FullHP);

	Gotoxy(56, 25);
	printf("                ");
	Gotoxy(56, 25);
	textcolor(1); //D_BLUE
	printf("방어막: %d", GP_Guard);

	Gotoxy(2, 4);
	printf("                ");
	Gotoxy(2, 4);
	textcolor(1); //D_BLUE
	printf("방어막: %d", GE_Guard);
}

void Card_remover()
{
	int i,x,y;
	for (i = 0;i <= 4;i++) { //플레이어 덱 정리
		for (x = 4 + (10 * i); x <= 4 + (10 * i) + 6; x += 2) {
			for (y = 23; y <= 23 + 5;y++) {
				Gotoxy(x, y);
				printf("  ");
			}
		}
	}
	for (i = 0;i <= 4;i++) { //적 덱 정리
		for (x = 28 + (10 * i); x <= 28 + (10 * i) + 6; x += 2) {
			for (y = 2; y <= 2 + 5;y++) {
				Gotoxy(x, y);
				printf("  ");
			}
		}
	}
	for (x = 24; x <= 30; x += 2) { //플레이어 소환카드정리
		for (y = 14; y <= 19;y++) {
			Gotoxy(x, y);
			printf("  ");
		}
	}
	for (x = 48; x <= 54; x += 2) { //적 소환카드정리
		for (y = 11; y <= 16;y++) {
			Gotoxy(x, y);
			printf("  ");
		}
	}
	

}

void Battle_Round_Result(BOOL player_win)
{
	int Card[2];
	Sleep(1500);
	if (player_win == TRUE) { //유리가 누구인가
		Card[0] = P_Select[0];
		Card[1] = P_Select[1];
	}
	else {
		Card[0] = E_Select[0];
		Card[1] = E_Select[1];
	}

	switch (Card[1]) //타입이 무엇인가
	{
	case 1: //공격
		if (player_win == TRUE) {
			if (GE_Guard > 0) { //방어막이 있나?
				if (GE_Guard - Card[0] < 0) { //방어막 초과치인가
					GE_Guard = 0;
				}
				else {
					GE_Guard = GE_Guard - Card[0];
				}
			}
			else {
				GE_HP = GE_HP - Card[0];
				
			}
			win_sound();
		}
		else {
			if (GP_Guard > 0) { //방어막이 있나?
				if (GP_Guard - Card[0] < 0) { //방어막 초과치인가
					GP_Guard = 0;
				}
				else {
					GP_Guard = GP_Guard - Card[0];
				}
			}
			else {
				GP_HP = GP_HP - Card[0];
			}
			defeat_sound();
		}
		break;
	case 2: //방어
		if (player_win == TRUE) {
			if ((Card[0] / 2) < 1) {
				GP_Guard += 1;
			}
			else {
				GP_Guard += Card[0] / 2;
			}
			win_sound();
		}
		else {
			if ((Card[0] / 2) < 1) {
				GE_Guard += 1;
			}
			else {
				GE_Guard += Card[0] / 2;
			}
			defeat_sound();
		}
		break;
	case 3: //치료
		if (player_win == TRUE) {
			if (GP_HP + Card[0] > GP_FullHP) {
				GP_HP = GP_FullHP;
			}
			else {
				GP_HP += Card[0];
			}
			win_sound();
		}
		else {
			if(GE_HP + Card[0] > GE_FullHP) {
				GE_HP = GE_FullHP;
			}
			else {
				GE_HP += Card[0];
				}
			defeat_sound();
		}
		break;
	}
	Sleep(500);
}

void Battle_system(BOOL intelligence)
{
	int i;

	int P_AT_Card = 0, P_GU_Card = 0, P_HE_Card = 0; // 플레이어 타입별 카드갯수

	int E_AT_Card_max[2], E_GU_Card_max[2], E_HE_Card_max[2]; //적 카드사용을 위한 가장 강한 카드([0] = power,[1] = 존재여부 (0 = 없음, 1 = 있음))

	while (GP_HP > 0 && GE_HP > 0) {

		srand(time(NULL)); //카드 타입,능력치 설정

		for (i = 0;i <= 4;i++) { //[0][i] = power, [1][i] = type
			P_Card[0][i] = rand() % 10 + 1;
			P_Card[1][i] = rand() % 3 + 1; // 1=공격(빨강), 2=방어(파랑), 3=치료(초록)

			switch (P_Card[1][i]) { //플레이어 타입별 카드갯수 저장
			case 1:
				P_AT_Card++;
				break;
			case 2:
				P_GU_Card++;
				break;
			case 3:
				P_HE_Card++;
				break;
			}
		}
		for (i = 0;i <= 4;i++) {
			Sleep(500);
			Beep(300, 50);
			Draw_Card(4 + (10 * i), 23, P_Card[1][i], P_Card[0][i], TRUE);
		}
		Sleep(200);

		E_AT_Card_max[0] = 0; //초기값
		E_GU_Card_max[0] = 0; 
		E_HE_Card_max[0] = 0; 

		E_AT_Card_max[1] = 0; //0 = 없음, 1 = 있음
		E_GU_Card_max[1] = 0;
		E_HE_Card_max[1] = 0; 

		srand(time(NULL));

		for (i = 0;i <= 4;i++) { //Enemy
			E_Card[0][i] = rand() % 10 + 1;
			E_Card[1][i] = rand() % 3 + 1; // 1=공격(빨강), 2=방어(파랑), 3=치료(초록)

			switch (E_Card[1][i]) {
			case 1:
				if (E_Card[0][i] > E_AT_Card_max[0]) {
					E_AT_Card_max[0] = E_Card[0][i];
					E_AT_Card_max[1] = 1;
				}
				break;
			case 2:
				if (E_Card[0][i] > E_GU_Card_max[0]) {
					E_GU_Card_max[0] = E_Card[0][i];
					E_GU_Card_max[1] = 1;
				}
				break;
			case 3:
				if (E_Card[0][i] > E_HE_Card_max[0]) {
					E_HE_Card_max[0] = E_Card[0][i];
					E_HE_Card_max[1] = 1;
				}
				break;
			}
		}
		for (i = 0;i <= 4;i++) {
			Sleep(500);
			Beep(300, 50);
			Draw_Card(28 + (10 * i), 2, E_Card[1][i], E_Card[0][i], FALSE);
		}

		i = Card_Selector(); //공격->치료->방어->공격

		P_Select[0] = P_Card[0][i - 1];
		P_Select[1] = P_Card[1][i - 1];

		Sleep(500);
		Beep(300, 50);
		Draw_Card(24, 14, P_Select[1], P_Select[0], TRUE);

		Sleep(500);

		srand(time(NULL));

		//적 카드 선정 (1 = 전략적, 0 = 랜덤)
		if (intelligence) { //전략적 판단
			if (P_AT_Card >= 3) { //공격카드가 많을때
				if (GE_Guard == 0) { //적 방어막이 없는가?
					if (E_GU_Card_max[1] == 1) {// 방어우선
						E_Select[1] = 2;
						E_Select[0] = E_GU_Card_max[0];
					}
					else if (E_HE_Card_max[1] == 1) {
						E_Select[1] = 3;
						E_Select[0] = E_HE_Card_max[0];
					}
					else {
						E_Select[1] = 1;
						E_Select[0] = E_AT_Card_max[0];
					}
				}
				else {
					if (E_AT_Card_max[1] == 1) { // 공격우선
						E_Select[1] = 1;
						E_Select[0] = E_AT_Card_max[0];
					}
					else if (E_GU_Card_max[1] == 1) {
						E_Select[1] = 2;
						E_Select[0] = E_GU_Card_max[0];
					}
					else {
						E_Select[1] = 3;
						E_Select[0] = E_HE_Card_max[0];
					}
				}
			}
			else if (P_GU_Card >= 3) { //방어카드가 많을때
				if (GE_HP >= (GE_FullHP / 100) * 30) { //적 체력이 많은가?
					if (E_GU_Card_max[1] == 1) {// 방어우선
						E_Select[1] = 2;
						E_Select[0] = E_GU_Card_max[0];
					}
					else if (E_HE_Card_max[1] == 1) {
						E_Select[1] = 3;
						E_Select[0] = E_HE_Card_max[0];
					}
					else {
						E_Select[1] = 1;
						E_Select[0] = E_AT_Card_max[0];
					}
				}
				else {
					if (GP_Guard > 0) { //플레이어 방어막이 있는가?
						if (E_GU_Card_max[1] == 1) {// 방어우선
							E_Select[1] = 2;
							E_Select[0] = E_GU_Card_max[0];
						}
						else if (E_HE_Card_max[1] == 1) {
							E_Select[1] = 3;
							E_Select[0] = E_HE_Card_max[0];
						}
						else {
							E_Select[1] = 1;
							E_Select[0] = E_AT_Card_max[0];
						}
					}
					else {
						if (E_AT_Card_max[1] == 1) { // 공격우선
							E_Select[1] = 1;
							E_Select[0] = E_AT_Card_max[0];
						}
						else if (E_GU_Card_max[1] == 1) {
							E_Select[1] = 2;
							E_Select[0] = E_GU_Card_max[0];
						}
						else {
							E_Select[1] = 3;
							E_Select[0] = E_HE_Card_max[0];
						}
					}
				}
			}
			else if (P_HE_Card >= 3) { //회복카드가 많을때
				if (GP_HP >= (GP_FullHP / 100) * 30) { // 플레이어 체력이 많은가?
					if (GE_HP >= (GE_FullHP / 100) * 30) { // 적 체력이 많은가?
						if (P_GU_Card == 0) { // 플레이어 방어카드가 없는가?
							if (E_AT_Card_max[1] == 1) { // 공격우선
								E_Select[1] = 1;
								E_Select[0] = E_AT_Card_max[0];
							}
							else if (E_GU_Card_max[1] == 1) {
								E_Select[1] = 2;
								E_Select[0] = E_GU_Card_max[0];
							}
							else {
								E_Select[1] = 3;
								E_Select[0] = E_HE_Card_max[0];
							}
						}
						else {
							if (E_GU_Card_max[1] == 1) {// 방어우선
								E_Select[1] = 2;
								E_Select[0] = E_GU_Card_max[0];
							}
							else if (E_HE_Card_max[1] == 1) {
								E_Select[1] = 3;
								E_Select[0] = E_HE_Card_max[0];
							}
							else {
								E_Select[1] = 1;
								E_Select[0] = E_AT_Card_max[0];
							}
						}
					}
					else {
						if (E_HE_Card_max[1] == 1) { //회복우선
							E_Select[1] = 3;
							E_Select[0] = E_HE_Card_max[0];
						}
						else if (E_AT_Card_max[1] == 1) {
							E_Select[1] = 1;
							E_Select[0] = E_AT_Card_max[0];
						}
						else {
							E_Select[1] = 2;
							E_Select[0] = E_GU_Card_max[0];
						}
					}
				}
				else {
					if (E_AT_Card_max[1] == 1) { //공격우선
						E_Select[1] = 1;
						E_Select[0] = E_AT_Card_max[0];
					}
					else if (E_HE_Card_max[1] == 1) {
						E_Select[1] = 3;
						E_Select[0] = E_HE_Card_max[0];
					}
					else {
						E_Select[1] = 2;
						E_Select[0] = E_GU_Card_max[0];
					}
				}
			}
			else { //아 애매하네 모르겠다 랜덤돌릴까 말까
				if (GE_HP >= (GE_FullHP / 100) * 30) { //적 체력이 많은가?
					if (GE_Guard > 0) { //적 방어막이 있는가?
						if (E_AT_Card_max[1] == 1) { //공격우선
							E_Select[1] = 1;
							E_Select[0] = E_AT_Card_max[0];
						}
						else if (E_HE_Card_max[1] == 1) {
							E_Select[1] = 3;
							E_Select[0] = E_HE_Card_max[0];
						}
						else {
							E_Select[1] = 2;
							E_Select[0] = E_GU_Card_max[0];
						}
					}
					else {
						if (E_GU_Card_max[1] == 1) {// 방어우선
							E_Select[1] = 2;
							E_Select[0] = E_GU_Card_max[0];
						}
						else if (E_HE_Card_max[1] == 1) {
							E_Select[1] = 3;
							E_Select[0] = E_HE_Card_max[0];
						}
						else {
							E_Select[1] = 1;
							E_Select[0] = E_AT_Card_max[0];
						}
					}
				}
				else {
					if (E_HE_Card_max[1] == 1) { //회복우선
						E_Select[1] = 3;
						E_Select[0] = E_HE_Card_max[0];
					}
					else if (E_AT_Card_max[1] == 1) {
						E_Select[1] = 1;
						E_Select[0] = E_AT_Card_max[0];
					}
					else {
						E_Select[1] = 2;
						E_Select[0] = E_GU_Card_max[0];
					}
				}
			}
			
		}
		else { //랜덤 판단
			i = rand() % 5 + 1; //랜덤 카드 고르기

			E_Select[0] = E_Card[0][i - 1];

			E_Select[1] = E_Card[1][i - 1];
		}

		
		Beep(300, 50);
		Draw_Card(48, 11, E_Select[1], E_Select[0], TRUE);

		// 유리 불리 판별 및 행동
		if (P_Select[1] == E_Select[1]) { // 타입 같을때

			if (P_Select[0] > E_Select[0]) { //유리
				Battle_Round_Result(TRUE);
			}
			else if (P_Select[0] < E_Select[0]) { //불리
				Battle_Round_Result(FALSE);
			}
			else { //비김
				Sleep(1000);
				Card_remover();
				Sleep(500);
				continue;
			}
		}
		else { //다를때

			if (P_Select[1] == 1 || E_Select[1] == 1) {
				switch (P_Select[1]) {
				case 1:
					switch (E_Select[1]) {
					case 2: //불리
						Battle_Round_Result(FALSE);
						break;
					case 3: //유리
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 2: //유리
					Battle_Round_Result(TRUE);
					break;
				case 3: //불리
					Battle_Round_Result(FALSE);
					break;
				}
			}
			else if (P_Select[1] == 2 || E_Select[1] == 2) {
				switch (P_Select[1]) {
				case 2:
					switch (E_Select[1]) {
					case 3: //불리
						Battle_Round_Result(FALSE);
						break;
					case 1: //유리
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 3: //유리
					Battle_Round_Result(TRUE);
					break;
				case 1: //불리
					Battle_Round_Result(FALSE);
					break;
				}
			}
			else {
				switch (P_Select[1]) {
				case 3:
					switch (E_Select[1]) {
					case 1: //불리
						Battle_Round_Result(FALSE);
						break;
					case 2: //유리
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 1: //유리
					Battle_Round_Result(TRUE);
					break;
				case 2: //불리
					Battle_Round_Result(FALSE);
					break;
				}
			}

		}
		Battle_Display_Update();
		Sleep(1000);
		Card_remover();
		Sleep(500);
	}
}

//화면 출력 사전 정의

int Explanation_Screen();
int Main_Screen();
int battle_Screen(char enemy_name[],BOOL intelligence);

//화면 출력 함수

int Main_Screen() //메인 화면 출력
{
	int menu_num = 1;
	GP_HP = GP_FullHP; // 초기값 세팅
	GE_HP = GE_FullHP;
	GP_Guard = 0;
	GE_Guard = 0;

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
			Beep(200, 50);

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //왼쪽
			if (menu_num - 1 >= 1) menu_num--;
			Main_Select_Clear();
			Beep(200, 50);
		}
		if (GetAsyncKeyState(VK_SPACE) & 1) { //space
			if (menu_num == 1) {
				system("cls");
				Beep(500, 25);
				Sleep(10);
				Beep(200, 25);
				battle_Screen("산적두목",FALSE);
			}
			else if (menu_num == 2) {
				system("cls");
				Beep(500, 25);
				Sleep(10);
				Beep(200, 25);
				Explanation_Screen();
				return 0;
				
			}
			else {
				system("cls");
				Beep(500, 25);
				Sleep(10);
				Beep(200, 25);
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
	system("mode con:cols=150 lines=31");        //화면크기
	system("title [danmoji] test_game");    //게임이름


	Gotoxy(0, 0);
	printf("이 게임은 미완성입니다.\n\n이 게임은 5장을 카드중 1장을 골라 서로 겨루는 게임으로 빨강은 공격, 파랑은 방어, 초록은 회복을 나타냅니다.\n\n각 카드별 상성이 존재하며 이는 빨강(공격) -> 초록(회복) -> 파랑(방어) -> 빨강(공격)순 입니다. 만약 동일 타입의 카드라면 숫자가 높은 카드가 이깁니다,\n\n게임에서 이기려면 상대방의 체력을 0이하로 만들어야합니다.\n\n공격카드는 숫자만큼 데미지를 주고 방어카드는 숫자의 반만큼 방어막 포인트를 주며 회복카드는 숫자만큼 회복합니다.\n\n방어막 포인트는 공격을 숫자만큼 막아주며 숫자 이상의 공격을 받으면 공격을 막아내며 제거됩니다.\n\n조작은 화살표와 스페이스바입니다.");

	Gotoxy(62,29);
	printf("돌아가려면 ESC..");

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE) & 1) { //esc
			Beep(500, 25);
			Sleep(10);
			Beep(200, 25);
			Main_Screen();
			return 0;
		}
	}
}

int battle_Screen(char enemy_name[],BOOL intelligence) //인게임 시스템
{
	enum ColorType { RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;

	int i;

	system("mode con:cols=80 lines=31");        //화면크기
	system("title [danmoji] test_game");    //게임이름

	Square_OutLine(39, 30);

	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 21);
		printf("■");
	}
	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 9);
		printf("■");
	}
	for (i = 22;i <= 30; i++) {
		Gotoxy(54, i);
		printf("■");
	}
	for (i = 0;i <= 9; i++) {
		Gotoxy(24, i);
		printf("■");
	}


	Battle_Display_Update(); //체력 업데이트

	Gotoxy(2, 1); //이름 출력
	textcolor(RED);
	if (intelligence) {
		printf("전략적인 %s", enemy_name);
	}
	else {
		printf("멍청한 %s", enemy_name);
	}
	Gotoxy(74, 22);
	textcolor(WHITE);
	printf("본인");

	Battle_system(intelligence);
	if (GP_HP > GE_HP) {
		game_win();
	}
	else {
		game_defeat();
	}
	textcolor(WHITE);
	Main_Screen();
	return 0;
}

/*메인코드*/

void main() {
	Cusor();

	Main_Screen();

}
