#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

#include "strvec.h"


int main() {
    StrVec v{"hello", "world"};
    StrVec v2 = v;
    for (auto a: v2)
        cout << a << " ";
    cout << endl;
}