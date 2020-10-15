#include "main.h"

// 커서 숨기는 함수 (c가 1(true)이면 숨김, 0(false)이면 보임) 
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

// 콘솔 크기를 정하는 함수(w=가로, h=세로)
void resizeConsole(int w, int h) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", w, h);
	system(chTemp);
}

// 커서를 이동시키는 함수(x,y)
void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//색을 바꾸는 함수(0~15)
void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (7 << 4));
}

// 이미지를 출력하는 함수(파일이름의 숫자, 시작출력위치x, 시작출력위치y, 이미지출력x, 이미지출력y)
void printImage(int pictureNum, int start_w, int start_h, int w, int h) {
	char path[101];
	//이미지파일 이름이 picture0, picture1 이런 형식으로 저장되어 있음
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

// n에 따라 필요한 줄을 지워주는 함수
void eraseSpace(int n) {
	switch (n)
	{
	//입력받는 부분
	case 1:
		gotoxy(6, 11);
		printf("                                                        ");
		break;

	//현재 단어 출력 부분
	case 2:
		gotoxy(30, 7);
		printf("                              ");
		break;

	//다음 단어 출력 부분
	case 3:
		gotoxy(30, 3);
		printf("                              ");
		break;
	
	//대화창의 메세지 출력 부분
	case 4:
		gotoxy(5, 19);
		printf("                                                                                                             ");
		break;
	}
}

// 단어장 화면 중 정적인 것을 그리는 함수
void drawWordbook_static(void) {
	system("cls");
	//입력 무시
	while (_kbhit())	_getch();

	drawFrame();
	gotoxy(42, 2);
	printf("S H I B A ' S   W O R D   B O O K");
	gotoxy(6, 3);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
	gotoxy(6, 4);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
	gotoxy(6, 5);
	printf("□□                                                □□ . ..... . . ... . . . .. . ..... . . . . . . . □□");
	gotoxy(6, 6);
	printf("□□                                                □□ .. .. . ... ... . .. ... ...... . ... . . . .  □□");
	gotoxy(6, 7);
	printf("□□                                                □□ ....   .... ... .  . ...   ...  .. . ..... ... □□");
	gotoxy(6, 8);
	printf("□□                                                □□  .. ..     ...   .... ...    ....    . ..  ... □□");
	gotoxy(6, 9);
	printf("□□                                                □□ . . . .  ..   ..   . . .   .   .. .   ........ □□");
	gotoxy(6, 10);
	printf("□□                                                □□. . . . .  . . .  . ..... . .. . . .. ... ..... □□");
	gotoxy(6, 11);
	printf("□□                                                □□ ... . ...   .... . ... ....   .... .... .... . □□");
	gotoxy(6, 12);
	printf("□□                                                □□ .. .. .. . .. . . . ... .. ... .. .. .... .... □□");
	gotoxy(6, 13);
	printf("□□                                                □□ .. .. .. .. .. . .. .. .. .. .. .. .. .. .. .. □□");
	gotoxy(6, 14);
	printf("□□                                                □□ .. . .. . . . . . . .. . . . . . .. . . . . .  □□");
	gotoxy(6, 15);
	printf("□□                                                □□ ..    .    . .  .  .    .    .   .   .   . . . □□");
	gotoxy(6, 16);
	printf("□□                                                □□... ..... ........ ...... ....... ......... ... □□");
	gotoxy(6, 17);
	printf("□□                                                □□..... ... .  ... ... . .. . . ... .. . . ... .. □□");
	gotoxy(6, 18);
	printf("□□                                                □□... ... ...    . . ..    ..  ..   . .. .    ..  □□");
	gotoxy(6, 19);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
	gotoxy(6, 20);
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□");
	gotoxy(2, 22);
	printf("<-- 뒤로가기 (BACKSPACE)");
}

// 단어장 화면 중 동적인 것을 그리는 함수
void drawWordbook_dynamic(void) {
	file3 = fopen("영단어장.txt", "r");
	for (int sNum = 0; sNum < 12; sNum++) {
		char en[12][100];
		char kr[12][100];
		fgets(en[sNum], 100, file3);
		fgets(kr[sNum], 100, file3);
		//처음이 공백이라면 한칸씩 당기기
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

// 제목 화면을 그려주는 함수
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

// 콘솔의 테두리를 그리는 함수
void drawFrame(void) {
	system("cls");
	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 120; x += 2) {
			setColor(15);
			gotoxy(x, y);
			printf("■");
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

	//키 입력들 무시
	while (_kbhit())
		_getch();
	GetAsyncKeyState(13);
	GetAsyncKeyState(8);
}

// 각각의 파일에서 영어와 한글 뜻을 불러와 변수에 저장시키는 함수
void getWord(void) {
	int randnum;
	int preNum[12] = { 0 };
	srand(time(NULL));

	//영단어 랜덤 저장
	for (int sNum = 0; sNum < 12; sNum++) {
		int x = 0;
		randnum = rand() % WORDNUM;
		//같은 숫자가 있었는지 검사
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
					//길이 저장
					length[sNum] = strlen(reverseString[sNum]) - 1;
				}
				else break;
			}
		}
		else sNum--;
		preNum[sNum] = randnum;
	}


	//한글 뜻 저장
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

// 게임 화면 중 정적인 것을 그리는 함수
void drawGame_static(void) {
	gotoxy(2, 16);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(2, 17);
	printf("┃                                                                                                                 ┃");
	gotoxy(2, 18);
	printf("┃                                                                                                                 ┃");
	gotoxy(2, 19);
	printf("┃                                                                                                                 ┃");
	gotoxy(2, 20);
	printf("┃                                                                                                                 ┃");
	gotoxy(2, 21);
	printf("┃                                                                                                                 ┃");
	gotoxy(2, 22);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(64, 2);
	printf("┌───────────────────────────────────────────────────┐");
	gotoxy(64, 3);
	printf("│                                                   │");
	gotoxy(64, 4);
	printf("│                                                   │");
	gotoxy(64, 5);
	printf("│                                                   │");
	gotoxy(64, 6);
	printf("│                                                   │");
	gotoxy(64, 7);
	printf("│                                                   │");
	gotoxy(64, 8);
	printf("│                                                   │");
	gotoxy(64, 9);
	printf("│                                                   │");
	gotoxy(64, 10);
	printf("│                                                   │");
	gotoxy(64, 11);
	printf("│                                                   │");
	gotoxy(64, 12);
	printf("│                                                   │");
	gotoxy(64, 13);
	printf("│                                                   │");
	gotoxy(64, 14);
	printf("│                                                   │");
	gotoxy(64, 15);
	printf("└───────────────────────────────────────────────────┘");

	gotoxy(16, 2);
	printf("┌───────────────────────────────────────────┐");
	gotoxy(16, 3);
	printf("│                                           │");
	gotoxy(16, 4);
	printf("└───────────────────────────────────────────┘");

	gotoxy(16, 6);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 7);
	printf("┃                                           ┃");
	gotoxy(16, 8);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(4, 12);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

// 게임이 시작했을 때 시바의 설명을 출력하는 도입 부분
void Introduction(void) {
	drawFrame();
	drawGame_static();
	gotoxy(100, 20);
	printf("다음 (엔터)");
	gotoxy(94, 17);
	printf("SKIP (스페이스바) --->");
	char ch;
	for (int i = 1; i <= 8; i++) {
		gotoxy(113, 20);
		printf("▼");
		gotoxy(113, 21);
		printf("  ");
		displayMessage(i);
		while (1) {
			printImage(5, 50, 340, 100, 100);
			if (_kbhit()) {
				ch = _getch();
				//스페이스바는 스킵
				if (ch == 32) return 0;
				//엔터는 다음
				if (ch == 13)
				{
					setColor(15);
					gotoxy(113, 21);
					printf("▼");
					gotoxy(113, 20);
					printf("  ");
					Sleep(200);
					setColor(0);
					break;
				}
				//백스페이스는 이전
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

// 도입 부분의 설명들이 담겨 있어 효과와 함께 출력해주는 함수
void displayMessage(int i) {
	while (_kbhit())
		_getch();
	char s1[] = "안녕 !! 나는 시바라고 해!! 내 영어 수업에 온 것을 환영 해 ^^";
	char s2[] = "오늘은 마침 영어 단어 시험을 보는 날인데 잘 왔어 !! ";
	char s3[] = "시험은 아주 간단해 !! 위에 나오는 단어를 보고 따라 쓰기만 하면 돼 !!";
	char s4[] = "잘 따라썼다면 오른쪽 단어 암기장에 단어를 추가해줄게 ! 오늘은 12개만 볼거야 !";
	char s5[] = "맞다 ! 어제 노트북이 고장났어서 알파벳의 대소문자가 뒤죽박죽일거야ㅠㅠ";
	char s6[] = "그러니까 대문자는 소문자로, 소문자는 대문자로 바꿔서 써줬으면 좋겠어 !!";
	char s7[] = "만약 틀려도 총 5번의 기회가 있으니 신중히 도전해봐 !!";
	char s8[] = "그럼 시작할게 !! 행운을 빌어 !!!";
	char s20[] = "첫 수업부터 엉망이야.. 처음부터 다시 외워 볼래??";
	char s21[] = "아주 잘했어 !! 다른 단어장도 만들어볼래?";
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
		printf("네");
		gotoxy(83, 20);
		printf("아니요");
		break;
	case 21:
		for (int i = 0; i < strlen(s21); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s21[i]);
			Sleep(20);
		}
		gotoxy(83, 18);
		printf("네");
		gotoxy(83, 20);
		printf("아니요");
		break;
	}
}

// 목숨을 그려주는 함수
void drawLife(int life) {
	gotoxy(4, 8);
	setColor(4);
	switch (life) {
	case 5:
		printf("♥♥♥♥♥");
		break;
	case 4:
		printf("♥♥♥♥♡");
		break;
	case 3:
		printf("♥♥♥♡♡");
		break;
	case 2:
		printf("♥♥♡♡♡");
		break;
	case 1:
		printf("♥♡♡♡♡");
		break;
	case 0:
		printf("♡♡♡♡♡");
		break;
	}
	setColor(0);
	gotoxy(6, 14);
	printf("대 문 자 는  소 문 자 로  ,  소 문 자 는  대 문 자 로 !");
}

// 랜덤으로 알파벳의 대소문자를 정해주는 함수
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

// 대문자는 소문자로, 소문자는 대문자로 출력해주는 함수
void printReverseWord(int sNum, char Gstring[100]) {
	//출력 전 공간 지우기(2=현재 단어, 3=다음 단어)
	eraseSpace(2);
	eraseSpace(3);
	//다음 단어 출력
	gotoxy(20, 3);
	setColor(8);
	printf("다음 단어 : ");
	for (int i = 0; i < length[sNum + 1]; i++) {
		char c = reverseString[sNum + 1][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
	//현재 단어 출력
	gotoxy(20, 7);
	printf("현재 단어 : ");
	setColor(12);
	for (int i = 0; i < length[sNum]; i++) {
		char c = reverseString[sNum][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
}

// 게임 중 사용자의 문자열을 입력 받아 맞는지 틀렸는지 판별해주는 함수
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

// 맞거나 틀렸을 때의 문구를 출력해주는 함수
void sendMessage(int i) {
	char s2[] = "아주 잘했어 !!!!!!! 왈왈왈왈왈 !!!";
	char s3[] = "정답이야 !!!!!!! 왈왈왈 !!!";
	char s4[] = "잘한다 잘한다 잘한다 !! 왈왈왈왈왈왈 !!!";
	char s5[] = "맞았어 !!!!!!! 왈왈왈왈 !!!";
	char s6[] = "틀렸어... 크르ㅡ르ㅡㄹ릉";
	char s7[] = "정답이 아니야... 크를를ㄹ르ㅡㅡ르릉";
	char s8[] = "다시 생각해봐... 크ㅡㄹ르를ㄹㄹ릉";
	char s9[] = "분발해야겠어.... 크르르르르ㄹ릉";
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

// 올바르게 단어를 썼을 경우 게임 화면 중 오른쪽 단어장에 영단어와 뜻을 써 주는 함수
void drawRightWord(int sNum, int countNum) {
	gotoxy(66, 3 + countNum);
	printf("%s", randomString[sNum]);
	gotoxy(81, 3 + countNum);
	printf("%s", meanString[sNum]);
}

// 게임이 끝났을 때 단어를 모두 잘 작성했다면 최근 단어장에 단어들을 추가하고 끝낼건지 다시할 건지 정하는 함수
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
		//영단어장 추가
		file3 = fopen("영단어장.txt", "r+");
		for (int i = 0; i < 12; i++)
		{
			//파일 지우기
			fprintf(file3, "%s", Clear[i]);
			//단어 넣기
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

// 게임이 끝났을 때 메뉴 선택의 화살표를 그려주는 함수
void drawSelectEndmenu(int s) {
	switch (s) {
	case 1:
		gotoxy(80, 18);
		printf("▶");
		gotoxy(80, 20);
		printf("  ");
		break;
	case 0:
		gotoxy(80, 18);
		printf("  ");
		gotoxy(80, 20);
		printf("▶");
		break;
	}
}