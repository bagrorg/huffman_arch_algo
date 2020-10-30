#include "huffman.h"
#include <climits>

int convert_to_int(unsigned char a, unsigned char b = 0, unsigned char c = 0, unsigned char d = 0) {
    return a + (b << CHAR_BIT) + (c << (CHAR_BIT * SECOND_EIGHT_FIELD)) + (d << (CHAR_BIT * THIRD_EIGHT_FIELD));
}

namespace huffman {
    huffman_algo::huffman_algo(std::ifstream &in) {
        if (!in.is_open()) {
            throw ArchivatingException(LOAD_FILE);
        }
        unsigned char s;
        while (in.read((char *) (&s), sizeof(s))) {
            file_in.push_back(s);
        }
    }

    void huffman_algo::table_make(huffman_node *root) {
        if (root->node_ret_l() != NULL) {
            code_tmp.push_back(LEFT_CODE);
            table_make(root->node_ret_l());
        }
        if (root->node_ret_r() != NULL) {
            code_tmp.push_back(RIGHT_CODE);
            table_make(root->node_ret_r());
        }
        if (root->node_ret_l() == NULL && root->node_ret_r() == NULL) {
            table[root->elem()] = code_tmp;
        }

        code_tmp.pop_back();
    }

    void huffman_algo::clear_file_in() {
        std::reverse(file_in.begin(), file_in.end());
        for (int i = 0; i < add_inf * TABLE_EL + TABLE_PAD_NUM; i++) {
            file_in.pop_back();
        }
        std::reverse(file_in.begin(), file_in.end());
    }

    void huffman_algo::mem_review() {
        if (mode) {
            std::cout << file_in.size() << std::endl << file_out.size() << std::endl << add_inf << std::endl;
        } else {
            std::cout << file_in.size() << std::endl << file_out.size() << std::endl << add_inf << std::endl;
        }
    }

    void huffman_algo::file_out_make_arch() {
        size_t index = 0;
        for (unsigned char el: file_in) {
            for (bool bit: table[el]) {
                if (index % CHAR_BIT == 0) {
                    unsigned char tmp = '\0';
                    file_out.push_back(tmp);
                }
                if (bit) {
                    file_out[index / CHAR_BIT] = file_out[index / CHAR_BIT] | (bit << (LAST_BIT - index % CHAR_BIT));
                }
                index++;
            }
        }
        padding = (CHAR_BIT - (index % CHAR_BIT)) % CHAR_BIT;
    }

    void huffman_algo::file_out_make_unarch() {
        int index = 0;
        huffman_node *decode = tree.root_get();
        for (unsigned char el: file_in) {
            for (int i = 0; i < CHAR_BIT; i++) {
                if ((int) (file_in.size() * CHAR_BIT - index) == (int) padding) {
                    return;
                }
                if (el & (BIT << (LAST_BIT - (index % CHAR_BIT)))) {
                    decode = decode->node_ret_r();
                } else {
                    decode = decode->node_ret_l();
                }

                if (decode->node_ret_l() == NULL && decode->node_ret_r() == NULL) {
                    file_out.push_back(decode->elem());
                    decode = tree.root_get();
                }

                index++;
            }
        }
        if (decode != tree.root_get()) {
            throw ArchivatingException(LOAD_INVALID_FILE);
        }
    }

    void huffman_algo::freq_make_arch() {
        for (char s: file_in) {
            if (freq_.find(s) != freq_.end()) {
                freq_[s]++;
            } else {
                freq_[s] = 1;
            }
        }
    }

    void huffman_algo::freq_make_unarch() {
        add_inf = convert_to_int(file_in[FIRST_COUNT_BYTE], file_in[SECOND_COUNT_BYTE]);
        int k = LIST_START;
        for (int i = 0; i < add_inf; i++, k += TABLE_EL) {
            char el = file_in[k];
            int count = convert_to_int(file_in[k + 1], file_in[k + 2], file_in[k + 3], file_in[k + 4]);

            freq_[el] = count;
        }
        padding = convert_to_int(file_in[k]);
    }

    void huffman_algo::archiving() {
        mode = true;

        if (!file_in.empty()) {
            freq_make_arch();
            tree = huffman_tree(freq_);
            table_make(tree.root_get());
            file_out_make_arch();
            add_inf = freq_.size() * TABLE_EL + TABLE_PAD_NUM;

            tree.clear_nodes(tree.root_get());
        }
    }

    void huffman_algo::unarchiving() {
        if (file_in.empty()) {
            throw ArchivatingException(LOAD_EMPTY_FILE);
        }

        mode = false;
        freq_make_unarch();
        if (freq_.size() > 0) {
            tree = huffman_tree(freq_);
        }
        clear_file_in();
        file_out_make_unarch();
        add_inf = add_inf * TABLE_EL + TABLE_PAD_NUM;

        if (freq_.size() > 0) {
            tree.clear_nodes(tree.root_get());
        }
    }

    std::ofstream &operator<<(std::ofstream &out, const huffman_algo &a) {
        if (a.mode) {
            int16_t count_char = a.freq_.size();
            out.write((char *) &count_char, sizeof(count_char));
            std::map<unsigned char, int>::const_iterator it;

            for (it = a.freq_.begin(); it != a.freq_.end(); it++) {
                out << it->first;
                out.write((char *) &it->second, sizeof(it->second));
            }
            out.write((char *) &a.padding, sizeof(a.padding));
        }


        for (unsigned char el: a.file_out) {
            out << el;
        }

        return out;
    }


    ArchivatingException::ArchivatingException(ERROR_TYPE type) {
        flag = type;
    }

    const char *ArchivatingException::what() const noexcept {
        switch (flag) {
            case 0:
                return "LOAD: unable to open file.";
            case 1:
                return "LOAD: invalid file format.";
            case 2:
                return "LOAD: unable to zip/unzip empty file";
            default:
                return "";
        }
    }
}