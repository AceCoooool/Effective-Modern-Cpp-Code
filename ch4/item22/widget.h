//
// Created by ace on 18-6-6.
//

#ifndef MODERNCPLUS_WIDGET98_H
#define MODERNCPLUS_WIDGET98_H

#include <memory>

class Widget98 {
public:
    Widget98();

    ~Widget98();

private:
    struct Impl;
    Impl *pImpl;
};

class Widget11 {
public:
    Widget11();

    ~Widget11();

    // move
    Widget11(Widget11 &&rhs);

    Widget11 &operator=(Widget11 &&rhs);

    // copy
    Widget11(const Widget11 &rhs);

    Widget11 &operator=(const Widget11 &rhs);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};


#endif //MODERNCPLUS_WIDGET98_H
