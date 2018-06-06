#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <boost/type_index.hpp>
#include "widget.h"

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: pimpl demo----- */
// C++98
void demo1() {
    Widget98 w98;
    Widget11 w11;
}


int main() {
/* -----demo1: weak_ptr expired----- */
    cout << "--------demo1--------" << endl;
    demo1();
}

