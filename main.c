/*
<<<< SHIBA's ENGLISH CLASS >>>>

�� ������ ������ '�ù�'�������� ���� ������ ���� �ϴµ�
��Ʈ���� ������ �� ����ܾ��� ��ҹ��ڰ� ���׹��׵� ���丮��
�����Ǿ� �ִ�. ���� Ÿ�ڿ����� ����� ��������� Ư���ϰ� �빮�ڴ�
�ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ��� �Ѵٴ� ��Ģ�� �ִ�.
�̷��� ������ �÷��̾��� ���� ���߷��� �䱸�ǰ� �ϼ��� 
�ܾ����� �ٽ� ���� �����ν� ���� �÷��� ��ü�� �������� �鵵
�����Ǿ� �ִ�. Ÿ�ڿ��� �ϵ��� Ű���带 �̿��Ͽ� ������ �����ϸ�
�� �ܿ��� ������ ����(����Ű�� ����)���� �޴� ���� ���� �� �� �ִ�.


<<<< ���� ���� �� �ʼ� ������ >>>>
 
 �� ��Ʈ���� �ػ󵵴� 1920 x 1080 ���� �������ּ��� !

 �� ��Ʈ���� ������ 125%�� �������ּ��� ! (�� �׷��� ȭ���� �����ϴ�)
	-> ����ȭ�� => ������ Ŭ�� => ���÷��� ���� => �ؽ�Ʈ, �� �� ��Ÿ �׸��� ũ�� ���� => 125%
 
 �� �ܼ�â�� ���� �� �� ��ٷ� ��Ʈ ������ 'NSImSun'���� ���� ���ּ���!
	-> �ܼ�â ���� => ��� �ٿ��� ������ Ŭ�� => �Ӽ� => �۲� => NSimSun
	-> �⺻ ��Ʈ�� ���� �ȿ��� �빮�� I�� �ҹ��� ���� �� ������ ���� �ʱ� ����
  
  */

#include "main.h"

#pragma comment(lib,"winmm.lib")

void init(void) {
	hideCursor(1);	// Ŀ�� ����
	system("color 70");	// ��� ���� ���ڻ� ����
	resizeConsole(WIDTH, HEIGHT);	// �ܼ� ũ�� ����
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);	//���� ���
}

int main() {
	init();	//���� ���� �� �⺻ ������
	int life;	//���

	/*���� ���� ����*/
	do{
		int current = 0;
		//drawTitle�� ���� ���� 10�̸� ���� ���� ��ư�� ���� ���̰�, 11�̸� �ܾ��� ��ư�� ���� ��
		current = drawTitle();

		//���� go==10(���� ���� ��ư�� �����ٸ�) ���� ����
		if (current == 10) {
			file1 = fopen("���ܾ�.txt", "r");	//���ܾ� ���� ����
			file2 = fopen("���ܾ��.txt", "r");	//�� ���� ����

			for (int sNum = 0; sNum < WORDNUM; sNum++) fgets(originalString[sNum], 100, file1);		//originalString �迭�� ���ܾ� ��� �ҷ�����
			for (int sNum = 0; sNum < WORDNUM; sNum++)	fgets(originalString2[sNum], 100, file2);	//originalString2 �迭�� �� ��� �ҷ�����
			fclose(file1);	//���� �ݱ�
			fclose(file2);	//���� �ݱ�

			while (1){
				system("cls");
				Introduction();	//�ù��� ���� ���
				drawFrame();		//�׵θ� �׸���(�ε�)
				drawGame_static();	//���� �� ������ Ʋ �׸���
				Inum = 1;
				isClear = 1;
				countNum = 0;
				go = 0;
				life = 5;
				getWord();	//������ ���� ����ܾ�� ���� �����Ų��

				drawLife(life);	//����� �׷��ش� (ó�� ���� ������ �� �ѹ��� ����)

				//for���� ���ι��� ���� ������ �ܾ� 12���� clear�ϴ°� ������ ��ǥ�̱� ����
				for (int sNum = 0; sNum < 12; sNum++) {
					char Gstring[100];						//Gstring�� ����ڰ� �Է� �ϴ� ���ڿ��� �����ϴ� �迭
					if (life >= 1) {						//���� ����� 1 �̻��̶��
						printReverseWord(sNum, Gstring);	//�ܾ� ���
						hideCursor(0);						//Ŀ�� ���̱�(�Է� ���� ������ Ŀ���� ������ ��
						switch (writeWord(sNum, Gstring)) { //�ܾ �޴µ� ���� 1�� �����ϸ� Ʋ������̰� 2�� �����ϸ� ���� �����
						
						case 1:						//���� wirteWord�� 1�� �����ϸ�
							sNum--;					//Snum�� �����ϸ� ���� �ܾ�� �Ѿ�Ƿ� �������� ����(���ҽ�Ŵ)
							drawLife(--life);		//����� �׷���
							continue;
						case 2:						//���� wirteWord�� 2�� �����ϸ�
							drawRightWord(sNum, countNum++);	//���� ȭ�� ������ ���ܾ��忡 ���� �ܾ ��� �Բ� �߰�
							continue;
						}

					}	
					//�׷��� �ʰ� life�� ���ٸ�
					else isClear = 0;
				}
				go = endGame();	//12�� ��� �����ϰų� ����� ������ �� endGame()�Լ� ����, ���� ���� go�� ����
				if (go == 5 ||go==6)break;	//���� endGame()�� ���ϰ��� 5�̸� go=5�̰� while�� Ż��
			}	
		}
		//11�� �ܾ��� ����
		else if (current == 11) {
			drawWordbook_static();	//������ �ܾ��� ȭ�� �׸���
			drawWordbook_dynamic();	//������ �ܾ��� ȭ�� �׸���
		}

	} while (go != 5);	//go�� 5�� �ƴҵ��� ���ӷ��� �ݺ� -> go�� 5�� ���� endGame���� 5�� ��ȯ�� ����� '�ƴϿ�'�� ������ ���
}

