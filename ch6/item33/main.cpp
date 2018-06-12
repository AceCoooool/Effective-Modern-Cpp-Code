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

/* -----demo1: lambda auto &&----- */
template<typename T>
void normalize(T &&param) {
    cout << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo1() {
    auto f = [](auto &&param) { normalize(forward<decltype(param)>(param)); };
    f(2);
    int a = 2;
    f(a);
}

int main() {
/* -----demo1: init capture----- */
    cout << "--------demo1--------" << endl;
    demo1();

}

