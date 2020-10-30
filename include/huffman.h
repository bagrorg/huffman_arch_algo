#ifndef UNTITLED1_HUFFMAN_H
#define UNTITLED1_HUFFMAN_H

#include <map>
#include <list>
#include <set>
#include <vector>

#include <algorithm>
#include <fstream>
#include <iostream>

#include "huffman_tree.h"

enum CONSTS {
    TABLE_EL = 5,
    TABLE_PAD_NUM = 3,
    LEFT_CODE = 0,
    RIGHT_CODE = 1,
    FIRST_COUNT_BYTE=0,
    SECOND_COUNT_BYTE = 1,
    SECOND_EIGHT_FIELD = 2,
    THIRD_EIGHT_FIELD = 3,
    BIT = 1,
    LIST_START = 2,
    LAST_BIT = 7,
};

namespace huffman {
    class huffman_algo {
    public:
        friend class huffman_test;

        huffman_algo() = default;

        explicit huffman_algo(std::ifstream &in);

        void unarchiving();

        void archiving();

        void mem_review();

        friend std::ofstream &operator<<(std::ofstream &out, const huffman_algo &a);

    private:
        void table_make(huffman_node *root);

        void file_out_make_arch();

        void file_out_make_unarch();

        void clear_file_in();

        void freq_make_arch();

        void freq_make_unarch();

        std::vector<bool> code_tmp;
        std::map<unsigned char, std::vector<bool>> table;
        std::map<unsigned char, int> freq_;
        std::vector<unsigned char> file_in;
        std::vector<unsigned char> file_out;
        huffman_tree tree;
        bool mode = 0;
        int8_t padding = 0;
        int add_inf = 0;
    };


    enum ERROR_TYPE {
        LOAD_FILE = 0,
        LOAD_INVALID_FILE,
        LOAD_EMPTY_FILE
    };

    class ArchivatingException : public std::exception {
    public:
        explicit ArchivatingException(ERROR_TYPE type);

        const char *what() const noexcept override;

    private:
        ERROR_TYPE flag;
    };
}

#endif