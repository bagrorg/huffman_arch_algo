#include "autotest.h"
#include <iostream>

void autotest::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    if (!expr){
        std::cout << "ERROR IN FUNCTION : " << func << ",implemented in file : " << filename << ",on line : " << lineNum << "\n";
        failedNum++;
    }
    totalNum++;
}

void autotest::showFinalResult() {
    std::cout << "Total number of tests : " << totalNum << "\n";
    std::cout << "Number of failed tests : " << failedNum << "\n";
}

int autotest::failedNum = 0;
int autotest::totalNum = 0;