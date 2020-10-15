#define _CRT_SECURE_NO_WARNINGS

// 총 단어의 개수
#define WORDNUM 500
// 가로 세로 크기
#define WIDTH 120
#define HEIGHT 24
// 헤더 정의
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//======================  변수  =============================//

FILE* file1;	//영어 단어 500개가 들어있음
FILE* file2;	//영어 단어 뜻 500개가 들어있음
FILE* file3;	//최근에 만들어진 영어단어와 뜻 12개가 들어있음

// file1에 영단어 500개를 모두 받아 저장하는 배열
char originalString[WORDNUM][100];

// file1의 500개의 영단어 중 랜덤으로 12개를 뽑아 저장하는 배열
char randomString[12][100];

// randomString의 12개의 영단어의 대소문자를 섞어놓아 저장하는 배열
char reverseString[12][100];

// 처음 받아오는 한글 뜻이 들어있는 배열
char originalString2[WORDNUM][100];

// 랜덤으로 뽑은 12개의 단어의 뜻
char meanString[12][100];

// 12개의 문자열의 길이가 들어있음
int length[12];
// 맞춘 단어의 개수를 세는 변수
int countNum;
// 화면의 위치를 정하는 변수
int go;
// 이미지의 번호를 정하는 변수
int Inum;
// 단어 12개를 모두 썼는지 혹은 틀렸는지 결정하는 변수
int isClear;

// 이미지 사용을 위함
HDC consoleDC, imageDC;
HBITMAP imageMap;
HWND consoleWindow;

//========================= 함수 ==================================//


/* 기능적인 함수 =================================================*/

// 커서 숨기는 함수
void hideCursor(int c);
// 콘솔 크기를 정하는 함수
void resizeConsole(int w, int h);
// 커서를 이동시키는 함수
void gotoxy(int x, int y);
//색을 바꾸는 함수
void setColor(unsigned short text);
// 이미지를 출력하는 함수
void printImage(int pictureNum, int start_w, int start_h, int w, int h);
// n에 따라 필요한 줄을 지워주는 함수
void eraseSpace(int n);



/* 단어장 관련 함수 ==============================================*/

// 단어장 화면 중 정적인 것을 그리는 함수
void drawWordbook_static(void);
// 단어장 화면 중 동적인 것을 그리는 함수
void drawWordbook_dynamic(void);



/*게임 시작 전 ===================================================*/

//게임 시작 전 기본 설정들
void init(void);
// 제목 화면을 그려주는 함수
int drawTitle(void);
// 콘솔의 테두리를 그리는 함수
void drawFrame(void);
// 각각의 파일에서 영어와 한글 뜻을 불러와 변수에 저장시키는 함수
void getWord(void);



/*게임 진행 중 ===================================================*/


// 게임 화면 중 정적인 것을 그리는 함수
void drawGame_static(void);
// 게임이 시작했을 때 시바의 설명을 출력하는 도입 부분
void Introduction(void);
// 도입 부분의 설명들이 담겨 있어 효과와 함께 출력해주는 함수
void displayMessage(int i);
// 목숨을 그려주는 함수
void drawLife(int life);
// 랜덤으로 알파벳의 대소문자를 정해주는 함수
char alphabet(char ch);
// 대문자는 소문자로, 소문자는 대문자로 출력해주는 함수
void printReverseWord(int sNum, char Gstring[100]);
// 게임 중 사용자의 문자열을 입력 받아 맞는지 틀렸는지 판별해주는 함수
int writeWord(int sNum, char Gstring[100]);
// 맞거나 틀렸을 때의 문구를 출력해주는 함수
void sendMessage(int i);
// 올바르게 단어를 썼을 경우 게임 화면 중 오른쪽 단어장에 영단어와 뜻을 써 주는 함수
void drawRightWord(int sNum, int countNum);


/*게임이 끝난 후 ==================================================*/


// 게임이 끝났을 때 단어를 모두 잘 작성했다면 최근 단어장에 단어들을 추가하고 끝낼건지 다시할 건지 정하는 함수
int endGame(void);
// 게임이 끝났을 때 메뉴 선택의 화살표를 그려주는 함수
void drawSelectEndmenu(int s);

