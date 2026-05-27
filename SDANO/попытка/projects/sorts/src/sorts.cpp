#include <vector>

#include "sorts.hpp"

void tkr::bubbleSort(std::vector<int>& arr) {
	const int size = arr.size();
	int temp;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			} 
		}
	}
}