#pragma once

#include "optypes.hpp"
#include "container.hpp"
#include <iostream>
#include <vector>

namespace range_queries {

class Parser {
private:
    template <typename InsertFunc, typename QueryFunc>
    static void parse_and_execute(std::istream &input, InsertFunc insert, QueryFunc query);
public:
    template <typename T>
    static std::vector<int> process(std::istream &input, Container<T> &con);
};

template <typename InsertFunc, typename QueryFunc>
void Parser::parse_and_execute(std::istream &input, InsertFunc insert, QueryFunc query) {
    std::string token;
    while(input >> token) {
        if (token == "k") {
            Key key;
            if(!(input >> key))
                throw std::runtime_error("Expected integer afyer 'k'");
            insert(key);
        } else if (token == "q") {
            int left, right;
            if(!(input >> left >> right))
                throw std::runtime_error("Expected two integers after 'q'");
            try {
                QueryOp q(left, right);
                query(q.left(), q.right());
            } catch(const std::invalid_argument &e) {
                throw std::runtime_error(std::string("Invalid range: ") + e.what());
            }
        } else {
            throw std::runtime_error("Unknown command '" + token + "'");
        }

    }
}

template <typename T>
std::vector<int> Parser::process(std::istream &input, Container<T> &con) {
    std::vector<int> result;

    parse_and_execute(input,
    [&](Key k) {
        con.insert(k);
    },
    [&](int left, int right) {
        int count = con.count_in_range(left, right);
        result.push_back(count);
    });
    return result;
}

}

