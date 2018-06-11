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

/* -----demo1: T&&----- */
class Widget {
public:
    Widget() = default;
};

Widget widgetFactory() {
    return Widget();
}

template<typename T>
void func(T &&param) {
    cout << "T:  " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo1() {
    Widget w;
    func(w);
    func(widgetFactory());
}

/* -----demo2: forward own----- */
//TODO: there is still a question
template<typename T>
T &&forward_own(remove_reference_t<T> param) {
    cout << "T:  " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
    return static_cast<T &&>(param);
}

void demo2() {
    Widget a;
    forward_own<Widget &>(a);
    forward_own<Widget &&>(widgetFactory());
}


int main() {
/* -----demo1: T&&----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: forward own----- */
    cout << "--------demo2--------" << endl;
    demo2();
}

