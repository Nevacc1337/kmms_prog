#include <iostream>

int main() {
    int size_m;
    std::cout << "Введите размер массива: ";
    std::cin >> size_m;
    double a[size_m];
    
    for (int i = 0; i < size_m; i++) {
        std::cout << "Введите " << i << " элемент: ";
        std::cin >> a[i];
    }

    bool is_increasing = true;
    for (int i = 0; i < size_m - 1; i++) {
        if (a[i] >= a[i+1]) {
            is_increasing  = false;
            break;
        }
    }
    

    if (is_increasing) {
        std::cout << "Возрастающая" << std::endl;
    } else {
        std::cout << "Не озрастающая" << std::endl;
    }
    
    return 0;
}