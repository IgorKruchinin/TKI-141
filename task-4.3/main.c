#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"
#include "math.h"

enum Choice {manually, randomly};

/**
* @brief печатает массив на экран
* @param **arr исходный массив, n и m - количество строк и столбцов соответственно
*/
void printArr(int **arr, size_t n, size_t m);

/**
* @brief считывает строку и проверяет, что в ней только числа
* @param *arr строка матрицы (одномерный массив), size размер массива, index - индекс, после которого нужно вставить, elem - элемент, который нужно вставить
* @return изменённый массив
*/
int *insert(int *arr, size_t size, int index, int elem);

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

/**
* @brief считывает целое число из stdin
* @param message сообщение, выводимое пользователю перед вводом
* @return введённое число
*/
size_t getSize(char const *message);

/**
* @brief считывает массив целых чисел из stdin или заполняет его случайными числами (выбор предоставляется пользователю при вводе)
* @param n, m Количество строк и столбцов в массиве соответственно
* @return полученный массив
*/
int **getIntArr(size_t n, size_t m);

/**
* @brief предлагают пользователю выбор, заполнять массив случайными числами или числами из пользовательского ввода (stdin)
* @return выбор пользователя
*/
enum Choice getChoice();

int main() {
	size_t n = getSize("Enter count of rows in array");
	size_t m = getSize("Enter count of columns in array");
	int **arr = getIntArr(n, m);
	int max = findMax(&arr, n, m);
	int *maxIndexes = findMaxColumns(&arr, n, m, max);
	printArr(arr, n, m);
	// Заменяем нулевой элемент максимальным по модулю элементом массива
	replaceMax(&arr, m, max);
	int insertedColumns = insertZeroColumns(&arr, n, m, maxIndexes);

	// Заменяем нулевой элемент иаксимальным по модулю элементом массива
	puts("Output array:\n");
	printArr(arr, n, m + insertedColumns);
	return 0;
}

size_t getSize(char const *message) {
	printf("%s\n", message);
	int value = 0;
	int condition = scanf("%d", &value);
	if (condition != 1) {
		puts("Invalid input!");
		abort();
	}
	if (value < 0) {
		puts("Invalid size!\n");
		abort();
	}
	return (size_t)value;
}

int **getIntArr(size_t n, size_t m) {
	if (m <= 0 || n <= 0) {
		puts("Invalid shape of array");
		abort();
	}
	int filling = 0;
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
	return arr;
}


int *insert(int *arr, size_t size, int index, int elem) {
	int *tmp = (int*)calloc(size + 1, sizeof(size_t));
	memset(tmp, 0, size + 1);
	size_t i = 0;
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

void printArr(int **arr, size_t n, size_t m) {
	puts("Array:\n");
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			printf("%d\t", arr[i][j]);
		}
		puts("\n");
	}
}


void randomInput(int ***arr, int n, int m) {
	srand(time(NULL));
	size_t i = 0, j = 0;
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
	size_t i = 0;
	for (i = 0; i < n; ++i) {
		arr[i] = (int*)calloc(m, sizeof(int));
	}
	return arr;
}

enum Choice getChoice() {
    int temp;
    int result = scanf("%d", &temp);
    if (result != 1)
    {
        puts("Error!");
        abort();
    }

    return (enum Choice)temp;
}
