#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

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
	case 1: //���� (����)
		for (int i = x; i <= x+6;i += 2) {
			for (int j = y; j <= y+5;j++) {
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
		textcolor(WHITE);
		break;
	case 2: //��� (�Ķ�)
		for (int i = x; i <= x + 6;i += 2) {
			for (int j = y; j <= y + 5;j++) {
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
		textcolor(WHITE);
		break;
	case 3: //ġ�� (�ʷ�)
		for (int i = x; i <= x + 6;i += 2) {
			for (int j = y; j <= y + 5;j++) {
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
		textcolor(WHITE);
		break;
	}
}

void Card_Selector()
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

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //����
			if (select_num - 1 >= 1) select_num--;
			battle_Select_Clear();
		}
		if (GetAsyncKeyState(VK_SPACE) & 1) { //space
			
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

//ȭ�� ��� ���� ����

int Explanation_Screen();
int Main_Screen();
int battle_Screen();

//ȭ�� ��� �Լ�

int Main_Screen() //���� ȭ�� ���
{
	int menu_num = 1;

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

		}
		if (GetAsyncKeyState(VK_LEFT) & 1) { //����
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
	system("mode con:cols=80 lines=31");        //ȭ��ũ��
	system("title [danmoji] test_game");    //�����̸�

	Square_OutLine(39, 30);

	Gotoxy(62,29);
	printf("���ư����� ESC..");

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE) & 1) { //esc
			Main_Screen();
			return 0;
		}
	}
}

int battle_Screen() //�ΰ��� �ý���
{
	int P_damage, P_Guard, P_Heal, P_Card[2][5], P_HP = 400;
	int E_damage, E_Guard, E_Heal, E_Card[2][5], E_HP = 400;
	int i, j;

	system("mode con:cols=80 lines=31");        //ȭ��ũ��
	system("title [danmoji] test_game");    //�����̸�

	Square_OutLine(39, 30);

	for (i = 0;i <= 78;i = i + 2) {
		Gotoxy(i, 21);
		printf("��");
	}
	for (i = 22;i <= 30; i++) {
		Gotoxy(54, i);
		printf("��");
	}

	srand(time(NULL));
	
	for (i = 0;i <= 4;i++) { //[0][i] = power, [1][i] = type
		P_Card[0][i] = rand() % 20 + 1;
		P_Card[1][i] = rand() % 3 + 1; // 1=����(����), 2=���(�Ķ�), 3=ġ��(�ʷ�)
	}
	for (i = 0;i <= 4;i++) {
		Sleep(500);
		Draw_Card(4+(10*i), 23, P_Card[1][i], P_Card[0][i]);
	}
	Card_Selector();
	
}

/*�����ڵ�*/

void main() {
	Cusor();

	Main_Screen();

}