#include <iostream>

int main() {
    int arr_size;
    std::cout << "Введите размер массива: ";
    std::cin >> arr_size;
    double arr[arr_size];
    
    for (int i = 0; i < arr_size; i++) {
        std::cout << "Введите " << i << " элемент: ";
        std::cin >> arr[i];
    }

    bool is_increasing = true;
    for (int i = 0; i < arr_size - 1; i++) {
        if (arr[i] >= arr[i+1]) {
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