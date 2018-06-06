//
// Created by ace on 18-6-6.
//

#include "widget.h"
#include "gadget.h"
#include <vector>
#include <string>

using namespace std;

struct Widget98::Impl {
    string name;
    vector<double> data;
    Gadget g1, g2, g3;
};

Widget98::Widget98() : pImpl(new Impl) { cout << "create widget98" << endl; }

Widget98::~Widget98() { delete pImpl; }

struct Widget11::Impl {
    string name;
    vector<double> data;
    Gadget g1, g2, g3;
};

Widget11::Widget11() : pImpl(make_unique<Impl>()) { cout << "create widget11" << endl; }

Widget11::~Widget11() = default;   // can not delete

// move
Widget11::Widget11(Widget11 &&rhs) = default;

Widget11 &Widget11::operator=(Widget11 &&rhs) = default;

// copy
Widget11::Widget11(const Widget11 &rhs) : pImpl(make_unique<Impl>(*rhs.pImpl)) {}

Widget11 &Widget11::operator=(const Widget11 &rhs) {
    *pImpl = *rhs.pImpl;
    return *this;
}