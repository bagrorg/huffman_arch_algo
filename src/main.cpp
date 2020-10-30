#include "huffman.h"
#include <cstring>

int main (int argc, char* argv[]) {
    if (strcmp(argv[1], "-c") == 0){
        std::ifstream in(argv[3], std::ios::binary);
        std::ofstream out(argv[5], std::ios::binary);

        try {
            huffman::huffman_algo arch(in);
            arch.archiving();
            out << arch;
            arch.mem_review();
        } catch(huffman::ArchivatingException &e) {
            std::cout << e.what();
        }
        in.close();
        out.close();

    } else if (strcmp(argv[1], "-u") == 0){
        std::ifstream in(argv[3], std::ios::binary);
        std::ofstream out(argv[5], std::ios::binary);

        try {
            huffman::huffman_algo unarch(in);
            unarch.unarchiving();
            out << unarch;
            unarch.mem_review();
        } catch (huffman::ArchivatingException &e){
            std::cout << e.what();
        }
        in.close();
        out.close();
    }
}
