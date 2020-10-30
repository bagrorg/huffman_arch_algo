#ifndef UNTITLED1_HUFFMAN_TREE_H
#define UNTITLED1_HUFFMAN_TREE_H

#include <map>
#include <list>

namespace huffman {

    class huffman_node {
    public:
        huffman_node(int c, char e) : elem_(e), count_(c) {};

        huffman_node(huffman_node *l, huffman_node *r);

        huffman_node *node_ret_l();

        huffman_node *node_ret_r();

        int count();

        unsigned char elem();

    private:
        unsigned char elem_;
        int count_;
        huffman_node *left = NULL;
        huffman_node *right = NULL;
    };

    class huffman_tree {
    public:
        huffman_tree() = default;

        explicit huffman_tree(std::map<unsigned char, int> &freq_);

        void tree_craft_algorithm();

        void convert_to_tree(std::map<unsigned char, int> &freq_);

        huffman_node *root_get();

        void clear_nodes(huffman_node *root);

    private:
        std::list<huffman_node *> tree;
    };


    struct compare_nodes {
        bool operator()(huffman_node *l, huffman_node *r) const;
    };

}
#endif //UNTITLED1_HUFFMAN_TREE_H
