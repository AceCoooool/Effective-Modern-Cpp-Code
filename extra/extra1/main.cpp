#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/type_index.hpp>

#include "range_own.h"

using namespace std;
using boost::typeindex::type_id_with_cvr;

/*------demo1: range for: only one time------*/
vector<int> arr{1, 2, 3, 4, 5};

vector<int> &get_range() {
    cout << "get_range -> : " << endl;
    return arr;
}

void demo1() {
    for (auto val:get_range())
        cout << val << endl;
}

/*------demo2: own range------*/
void demo2() {
    cout << "range(15): ";
    for (auto i: range(15))
        cout << " " << i;
    cout << endl;
    cout << "range(2, 6): ";
    for (auto i: range(2, 6))
        cout << " " << i;
    cout << endl;
    cout << "range(2, 6, 3): ";
    for (auto i: range(2, 6, 3))
        cout << " " << i;
    cout << endl;
}


int main() {
/*------demo1: range for only one time------*/
    cout << "-----demo1-----" << endl;
    demo1();
/*------demo2: own range------*/
    cout << "-----demo2-----" << endl;
    demo2();
}
