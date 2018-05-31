#include <iostream>
#include <memory>
#include <unordered_map>
#include <list>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: overload func----- */
// two same definition
typedef unique_ptr<unordered_map<string, string>> UPtrMapSS1;

using UPtrMapSS2 = unique_ptr<unordered_map<string, string>>;

// two same definition --- function
typedef void (*FP1)(int, const string &);

using FP2 = void (*)(int, const string &);

// two same definition --- template
template<typename T>
struct MyAllocList1 {
    typedef list<T> type;
};

template<typename T>
class Widget1 {
public:
    Widget1(list<T> i) : l(i) { cout << "Using typedef" << endl; }

private:
    typename MyAllocList1<T>::type l;
};

template<typename T>
using MyAllocList2 = list<T>;

template<typename T>
class Widget2 {
public:
    Widget2(list<T> i) : l(i) { cout << "Using using" << endl; }

private:
    MyAllocList2<T> l;
};

void demo1() {
    list<int> tmp;
    Widget1<int> w1{tmp};
    Widget2<int> w2{tmp};
}

int main() {
/* -----demo1: using and typedef----- */
    cout << "--------demo1--------" << endl;
    demo1();
}
