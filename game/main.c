#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#pragma warning(disable:6385)
#pragma warning(disable:4244)
#pragma warning(disable:4101)
 

/*�������� ����*/
int P_Card[2][5], P_Select[2]; //P_Select[0] = power, P_Select[1] = cost
int E_Card[2][5], E_Select[2];
int GP_HP, GE_HP, GP_Guard, GE_Guard, GP_FullHP=20, GE_FullHP=20;

/*�Լ�����*/

void Gotoxy(int x, int y) //��ǥ 
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Cusor() //Ŀ�������
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0; // Ŀ���� ������ ���� ����(0�̸� �Ⱥ���, 0���� ���� ���̸� ����)
	cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
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

void Square_OutLine(int x, int y) //�簢�� ����
{ 

	int i;

	for (i = 0;i <= x*2;i = i + 2) {
		Gotoxy(i, 0);
		printf("��");
	}
	for (i = 1;i <= y-1;i++) {
		Gotoxy(0, i);
		printf("��");
	}
	for (i = 1;i <= y-1;i++) {
		Gotoxy(x*2, i);
		printf("��");
	}
	for (i = 0;i <= x*2;i = i + 2) {
		Gotoxy(i, y);
		printf("��");
	}

}

void Main_Select_Clear() //���� ǥ�� ����
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

void battle_Select_Clear() //���� ǥ�� ����
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
	case 1: //���� (����)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(RED);
					printf("��");
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
					printf("��");
				}
			}
		}
		textcolor(WHITE);
		break;
	case 2: //��� (�Ķ�)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(BLUE);
					printf("��");
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
					printf("��");
				}
			}
		}
		textcolor(WHITE);
		break;
	case 3: //ġ�� (�ʷ�)
		if (flip == TRUE) {
			for (i = x; i <= x + 6;i += 2) {
				for (j = y; j <= y + 5;j++) {
					Gotoxy(i, j);
					textcolor(GREEN);
					printf("��");
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
					printf("��");
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
	printf("������������������ ");
	Gotoxy(3, 29);
	printf("������������������ ");

	while (1) //�Է� ��
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1) { //������
			if (select_num + 1 <= 5) select_num++;
			battle_Select_Clear();
			Beep(200, 50);
		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //����
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
			printf("���������������������� ");
			Gotoxy(2, 29);
			printf("���������������������� ");

			break;
		case 2:
			
			Gotoxy(12, 22);
			printf("���������������������� ");
			Gotoxy(12, 29);
			printf("���������������������� ");

			break;
		case 3:
			
			Gotoxy(22, 22);
			printf("���������������������� ");
			Gotoxy(22, 29);
			printf("���������������������� ");

			break;
		case 4:
			
			Gotoxy(32, 22);
			printf("���������������������� ");
			Gotoxy(32, 29);
			printf("���������������������� ");

			break;
		case 5:
			
			Gotoxy(42, 22);
			printf("���������������������� ");
			Gotoxy(42, 29);
			printf("���������������������� ");

			break;
		default:
			break;
		}
	}
}

void Battle_Display_Update() //��Ʋȭ�� ui ǥ��
{
	enum ColorType { D_RED = 4, RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;


	Gotoxy(56,24);
	printf("                ");
	Gotoxy(56, 24);
	textcolor(D_RED);
	printf("ü��: %d/%d", GP_HP, GP_FullHP);

	Gotoxy(2, 3);
	printf("                ");
	Gotoxy(2, 3);
	textcolor(D_RED);
	printf("ü��: %d/%d", GE_HP, GE_FullHP);

	Gotoxy(56, 25);
	printf("                ");
	Gotoxy(56, 25);
	textcolor(1); //D_BLUE
	printf("��: %d", GP_Guard);

	Gotoxy(2, 4);
	printf("                ");
	Gotoxy(2, 4);
	textcolor(1); //D_BLUE
	printf("��: %d", GE_Guard);
}

void Card_remover()
{
	int i,x,y;
	for (i = 0;i <= 4;i++) { //�÷��̾� �� ����
		for (x = 4 + (10 * i); x <= 4 + (10 * i) + 6; x += 2) {
			for (y = 23; y <= 23 + 5;y++) {
				Gotoxy(x, y);
				printf("  ");
			}
		}
	}
	for (i = 0;i <= 4;i++) { //�� �� ����
		for (x = 28 + (10 * i); x <= 28 + (10 * i) + 6; x += 2) {
			for (y = 2; y <= 2 + 5;y++) {
				Gotoxy(x, y);
				printf("  ");
			}
		}
	}
	for (x = 24; x <= 30; x += 2) { //�÷��̾� ��ȯī������
		for (y = 14; y <= 19;y++) {
			Gotoxy(x, y);
			printf("  ");
		}
	}
	for (x = 48; x <= 54; x += 2) { //�� ��ȯī������
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
	if (player_win == TRUE) { //������ �����ΰ�
		Card[0] = P_Select[0];
		Card[1] = P_Select[1];
	}
	else {
		Card[0] = E_Select[0];
		Card[1] = E_Select[1];
	}

	switch (Card[1]) //Ÿ���� �����ΰ�
	{
	case 1: //����
		if (player_win == TRUE) {
			if (GE_Guard > 0) { //���� �ֳ�?
				if (GE_Guard - Card[0] < 0) { //�� �ʰ�ġ�ΰ�
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
			if (GP_Guard > 0) { //���� �ֳ�?
				if (GP_Guard - Card[0] < 0) { //�� �ʰ�ġ�ΰ�
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
	case 2: //���
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
	case 3: //ġ��
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

	int P_AT_Card = 0, P_GU_Card = 0, P_HE_Card = 0; // �÷��̾� Ÿ�Ժ� ī�尹��

	int E_AT_Card_max[2], E_GU_Card_max[2], E_HE_Card_max[2]; //�� ī������ ���� ���� ���� ī��([0] = power,[1] = ���翩�� (0 = ����, 1 = ����))

	while (GP_HP > 0 && GE_HP > 0) {

		srand(time(NULL)); //ī�� Ÿ��,�ɷ�ġ ����

		for (i = 0;i <= 4;i++) { //[0][i] = power, [1][i] = type
			P_Card[0][i] = rand() % 10 + 1;
			P_Card[1][i] = rand() % 3 + 1; // 1=����(����), 2=���(�Ķ�), 3=ġ��(�ʷ�)

			switch (P_Card[1][i]) { //�÷��̾� Ÿ�Ժ� ī�尹�� ����
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

		E_AT_Card_max[0] = 0; //�ʱⰪ
		E_GU_Card_max[0] = 0; 
		E_HE_Card_max[0] = 0; 

		E_AT_Card_max[1] = 0; //0 = ����, 1 = ����
		E_GU_Card_max[1] = 0;
		E_HE_Card_max[1] = 0; 

		srand(time(NULL));

		for (i = 0;i <= 4;i++) { //Enemy
			E_Card[0][i] = rand() % 10 + 1;
			E_Card[1][i] = rand() % 3 + 1; // 1=����(����), 2=���(�Ķ�), 3=ġ��(�ʷ�)

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

		i = Card_Selector(); //����->ġ��->���->����

		P_Select[0] = P_Card[0][i - 1];
		P_Select[1] = P_Card[1][i - 1];

		Sleep(500);
		Beep(300, 50);
		Draw_Card(24, 14, P_Select[1], P_Select[0], TRUE);

		Sleep(500);

		srand(time(NULL));

		//�� ī�� ���� (1 = ������, 0 = ����)
		if (intelligence) { //������ �Ǵ�
			if (P_AT_Card >= 3) { //����ī�尡 ������
				if (GE_Guard == 0) { //�� ���� ���°�?
					if (E_GU_Card_max[1] == 1) {// ���켱
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
					if (E_AT_Card_max[1] == 1) { // ���ݿ켱
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
			else if (P_GU_Card >= 3) { //���ī�尡 ������
				if (GE_HP >= (GE_FullHP / 100) * 30) { //�� ü���� ������?
					if (E_GU_Card_max[1] == 1) {// ���켱
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
					if (GP_Guard > 0) { //�÷��̾� ���� �ִ°�?
						if (E_GU_Card_max[1] == 1) {// ���켱
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
						if (E_AT_Card_max[1] == 1) { // ���ݿ켱
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
			else if (P_HE_Card >= 3) { //ȸ��ī�尡 ������
				if (GP_HP >= (GP_FullHP / 100) * 30) { // �÷��̾� ü���� ������?
					if (GE_HP >= (GE_FullHP / 100) * 30) { // �� ü���� ������?
						if (P_GU_Card == 0) { // �÷��̾� ���ī�尡 ���°�?
							if (E_AT_Card_max[1] == 1) { // ���ݿ켱
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
							if (E_GU_Card_max[1] == 1) {// ���켱
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
						if (E_HE_Card_max[1] == 1) { //ȸ���켱
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
					if (E_AT_Card_max[1] == 1) { //���ݿ켱
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
			else { //�� �ָ��ϳ� �𸣰ڴ� ���������� ����
				if (GE_HP >= (GE_FullHP / 100) * 30) { //�� ü���� ������?
					if (GE_Guard > 0) { //�� ���� �ִ°�?
						if (E_AT_Card_max[1] == 1) { //���ݿ켱
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
						if (E_GU_Card_max[1] == 1) {// ���켱
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
					if (E_HE_Card_max[1] == 1) { //ȸ���켱
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
		else { //���� �Ǵ�
			i = rand() % 5 + 1; //���� ī�� ����

			E_Select[0] = E_Card[0][i - 1];

			E_Select[1] = E_Card[1][i - 1];
		}

		
		Beep(300, 50);
		Draw_Card(48, 11, E_Select[1], E_Select[0], TRUE);

		// ���� �Ҹ� �Ǻ� �� �ൿ
		if (P_Select[1] == E_Select[1]) { // Ÿ�� ������

			if (P_Select[0] > E_Select[0]) { //����
				Battle_Round_Result(TRUE);
			}
			else if (P_Select[0] < E_Select[0]) { //�Ҹ�
				Battle_Round_Result(FALSE);
			}
			else { //���
				Sleep(1000);
				Card_remover();
				Sleep(500);
				continue;
			}
		}
		else { //�ٸ���

			if (P_Select[1] == 1 || E_Select[1] == 1) {
				switch (P_Select[1]) {
				case 1:
					switch (E_Select[1]) {
					case 2: //�Ҹ�
						Battle_Round_Result(FALSE);
						break;
					case 3: //����
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 2: //����
					Battle_Round_Result(TRUE);
					break;
				case 3: //�Ҹ�
					Battle_Round_Result(FALSE);
					break;
				}
			}
			else if (P_Select[1] == 2 || E_Select[1] == 2) {
				switch (P_Select[1]) {
				case 2:
					switch (E_Select[1]) {
					case 3: //�Ҹ�
						Battle_Round_Result(FALSE);
						break;
					case 1: //����
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 3: //����
					Battle_Round_Result(TRUE);
					break;
				case 1: //�Ҹ�
					Battle_Round_Result(FALSE);
					break;
				}
			}
			else {
				switch (P_Select[1]) {
				case 3:
					switch (E_Select[1]) {
					case 1: //�Ҹ�
						Battle_Round_Result(FALSE);
						break;
					case 2: //����
						Battle_Round_Result(TRUE);
						break;
					}
					break;
				case 1: //����
					Battle_Round_Result(TRUE);
					break;
				case 2: //�Ҹ�
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

//ȭ�� ��� ���� ����

int Explanation_Screen();
int Main_Screen();
int battle_Screen(char enemy_name[],BOOL intelligence);

//ȭ�� ��� �Լ�

int Main_Screen() //���� ȭ�� ���
{
	int menu_num = 1;
	GP_HP = GP_FullHP; // �ʱⰪ ����
	GE_HP = GE_FullHP;
	GP_Guard = 0;
	GE_Guard = 0;

	system("mode con:cols=80 lines=11");        //ȭ��ũ��
	system("title [danmoji] test_game");    //�����̸�

	Square_OutLine(39, 10);

	Gotoxy(35, 3); //����ȭ�� ����
	printf("�׽�Ʈ����");

	Gotoxy(14, 6);
	printf("���ӽ���");

	Gotoxy(36, 6);
	printf("���Ӽ���");

	Gotoxy(58, 6);
	printf("��������");

	while (1) //�Է� ��
	{
		if (GetAsyncKeyState(VK_RIGHT) & 1) { //������
			if (menu_num + 1 <= 3) menu_num++;
			Main_Select_Clear();
			Beep(200, 50);

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //����
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
				battle_Screen("�����θ�",FALSE);
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
			printf("��");
			Gotoxy(22, 6);
			printf("��");

			break;
		case 2:
			Gotoxy(34, 6);
			printf("��");
			Gotoxy(44, 6);
			printf("��");

			break;
		case 3:
			Gotoxy(56, 6);
			printf("��");
			Gotoxy(66, 6);
			printf("��");

			break;
		default:
			break;
		}
	}
}

int Explanation_Screen() //���� ���� ȭ�� ���
{
	system("mode con:cols=150 lines=31");        //ȭ��ũ��
	system("title [danmoji] test_game");    //�����̸�


	Gotoxy(0, 0);
	printf("�� ������ �̿ϼ��Դϴ�.\n\n�� ������ 5���� ī���� 1���� ��� ���� �ܷ�� �������� ������ ����, �Ķ��� ���, �ʷ��� ȸ���� ��Ÿ���ϴ�.\n\n�� ī�庰 ���� �����ϸ� �̴� ����(����) -> �ʷ�(ȸ��) -> �Ķ�(���) -> ����(����)�� �Դϴ�. ���� ���� Ÿ���� ī���� ���ڰ� ���� ī�尡 �̱�ϴ�,\n\n���ӿ��� �̱���� ������ ü���� 0���Ϸ� �������մϴ�.\n\n����ī��� ���ڸ�ŭ �������� �ְ� ���ī��� ������ �ݸ�ŭ �� ����Ʈ�� �ָ� ȸ��ī��� ���ڸ�ŭ ȸ���մϴ�.\n\n�� ����Ʈ�� ������ ���ڸ�ŭ �����ָ� ���� �̻��� ������ ������ ������ ���Ƴ��� ���ŵ˴ϴ�.\n\n������ ȭ��ǥ�� �����̽����Դϴ�.");

	Gotoxy(62,29);
	printf("���ư����� ESC..");

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

int battle_Screen(char enemy_name[],BOOL intelligence) //�ΰ��� �ý���
{
	enum ColorType { RED = 12, BLUE = 9, GREEN = 10, WHITE = 15 }COLOR;

	int i;

	system("mode con:cols=80 lines=31");        //ȭ��ũ��
	system("title [danmoji] test_game");    //�����̸�

	Square_OutLine(39, 30);

	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 21);
		printf("��");
	}
	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 9);
		printf("��");
	}
	for (i = 22;i <= 30; i++) {
		Gotoxy(54, i);
		printf("��");
	}
	for (i = 0;i <= 9; i++) {
		Gotoxy(24, i);
		printf("��");
	}


	Battle_Display_Update(); //ü�� ������Ʈ

	Gotoxy(2, 1); //�̸� ���
	textcolor(RED);
	if (intelligence) {
		printf("�������� %s", enemy_name);
	}
	else {
		printf("��û�� %s", enemy_name);
	}
	Gotoxy(74, 22);
	textcolor(WHITE);
	printf("����");

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

/*�����ڵ�*/

void main() {
	Cusor();

	Main_Screen();

}
