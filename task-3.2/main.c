#include "stdio.h"
#include "math.h"
#include "stdlib.h"

/*
* @brief Вычисляет факториал от x
* @params x - число, для которого нужно вычислить факториал
* @return факториал x
*/
double factorial(int x);

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

int main() {
	int n = 0;
	int e = 0;
	puts("Enter n and e values: ");
	scanf("%d %d", &n, &e);
	puts("\n");
	if (n <= 0 || e <= 0) {
		puts("Invalid input!\n");
		abort();
	}
	int k = 0;
	double sum = 0;
	for (k = 1; k <= n; ++k) {
		sum += sequency(k);
	}
	double limit = lim(e, sequency);
	puts("Answers:\n");
	printf("a) %lf\n b) %lf\n", sum, limit);
	return 0;
}
 
double sequency(int n) {
	int k = 0;
	double sum = 0;
	for (k = 0; k <= n; ++k) {
		 sum += ((double)pow(-1, k) / (double)factorial(k)) * (double)k;
	}
	return sum;
}

double factorial(int x) {
	int res = 1;
	int k = 0;
	for (k = 1; k <= x; ++k) {
		res *= k;
	}
	return res;
}

double lim(int n, double (*func)(int)) {
	double a = (double)func(n);
	double b = (double)func(n + 1);
	double arg = n + 2;
	while (fabs(a - b) >= 0.000001) {
		a = b;
		b = func(arg);
		++arg;
	}
	return b;
}
