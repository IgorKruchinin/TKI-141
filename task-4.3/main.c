#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "limits.h"
#include "stdbool.h"
#include "string.h"
#include "math.h"

/**
* @brief печатает массив на экран
* @param **arr исходный массив, n и m - количество строк и столбцов соответственно
*/
void printArr(int **arr, int n, int m);

/**
* @brief считывает строку и проверяет, что в ней только числа
* @param *arr строка матрицы (одномерный массив), size размер массива, index - индекс, после которого нужно вставить, elem - элемент, который нужно вставить
* @return изменённый массив
*/
int *insert(int *arr, int size, int index, int elem);

int *insert(int *arr, int size, int index, int elem) {
	int *tmp = (int*)calloc(size + 1, sizeof(int));
	memset(tmp, 0, size + 1);
	int i = 0;
	int offset = 0;
	//puts("1.1\n");
	for (i = 0; i < size; ++i) {
		if (i == index) {
			tmp[i + offset] = elem;
			++offset;
		}
		tmp[i + offset] = arr[i];
	}
	free(arr);
	arr = tmp;
	return tmp;
	//puts("1.2");
}

void printArr(int **arr, int n, int m) {
	int i = 0;
	int j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			printf("%d\t", arr[i][j]);
		}
		puts("\n");
	}
}

int main() {
	srand(time(NULL));
	int n = 0, m = 0, filling = 0;
	puts("Enter shape of array (n and m): ");
	if (scanf("%d %d", &n, &m) != 2) {
		puts("Invalid number of arguments!");
		abort();
	}
	int **arr = (int**)calloc(n, sizeof(int*));
	int a = 0;
	for (a = 0; a < n; ++a) {
		arr[a] = (int*)calloc(m, sizeof(int));
	} 
	puts("\nDo you want to enter the array or fill it random digits? (0 - for enter, 1 - for random): ");
	if (scanf("%d", &filling) != 1) {
		puts("Invalid number of arguments!");
		abort();
	}
	int i = 0;
	int j = 0;
	int max = INT_MIN;
	if (!filling) {
		puts("Enter array elements:\n");
        }
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			if (filling) {
				arr[i][j] = rand() % 1000;
			} else {
				scanf("%d", &arr[i][j]);
			}
			if (abs(arr[i][j]) > max) {
				max = arr[i][j];
			}
		}
		if (!filling) {
			puts("\n");
		}
	}
	puts("Entered array:\n");
	printArr(arr, n, m);
	bool maxIndexes[m];
	int maxCount = 0;
	memset(&maxIndexes, 0, m);
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j)
		{
			if (arr[i][j] == max) {
				if (!maxIndexes[j]) {
					maxCount++;
				}
				// если хоть одна строка содержит на индексе j максимальное число, значит столбец j содержит максимальное число
				maxIndexes[j] = 1;
			}
		}
	}
	// Заменяем нулевой элемент иаксимальным по модулю элементом массива
        for (j = 0; j < m; ++j) {
                arr[0][j] = max;
        }
	//printf("%d\n", max);
	int offset = 0;
	for (i = 0; i < n; ++i) {
		offset = 0;
		for (j = 0; j < m; ++j) {
			if (maxIndexes[j]) {
				//puts("1");
				arr[i] = insert(arr[i], m + offset, j + offset + 1, 0);
				offset++;
				//puts("2");
			}
		}
	}

	// Заменяем нулевой элемент иаксимальным по модулю элементом массива
	puts("Output array:\n");
	printArr(arr, n, m + offset);
	return 0;
}
