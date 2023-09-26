#include "stdio.h"
#include "stdlib.h"
#include "time.h"
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

/**
* @brief заполняет массив целыми числами
* @param ***arr двумерный массив, n и m - размеры массива
*/
void randomInput(int ***arr, int n, int m);

/**
* @brief заполняет массив пользовательским вводом
* @param ***arr двумерный массив, n и m - размеры массива
*/
void userInput(int ***arr, int n, int m);

/**
* @brief ищет максимальный элемент массива
* @param ***arr массив, n и m размер массива
* @return максимальный элемент
*/
int findMax(int ***arr, int n, int m);

/**
* @brief ищет максимальный элемент массива
* @param ***arr массив, n и m размер массива, max - максимальный элемент массива
* @return массив bool, где на каждом индексе j стоит или не стоит флаг, есть ли в столбце максимальный элемент
*/
int *findMaxColumns(int ***arr, int n, int m, int max);

/**
* @brief заменяет 0-е элементы столбца максимальным элементом в массиве
* @param ***arr массив, m количество столбцов в массиве, max - максимальный элемент массива
*/
void replaceMax(int ***arr, int m, int max);

/**
* @brief вставляет нули после столбца, содержащего максимальный элемент в массиве
* @param ***arr массив, n и m размер массива, maxIndexes - массив bool, где на каждом индексе j стоит или не стоит флаг, есть ли в столбце максимальный элемент
* @return изменённый массив
*/
int insertZeroColumns(int ***arr, int n, int m, int *maxIndexes);

/**
* @brief выделяет память для массива
* @param n и m размер массива
* @return созданный массив
*/
int **initArray(size_t n, size_t m);

int main() {
	int i = 0;
	int j = 0;
	int n = 0, m = 0, filling = 0;
	puts("Enter shape of array (n and m): ");
	if (scanf("%d %d", &n, &m) != 2) {
		puts("Invalid number of arguments!");
		abort();
	}
	if (m <= 0 || n <= 0) {
		puts("Invalid shape of array");
		abort();
	}
	int **arr = initArray(n, m);
	puts("\nDo you want to enter the array or fill it random digits? (0 - for enter, 1 - for random): ");
	if (scanf("%d", &filling) != 1) {
		puts("Invalid number of arguments!");
		abort();
	}
	if (filling) {
		randomInput(&arr, n, m);
	} else {
		userInput(&arr, n, m);
	}
	int max = findMax(&arr, n, m);
	bool *maxIndexes = findMaxColumns(&arr, n, m, max);
	puts("Entered array:\n");
	printArr(arr, n, m);

	// Заменяем нулевой элемент максимальным по модулю элементом массива
	replaceMax(&arr, m, max);
	int insertedColumns = insertZeroColumns(&arr, n, m, maxIndexes);

	// Заменяем нулевой элемент иаксимальным по модулю элементом массива
	puts("Output array:\n");
	printArr(arr, n, m + insertedColumns);
	return 0;
}

int *insert(int *arr, int size, int index, int elem) {
	int *tmp = (int*)calloc(size + 1, sizeof(int));
	memset(tmp, 0, size + 1);
	int i = 0;
	int insertedColumns = 0;
	for (i = 0; i < size; ++i) {
		if (i == index) {
			tmp[i + insertedColumns] = elem;
			++insertedColumns;
		}
		tmp[i + insertedColumns] = arr[i];
	}
	free(arr);
	arr = tmp;
	return tmp;
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


void randomInput(int ***arr, int n, int m) {
	srand(time(NULL));
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			(*arr)[i][j] = rand() % 1000;
		}
	}
}

void userInput(int ***arr, int n, int m) {
	puts("Enter array elements:\n");
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
				if (scanf("%d", &((*arr)[i][j])) != 1) {
					puts("Invalid number of arguments!");
					abort();
				}
		}
		puts("\n");
	}
}

int findMax(int ***arr, int n, int m) {
	int max = (*arr)[0][0];
	int i = 0;
	int j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			if (abs((*arr)[i][j]) > max) {
				max = (*arr)[i][j];
			}
		}
	}
	return max;
}

int *findMaxColumns(int ***arr, int n, int m, int max) {
	int *maxIndexes = calloc(m, sizeof(int));
	memset(maxIndexes, 0, m);
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j)
		{
			if ((*arr)[i][j] == max) {
				// если хоть одна строка содержит на индексе j максимальное число, значит столбец j содержит максимальное число
				maxIndexes[j] = 1;
			}
		}
	}
	return maxIndexes;
}

void replaceMax(int ***arr, int m, int max) {
	int j = 0;
	for (j = 0; j < m; ++j) {
		(*arr)[0][j] = max;
	}
}

int insertZeroColumns(int ***arr, int n, int m, int *maxIndexes) {
	int insertedColumns = 0;
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		insertedColumns = 0;
		for (j = 0; j < m; ++j) {
			if (maxIndexes[j]) {
				(*arr)[i] = insert((*arr)[i], m + insertedColumns, j + insertedColumns + 1, 0);
				insertedColumns++;
			}
		}
	}
	return insertedColumns;
}

int **initArray(size_t n, size_t m) {
	int **arr = (int**)calloc(n, sizeof(int*));
	int i = 0;
	for (i = 0; i < n; ++i) {
		arr[i] = (int*)calloc(m, sizeof(int));
	}
	return arr;
}
