#ifndef ANALYSIS_H
#define ANALYSIS_H

namespace dsv
{
    namespace analysis
    {
        double average(const double* arr, int size);
        double minimum(const double* arr, int size);
        double maximum(const double* arr, int size);
        bool isIncreasing(const double* arr, int size);
    }
}

#endif