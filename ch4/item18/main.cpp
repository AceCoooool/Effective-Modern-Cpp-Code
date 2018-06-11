#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/type_index.hpp>
#include <memory>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: unique_ptr----- */
class Investment {
public:
    Investment(int v1, int v2) : val1(v1), val2(v2) {}

    virtual void Print() { cout << "Investment" << endl; };

private:
    int val1, val2;
};

class Stock : public Investment {
public:
    Stock(int v1, int v2) : Investment(v1, v2) {}

    void Print() override { cout << "Stock" << endl; }
};

class Bond : public Investment {
public:
    Bond(int v1, int v2) : Investment(v1, v2) {}

    void Print() override { cout << "Bond" << endl; }
};

class RealEstate : public Investment {
public:
    RealEstate(int v1, int v2) : Investment(v1, v2) {}

    void Print() override { cout << "RealEstate" << endl; }
};

template<typename ... Ts>
auto makeInvestment(int k, Ts &&...params) -> unique_ptr<Investment> {
    unique_ptr<Investment> pInv(nullptr);
    if (k == 0)
        pInv.reset(new Stock(forward<Ts>(params)...));
    else if (k == 1)
        pInv.reset(new Bond(forward<Ts>(params)...));
    else if (k == 2)
        pInv.reset(new RealEstate(forward<Ts>(params)...));
    return pInv;
}

void demo1() {
    auto pInv1 = makeInvestment(0, 10, 20);
    pInv1->Print();
    auto pInv2 = makeInvestment(1, 10, 20);
    pInv2->Print();
    auto pInv3 = makeInvestment(2, 10, 20);
    pInv3->Print();
}

/* -----demo2: unique_ptr with custom deleter----- */
class Investment1 {
public:
    Investment1(int v1, int v2) : val1(v1), val2(v2) {}

    virtual void Log() { cout << "Delete Investment" << endl; };

    virtual ~Investment1() = default;

private:
    int val1, val2;
};

class Stock1 : public Investment1 {
public:
    Stock1(int v1, int v2) : Investment1(v1, v2) {}

    void Log() override { cout << "Delete Stock" << endl; }

    ~Stock1() = default;
};

class Bond1 : public Investment1 {
public:
    Bond1(int v1, int v2) : Investment1(v1, v2) {}

    void Log() override { cout << "Delete Bond" << endl; }

    ~Bond1() = default;
};

class RealEstate1 : public Investment1 {
public:
    RealEstate1(int v1, int v2) : Investment1(v1, v2) {}

    void Log() override { cout << "Delete RealEstate" << endl; }

    ~RealEstate1() = default;
};

void makeLogEntry(Investment1 *pinvestment) {
    pinvestment->Log();
}

// C++11 form
auto delInvmt = [](Investment1 *pInvestment) {
    makeLogEntry(pInvestment);
    delete pInvestment;
};

template<typename ... Ts>
auto makeInvestment1(int k, Ts &&...params) -> unique_ptr<Investment1, decltype(delInvmt)> {
    unique_ptr<Investment1, decltype(delInvmt)> pInv(nullptr, delInvmt);
    if (k == 0)
        pInv.reset(new Stock1(forward<Ts>(params)...));
    else if (k == 1)
        pInv.reset(new Bond1(forward<Ts>(params)...));
    else if (k == 2)
        pInv.reset(new RealEstate1(forward<Ts>(params)...));
    return pInv;
}

void demo2() {
    auto ptr1 = makeInvestment1(0, 10, 20);
    auto ptr2 = makeInvestment1(1, 10, 20);
    auto ptr3 = makeInvestment1(2, 10, 20);
}

// C++14 form
template<typename ... Ts>
auto makeInvestment2(int k, Ts &&...params) {
    auto delInvmt1 = [](Investment1 *pInvestment) {
        makeLogEntry(pInvestment);
        delete pInvestment;
    };
    unique_ptr<Investment1, decltype(delInvmt1)> pInv(nullptr, delInvmt1);
    if (k == 0)
        pInv.reset(new Stock1(forward<Ts>(params)...));
    else if (k == 1)
        pInv.reset(new Bond1(forward<Ts>(params)...));
    else if (k == 2)
        pInv.reset(new RealEstate1(forward<Ts>(params)...));
    return pInv;
}

void demo3() {
    auto ptr1 = makeInvestment2(0, 10, 20);
    auto ptr2 = makeInvestment2(1, 10, 20);
    auto ptr3 = makeInvestment2(2, 10, 20);
}

/* -----demo3: unique_ptr to shared_ptr----- */
void demo4() {
    shared_ptr<Investment> sp = makeInvestment(0, 10, 20);
    sp->Print();
    cout << "convert success" << endl;
}

void demo5() {
    unique_ptr<string> unique = make_unique<string>("test");
    shared_ptr<string> shared1 = move(unique);
    shared_ptr<string> shared2 = make_unique<string>("test");
    cout << "convert success" << endl;
}

int main() {
/* -----demo1: unique_ptr----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: unique_ptr with custom deleter----- */
    cout << "--------demo2--------" << endl;
    demo2();
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo3: unique_ptr to shared_ptr----- */
    cout << "--------demo4--------" << endl;
    demo4();
    cout << "--------demo5--------" << endl;
    demo5();
}
