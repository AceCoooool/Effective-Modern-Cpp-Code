#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: weak_ptr expired----- */
class Widget {
public:
    Widget() = default;

    ~Widget() = default;
};

void demo1() {
    auto spw = make_shared<Widget>();
    weak_ptr<Widget> wpw(spw);
    spw = nullptr;
    if (wpw.expired())
        cout << "weak pointer is expired" << endl;
}

/* -----demo2: weak_ptr to shared_ptr----- */
void demo2() {
    auto spw = make_shared<Widget>();
    weak_ptr<Widget> wpw(spw);
    auto sp1 = wpw.lock();
    if (sp1)
        cout << "create sp1" << endl;
    auto sp2(spw);
    if (sp2)
        cout << "create sp2" << endl;
}


int main() {
/* -----demo1: weak_ptr expired----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: weak_ptr to shared_ptr----- */
    cout << "--------demo2--------" << endl;
    demo2();
///* -----demo3: shared_from_this----- */
//    cout << "--------demo3--------" << endl;
//    demo3();
}

