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


int main() {
/* -----demo1: simple enum & class enum----- */
    cout << "--------demo1--------" << endl;
    demo1();
}
