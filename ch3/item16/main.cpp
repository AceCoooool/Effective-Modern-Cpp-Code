#include <iostream>
#include <algorithm>
#include <vector>
#include <future>
#include <atomic>
#include <mutex>
#include <thread>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: multi thread----- */
// it's a demo, not calculate polynomial
// thread unsafe
class Polynominal {
public:
    void roots() const {
        if (!rootsAreValid) {
            this_thread::sleep_for(chrono::microseconds(1));
            cout << "root are invalid" << endl;
            rootsAreValid = true;
        } else {
            cout << "root are valid" << endl;
        }
    }

private:
    mutable bool rootsAreValid{false};
};

// you need to run several times to see the diff
void demo1() {
    Polynominal *p = new Polynominal();
    constexpr auto num_threads = 10;
    vector<future<void>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Polynominal::roots, p));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
}

// thread safe --- use mutex
class Polynominal1 {
public:
    void roots() const {
        lock_guard<mutex> g(m);
        if (!rootsAreValid) {
            this_thread::sleep_for(chrono::microseconds(1));
            cout << "root are invalid" << endl;
            rootsAreValid = true;
        } else {
            cout << "root are valid" << endl;
        }
    }

private:
    mutable mutex m;
    mutable bool rootsAreValid{false};
};

void demo2() {
    Polynominal1 *p = new Polynominal1();
    constexpr auto num_threads = 10;
    vector<future<void>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Polynominal1::roots, p));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
}

// unsafe
class Point {
public:
    Point(double a, double b) : x(a), y(b) {}

    double distanceFromOrigin() const noexcept {
        for (int i = 0; i < 10000; ++i) {
            callCount = callCount + 5;
            callCount = callCount - 5;
        }
        return sqrt(x * x + y * y);
    }

    unsigned Count() {
        cout << "final(not atomic):" << callCount << endl;
    }

private:
    mutable unsigned callCount{0};
    double x, y;
};

void demo3() {
    Point *p = new Point(2.0, 2.0);
    constexpr auto num_threads = 10;
    vector<future<double>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Point::distanceFromOrigin, p));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
    p->Count();
}


// atomic: for one parameter situation
class Point1 {
public:
    Point1(double a, double b) : x(a), y(b) {}

    double distanceFromOrigin() const noexcept {
        for (int i = 0; i < 10000; ++i) {
            callCount += 5;
            callCount -= 5;
        }
        return sqrt(x * x + y * y);
    }

    unsigned Count() {
        cout << "final(atomic):" << callCount << endl;
    }

private:
    mutable atomic<unsigned> callCount{0};
    double x, y;
};

void demo4() {
    Point1 *p = new Point1(2.0, 2.0);
    constexpr auto num_threads = 10;
    vector<future<double>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Point1::distanceFromOrigin, p));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
    p->Count();
}

// unsafe
class Widget1 {
public:
    int magicValue() const {
        if (cacheValid) cout << "cache valid" << endl;
        else {
            this_thread::sleep_for(chrono::microseconds(1));
            cachedValue = 10;
            cout << "cache invalid" << endl;
            cacheValid = true;
        }
    }

private:
    mutable atomic<bool> cacheValid{false};
    mutable atomic<int> cachedValue;
};

void demo5() {
    Widget1 *w = new Widget1();
    constexpr auto num_threads = 10;
    vector<future<int>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Widget1::magicValue, w));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
}

// safe
class Widget2 {
public:
    int magicValue() const {
        lock_guard<mutex> g(m);
        if (cacheValid) cout << "cache valid" << endl;
        else {
            this_thread::sleep_for(chrono::microseconds(1));
            cachedValue = 10;
            cout << "cache invalid" << endl;
            cacheValid = true;
        }
    }

private:
    mutable mutex m;
    mutable bool cacheValid{false};
    mutable int cachedValue;
};

void demo6() {
    Widget2 *w = new Widget2();
    constexpr auto num_threads = 10;
    vector<future<int>> f;
    for (auto i = 0; i < num_threads; ++i)
        f.push_back(async(launch::async, &Widget2::magicValue, w));
    for (auto i = 0; i < num_threads; ++i)
        f[i].wait();
}

int main() {
/* -----demo1: unsafe----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: mutex----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: atomic----- */
    cout << "--------demo3--------" << endl;
    demo3();
    cout << "--------demo4--------" << endl;
    demo4();
/* -----demo4: problem of atomic----- */
    cout << "--------demo5--------" << endl;
    demo5();
    cout << "--------demo6--------" << endl;
    demo6();

}
