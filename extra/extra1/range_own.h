#ifndef MODERNCPLUS_RANGE_OWN_H
#define MODERNCPLUS_RANGE_OWN_H

#include <iostream>

using namespace std;

// 迭代器类
template<typename T>
class range_iterator {
public:
    using value_type = T;
    using size_type = size_t;

public:
    range_iterator(size_t cur_start, T begin_val, T step_val) : cursor_(cur_start), step_(step_val),
                                                                value_(begin_val) {
        value_ += (step_ * cursor_);
    }

    T operator*() const { return value_; }

    bool operator!=(const range_iterator &rhs) const { return (cursor_ != rhs.cursor_); }

    range_iterator &operator++() {
        value_ += step_;
        ++cursor_;
        return (*this);
    }

private:
    size_t cursor_;
    const T step_;
    T value_;
};

// 具体实现: begin()和end()均返回一个迭代器
template<typename T>
class impl {
public:
    using value_type = T;
    using reference = const value_type &;
    using const_reference = const value_type &;
    using iterator = const range_iterator<value_type>;
    using const_iterator = const range_iterator<value_type>;
    using size_type = size_t;

public:
    impl(T begin_val, T end_val, T step_val) : begin_(begin_val), end_(end_val), step_(step_val),
                                               max_count_(get_adjusted_count()) {};

    size_t size() { return max_count_; }

    const_iterator begin() const {
        return {0, begin_, step_};
    }

    const_iterator end() const {
        return {max_count_, begin_, step_};
    }

private:
    const T begin_;
    const T end_;
    const T step_;
    const size_t max_count_;

    size_t get_adjusted_count() const {
        if (step_ > 0 && begin_ >= end_) {
            throw logic_error("End value must greater than begin value");
        } else if (step_ < 0 && begin_ <= end_) {
            throw logic_error("End value must be less than begin value");
        }
        size_t x = static_cast<size_t >((end_ - begin_) / step_);
        if (begin_ + (step_ * x) != end_) ++x;
        return x;
    }
};

template<typename T>
impl<T> range(T end) {
    return {{}, end, 1};
}

template<typename T>
impl<T> range(T begin, T end) {
    return {begin, end, 1};
}


template<typename T, typename U>
decltype(auto) range(T begin, T end, U step) {
    return impl<decltype(begin + step)>(begin, end, step);
};

#endif //MODERNCPLUS_RANGE_OWN_H
