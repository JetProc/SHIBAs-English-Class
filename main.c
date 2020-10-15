/*
<<<< SHIBA's ENGLISH CLASS >>>>

이 게임은 강아지 '시바'선생님이 영어 시험을 보게 하는데
노트북이 고장이 나 영어단어의 대소문자가 뒤죽박죽된 스토리로
구성되어 있다. 영어 타자연습과 비슷한 방식이지만 특이하게 대문자는
소문자로, 소문자는 대문자로 써야 한다는 규칙이 있다.
이러한 점에서 플레이어의 고도의 집중력이 요구되고 완성된 
단어장은 다시 보게 함으로써 게임 플레이 자체에 교육적인 면도
내포되어 있다. 타자연습 하듯이 키보드를 이용하여 게임을 진행하며
그 외에도 간단한 조작(방향키와 엔터)으로 메뉴 선택 등을 할 수 있다.


<<<< 게임 시작 전 필수 설정들 >>>>
 
 ▶ 노트북의 해상도는 1920 x 1080 으로 변경해주세요 !

 ▶ 노트북의 배율은 125%로 설정해주세요 ! (안 그러면 화면이 깨집니다)
	-> 바탕화면 => 오른쪽 클릭 => 디스플레이 설정 => 텍스트, 앱 및 기타 항목의 크기 변경 => 125%
 
 ▶ 콘솔창이 실행 된 뒤 곧바로 폰트 설정을 'NSImSun'으로 변경 해주세요!
	-> 콘솔창 실행 => 상단 바에서 오른쪽 클릭 => 속성 => 글꼴 => NSimSun
	-> 기본 폰트는 게임 안에서 대문자 I와 소문자 ㅣ이 잘 구별이 되지 않기 때문
  
  */

#include "main.h"

#pragma comment(lib,"winmm.lib")

void init(void) {
	hideCursor(1);	// 커서 숨김
	system("color 70");	// 배경 색과 글자색 변경
	resizeConsole(WIDTH, HEIGHT);	// 콘솔 크기 지정
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);	//음악 재생
}

int main() {
	init();	//게임 시작 전 기본 설정들
	int life;	//목숨

	/*게임 루프 시작*/
	do{
		int current = 0;
		//drawTitle의 리턴 값이 10이면 게임 시작 버튼을 누른 것이고, 11이면 단어장 버튼을 누른 것
		current = drawTitle();

		//만약 go==10(게임 시작 버튼을 눌렀다면) 게임 시작
		if (current == 10) {
			file1 = fopen("영단어.txt", "r");	//영단어 파일 열기
			file2 = fopen("영단어뜻.txt", "r");	//뜻 파일 열기

			for (int sNum = 0; sNum < WORDNUM; sNum++) fgets(originalString[sNum], 100, file1);		//originalString 배열에 영단어 모두 불러오기
			for (int sNum = 0; sNum < WORDNUM; sNum++)	fgets(originalString2[sNum], 100, file2);	//originalString2 배열에 뜻 모두 불러오기
			fclose(file1);	//파일 닫기
			fclose(file2);	//파일 닫기

			while (1){
				system("cls");
				Introduction();	//시바의 설명 듣기
				drawFrame();		//테두리 그리기(로딩)
				drawGame_static();	//게임 안 정적인 틀 그리기
				Inum = 1;
				isClear = 1;
				countNum = 0;
				go = 0;
				life = 5;
				getWord();	//파일을 열어 영어단어와 뜻을 저장시킨다

				drawLife(life);	//목숨을 그려준다 (처음 게임 시작할 때 한번만 실행)

				//for문이 열두번이 도는 이유는 단어 12개를 clear하는게 게임의 목표이기 때문
				for (int sNum = 0; sNum < 12; sNum++) {
					char Gstring[100];						//Gstring은 사용자가 입력 하는 문자열을 저장하는 배열
					if (life >= 1) {						//만약 목숨이 1 이상이라면
						printReverseWord(sNum, Gstring);	//단어 출력
						hideCursor(0);						//커서 보이기(입력 받을 때에는 커서가 보여야 함
						switch (writeWord(sNum, Gstring)) { //단어를 받는데 만약 1을 리턴하면 틀린경우이고 2를 리턴하면 맞은 경우임
						
						case 1:						//만약 wirteWord가 1을 리턴하면
							sNum--;					//Snum이 증가하면 다음 단어로 넘어가므로 증가하지 않음(감소시킴)
							drawLife(--life);		//목숨을 그려줌
							continue;
						case 2:						//만약 wirteWord가 2를 리턴하면
							drawRightWord(sNum, countNum++);	//게임 화면 오른쪽 영단어장에 맞은 단어를 뜻과 함께 추가
							continue;
						}

					}	
					//그렇지 않고 life가 없다면
					else isClear = 0;
				}
				go = endGame();	//12번 모두 성공하거나 목숨이 끝났을 때 endGame()함수 실행, 리턴 값을 go에 저장
				if (go == 5 ||go==6)break;	//만약 endGame()의 리턴값이 5이면 go=5이고 while문 탈출
			}	
		}
		//11은 단어장 리턴
		else if (current == 11) {
			drawWordbook_static();	//정적인 단어장 화면 그리기
			drawWordbook_dynamic();	//동적인 단어장 화면 그리기
		}

	} while (go != 5);	//go가 5가 아닐동안 게임루프 반복 -> go가 5인 경우는 endGame에서 5를 반환한 경우인 '아니요'를 선택한 경우
}

