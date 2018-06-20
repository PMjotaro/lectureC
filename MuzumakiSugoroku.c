/*
*	���ォ�玞�v���ɉQ������ɐi��ł��������낭�Q�[��
*	�X�^�[�g�ʒu��ς������Ƃ��Q����������ς������Ƃ���������͂�
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define R 7		// �Ֆʂ̑傫��(�s)
#define C 7		// �Ֆʂ̑傫��(��)
#define SR 0	// �X�^�[�g�ʒu(�s)
#define SC 0	// �X�^�[�g�ʒu(��)
#define GR 3	// �S�[���ʒu(�s)
#define GC 3	// �S�[���ʒu(��)

void setField(char **field){
	int i,j;

	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			field[i][j] = '-';
		}
	}
}

void setGoal(char **field){
	field[GR][GC] = 'G';
}

void setChar(char **field, char c){
	field[SR][SC] = c;
}


void print(char **field){
	int i,j;


	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			printf("%c ", field[i][j]);
		}
		puts("");
	}
}

int saikoro(){
	int o = (rand() % 6) + 1;
	return o;
}

void susumu(char **field, char c, int me, int *row, int *col, int *rmax, int *rmin, int *cmax, int *cmin, int *muki){
	int i=0;
	int y = *row;
	int x = *col;
	int yx = *rmax;
	int yn = *rmin;
	int xx = *cmax;
	int xn = *cmin;
	int direction = *muki;


	field[y][x] = '-';
	
	printf("%d, %d, %d\n", y, x, direction);

	while((i != me) && (field[y][x] != field[GR][GC])){			// true��{}�����s
		direction = direction % 12;	// �i�ތ���(���v�̌���)

		if(direction == 3){
			if(x != xx){
				x++;
				i++;
			} else {
				direction += 3;	// ���E(���������Ă�̂͌�Ń��[���ǉ����邽��)
				yn++;		// �[�ɓ��B�����̂Ń��C�������߂�(�s�v�ɂȂ��������)
			}
		} else if(direction == 6){
			if(y != yx){
				y++;
				i++;
			} else {
				direction += 3;
				xx--;
			}
		} else if(direction == 9){
			if(x != xn){
				x--;
				i++;
			} else {
				direction += 3;
				yx--;
			}
		} else if(direction == 0){
			if(y != yn){
				y--;
				i++;
			} else {
				direction += 3;
				xn++;
			}
		}
	}

	printf("%d, %d, %d\n", y, x, direction);
	field[y][x] = c;	//�@�Ֆʂ��X�V���ďI���
	// print(field);
	*row = y;
	*col = x;
	*rmax = yx;
	*rmin = yn;
	*cmax = xx;
	*cmin = xn;
	*muki = direction;

}

int input(int q){
	rewind(stdin); // ���̓o�b�t�@�̃N���A
	q = getchar();
	return q;
}

void game(char **field, char c, int row, int col, int rmax, int rmin, int cmax, int cmin, int muki){
	char *now[C];
	int i, me;
	int q = 0;

	for(i=0; i<C; i++) now[i] = field[i];


	

	while(field[GR][GC] != c){ // �Q�[���̌p������
		print(now);
		printf("�T�C�R���U��܂�. [type y/n]\n");
		//q = input(q);
		q = 'y';
		printf("%c\n", q);
		
		if(q == 'y'){
			me = saikoro();
			printf("�o���ڂ�%d�ł�.\n", me);
			susumu(now, c, me, &row, &col, &rmax, &rmin, &cmax, &cmin, &muki);
		} else if(q == 'n'){
			break;
		} else {
			break;
		}
		
	}

	print(now);
	printf("GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL\n");
}


int main()
{
	srand((unsigned)time(NULL));
	char field[R][C];

	int row = SR;	// ���L�����̋��ꏊ
	int	col = SC;	// ���L�����̋��ꏊ
	char c = 'c';	// ���L����
	int rmax = R-1;
	int rmin = 0;
	int cmax = C-1;
	int cmin = 0;
	int muki = 3;	// ���L�����̌���
	int i;

	char *ban[C];
	for(i=0; i<C; i++) ban[i] = field[i];

	setField(ban);	
	setGoal(ban);
	setChar(ban, c);
	// print(ban);

	game(ban, c, row, col, rmax, rmin, cmax, cmin, muki);


	
	return 0;
}

