#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: noexcept call except----- */
void setup() {
    cout << "setup function" << endl;
}

void cleanup() {
    cout << "cleanup function" << endl;
}

void doWork() noexcept {
    setup();
    cleanup();
}

int main() {
/* -----demo1: noexcept call except----- */
    cout << "--------demo1--------" << endl;
    doWork();
}
