#include "main.h"

// Ŀ�� ����� �Լ� (c�� 1(true)�̸� ����, 0(false)�̸� ����) 
void hideCursor(int c)
{
	CONSOLE_CURSOR_INFO consoleCursor;
	if (c == 1) {
		consoleCursor.bVisible = 0;
		consoleCursor.dwSize = 1;
	}
	else if (c == 0) {
		consoleCursor.bVisible = 1;
		consoleCursor.dwSize = 100;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

// �ܼ� ũ�⸦ ���ϴ� �Լ�(w=����, h=����)
void resizeConsole(int w, int h) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", w, h);
	system(chTemp);
}

// Ŀ���� �̵���Ű�� �Լ�(x,y)
void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//���� �ٲٴ� �Լ�(0~15)
void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (7 << 4));
}

// �̹����� ����ϴ� �Լ�(�����̸��� ����, ���������ġx, ���������ġy, �̹������x, �̹������y)
void printImage(int pictureNum, int start_w, int start_h, int w, int h) {
	char path[101];
	//�̹������� �̸��� picture0, picture1 �̷� �������� ����Ǿ� ����
	sprintf(path, "shiba%d.bmp", pictureNum);
	consoleWindow = GetConsoleWindow();
	consoleDC = GetDC(consoleWindow);
	imageDC = CreateCompatibleDC(consoleDC);
	imageMap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(imageDC, imageMap);
	BitBlt(consoleDC, start_w, start_h, w, h, imageDC, 0, 0, SRCCOPY);
	DeleteObject(imageMap);
	DeleteDC(imageDC);
	ReleaseDC(consoleWindow, consoleDC);
}

// n�� ���� �ʿ��� ���� �����ִ� �Լ�
void eraseSpace(int n) {
	switch (n)
	{
	//�Է¹޴� �κ�
	case 1:
		gotoxy(6, 11);
		printf("                                                        ");
		break;

	//���� �ܾ� ��� �κ�
	case 2:
		gotoxy(30, 7);
		printf("                              ");
		break;

	//���� �ܾ� ��� �κ�
	case 3:
		gotoxy(30, 3);
		printf("                              ");
		break;
	
	//��ȭâ�� �޼��� ��� �κ�
	case 4:
		gotoxy(5, 19);
		printf("                                                                                                             ");
		break;
	}
}

// �ܾ��� ȭ�� �� ������ ���� �׸��� �Լ�
void drawWordbook_static(void) {
	system("cls");
	//�Է� ����
	while (_kbhit())	_getch();

	drawFrame();
	gotoxy(42, 2);
	printf("S H I B A ' S   W O R D   B O O K");
	gotoxy(6, 3);
	printf("�������������������������������������������������������");
	gotoxy(6, 4);
	printf("�������������������������������������������������������");
	gotoxy(6, 5);
	printf("���                                                ��� . ..... . . ... . . . .. . ..... . . . . . . . ���");
	gotoxy(6, 6);
	printf("���                                                ��� .. .. . ... ... . .. ... ...... . ... . . . .  ���");
	gotoxy(6, 7);
	printf("���                                                ��� ....   .... ... .  . ...   ...  .. . ..... ... ���");
	gotoxy(6, 8);
	printf("���                                                ���  .. ..     ...   .... ...    ....    . ..  ... ���");
	gotoxy(6, 9);
	printf("���                                                ��� . . . .  ..   ..   . . .   .   .. .   ........ ���");
	gotoxy(6, 10);
	printf("���                                                ���. . . . .  . . .  . ..... . .. . . .. ... ..... ���");
	gotoxy(6, 11);
	printf("���                                                ��� ... . ...   .... . ... ....   .... .... .... . ���");
	gotoxy(6, 12);
	printf("���                                                ��� .. .. .. . .. . . . ... .. ... .. .. .... .... ���");
	gotoxy(6, 13);
	printf("���                                                ��� .. .. .. .. .. . .. .. .. .. .. .. .. .. .. .. ���");
	gotoxy(6, 14);
	printf("���                                                ��� .. . .. . . . . . . .. . . . . . .. . . . . .  ���");
	gotoxy(6, 15);
	printf("���                                                ��� ..    .    . .  .  .    .    .   .   .   . . . ���");
	gotoxy(6, 16);
	printf("���                                                ���... ..... ........ ...... ....... ......... ... ���");
	gotoxy(6, 17);
	printf("���                                                ���..... ... .  ... ... . .. . . ... .. . . ... .. ���");
	gotoxy(6, 18);
	printf("���                                                ���... ... ...    . . ..    ..  ..   . .. .    ..  ���");
	gotoxy(6, 19);
	printf("�������������������������������������������������������");
	gotoxy(6, 20);
	printf("�������������������������������������������������������");
	gotoxy(2, 22);
	printf("<-- �ڷΰ��� (BACKSPACE)");
}

// �ܾ��� ȭ�� �� ������ ���� �׸��� �Լ�
void drawWordbook_dynamic(void) {
	file3 = fopen("���ܾ���.txt", "r");
	for (int sNum = 0; sNum < 12; sNum++) {
		char en[12][100];
		char kr[12][100];
		fgets(en[sNum], 100, file3);
		fgets(kr[sNum], 100, file3);
		//ó���� �����̶�� ��ĭ�� ����
		if (en[0][0] == ' ') {
			for (int i = 0; i < 100; i++) {
				en[0][i] = en[0][i + 1];
			}
		}
		gotoxy(12, 6 + sNum);
		printf("%s", en[sNum]);
		gotoxy(27, 6 + sNum);
		printf("%s", kr[sNum]);
	}
	fclose(file3);
	while (1) {
		if (GetAsyncKeyState(8)) {
			drawFrame();
			return 0;
		}
	}
}

// ���� ȭ���� �׷��ִ� �Լ�
int drawTitle(void) {
	int x = 1000;
	while (1) {
		printImage(x, 0, 0, 1200, 480);
		if (GetAsyncKeyState(VK_UP)) {
			x = 1000;
			printImage(x, 0, 0, 1200, 480);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			x = 1001;
			printImage(x, 0, 0, 1200, 480);
		}
		if (GetAsyncKeyState(13)) {
			if (x == 1000) {
				return 10;
				break;
			}
			if (x == 1001) {
				return 11;
				break;
			}

		}
		GetAsyncKeyState(8);
	}
}

// �ܼ��� �׵θ��� �׸��� �Լ�
void drawFrame(void) {
	system("cls");
	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 120; x += 2) {
			setColor(15);
			gotoxy(x, y);
			printf("��");
		}
		Sleep(10);
	}
	Sleep(300);
	setColor(0);
	for (int y = 1; y < 23; y++) {
		for (int x = 2; x < 118; x += 2) {
			gotoxy(x, y);
			printf("  ");
		}
		Sleep(10);
	}

	//Ű �Էµ� ����
	while (_kbhit())
		_getch();
	GetAsyncKeyState(13);
	GetAsyncKeyState(8);
}

// ������ ���Ͽ��� ����� �ѱ� ���� �ҷ��� ������ �����Ű�� �Լ�
void getWord(void) {
	int randnum;
	int preNum[12] = { 0 };
	srand(time(NULL));

	//���ܾ� ���� ����
	for (int sNum = 0; sNum < 12; sNum++) {
		int x = 0;
		randnum = rand() % WORDNUM;
		//���� ���ڰ� �־����� �˻�
		for (int i = 0; i < 12; i++)
		{
			if (preNum[i] == randnum)
			{
				x = 1;
				break;
			}
			else x = 0;
		}

		if (x == 0) {
			for (int i = 0; i < 100; i++) {
				if (originalString[randnum][i] != NULL) {
					randomString[sNum][i] = originalString[randnum][i];
					reverseString[sNum][i] = alphabet(randomString[sNum][i]);
					//���� ����
					length[sNum] = strlen(reverseString[sNum]) - 1;
				}
				else break;
			}
		}
		else sNum--;
		preNum[sNum] = randnum;
	}


	//�ѱ� �� ����
	for (int sNum = 0; sNum < 12; sNum++)
	{
		for (int j = 0; j < 100; j++) {
			if (originalString2[preNum[sNum]][j] != NULL) {
				meanString[sNum][j] = originalString2[preNum[sNum]][j];
			}
			else break;
		}
	}
}

// ���� ȭ�� �� ������ ���� �׸��� �Լ�
void drawGame_static(void) {
	gotoxy(2, 16);
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	gotoxy(2, 17);
	printf("��                                                                                                                 ��");
	gotoxy(2, 18);
	printf("��                                                                                                                 ��");
	gotoxy(2, 19);
	printf("��                                                                                                                 ��");
	gotoxy(2, 20);
	printf("��                                                                                                                 ��");
	gotoxy(2, 21);
	printf("��                                                                                                                 ��");
	gotoxy(2, 22);
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	gotoxy(64, 2);
	printf("����������������������������������������������������������������������������������������������������������");
	gotoxy(64, 3);
	printf("��                                                   ��");
	gotoxy(64, 4);
	printf("��                                                   ��");
	gotoxy(64, 5);
	printf("��                                                   ��");
	gotoxy(64, 6);
	printf("��                                                   ��");
	gotoxy(64, 7);
	printf("��                                                   ��");
	gotoxy(64, 8);
	printf("��                                                   ��");
	gotoxy(64, 9);
	printf("��                                                   ��");
	gotoxy(64, 10);
	printf("��                                                   ��");
	gotoxy(64, 11);
	printf("��                                                   ��");
	gotoxy(64, 12);
	printf("��                                                   ��");
	gotoxy(64, 13);
	printf("��                                                   ��");
	gotoxy(64, 14);
	printf("��                                                   ��");
	gotoxy(64, 15);
	printf("����������������������������������������������������������������������������������������������������������");

	gotoxy(16, 2);
	printf("������������������������������������������������������������������������������������������");
	gotoxy(16, 3);
	printf("��                                           ��");
	gotoxy(16, 4);
	printf("������������������������������������������������������������������������������������������");

	gotoxy(16, 6);
	printf("������������������������������������������������������������������������������������������");
	gotoxy(16, 7);
	printf("��                                           ��");
	gotoxy(16, 8);
	printf("������������������������������������������������������������������������������������������");
	gotoxy(4, 12);
	printf("��������������������������������������������������������������������������������������������������������������������");
}

// ������ �������� �� �ù��� ������ ����ϴ� ���� �κ�
void Introduction(void) {
	drawFrame();
	drawGame_static();
	gotoxy(100, 20);
	printf("���� (����)");
	gotoxy(94, 17);
	printf("SKIP (�����̽���) --->");
	char ch;
	for (int i = 1; i <= 8; i++) {
		gotoxy(113, 20);
		printf("��");
		gotoxy(113, 21);
		printf("  ");
		displayMessage(i);
		while (1) {
			printImage(5, 50, 340, 100, 100);
			if (_kbhit()) {
				ch = _getch();
				//�����̽��ٴ� ��ŵ
				if (ch == 32) return 0;
				//���ʹ� ����
				if (ch == 13)
				{
					setColor(15);
					gotoxy(113, 21);
					printf("��");
					gotoxy(113, 20);
					printf("  ");
					Sleep(200);
					setColor(0);
					break;
				}
				//�齺���̽��� ����
				if (ch == 8) {
					if (i <= 1) i = 2;
					i -= 2;
					break;
				}
			}
		}
	}
	eraseSpace(4);
	gotoxy(108, 20);
	printf("        ");
	gotoxy(108, 21);
	printf("        ");
}

// ���� �κ��� ������� ��� �־� ȿ���� �Բ� ������ִ� �Լ�
void displayMessage(int i) {
	while (_kbhit())
		_getch();
	char s1[] = "�ȳ� !! ���� �ùٶ�� ��!! �� ���� ������ �� ���� ȯ�� �� ^^";
	char s2[] = "������ ��ħ ���� �ܾ� ������ ���� ���ε� �� �Ծ� !! ";
	char s3[] = "������ ���� ������ !! ���� ������ �ܾ ���� ���� ���⸸ �ϸ� �� !!";
	char s4[] = "�� �����ٸ� ������ �ܾ� �ϱ��忡 �ܾ �߰����ٰ� ! ������ 12���� ���ž� !";
	char s5[] = "�´� ! ���� ��Ʈ���� ���峵� ���ĺ��� ��ҹ��ڰ� ���׹����ϰžߤФ�";
	char s6[] = "�׷��ϱ� �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� �ٲ㼭 �������� ���ھ� !!";
	char s7[] = "���� Ʋ���� �� 5���� ��ȸ�� ������ ������ �����غ� !!";
	char s8[] = "�׷� �����Ұ� !! ����� ���� !!!";
	char s20[] = "ù �������� �����̾�.. ó������ �ٽ� �ܿ� ����??";
	char s21[] = "���� ���߾� !! �ٸ� �ܾ��嵵 ������?";
	eraseSpace(4);
	gotoxy(20, 19);
	switch (i) {
	case 1:
		for (int i = 0; i < strlen(s1); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s1[i]);
			Sleep(20);
		}
		break;
	case 2:
		for (int i = 0; i < strlen(s2); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s2[i]);
			Sleep(20);
		}
		break;
	case 3:
		for (int i = 0; i < strlen(s3); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s3[i]);
			Sleep(20);
		}
		break;
	case 4:
		for (int i = 0; i < strlen(s4); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s4[i]);
			Sleep(20);
		}
		break;
	case 5:
		for (int i = 0; i < strlen(s5); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s5[i]);
			Sleep(20);
		}
		break;
	case 6:
		for (int i = 0; i < strlen(s6); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s6[i]);
			Sleep(20);
		}
		break;
	case 7:
		for (int i = 0; i < strlen(s7); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s7[i]);
			Sleep(20);
		}
		break;
	case 8:
		for (int i = 0; i < strlen(s8); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s8[i]);
			Sleep(20);
		}
		break;
	case 20:
		for (int i = 0; i < strlen(s20); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s20[i]);
			Sleep(20);
		}
		gotoxy(83, 18);
		printf("��");
		gotoxy(83, 20);
		printf("�ƴϿ�");
		break;
	case 21:
		for (int i = 0; i < strlen(s21); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s21[i]);
			Sleep(20);
		}
		gotoxy(83, 18);
		printf("��");
		gotoxy(83, 20);
		printf("�ƴϿ�");
		break;
	}
}

// ����� �׷��ִ� �Լ�
void drawLife(int life) {
	gotoxy(4, 8);
	setColor(4);
	switch (life) {
	case 5:
		printf("����������");
		break;
	case 4:
		printf("����������");
		break;
	case 3:
		printf("����������");
		break;
	case 2:
		printf("����������");
		break;
	case 1:
		printf("����������");
		break;
	case 0:
		printf("����������");
		break;
	}
	setColor(0);
	gotoxy(6, 14);
	printf("�� �� �� ��  �� �� �� ��  ,  �� �� �� ��  �� �� �� �� !");
}

// �������� ���ĺ��� ��ҹ��ڸ� �����ִ� �Լ�
char alphabet(char ch) {
	int capital = 0;
	capital = rand() % 2;
	if ((ch >= 'a' && ch <= 'z') && capital == 1)
		return ch - 32;
	else if ((ch >= 'A' && ch <= 'Z') && capital == 1)
		return ch + 32;
	else
		return ch;
}

// �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ������ִ� �Լ�
void printReverseWord(int sNum, char Gstring[100]) {
	//��� �� ���� �����(2=���� �ܾ�, 3=���� �ܾ�)
	eraseSpace(2);
	eraseSpace(3);
	//���� �ܾ� ���
	gotoxy(20, 3);
	setColor(8);
	printf("���� �ܾ� : ");
	for (int i = 0; i < length[sNum + 1]; i++) {
		char c = reverseString[sNum + 1][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
	//���� �ܾ� ���
	gotoxy(20, 7);
	printf("���� �ܾ� : ");
	setColor(12);
	for (int i = 0; i < length[sNum]; i++) {
		char c = reverseString[sNum][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
}

// ���� �� ������� ���ڿ��� �Է� �޾� �´��� Ʋ�ȴ��� �Ǻ����ִ� �Լ�
int writeWord(int sNum,char Gstring[100]) {
	Inum = 1;
	eraseSpace(4);
	gotoxy(6, 11);
	while (_kbhit())_getch();
	for (int i = 0; i < length[sNum]; i++)
	{
		while (1)
		{
			printImage(Inum, 40, 40, 100, 100);
			if (_kbhit()) {
				Gstring[i] = _getch();
				printf("%c", Gstring[i]);
				if (Gstring[i] != reverseString[sNum][i]) {
					Inum = rand() % 4 + 6;
					printImage(Inum, 40, 40, 100, 100);
					hideCursor(1);
					sendMessage(Inum);
					Sleep(600);
					eraseSpace(4);
					eraseSpace(1);
					return 1;
				}
				break;
			}
		}
	}
	Inum = rand() % 4 + 2;
	printImage(Inum, 40, 40, 100, 100);
	hideCursor(1);
	sendMessage(Inum);
	while (_kbhit())_getch();
	Sleep(600);
	eraseSpace(1);
	return 2;
}

// �°ų� Ʋ���� ���� ������ ������ִ� �Լ�
void sendMessage(int i) {
	char s2[] = "���� ���߾� !!!!!!! �пппп� !!!";
	char s3[] = "�����̾� !!!!!!! �пп� !!!";
	char s4[] = "���Ѵ� ���Ѵ� ���Ѵ� !! �ппппп� !!!";
	char s5[] = "�¾Ҿ� !!!!!!! �ппп� !!!";
	char s6[] = "Ʋ�Ⱦ�... ũ���Ѹ��Ѥ���";
	char s7[] = "������ �ƴϾ�... ũ���������ѤѸ���";
	char s8[] = "�ٽ� �����غ�... ũ�Ѥ�����������";
	char s9[] = "�й��ؾ߰ھ�.... ũ������������";
	eraseSpace(4);
	gotoxy(5, 19);
	switch (i) {
	case 2:
		for (int i = 0; i < strlen(s2); i++) {
			printf("%c", s2[i]);
			Sleep(25);
		}
		break;
	case 3:
		for (int i = 0; i < strlen(s3); i++) {
			printf("%c", s3[i]);
			Sleep(25);
		}
		break;
	case 4:
		for (int i = 0; i < strlen(s4); i++) {
			printf("%c", s4[i]);
			Sleep(25);
		}
		break;
	case 5:
		for (int i = 0; i < strlen(s5); i++) {
			printf("%c", s5[i]);
			Sleep(25);
		}
		break;
	case 6:
		for (int i = 0; i < strlen(s6); i++) {
			printf("%c", s6[i]);
			Sleep(25);
		}
		break;
	case 7:
		for (int i = 0; i < strlen(s7); i++) {
			printf("%c", s7[i]);
			Sleep(25);
		}
		break;
	case 8:
		for (int i = 0; i < strlen(s8); i++) {
			printf("%c", s8[i]);
			Sleep(25);
		}
		break;
	case 9:
		for (int i = 0; i < strlen(s9); i++) {
			printf("%c", s9[i]);
			Sleep(25);
		}
		break;
	}
}

// �ùٸ��� �ܾ ���� ��� ���� ȭ�� �� ������ �ܾ��忡 ���ܾ�� ���� �� �ִ� �Լ�
void drawRightWord(int sNum, int countNum) {
	gotoxy(66, 3 + countNum);
	printf("%s", randomString[sNum]);
	gotoxy(81, 3 + countNum);
	printf("%s", meanString[sNum]);
}

// ������ ������ �� �ܾ ��� �� �ۼ��ߴٸ� �ֱ� �ܾ��忡 �ܾ���� �߰��ϰ� �������� �ٽ��� ���� ���ϴ� �Լ�
int endGame() {
	char Clear[60][80] = { ' ' };
	for (int y = 17; y <= 21; y++) {
		for (int x = 4; x <= 100; x++) {
			gotoxy(x, y);
			printf(" ");
		}
	}
	eraseSpace(4);

	if (isClear == 0) 
		displayMessage(20);
	else if (isClear == 1) {
		displayMessage(21);
		//���ܾ��� �߰�
		file3 = fopen("���ܾ���.txt", "r+");
		for (int i = 0; i < 12; i++)
		{
			//���� �����
			fprintf(file3, "%s", Clear[i]);
			//�ܾ� �ֱ�
			fprintf(file3, "%s%s", randomString[i], meanString[i]);
		}
		fclose(file3);
	}
	int s=1;
	drawSelectEndmenu(s);
	while (1) {
		printImage(1, 50, 340, 100, 100);
		char ch=NULL;
		while (1)
		{
			printImage(1, 50, 340, 100, 100);
			if (_kbhit()) {
				ch = _getch();
				if (ch == 72)
				{
					s = 1;
					drawSelectEndmenu(s);
					break;
				}
				if (ch == 80)
				{
					s = 0;
					drawSelectEndmenu(s);
					break;
				}
				if (ch == 13)
				{
					if (s == 0)
					{
						system("cls");
						return 5;
					}
					else return 6;
				}
			}
		}
	}
}

// ������ ������ �� �޴� ������ ȭ��ǥ�� �׷��ִ� �Լ�
void drawSelectEndmenu(int s) {
	switch (s) {
	case 1:
		gotoxy(80, 18);
		printf("��");
		gotoxy(80, 20);
		printf("  ");
		break;
	case 0:
		gotoxy(80, 18);
		printf("  ");
		gotoxy(80, 20);
		printf("��");
		break;
	}
}