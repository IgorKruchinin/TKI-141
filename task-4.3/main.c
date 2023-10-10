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
* @brief Освобождает массив по указателю
* @param **arr исходный массив, n - количество строк
*/
void deleteArr(int **arr, size_t n);

/**
* @brief считывает строку и проверяет, что в ней только числа
* @param *arr строка матрицы (одномерный массив), size размер массива, index - индекс, после которого нужно вставить, elem - элемент, который нужно вставить
* @return изменённый массив
*/
int *insert(int *arr, size_t size, size_t index, int elem);

/**
* @brief заполняет массив целыми числами
* @param ***arr двумерный массив, n и m - размеры массива
*/
void randomInput(int ***arr, size_t n, size_t m);

/**
* @brief заполняет массив пользовательским вводом
* @param ***arr двумерный массив, n и m - размеры массива
*/
void userInput(int ***arr, size_t n, size_t m);

/**
* @brief ищет максимальный элемент массива
* @param **arr массив, n и m размер массива
* @return максимальный элемент
*/
int findMax(int **arr, size_t n, size_t m);

/**
* @brief ищет максимальный элемент массива
* @param ***arr массив, n и m размер массива, max - максимальный элемент массива
* @return массив bool, где на каждом индексе j стоит или не стоит флаг, есть ли в столбце максимальный элемент
*/
int *findMaxColumns(int **arr, size_t n, size_t m, int max);

/**
* @brief заменяет 0-е элементы столбца максимальным элементом в массиве
* @param ***arr массив, m количество столбцов в массиве, max - максимальный элемент массива
*/
void replaceMax(int ***arr, size_t m, int max);

/**
* @brief вставляет нули после столбца, содержащего максимальный элемент в массиве
* @param ***arr массив, n и m размер массива, maxIndexes - массив bool, где на каждом индексе j стоит или не стоит флаг, есть ли в столбце максимальный элемент
* @return изменённый массив
*/
int insertZeroColumns(int ***arr, size_t n, size_t m, int *maxIndexes);

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
size_t getSize(const char *message);

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

/**
* @brief целое число из stdin и возвращает результат
* @param message сообщение, выводимое пользователю перед вводом
* @return считанное целое число
*/
int getInt(const char *message);

/**
* @brief проверяет размер на корректность, если размер некорректен, выходит из программы
* @param n, m размер
*/
void checkSize(size_t n);

int main() {
	size_t n = getSize("Enter count of rows in array: ");
	size_t m = getSize("Enter count of columns in array: ");
	int **arr = getIntArr(n, m);
	int max = findMax(arr, n, m);
	int *maxIndexes = findMaxColumns(arr, n, m, max);
	printArr(arr, n, m);
	// Заменяем нулевой элемент максимальным по модулю элементом массива
	replaceMax(&arr, m, max);
	int insertedColumns = insertZeroColumns(&arr, n, m, maxIndexes);
	puts("Output array:\n");
	printArr(arr, n, m + insertedColumns);
	deleteArr(arr, n);
	return 0;
}

size_t getSize(const char *message) {
	int value = getInt(message);
	checkSize(value);
	return (size_t)value;
}

int **getIntArr(size_t n, size_t m) {
	if (m <= 0 || n <= 0) {
		puts("Invalid shape of array");
		abort();
	}
	enum Choice filling = getChoice();
	int **arr = initArray(n, m);
	if (filling == randomly) {
		randomInput(&arr, n, m);
	} else if (filling == manually) {
		userInput(&arr, n, m);
	} else {
		puts("Invalid choice!");
		abort();
	}
	return arr;
}


int *insert(int *arr, size_t size, size_t index, int elem) {
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


void randomInput(int ***arr, size_t n, size_t m) {
	srand(time(NULL));
	size_t i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			(*arr)[i][j] = rand() % 1000;
		}
	}
}

void userInput(int ***arr, size_t n, size_t m) {
	puts("Enter array elements:\n");
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			(*arr)[i][j] = getInt(NULL);
		}
		puts("\n");
	}
}

int findMax(int **arr, size_t n, size_t m) {
	int max = arr[0][0];
	int i = 0;
	int j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			if (abs(arr[i][j]) > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}

int *findMaxColumns(int **arr, size_t n, size_t m, int max) {
	int *maxIndexes = calloc(m, sizeof(int));
	memset(maxIndexes, 0, m);
	int i = 0, j = 0;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j)
		{
			if (arr[i][j] == max) {
				// если хоть одна строка содержит на индексе j максимальное число, значит столбец j содержит максимальное число
				maxIndexes[j] = 1;
			}
		}
	}
	return maxIndexes;
}

void replaceMax(int ***arr, size_t m, int max) {
	int j = 0;
	for (j = 0; j < m; ++j) {
		(*arr)[0][j] = max;
	}
}

int insertZeroColumns(int ***arr, size_t n, size_t m, int *maxIndexes) {
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
    printf("\nDo you want to enter the array or fill it random digits? (%d - for enter, %d - for random): ", (int)manually, (int)randomly);
    int temp = getInt(NULL);
    return (enum Choice)temp;
}

void deleteArr(int **arr, size_t n) {
	int i = 0;
	for (i = 0; i < n; ++i) {
		free(arr[i]);
	}
	free(arr);
}

int getInt(const char *message) {
	if (message) {
		printf("%s", message);
	}
	int value = 0;
	if (scanf("%d", &value) != 1) {
		puts("Error!\n");
		abort();
	}
	// По условию нужны целые числа, т.е. знаковые, поэтому знак не проверяем
	return value;
}

void checkSize(size_t n) {
	if (n <= 0) {
		puts("Error!\n");
		abort();
	}
}
	
