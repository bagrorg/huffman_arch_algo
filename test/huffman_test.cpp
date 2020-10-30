#include "huffman_test.h"

namespace huffman {

    void huffman_test::test_table_make_1() {
        huffman_algo test_al;
        std::map<unsigned char, int> test_freq;
        test_freq['a'] = 3;
        test_freq['b'] = 3;
        test_freq['c'] = 1;

        huffman_tree test_tree(test_freq);
        test_al.table_make(test_tree.root_get());
        DO_CHECK(test_al.table['a'].size() == 2 && test_al.table['b'].size() == 1 && test_al.table['c'].size() == 2);
	test_tree.clear_nodes(test_tree.root_get());
    }

    void huffman_test::test_table_make_2() {
        huffman_algo test_al;
        std::map<unsigned char, int> test_freq;
        test_freq['a'] = 10000;

        huffman_tree test_tree(test_freq);
        test_al.table_make(test_tree.root_get());
        DO_CHECK(test_al.table['a'].size() == 1);
	test_tree.clear_nodes(test_tree.root_get());
    }

    void huffman_test::test_file_out_arch_1() {
        huffman_algo test_al;
        test_al.file_in = {'a', 'b', 'c'};
        test_al.archiving();

        DO_CHECK(test_al.file_out[0] == 176);
    }

    void huffman_test::test_file_out_arch_2() {
        huffman_algo test_al;
        test_al.file_in = {'a', 'a', 'a'};
        test_al.archiving();

        DO_CHECK(test_al.file_out[0] == 0);
    }

    void huffman_test::test_file_out_arch_3() {
        huffman_algo test_al;
        test_al.file_in = {'a'};
        test_al.archiving();

        DO_CHECK(test_al.file_out[0] == 0);
    }

    void huffman_test::test_file_out_unarch_1() {
        huffman_algo test_al;
        test_al.file_in = {1, 0, 97, 1, 0, 0, 0, 7, 0};
        test_al.unarchiving();

        std::vector<unsigned char> tmp = {'a'};
        DO_CHECK(test_al.file_out == tmp);
    }

    void huffman_test::test_file_out_unarch_2() {
        huffman_algo test_al;
        test_al.file_in = {3, 0, 97, 1, 0, 0, 0, 98, 1, 0, 0, 0, 99, 1, 0, 0, 0, 3, 176};
        test_al.unarchiving();

        std::vector<unsigned char> tmp = {'a', 'b', 'c'};
        DO_CHECK(test_al.file_out == tmp);
    }

    void huffman_test::test_file_out_unarch_3() {
        huffman_algo test_al;
        test_al.file_in = {1, 0, 97, 3, 0, 0, 0, 5, 0};
        test_al.unarchiving();

        std::vector<unsigned char> tmp = {'a', 'a', 'a'};
        DO_CHECK(test_al.file_out == tmp);
    }

    void huffman_test::test_freq_make_arch_1() {
        huffman_algo test_al;
        test_al.file_in = {'a', 'a', 'b', 'b', 'c', 'c'};
        test_al.freq_make_arch();

        DO_CHECK(test_al.freq_['a'] == 2 && test_al.freq_['b'] == 2 && test_al.freq_['c'] == 2);
    }

    void huffman_test::test_freq_make_arch_2() {
        huffman_algo test_al;
        test_al.file_in = {'a', 'a', 'a', 'a'};
        test_al.freq_make_arch();

        DO_CHECK(test_al.freq_['a'] == 4);
    }

    void huffman_test::test_freq_make_unarch_1() {
        huffman_algo test_al;
        test_al.file_in = {1, 0, 97, 3, 0, 0, 0, 5};
        test_al.freq_make_unarch();

        DO_CHECK(test_al.freq_['a'] == 3 && test_al.padding == 5);
    }

    void huffman_test::test_freq_make_unarch_2() {
        huffman_algo test_al;
        test_al.file_in = {2, 0, 97, 1, 0, 0, 0, 98, 1, 0, 0, 0, 6};
        test_al.freq_make_unarch();

        DO_CHECK(test_al.freq_['a'] == 1 && test_al.freq_['b'] == 1 && test_al.padding == 6);
    }

    void huffman_test::runAllTests() {
        test_table_make_1();
        test_table_make_2();

        test_file_out_arch_1();
        test_file_out_arch_2();
        test_file_out_arch_3();

        test_file_out_unarch_1();
        test_file_out_unarch_2();
        test_file_out_unarch_3();

        test_freq_make_arch_1();
        test_freq_make_arch_2();

        test_freq_make_unarch_1();
        test_freq_make_unarch_2();
    }

}


