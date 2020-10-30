#ifndef UNTITLED1_AUTOTEST_H
#define UNTITLED1_AUTOTEST_H
#include <cstddef>


class autotest {
protected:
    static int failedNum;
    static int totalNum;

    static void check(bool expr, const char *func, const char  *filename, size_t lineNum);

public:
    static void showFinalResult();

    virtual void runAllTests() =0;
};

#endif //UNTITLED1_AUTOTEST_H
