#include "Task2.h"
#include "Matrix.h"
#include <algorithm>
#include <vector>

void Task2::run() {
    size_t maxJIdx = matrix->findMaxColumn();
	for (size_t i = 0; i < matrix->countRows(); ++i) {
		(*matrix)[i].insert((*matrix)[i].begin() + maxJIdx, 0);
	}
}
