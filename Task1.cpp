#include "Task1.h"
#include "Matrix.h"
#include <algorithm>
#include <memory>
#include <vector>

void Task1::run() {
    int maximum = matrix->findMax();
	for (size_t j = 0; j < matrix->countCols(); ++j) {
		(*matrix)[0][j] = maximum;
	}
}
