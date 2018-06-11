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

/* -----demo1: override vs universal----- */
// un-efficient version
multiset<string> names1;

void logAndAdd1(const string &name) {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    cout << name << " " << put_time(localtime(&now_c), "%F %T") << endl;
    names1.emplace(name);
}

void demo1() {
    string pName("Darla");
    logAndAdd1(pName);
    logAndAdd1(string("Persephone"));
    logAndAdd1("Patty Dog");
}

// universal version
multiset<string> names2;

template<typename T>
void logAndAdd2(T &&name) {
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
    cout << name << " " << put_time(localtime(&now_c), "%F %T") << endl;
    names2.emplace(forward<T>(name));
}

void demo2() {
    string pName("Darla");
    logAndAdd2(pName);
    logAndAdd2(string("Persephone"));
    logAndAdd2("Patty Dog");
}

unordered_map<int, string> table{{1, "name1"},
                                 {2, "name2"},
                                 {3, "name3"}};

string nameFromIdx(int idx) {
    return table[idx];
}

void logAndAdd2(int idx) {
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
    cout << nameFromIdx(idx) << " " << put_time(localtime(&now_c), "%F %T") << endl;
    names2.emplace(nameFromIdx(idx));
}

void demo3() {
    logAndAdd2(2);
    // Note: error
//    short a = 3;
//    logAndAdd2(a);
}

/* -----demo2: class use universal----- */
class Person {
public:
    template<typename T>
    explicit Person(T &&n):name(forward<T>(n)) {
        cout << "Person(&&)" << endl;
    };

    explicit Person(int idx) { cout << "Person(int)" << endl; }

    Person(const Person &rhs) : name(rhs.name) { cout << "Person(const Person&)" << endl; }

    Person(Person &&rhs) : name(move(rhs.name)) { cout << "Person(Person&&)" << endl; }

private:
    string name;
};

void demo4() {
    Person p("Nancy");
    // Note: error
//    auto p2(p);
    const Person p2("Nancy");
    auto p3(p2);
}


int main() {
/* -----demo1: override vs universal----- */
    cout << "--------demo1--------" << endl;
    demo1();
    cout << "--------demo2--------" << endl;
    demo2();
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo2: class use universal----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

