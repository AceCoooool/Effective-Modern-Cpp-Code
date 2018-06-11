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

/* -----demo1: test array and vector----- */
class Widget{

};
void demo1() {
    // copy vector
    vector<Widget> v(1000, Widget());
    auto start = chrono::high_resolution_clock::now();
    auto v2 = v;
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "copy vector: " << time << " ns" << endl;
    // move vector
    start = chrono::high_resolution_clock::now();
    auto v3 = move(v);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "move vector: " << time << " ns" << endl;
    // copy array
    array<Widget, 1000> arr1;
    start = chrono::high_resolution_clock::now();
    auto arr2 = arr1;
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "copy array: " << time << " ns" << endl;
    // move array
    start = chrono::high_resolution_clock::now();
    auto arr3 = move(arr1);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "move array: " << time << " ns" << endl;
}

/* -----demo2: test small string----- */
void demo2(){
//    string s{"hello world, you are so beautiful~"};
    string s{"hello world"};
    auto start = chrono::high_resolution_clock::now();
    auto s1 = s;
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "copy string: " << time << " ns" << endl;
    start = chrono::high_resolution_clock::now();
    auto s2 = move(s);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "move string: " << time << " ns" << endl;
}

int main() {
/* -----demo1: test array and vector----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: test small string----- */
    cout << "--------demo2--------" << endl;
    demo2();
}

