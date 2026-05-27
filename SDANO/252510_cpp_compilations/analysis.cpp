#include "analysis.h"

namespace dsv
{
    namespace analysis
    {
        double average(const double* arr, int size)
        {
            double sum = 0.0;
            for (int i = 0; i < size; i++)
            {
                sum += arr[i];
            }
            return sum / size;
        }

        double minimum(const double* arr, int size)
        {
            double minVal = arr[0];
            for (int i = 1; i < size; i++)
            {
                if (arr[i] < minVal)
                {
                    minVal = arr[i];
                }
            }
            return minVal;
        }

        double maximum(const double* arr, int size)
        {
            double maxVal = arr[0];
            for (int i = 1; i < size; i++)
            {
                if (arr[i] > maxVal)
                {
                    maxVal = arr[i];
                }
            }
            return maxVal;
        }

        bool isIncreasing(const double* arr, int size)
        {
            for (int i = 0; i < size - 1; i++)
            {
                if (arr[i] >= arr[i + 1])
                {
                    return false;
                }
            }
            return true;
        }
    }
}