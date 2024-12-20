#include "Exercise.h"
#include "Task1.h"
#include "Task2.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "Generator.h"
#include <iostream>
#include <memory>

int main() {
        size_t rows = 5;
        size_t cols = 5;
	auto generator = std::make_shared<RandomGenerator>(0, 100);
	auto matrix = std::make_shared<Matrix>(rows, cols);
	matrix->fill(generator);
	std::cout << "Матрица до изменений:\n" << *matrix << std::endl;
	Exercise *task1 = new Task1(rows, cols, generator, matrix);
	task1->run();
	std::cout << "Матрица после 1 задания:\n" << *matrix << std::endl;
	Exercise *task2 = new Task2(rows, cols, generator, matrix);
	task2->run();
	std::cout << "Матрица после 2 задания:\n" << *matrix << std::endl;
	delete task1;
	delete task2;
	return 0;
}
