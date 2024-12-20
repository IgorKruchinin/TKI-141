#pragma once
#include "Generator.h"
#include "Matrix.h"
#include <memory>
using namespace miit::algebra;
class Exercise {
protected:
	std::shared_ptr<Matrix> matrix;
	std::shared_ptr<Generator> generator;
public:
	Exercise(size_t rows, size_t cols, std::shared_ptr<Generator> generator, std::shared_ptr<Matrix> matrix);
	virtual ~Exercise();
	virtual void run();
};
