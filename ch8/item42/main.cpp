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

// TODO: still some error
/* -----demo1: emplace vs push----- */
void demo1(){
    vector<string> vs;
    auto start = chrono::high_resolution_clock::now();
    vs.push_back("xyzzy");
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
//    cout << "copy string: " << time << " ns" << endl;
    start = chrono::high_resolution_clock::now();
    vs.emplace_back("xyzzyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "emplace_back: " << time << " ns" << endl;
    start = chrono::high_resolution_clock::now();
    vs.push_back("xyzzyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "push_back: " << time << " ns" << endl;
}

int main() {
/* -----demo1: emplace vs push----- */
    cout << "--------demo1--------" << endl;
    demo1();

}

