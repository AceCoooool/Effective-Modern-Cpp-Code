#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: make_unique for c++11----- */
// C++11
template<typename T, typename ... Ts>
unique_ptr<T> make_unique_11(Ts &&...params) {
    return unique_ptr<T>(new T(forward<Ts>(params)...));
};

void demo1() {
    auto ptr11(make_unique_11<vector<int>>(2, 10));
    cout << ptr11->front() << endl;
    auto ptr14(make_unique<vector<int>>(2, 20));
    cout << ptr14->front() << endl;
}

/* -----demo2: make_xxx is better than new----- */
class Widget {
public:
    Widget() = default;
};

void processWidget(shared_ptr<Widget> spw, int priority) {
    cout << "process widget" << endl;
}

int computePriority() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

void demo2() {
    // worse version: use new: potential resource leak
    processWidget(shared_ptr<Widget>(new Widget), computePriority());
    // better version
    processWidget(make_shared<Widget>(), computePriority());
}

/* -----demo3: shared_ptr with deleter----- */
auto deleter = [](Widget *p) { cout << "delete 1" << endl; };

void demo3() {
    // bad version
    processWidget(shared_ptr<Widget>(new Widget, deleter), computePriority());
    // better version
    shared_ptr<Widget> spw(new Widget, deleter);
    processWidget(spw, computePriority());
    // best version
    processWidget(move(spw), computePriority());
}


int main() {
/* -----demo1: weak_ptr expired----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: make_xxx is better than new----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: shared_ptr with deleter----- */
    cout << "--------demo3--------" << endl;
    demo3();
}

