#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <boost/type_index.hpp>


using namespace std;
using boost::typeindex::type_id_with_cvr;

/*------------demo1: create tuple--------------*/

void demo1() {
    // use make_tuple
    tuple<string, int> tp = make_tuple("hello", 10);
    cout << "elem1: " << get<0>(tp) << ", elem2: " << get<1>(tp) << endl;
    // use tie
    int x = 1, y = 2;
    string s = "hello";
    auto tp2 = tie(x, y, s);
    cout << "elem1: " << get<0>(tp2) << ", elem2: " << get<1>(tp2) << ", elem3: " << get<2>(tp2) << endl;
}

/*------------demo2: cat tuple--------------*/
// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple &t) {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple &t) {
        std::cout << std::get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...> &t) {
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}
// end helper function

void demo2() {
    tuple<int, string, float> t1(10, "test", 3.14);
    int n = 7;
    auto t2 = tuple_cat(t1, make_pair("Foo", "bar"), t1, tie(n));
    print(t2);
}


int main() {
/*------------demo1: create tuple--------------*/
    cout << "------demo1------" << endl;
    demo1();
/*------------demo2: cat tuple--------------*/
    cout << "------demo2------" << endl;
    demo2();
}
