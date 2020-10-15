#define _CRT_SECURE_NO_WARNINGS

// �� �ܾ��� ����
#define WORDNUM 500
// ���� ���� ũ��
#define WIDTH 120
#define HEIGHT 24
// ��� ����
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//======================  ����  =============================//

FILE* file1;	//���� �ܾ� 500���� �������
FILE* file2;	//���� �ܾ� �� 500���� �������
FILE* file3;	//�ֱٿ� ������� ����ܾ�� �� 12���� �������

// file1�� ���ܾ� 500���� ��� �޾� �����ϴ� �迭
char originalString[WORDNUM][100];

// file1�� 500���� ���ܾ� �� �������� 12���� �̾� �����ϴ� �迭
char randomString[12][100];

// randomString�� 12���� ���ܾ��� ��ҹ��ڸ� ������� �����ϴ� �迭
char reverseString[12][100];

// ó�� �޾ƿ��� �ѱ� ���� ����ִ� �迭
char originalString2[WORDNUM][100];

// �������� ���� 12���� �ܾ��� ��
char meanString[12][100];

// 12���� ���ڿ��� ���̰� �������
int length[12];
// ���� �ܾ��� ������ ���� ����
int countNum;
// ȭ���� ��ġ�� ���ϴ� ����
int go;
// �̹����� ��ȣ�� ���ϴ� ����
int Inum;
// �ܾ� 12���� ��� ����� Ȥ�� Ʋ�ȴ��� �����ϴ� ����
int isClear;

// �̹��� ����� ����
HDC consoleDC, imageDC;
HBITMAP imageMap;
HWND consoleWindow;

//========================= �Լ� ==================================//


/* ������� �Լ� =================================================*/

// Ŀ�� ����� �Լ�
void hideCursor(int c);
// �ܼ� ũ�⸦ ���ϴ� �Լ�
void resizeConsole(int w, int h);
// Ŀ���� �̵���Ű�� �Լ�
void gotoxy(int x, int y);
//���� �ٲٴ� �Լ�
void setColor(unsigned short text);
// �̹����� ����ϴ� �Լ�
void printImage(int pictureNum, int start_w, int start_h, int w, int h);
// n�� ���� �ʿ��� ���� �����ִ� �Լ�
void eraseSpace(int n);



/* �ܾ��� ���� �Լ� ==============================================*/

// �ܾ��� ȭ�� �� ������ ���� �׸��� �Լ�
void drawWordbook_static(void);
// �ܾ��� ȭ�� �� ������ ���� �׸��� �Լ�
void drawWordbook_dynamic(void);



/*���� ���� �� ===================================================*/

//���� ���� �� �⺻ ������
void init(void);
// ���� ȭ���� �׷��ִ� �Լ�
int drawTitle(void);
// �ܼ��� �׵θ��� �׸��� �Լ�
void drawFrame(void);
// ������ ���Ͽ��� ����� �ѱ� ���� �ҷ��� ������ �����Ű�� �Լ�
void getWord(void);



/*���� ���� �� ===================================================*/


// ���� ȭ�� �� ������ ���� �׸��� �Լ�
void drawGame_static(void);
// ������ �������� �� �ù��� ������ ����ϴ� ���� �κ�
void Introduction(void);
// ���� �κ��� ������� ��� �־� ȿ���� �Բ� ������ִ� �Լ�
void displayMessage(int i);
// ����� �׷��ִ� �Լ�
void drawLife(int life);
// �������� ���ĺ��� ��ҹ��ڸ� �����ִ� �Լ�
char alphabet(char ch);
// �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ������ִ� �Լ�
void printReverseWord(int sNum, char Gstring[100]);
// ���� �� ������� ���ڿ��� �Է� �޾� �´��� Ʋ�ȴ��� �Ǻ����ִ� �Լ�
int writeWord(int sNum, char Gstring[100]);
// �°ų� Ʋ���� ���� ������ ������ִ� �Լ�
void sendMessage(int i);
// �ùٸ��� �ܾ ���� ��� ���� ȭ�� �� ������ �ܾ��忡 ���ܾ�� ���� �� �ִ� �Լ�
void drawRightWord(int sNum, int countNum);


/*������ ���� �� ==================================================*/


// ������ ������ �� �ܾ ��� �� �ۼ��ߴٸ� �ֱ� �ܾ��忡 �ܾ���� �߰��ϰ� �������� �ٽ��� ���� ���ϴ� �Լ�
int endGame(void);
// ������ ������ �� �޴� ������ ȭ��ǥ�� �׷��ִ� �Լ�
void drawSelectEndmenu(int s);

