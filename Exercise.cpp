#include "Exercise.h"

Exercise::Exercise(size_t rows, size_t cols, std::shared_ptr<Generator> generator, std::shared_ptr<Matrix> matrix){
	this->matrix = matrix;
	this->generator = generator;
}

Exercise::~Exercise() {}

void Exercise::run() {}
