#include "parser.hpp"
#include "rb_tree.hpp"
#include <vector>
#include <iostream>

int main() {

    range_queries::RBTree<int> tree;
    try {
        std::vector<int> res = range_queries::Parser::process(std::cin, tree);

        for(const auto &v : res)
            std::cout << v << ' ';
        std::cout << '\n';
    
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}