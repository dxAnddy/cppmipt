#include <gtest/gtest.h>
#include <sstream>
#include <vector>

#include "parser.hpp"

using namespace range_queries;

class MockContainer : public Container<int> {
private:
    std::vector<int> inserted;
public:
    void insert(const int &value) override {
        inserted.push_back(value);
    }

    int count_in_range(const int &left, const int &right) const override {
        int count = 0;
        for(int k : inserted)
            if(k >= left && k <= right)
                count++;
        return count;
    }

};

TEST(ParserTest, ValidInserts) {
    std::istringstream iss("k 10 q 5 15 k 20 q 10 30");
    MockContainer container;
    std::vector<int> res = Parser::process(iss, container);
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], 1);
    EXPECT_EQ(res[1], 2);
}

TEST(ParserTest, InvalidKey) {
    std::istringstream iss1("k 10 x 20");
    MockContainer container;
    EXPECT_THROW(Parser::process(iss1, container), std::runtime_error);

    std::istringstream iss2("k");
    EXPECT_THROW(Parser::process(iss2, container), std::runtime_error);
}

TEST(ParserTest, InvalidRange) {
    std::istringstream iss1("q 20 10");
    MockContainer container;
    EXPECT_THROW(Parser::process(iss1, container), std::runtime_error);

    std::istringstream iss2("q 30");
    EXPECT_THROW(Parser::process(iss2, container), std::runtime_error);
}

