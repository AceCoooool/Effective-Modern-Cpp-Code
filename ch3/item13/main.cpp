#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: const_iterator----- */
typedef vector<int>::iterator IterT;
typedef vector<int>::const_iterator ConstIterT;

void demo1() {
    vector<int> values{1953, 1983};
    int v = 1983;
    // C++98 --- Note: not work
//    ConstIterT ci = find(static_cast<ConstIterT>(values.begin()), static_cast<ConstIterT>(values.end()), 1983);
//    values.insert(static_cast<IterT>(ci), 1998);
//    for (auto a: values)
//        cout << a << " ";
//    cout << endl;
    auto it = std::find(values.begin(), values.end(), v);
    values.insert(it, 1998);
    for (auto a: values)
        cout << a << " ";
    cout << endl;
}

/* -----demo2: template const_iterator----- */
// C++14
template<typename C, typename V>
void findAndInsert(C &container, const V &targetVal, const V &insertVal) {
    auto it = find(cbegin(container), cend(container), targetVal);
//    cout << type_id_with_cvr<decltype(cbegin(container))>().pretty_name() << endl;
//    cout << type_id_with_cvr<decltype(it)>().pretty_name() << endl;
    container.insert(it, insertVal);
};

void demo2() {
    vector<int> values{1953, 1983};
    int targetVal = 1983, insertVal = 1998;
    findAndInsert(values, targetVal, insertVal);
    for (auto a: values)
        cout << a << " ";
    cout << endl;
}

// C++11
template<typename C>
auto cbegin11(const C &container) -> decltype(begin(container)) {
    return begin(container);
}

template<typename C>
auto cend11(const C &container) -> decltype(end(container)){
    return end(container);
}

template<typename C, typename V>
void findAndInsert11(C &container, const V &targetVal, const V &insertVal) {
    auto it = find(cbegin11(container), cend11(container), targetVal);
//    cout << type_id_with_cvr<decltype(it)>().pretty_name() << endl;
    container.insert(it, insertVal);
};

void demo3() {
    vector<int> values{1953, 1983};
    int targetVal = 1983, insertVal = 1998;
    findAndInsert11(values, targetVal, insertVal);
    for (auto a: values)
        cout << a << " ";
    cout << endl;
}

int main() {
/* -----demo1: without override----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: template const_iterator----- */
    cout << "--------demo2--------" << endl;
    demo2();
    cout << "--------demo3--------" << endl;
    demo3();

}
