#pragma once
#include <variant>
#include <utility>
#include <stdexcept>

namespace range_queries {

using Key = int;
using Range = std::pair<int, int>;

class QueryOp final {
private:
    int left_;
    int right_;
    void validate(int l, int r) {
        if(l >= r) throw std::invalid_argument("Invalid range: left >= right");
    }
public:
    explicit QueryOp(int l, int r) : left_(l), right_(r) {
        validate(l, r);
    }

    int left() const {return left_;}
    int right() const {return right_;}

    void set_range(int l, int r) {
        validate(l, r);
        left_ = l;
        right_ = r;
    }
};

class InsertOp final {
private:
    Key key_;
public:
    explicit InsertOp(Key k) : key_(k) {}
    Key key() const { return key_;}
    void set_key(Key k) {key_ = k;}
};

using Operation = std::variant<InsertOp, QueryOp>;

}