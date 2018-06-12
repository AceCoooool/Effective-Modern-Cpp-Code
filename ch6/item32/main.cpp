#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <chrono>
#include <set>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: init capture----- */
class Widget {
public:
    Widget(bool v, bool p, bool a) : validated(v), processed(p), archived(a) {};

    Widget() : validated(true), processed(true), archived(true) {};

    bool isValidated() const { return validated; }

    bool isProcessed() const { return processed; }

    bool isArchived() const { return archived; }

private:
    bool validated;
    bool processed;
    bool archived;
};

void demo1() {
    auto func = [pw = make_unique<Widget>()]() { return pw->isValidated() && pw->isArchived(); };
    if (func()) {
        cout << "init capture(c++14): true!!!!" << endl;
    } else
        cout << "init capture(c++14): false!!!" << endl;
}

/* -----demo2: c++11 struct equal to init capture----- */
class IsValAndArch {
public:
    using DataType = unique_ptr<Widget>;

    explicit IsValAndArch(DataType &&ptr) : pw(move(ptr)) {
    }

    bool operator()() const {
        return pw->isValidated() && pw->isArchived();
    }

private:
    DataType pw;
};

void demo2() {
    auto func = IsValAndArch(make_unique<Widget>());
    if (func()) {
        cout << "class form(c++11): true!!!!" << endl;
    } else
        cout << "class form(c++11): false!!!" << endl;
}

/* -----demo3: c++11 bind+lambda----- */
void demo3() {
    auto func = bind([](const unique_ptr<Widget> &pw) { return pw->isValidated() && pw->isArchived(); },
                     make_unique<Widget>());
    func(Widget());
    if (func()) {
        cout << "bind form(c++11): true!!!!" << endl;
    } else
        cout << "bind form(c++11): false!!!" << endl;
}

/* -----demo4: another demo----- */
void demo4() {
    vector<double> data1{1.2, 2.4, 3.6};
    auto func = [data = move(data1)] {
        cout << "c++14 form: ";
        for (auto a: data) { cout << a << " "; }
        cout << endl;
    };
    func();
    vector<double> data2{1.2, 2.4, 3.6};
    auto func2 = bind([](const vector<double> &data) {
        cout << "c++11 form: ";
        for (auto a: data) { cout << a << " "; }
        cout << endl;
    }, move(data2));
    func2(data2);
}


int main() {
/* -----demo1: init capture----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: c++11 struct equal to init capture----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: c++11 bind+lambda----- */
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo4: another demo----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

