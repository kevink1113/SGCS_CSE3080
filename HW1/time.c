#include <stdio.h>
#include <time.h>


int main() {
	
	int i, j, k, sum = 0;
	double duration;

	clock_t start = clock();									// �ð� ����

	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 1000; j++) {
			for (k = 0; k < 1000; k++) {
				sum++;
			}
		}
	}

	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;	// �ð� ��

	printf("time : %f\n", duration);

	return 0;
}
