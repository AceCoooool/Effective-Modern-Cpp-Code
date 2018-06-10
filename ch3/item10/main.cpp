#include <iostream>
#include <memory>
#include <unordered_map>
#include <list>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: simple enum & class enum----- */

void demo1() {
    // Note: will cause error
//    enum Color1 {
//        black, white, red
//    };
//    auto white = false;
    enum class Color2 {
        black, white, red
    };
    auto white = false;
    auto c = Color2::white;
    cout << white << endl;
    cout << type_id_with_cvr<decltype(c)>().pretty_name() << endl;
    cout << static_cast<int>(c) << endl;
}

void demo2() {
    // un-scoped enum
    enum Color {
        black, white, red
    };
    auto f = [](size_t x) { return x; };

    Color c = red;
    if (c < 14.5) {
        auto res = f(c);
        cout << res << endl;
    }
    // scoped enum
    enum class C {
        b, w, r
    };
    auto c2 = C::r;
    if (static_cast<double>(c2) < 14.5) {
        auto res = f(static_cast<size_t>(c2));
        cout << res << endl;
    }
}

int main() {
/* -----demo1: simple enum & class enum----- */
    cout << "--------demo1--------" << endl;
    demo1();

    cout << "--------demo2--------" << endl;
    demo2();
}
