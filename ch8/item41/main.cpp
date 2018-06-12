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

/* -----demo1: three version of addName----- */
class Widget1 {    // overload for lvalues and rvalues
public:
    void addName(const string &newName) { names.push_back(newName); }

    void addName(string &&newName) { names.push_back(move(newName)); }

private:
    vector<string> names;
};

class Widget2 {   // use universal reference
public:
    template<typename T>
    void addName(T &&newName) { names.push_back(forward<T>(newName)); }

private:
    vector<string> names;
};

class Widget3 {    // pass by value
public:
    void addName(string newName) { names.push_back(move(newName)); }

private:
    vector<string> names;
};

void demo1() {
    cout << "process Widget1" << endl;
    auto start = chrono::high_resolution_clock::now();
    Widget1 w1;
    string name("Bart");
    w1.addName(name);
    w1.addName(name + "Jenne");
    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "time: " << time << " ns" << endl;
    cout << "process Widget2" << endl;
    start = chrono::high_resolution_clock::now();
    Widget2 w2;
    string name2("Bart");
    w2.addName(name2);
    w2.addName(name2 + "Jenne");
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "time: " << time << " ns" << endl;
    cout << "process Widget3" << endl;
    start = chrono::high_resolution_clock::now();
    Widget3 w3;
    string name3("Bart");
    w3.addName(name);
    w3.addName(name + "Jenne");
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "time: " << time << " ns" << endl;
}


int main() {
/* -----demo1: three version of addName----- */
    cout << "--------demo1--------" << endl;
    demo1();

}

