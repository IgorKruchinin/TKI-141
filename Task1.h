#pragma once
#include "Exercise.h"
#include <memory>
#include "Matrix.h"
using namespace miit::algebra;
class Task1 : public Exercise {
public:
       	Task1(size_t rows, size_t cols, std::shared_ptr<Generator> generator, std::shared_ptr<Matrix> matrix) : Exercise(rows, cols, generator, matrix) {}
        virtual void run();
        ~Task1() {}
};
