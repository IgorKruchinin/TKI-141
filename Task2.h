#pragma once
#include "Exercise.h"
#include "Matrix.h"
#include <memory>
using namespace miit::algebra;
class Task2 : public Exercise {
public:
	Task2(size_t rows, size_t cols, std::shared_ptr<Generator> generator, std::shared_ptr<Matrix> matrix) : Exercise(rows, cols,  generator, matrix) {};
	virtual void run();
	~Task2() {}
};
