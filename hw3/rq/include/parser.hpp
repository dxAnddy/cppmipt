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

}

