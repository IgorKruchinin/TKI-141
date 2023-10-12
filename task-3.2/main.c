#include "stdio.h"
#include "stdlib.h"
#include "float.h"
#include "math.h"

/*
* @brief Вычисляет по указанной в задании формуле
* @params n - число, для которого нужно вычислить формулу
* @return результат вычисления по формуле
*/
double sequency(int n);

/*
* @brief Вычисляет предел функции func от n до бесконечности с точностью до 8 знаков после запятой
* @params n - число, от которого нужно вычислять предел, func - указатель на функцию, от которой нужно вычислить предел
* @return вычисленный предел
*/
double lim(int n, double (*func)(int));

/*
* @brief Печатает сообщение message и получает целое число из stdin
* @params message - сообщение для вывода
* @return считанное число
*/
int getInt(char const *message);

int main() {
	int n = getInt("Enter n value:");
	int e = getInt("Enter e value:");
	size_t k = 0;
	double sum = 0;
	for (k = 1; k <= n; ++k) {
		sum += sequency(k);
	}
	double limit = lim(e, sequency);
	puts("Answers:\n");
	printf("a) %lf\n b) %lf\n", sum, limit);
	return 0;
}

int getInt(char const *message) {
	printf("%s\n", message);
	int value = 0;
	scanf("%d", &value);
	if (value <= 0) {
		puts("Invalid input!\n");
		abort();
	}
	return value;
}
	
double sequency(int n) {
        int k = 0;
        double sum = 0;
        double prev = 1;
        double curr = -1;
        for (k = 2; k <= n; ++k) {
                 curr = prev * (-1/((double)k));
                 sum += curr;
                 prev = curr;
        }
        return sum;
}

double lim(int n, double (*func)(int)) {
	double a = (double)func(n);
	double b = (double)func(n + 1);
	double arg = n + 2;
	while (fabs(a - b) >= DBL_MIN) {
		a = b;
		b = func(arg);
		++arg;
	}
	return b;
}
