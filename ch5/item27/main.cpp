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

/* -----demo1: pass by value----- */
unordered_map<int, string> table{{1, "name1"},
                                 {2, "name2"},
                                 {3, "name3"}};

string nameFromIdx(int idx) {
    return table[idx];
}

class Person {
public:
    explicit Person(string n) : name(move(n)) { cout << "Person(string)" << endl; };

    explicit Person(int idx) : name(nameFromIdx(idx)) { cout << "Person(int)" << endl; };

private:
    string name;
};

void demo1() {
    Person p1("bob");
    Person p2(2);
}

/* -----demo2: use tag dispatch----- */
multiset<string> names;

template<typename T>
void logAndAdd(T &&name);

template<typename T>
void logAndAddImp(T &&name, false_type) {
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
    cout << name << " " << put_time(localtime(&now_c), "%F %T") << endl;
    names.emplace(forward<T>(name));
}

void logAndAddImp(int idx, true_type) {
    logAndAdd(nameFromIdx(idx));
}

template<typename T>
void logAndAdd(T &&name) {
    logAndAddImp(forward<T>(name), is_integral<remove_reference_t<T>>());
}

void demo2() {
    logAndAdd("bob");
    logAndAdd(1);
}

/* -----demo3: Constraining templates that take universal references----- */
// can be improved --- see Person2
class Person1 {
public:
    template<typename T, typename=enable_if_t<!is_same<Person1, decay_t<T>>::value>>
    explicit Person1(T &&n):name(forward<T>(n)) {
        cout << "Person(&&)" << endl;
    };

    Person1(int idx) : name(nameFromIdx(idx)) { cout << "Person(int)" << endl; }

    Person1(const Person1 &rhs) : name(rhs.name) { cout << "Person(const Person&)" << endl; }

    Person1(Person1 &&rhs) : name(move(rhs.name)) { cout << "Person(Person&&)" << endl; }

private:
    string name;
};

void demo3() {
    Person1 p1("Nancy");
    auto p2(p1);
}

class Person2 {
public:
    template<typename T, typename=enable_if_t<!is_base_of<Person2, decay_t<T>>::value &&
                                              !is_integral<remove_reference_t<T>>::value>>
    explicit Person2(T &&n):name(forward<T>(n)) {
        cout << "Person(&&)" << endl;
    };

    Person2(int idx) : name(nameFromIdx(idx)) { cout << "Person(int)" << endl; }

    Person2(const Person2 &rhs) : name(rhs.name) { cout << "Person(const Person&)" << endl; }

    Person2(Person2 &&rhs) : name(move(rhs.name)) { cout << "Person(Person&&)" << endl; }

private:
    string name;
};

void demo4() {
    Person2 p1("Nancy");
    Person2 p2(1);
    short a = 2;
    Person2 p3(a);
}

int main() {
/* -----demo1: pass by value----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: use tag dispatch----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: Constraining templates that take universal references----- */
    cout << "--------demo3--------" << endl;
    demo3();
    cout << "--------demo4--------" << endl;
    demo4();
}

