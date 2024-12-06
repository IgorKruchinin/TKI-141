#include "lists.h"
#include <iostream>
int main() {
    List<int> l1;
    std::cout << l1.getSize() << std::endl;
    List l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //l[4] = 10;
    l.remove(3);
    for (size_t i = 0; i < l.getSize(); ++i) {
        std::cout << l[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
