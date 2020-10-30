#ifndef UNTITLED1_HUFFMAN_TEST_H
#define UNTITLED1_HUFFMAN_TEST_H
#include "autotest.h"
#include "huffman.h"
#include <sstream>

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

namespace huffman {
    class huffman_test : public autotest {
    private:
        void test_table_make_1();

        void test_table_make_2();

        void test_file_out_arch_1();

        void test_file_out_arch_2();

        void test_file_out_arch_3();

        void test_file_out_unarch_1();

        void test_file_out_unarch_2();

        void test_file_out_unarch_3();

        void test_freq_make_arch_1();

        void test_freq_make_arch_2();

        void test_freq_make_unarch_1();

        void test_freq_make_unarch_2();

    public:
        void runAllTests() override;
    };
}
#endif //UNTITLED1_HUFFMAN_TEST_H
