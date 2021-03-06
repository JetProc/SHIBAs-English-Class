#include "main.h"

// 醴憮 獗晦朝 л熱 (c陛 1(true)檜賊 獗梯, 0(false)檜賊 爾歜) 
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

// 夔樂 觼晦蒂 薑ж朝 л熱(w=陛煎, h=撮煎)
void resizeConsole(int w, int h) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", w, h);
	system(chTemp);
}

// 醴憮蒂 檜翕衛酈朝 л熱(x,y)
void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//儀擊 夥紱朝 л熱(0~15)
void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (7 << 4));
}

// 檜嘐雖蒂 轎溘ж朝 л熱(だ橾檜葷曖 璋濠, 衛濛轎溘嬪纂x, 衛濛轎溘嬪纂y, 檜嘐雖轎溘x, 檜嘐雖轎溘y)
void printImage(int pictureNum, int start_w, int start_h, int w, int h) {
	char path[101];
	//檜嘐雖だ橾 檜葷檜 picture0, picture1 檜楛 ⑽衝戲煎 盪濰腎橫 氈擠
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

// n縑 評塭 в蹂и 還擊 雖錶輿朝 л熱
void eraseSpace(int n) {
	switch (n)
	{
	//殮溘嫡朝 睡碟
	case 1:
		gotoxy(6, 11);
		printf("                                                        ");
		break;

	//⑷營 欽橫 轎溘 睡碟
	case 2:
		gotoxy(30, 7);
		printf("                              ");
		break;

	//棻擠 欽橫 轎溘 睡碟
	case 3:
		gotoxy(30, 3);
		printf("                              ");
		break;
	
	//渠�倥Ⅷ� 詭撮雖 轎溘 睡碟
	case 4:
		gotoxy(5, 19);
		printf("                                                                                                             ");
		break;
	}
}

// 欽橫濰 �飛� 醞 薑瞳檣 匙擊 斜葬朝 л熱
void drawWordbook_static(void) {
	system("cls");
	//殮溘 鼠衛
	while (_kbhit())	_getch();

	drawFrame();
	gotoxy(42, 2);
	printf("S H I B A ' S   W O R D   B O O K");
	gotoxy(6, 3);
	printf("﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤");
	gotoxy(6, 4);
	printf("﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤");
	gotoxy(6, 5);
	printf("﹤﹤                                                ﹤﹤ . ..... . . ... . . . .. . ..... . . . . . . . ﹤﹤");
	gotoxy(6, 6);
	printf("﹤﹤                                                ﹤﹤ .. .. . ... ... . .. ... ...... . ... . . . .  ﹤﹤");
	gotoxy(6, 7);
	printf("﹤﹤                                                ﹤﹤ ....   .... ... .  . ...   ...  .. . ..... ... ﹤﹤");
	gotoxy(6, 8);
	printf("﹤﹤                                                ﹤﹤  .. ..     ...   .... ...    ....    . ..  ... ﹤﹤");
	gotoxy(6, 9);
	printf("﹤﹤                                                ﹤﹤ . . . .  ..   ..   . . .   .   .. .   ........ ﹤﹤");
	gotoxy(6, 10);
	printf("﹤﹤                                                ﹤﹤. . . . .  . . .  . ..... . .. . . .. ... ..... ﹤﹤");
	gotoxy(6, 11);
	printf("﹤﹤                                                ﹤﹤ ... . ...   .... . ... ....   .... .... .... . ﹤﹤");
	gotoxy(6, 12);
	printf("﹤﹤                                                ﹤﹤ .. .. .. . .. . . . ... .. ... .. .. .... .... ﹤﹤");
	gotoxy(6, 13);
	printf("﹤﹤                                                ﹤﹤ .. .. .. .. .. . .. .. .. .. .. .. .. .. .. .. ﹤﹤");
	gotoxy(6, 14);
	printf("﹤﹤                                                ﹤﹤ .. . .. . . . . . . .. . . . . . .. . . . . .  ﹤﹤");
	gotoxy(6, 15);
	printf("﹤﹤                                                ﹤﹤ ..    .    . .  .  .    .    .   .   .   . . . ﹤﹤");
	gotoxy(6, 16);
	printf("﹤﹤                                                ﹤﹤... ..... ........ ...... ....... ......... ... ﹤﹤");
	gotoxy(6, 17);
	printf("﹤﹤                                                ﹤﹤..... ... .  ... ... . .. . . ... .. . . ... .. ﹤﹤");
	gotoxy(6, 18);
	printf("﹤﹤                                                ﹤﹤... ... ...    . . ..    ..  ..   . .. .    ..  ﹤﹤");
	gotoxy(6, 19);
	printf("﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤");
	gotoxy(6, 20);
	printf("﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤");
	gotoxy(2, 22);
	printf("<-- 菴煎陛晦 (BACKSPACE)");
}

// 欽橫濰 �飛� 醞 翕瞳檣 匙擊 斜葬朝 л熱
void drawWordbook_dynamic(void) {
	file3 = fopen("艙欽橫濰.txt", "r");
	for (int sNum = 0; sNum < 12; sNum++) {
		char en[12][100];
		char kr[12][100];
		fgets(en[sNum], 100, file3);
		fgets(kr[sNum], 100, file3);
		//籀擠檜 奢寥檜塭賊 и蘊噶 渡晦晦
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

// 薯跡 �飛橉� 斜溥輿朝 л熱
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

// 夔樂曖 纔舒葬蒂 斜葬朝 л熱
void drawFrame(void) {
	system("cls");
	for (int y = 0; y < 24; y++) {
		for (int x = 0; x < 120; x += 2) {
			setColor(15);
			gotoxy(x, y);
			printf("﹥");
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

	//酈 殮溘菟 鼠衛
	while (_kbhit())
		_getch();
	GetAsyncKeyState(13);
	GetAsyncKeyState(8);
}

// 陝陝曖 だ橾縑憮 艙橫諦 и旋 嗆擊 碳楝諦 滲熱縑 盪濰衛酈朝 л熱
void getWord(void) {
	int randnum;
	int preNum[12] = { 0 };
	srand(time(NULL));

	//艙欽橫 楠渾 盪濰
	for (int sNum = 0; sNum < 12; sNum++) {
		int x = 0;
		randnum = rand() % WORDNUM;
		//偽擎 璋濠陛 氈歷朝雖 匐餌
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
					//望檜 盪濰
					length[sNum] = strlen(reverseString[sNum]) - 1;
				}
				else break;
			}
		}
		else sNum--;
		preNum[sNum] = randnum;
	}


	//и旋 嗆 盪濰
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

// 啪歜 �飛� 醞 薑瞳檣 匙擊 斜葬朝 л熱
void drawGame_static(void) {
	gotoxy(2, 16);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(2, 17);
	printf("早                                                                                                                 早");
	gotoxy(2, 18);
	printf("早                                                                                                                 早");
	gotoxy(2, 19);
	printf("早                                                                                                                 早");
	gotoxy(2, 20);
	printf("早                                                                                                                 早");
	gotoxy(2, 21);
	printf("早                                                                                                                 早");
	gotoxy(2, 22);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	gotoxy(64, 2);
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(64, 3);
	printf("弛                                                   弛");
	gotoxy(64, 4);
	printf("弛                                                   弛");
	gotoxy(64, 5);
	printf("弛                                                   弛");
	gotoxy(64, 6);
	printf("弛                                                   弛");
	gotoxy(64, 7);
	printf("弛                                                   弛");
	gotoxy(64, 8);
	printf("弛                                                   弛");
	gotoxy(64, 9);
	printf("弛                                                   弛");
	gotoxy(64, 10);
	printf("弛                                                   弛");
	gotoxy(64, 11);
	printf("弛                                                   弛");
	gotoxy(64, 12);
	printf("弛                                                   弛");
	gotoxy(64, 13);
	printf("弛                                                   弛");
	gotoxy(64, 14);
	printf("弛                                                   弛");
	gotoxy(64, 15);
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

	gotoxy(16, 2);
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(16, 3);
	printf("弛                                           弛");
	gotoxy(16, 4);
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

	gotoxy(16, 6);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(16, 7);
	printf("早                                           早");
	gotoxy(16, 8);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(4, 12);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

// 啪歜檜 衛濛ц擊 陽 衛夥曖 撲貲擊 轎溘ж朝 紫殮 睡碟
void Introduction(void) {
	drawFrame();
	drawGame_static();
	gotoxy(100, 20);
	printf("棻擠 (縛攪)");
	gotoxy(94, 17);
	printf("SKIP (蝶む檜蝶夥) --->");
	char ch;
	for (int i = 1; i <= 8; i++) {
		gotoxy(113, 20);
		printf("∪");
		gotoxy(113, 21);
		printf("  ");
		displayMessage(i);
		while (1) {
			printImage(5, 50, 340, 100, 100);
			if (_kbhit()) {
				ch = _getch();
				//蝶む檜蝶夥朝 蝶霾
				if (ch == 32) return 0;
				//縛攪朝 棻擠
				if (ch == 13)
				{
					setColor(15);
					gotoxy(113, 21);
					printf("∪");
					gotoxy(113, 20);
					printf("  ");
					Sleep(200);
					setColor(0);
					break;
				}
				//寥蝶む檜蝶朝 檜瞪
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

// 紫殮 睡碟曖 撲貲菟檜 氬啖 氈橫 �膩�諦 л眷 轎溘п輿朝 л熱
void displayMessage(int i) {
	while (_kbhit())
		_getch();
	char s1[] = "寰喟 !! 釭朝 衛夥塭堅 п!! 頂 艙橫 熱機縑 螞 匙擊 �紊� п ^^";
	char s2[] = "螃棺擎 葆藹 艙橫 欽橫 衛я擊 爾朝 陳檣等 澀 諮橫 !! ";
	char s3[] = "衛я擎 嬴輿 除欽п !! 嬪縑 釭螃朝 欽橫蒂 爾堅 評塭 噙晦虜 ж賊 腋 !!";
	char s4[] = "澀 評塭質棻賊 螃艇薹 欽橫 懍晦濰縑 欽橫蒂 蹺陛п還啪 ! 螃棺擎 12偃虜 獐剪撿 !";
	char s5[] = "蜃棻 ! 橫薯 喻お磁檜 堅濰陬橫憮 憲だ漯曖 渠模僥濠陛 菴避夢避橾剪撿壬壬";
	char s6[] = "斜楝棲梱 渠僥濠朝 模僥濠煎, 模僥濠朝 渠僥濠煎 夥脯憮 賦鍍戲賊 謠啊橫 !!";
	char s7[] = "虜擒 ぎ溥紫 識 5廓曖 晦�萼� 氈戲棲 褐醞�� 紫瞪п瑭 !!";
	char s8[] = "斜歲 衛濛й啪 !! ч遴擊 網橫 !!!";
	char s20[] = "羅 熱機睡攪 氅蜂檜撿.. 籀擠睡攪 棻衛 諼錶 獐楚??";
	char s21[] = "嬴輿 澀ц橫 !! 棻艇 欽橫濰紫 虜菟橫獐楚?";
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
		printf("啻");
		gotoxy(83, 20);
		printf("嬴棲蹂");
		break;
	case 21:
		for (int i = 0; i < strlen(s21); i++) {
			printImage(5, 50, 340, 100, 100);
			printf("%c", s21[i]);
			Sleep(20);
		}
		gotoxy(83, 18);
		printf("啻");
		gotoxy(83, 20);
		printf("嬴棲蹂");
		break;
	}
}

// 跡獗擊 斜溥輿朝 л熱
void drawLife(int life) {
	gotoxy(4, 8);
	setColor(4);
	switch (life) {
	case 5:
		printf("ⅥⅥⅥⅥⅥ");
		break;
	case 4:
		printf("ⅥⅥⅥⅥⅤ");
		break;
	case 3:
		printf("ⅥⅥⅥⅤⅤ");
		break;
	case 2:
		printf("ⅥⅥⅤⅤⅤ");
		break;
	case 1:
		printf("ⅥⅤⅤⅤⅤ");
		break;
	case 0:
		printf("ⅤⅤⅤⅤⅤ");
		break;
	}
	setColor(0);
	gotoxy(6, 14);
	printf("渠 僥 濠 朝  模 僥 濠 煎  ,  模 僥 濠 朝  渠 僥 濠 煎 !");
}

// 楠渾戲煎 憲だ漯曖 渠模僥濠蒂 薑п輿朝 л熱
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

// 渠僥濠朝 模僥濠煎, 模僥濠朝 渠僥濠煎 轎溘п輿朝 л熱
void printReverseWord(int sNum, char Gstring[100]) {
	//轎溘 瞪 奢除 雖辦晦(2=⑷營 欽橫, 3=棻擠 欽橫)
	eraseSpace(2);
	eraseSpace(3);
	//棻擠 欽橫 轎溘
	gotoxy(20, 3);
	setColor(8);
	printf("棻擠 欽橫 : ");
	for (int i = 0; i < length[sNum + 1]; i++) {
		char c = reverseString[sNum + 1][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
	//⑷營 欽橫 轎溘
	gotoxy(20, 7);
	printf("⑷營 欽橫 : ");
	setColor(12);
	for (int i = 0; i < length[sNum]; i++) {
		char c = reverseString[sNum][i];
		if (c >= 'a' && c <= 'z')	printf("%c", c - 32);
		else if (c >= 'A' && c <= 'Z')	printf("%c", c + 32);
		else printf("%c", c);
	}
	setColor(0);
}

// 啪歜 醞 餌辨濠曖 僥濠翮擊 殮溘 嫡嬴 蜃朝雖 ぎ溜朝雖 っ滌п輿朝 л熱
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

// 蜃剪釭 ぎ溜擊 陽曖 僥掘蒂 轎溘п輿朝 л熱
void sendMessage(int i) {
	char s2[] = "嬴輿 澀ц橫 !!!!!!! 諱諱諱諱諱 !!!";
	char s3[] = "薑港檜撿 !!!!!!! 諱諱諱 !!!";
	char s4[] = "澀и棻 澀и棻 澀и棻 !! 諱諱諱諱諱諱 !!!";
	char s5[] = "蜃懊橫 !!!!!!! 諱諱諱諱 !!!";
	char s6[] = "ぎ溜橫... 觼腦天腦天予葵";
	char s7[] = "薑港檜 嬴棲撿... 觼蒂蒂予腦天天腦葵";
	char s8[] = "棻衛 儅陝п瑭... 觼天予腦蒂予予葵";
	char s9[] = "碟嫦п撿啊橫.... 觼腦腦腦腦予葵";
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

// 螢夥腦啪 欽橫蒂 質擊 唳辦 啪歜 �飛� 醞 螃艇薹 欽橫濰縑 艙欽橫諦 嗆擊 賦 輿朝 л熱
void drawRightWord(int sNum, int countNum) {
	gotoxy(66, 3 + countNum);
	printf("%s", randomString[sNum]);
	gotoxy(81, 3 + countNum);
	printf("%s", meanString[sNum]);
}

// 啪歜檜 部陬擊 陽 欽橫蒂 賅舒 澀 濛撩ц棻賊 譆斬 欽橫濰縑 欽橫菟擊 蹺陛ж堅 部鳥勒雖 棻衛й 勒雖 薑ж朝 л熱
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
		//艙欽橫濰 蹺陛
		file3 = fopen("艙欽橫濰.txt", "r+");
		for (int i = 0; i < 12; i++)
		{
			//だ橾 雖辦晦
			fprintf(file3, "%s", Clear[i]);
			//欽橫 厥晦
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

// 啪歜檜 部陬擊 陽 詭景 摹鷗曖 �香嚂斥� 斜溥輿朝 л熱
void drawSelectEndmenu(int s) {
	switch (s) {
	case 1:
		gotoxy(80, 18);
		printf("Ⅱ");
		gotoxy(80, 20);
		printf("  ");
		break;
	case 0:
		gotoxy(80, 18);
		printf("  ");
		gotoxy(80, 20);
		printf("Ⅱ");
		break;
	}
}