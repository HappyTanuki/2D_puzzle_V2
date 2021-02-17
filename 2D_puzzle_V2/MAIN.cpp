#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_RIGHT	77
#define KEY_LEFT	75

#define P_SIZE_OF_SIDE		4
#define P_SIZE_		P_SIZE_OF_SIDE * P_SIZE_OF_SIDE

int getKey();
int init(int* puzzle, int len);
int check(int* puzzle, int len);
void dispaly(int* puzzle, int len);
int getIndex(int key, int currentIndex, int* changeIndex, int len);
int change(int* puzzle, int currentIndex, int changeIndex);
void p_sort(int* puzzle, int len) {
	int i, j, tmp;

	for (i=0; i<len; i++)
		for (j=i; j<len; j++)
			if (puzzle[i] > puzzle[j]) {
				tmp = puzzle[i];
				puzzle[i] = puzzle[j];
				puzzle[j] = tmp;
			}

	tmp = puzzle[0];
	for (i = 0; i < len - 1; i++)
		puzzle[i] = puzzle[i + 1];
	puzzle[len-1] = tmp;
}

int main() {
	int *puzzle, len = 0, index = 0, c_index = 0;
	int key;

	printf("Please insert your 2DPUZZLE size:");
	scanf_s("%d", &len);
	len = pow(len, 2);

	puzzle = (int *)calloc(len, sizeof(int));

	index = init(puzzle, len);

	dispaly(puzzle, len);
	while (1) {
		while (!_kbhit());

		key = getKey();
		if (getIndex(key, index, &c_index, len))
			index = change(puzzle, index, c_index);

		if (key == 13)
			p_sort(puzzle, len);

		dispaly(puzzle, len);

		if (check(puzzle, len))
			break;
	}
	system("pause");

	return 0;
}

int getKey() {
	int key;

	key = _getch();
	if (key == 224)
		switch (_getch()) {
		case KEY_UP:
			return KEY_UP;
		case KEY_DOWN:
			return KEY_DOWN;
		case KEY_RIGHT:
			return KEY_RIGHT;
		case KEY_LEFT:
			return KEY_LEFT;
		default:
			break;
		}
	else if (key == 13)
		return 13;
	return 0;
}

int init(int* puzzle, int len) {
	int i, P1, P2, tmp = 0, zero = 0;

	srand(time(NULL));

	for (i = 0; i < len; i++)
		puzzle[i] = i;

	for (i = 0; i < 30; i++) {
		P1 = rand() % len;
		P2 = rand() % len;
		if (P1 != P2) {
			if (P1 == zero)
				zero = P2;
			else if (P2 == zero)
				zero = P1;
			tmp = puzzle[P1];
			puzzle[P1] = puzzle[P2];
			puzzle[P2] = tmp;
		}
		else
			i--;
	}

	return zero;
}

int check(int* puzzle, int len) {
	int i;

	for (i = 0; i < len - 1; i++)
		if (puzzle[i] != i + 1)
			return 0;
	return 1;
}

void dispaly(int* puzzle, int len) {
	int i, j;

	system("cls");

	printf("忙式式式成");
	for (i = 0; i < sqrt(len)-2; i++)
		printf("式式式成");
	printf("式式式忖\n");

	j = 0;
	for (j = j; j < len; j += sqrt(len)) {
		for (i = 0; i < sqrt(len); i++)
			if (puzzle[j + i] != 0)
				printf("弛%3d", puzzle[j + i]);
			else
				printf("弛%3s", "﹥");
		printf("弛\n");
		if (j != len - sqrt(len)) {
			printf("戍式式式托");
			for (i = 0; i < sqrt(len) - 2; i++)
				printf("式式式托");
			printf("式式式扣\n");
		}
	}
	printf("戌式式式扛");
	for (i = 0; i < sqrt(len) - 2; i++)
		printf("式式式扛");
	printf("式式式戎\n");
}

int getIndex(int key, int currentIndex, int* changeIndex, int len) {
	int i;
	bool flag = false;

	switch (key) {
	case KEY_UP:
		if (currentIndex >= sqrt(len)) {
			*changeIndex = currentIndex - sqrt(len);
			return 1;
		}
		break;
	case KEY_DOWN:
		if (currentIndex <= sqrt(len)*(sqrt(len) - 1) - 1) {
			*changeIndex = currentIndex + sqrt(len);
			return 1;
		}
		break;
	case KEY_RIGHT:
		flag = false;
		for (i = sqrt(len) - 1; i < len; i += sqrt(len))
			if (currentIndex == i)
				flag = true;
		if (!flag)
			*changeIndex = currentIndex + 1;
			return 1;
		break;
	case KEY_LEFT:
		flag = false;
		for (i = 0; i < len; i += sqrt(len))
			if (currentIndex == i)
				flag = true;
		if (!flag) {
			*changeIndex = currentIndex - 1;
			return 1;
		}
		break;
	default:
		break;
	}

	return 0;
}

int change(int* puzzle, int currentIndex, int changeIndex) {
	int tmp = puzzle[currentIndex];
	puzzle[currentIndex] = puzzle[changeIndex];
	puzzle[changeIndex] = tmp;

	return changeIndex;
}