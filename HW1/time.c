#include <stdio.h>
#include <time.h>


int main() {
	
	int i, j, k, sum = 0;
	double duration;

	clock_t start = clock();									// 시간 시작

	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 1000; j++) {
			for (k = 0; k < 1000; k++) {
				sum++;
			}
		}
	}

	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;	// 시간 끝

	printf("time : %f\n", duration);

	return 0;
}
