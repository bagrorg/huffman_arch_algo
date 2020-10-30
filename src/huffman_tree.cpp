#include "huffman_tree.h"

namespace huffman {
    huffman_node::huffman_node(huffman_node *l, huffman_node *r) {
        left = l;
        right = r;
        if (l != NULL && r != NULL) {
            count_ = l->count_ + r->count_;
        }
    }

    huffman_node *huffman_node::node_ret_l() {
        return left;
    }

    huffman_node *huffman_node::node_ret_r() {
        return right;
    }

    unsigned char huffman_node::elem() {
        return elem_;
    }

    int huffman_node::count() {
        return count_;
    }


    huffman_node *huffman_tree::root_get() {
        return *tree.begin();
    }

    void huffman_tree::tree_craft_algorithm() {
        if (tree.size() == 1) {
            huffman_node *l = tree.front();
            tree.pop_front();

            huffman_node *p = new huffman_node(l, NULL);
            tree.push_back(p);
        }
        while (tree.size() != 1) {
            tree.sort(compare_nodes());

            huffman_node *l = tree.front();
            tree.pop_front();
            huffman_node *r = tree.front();
            tree.pop_front();

            huffman_node *p = new huffman_node(l, r);
            tree.push_back(p);
        }
    }

    void huffman_tree::convert_to_tree(std::map<unsigned char, int> &freq_) {
        std::map<unsigned char, int>::iterator it;

        for (it = freq_.begin(); it != freq_.end(); it++) {
            huffman_node *n = new huffman_node(it->second, it->first);
            tree.push_back(n);
        }
    }

    huffman_tree::huffman_tree(std::map<unsigned char, int> &freq_) {
        convert_to_tree(freq_);
        tree_craft_algorithm();
    }

    void huffman_tree::clear_nodes(huffman_node *root) {
        if (root->node_ret_r() != NULL) {
            clear_nodes(root->node_ret_r());
        }
        if (root->node_ret_l() != NULL) {
            clear_nodes(root->node_ret_l());
        }
        delete root;
    }


    bool compare_nodes::operator()(huffman_node *l, huffman_node *r) const {
        return l->count() < r->count();
    }
}

