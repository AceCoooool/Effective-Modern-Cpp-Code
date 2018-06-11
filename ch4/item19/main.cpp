#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: shared_ptr custom deleter----- */
class Widget {
public:
    Widget() = default;

    ~Widget() = default;
};

auto customDeleter1 = [](Widget *pw) {
    cout << "custom deleter (1)" << endl;
    delete pw;
};

auto customDeleter2 = [](Widget *pw) {
    cout << "custom deleter (2)" << endl;
    delete pw;
};

void demo1() {
    shared_ptr<Widget> pw1(new Widget, customDeleter1);
    shared_ptr<Widget> pw2(new Widget, customDeleter2);
    vector<shared_ptr<Widget>> vpw{pw1, pw2};
};

/* -----demo2: shared_ptr use raw pointer----- */
void demo2() {
    auto pw = new Widget;
    // Note: it's bad --- however, it wont throw error in my compiler
    shared_ptr<Widget> spw1(pw, customDeleter1);
    shared_ptr<Widget> spw2(pw, customDeleter2);
}

/* -----demo3: shared_from_this----- */
class Widget1;

vector<shared_ptr<Widget1>> processedWidgets;

class Widget1 : public enable_shared_from_this<Widget1> {
public:
    template<typename ... Ts>
    static shared_ptr<Widget1> create(Ts &&... params) {
        cout << "create " << endl;
        shared_ptr<Widget1> p(new Widget1);
        return p;
    }

    void process() {
        cout << "process this" << endl;
        processedWidgets.emplace_back(shared_from_this());
    }

private:
    Widget1() = default;
};

void demo3() {
    shared_ptr<Widget1> w = Widget1::create(1);
    processedWidgets.emplace_back(w);
    cout << processedWidgets.size() << endl;
    w->process();
    cout << processedWidgets.size() << endl;
    w->process();
    cout << processedWidgets.size() << endl;
}

int main() {
/* -----demo1: shared_ptr custom deleter----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: shared_ptr use raw pointer----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: shared_from_this----- */
    cout << "--------demo3--------" << endl;
    demo3();
}

