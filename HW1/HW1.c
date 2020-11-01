#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion(int arr[], int cnt) {
	int key, i, j;
	for (i = 1; i < cnt; i++) {
		key = arr[i];

		for (j = i - 1; j >= 0 && arr[j] > key; j--) 
			arr[j + 1] = arr[j];

		arr[j + 1] = key;
	}
}

void problem1() {
	FILE* in;
	int cnt = 0;
	int size = 15, input;
	int *arr = (int*)calloc(size, sizeof(int));
	in = fopen("lab1.data", "r");

	while (EOF != fscanf(in, "%d", &input)) {
		//EOF 전까지 입력받기
		if (cnt < size) {
			arr[cnt++] = input;
		}
		else { //할당한 수보다 커지면 추가 할당
			size += 5;
			arr = (int*)realloc(arr, size * sizeof(int));
			arr[cnt++] = input;
		}
	}
	printf("Input: ");
	for (int i = 0; i < cnt; i++) printf("%d ", arr[i]);
	insertion(arr, cnt);
	printf("\nSorted: ");
	for (int i = 0; i < cnt; i++) printf("%d ", arr[i]);
	printf("\n");

	free(arr);
}

void problem2() {
	int repitition;	//반복 횟수
	double time_elap;	//지난 시간
	printf("   n  repetitions     time\n");
	//n에 따라 출력 (반복)
	for (int n = 0; n <= 100; n += 10) {
		//-----------------------------------------------
		int* arr2 = calloc(n, sizeof(int));
		repitition = 100000 / (n + 1);
		time_elap = 0;	//지난 시간 초기화

		for (int p = 0; p < repitition; p++) {
			for (int j = 0; j < n; j++) {
				arr2[j] = n - j;
			}
			clock_t start = clock();	//시간 시작
			insertion(arr2, n);
			time_elap += (double)(clock() - start);	//시간 끝
		}
		time_elap /= CLOCKS_PER_SEC;
		/* //정렬 확인용 
		for (int l = 0; l < n; l++) printf("%d ", arr2[l]);
		printf("\n");
		*/
		printf("%4d %12d %12.6f\n", n, repitition, time_elap);
		free(arr2);
		//-------------------------------------------------
	}
}

int main() {
	problem1();
	problem2();
	
	return 0;
}
