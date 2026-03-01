namespace range_queries {

template <typename T>
class Container {
public:
    virtual void insert(const T& value) = 0;
    virtual int count_in_range(const T& left, const T& right) const = 0;
    virtual ~Container() = default;
};

}