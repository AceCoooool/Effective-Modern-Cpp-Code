#include <iostream>
#include <memory>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: override----- */
class Base {
public:
    virtual void doWork() { cout << "Base doWork" << endl; }
};

class Derived : public Base {
public:
    virtual void doWork() { cout << "Derived doWork" << endl; }
};

void demo1() {
    unique_ptr<Base> ptr = make_unique<Derived>();
    ptr->doWork();
}

/* -----demo2: with override----- */
class Base1 {
public:
    virtual void mf1() const { cout << "Base mf1" << endl; };

    virtual void mf2(int x) { cout << "Base mf2" << endl; };

    virtual void mf3() &{ cout << "Base mf3" << endl; };

    virtual void mf4() const { cout << "Base mf4" << endl; };
};

class Derived1 : public Base1 {
    virtual void mf1() const override { cout << "Derived mf1" << endl; };

    virtual void mf2(int x) override { cout << "Derived mf2" << endl; };

    virtual void mf3() &override { cout << "Derived mf3" << endl; };

    virtual void mf4() const override { cout << "Derived mf4" << endl; };
};

void demo2() {
    unique_ptr<Base1> ptr = make_unique<Derived1>();
    ptr->mf1();
    ptr->mf2(2);
    ptr->mf3();
    ptr->mf4();
}

/* -----demo3: reference qualifier----- */
class Widget {
public:
    using DataType = vector<double>;

    Widget(DataType v) : values(v) {}

    DataType &data() &{
        cout << "data()&" << endl;
        return values;
    }

    DataType data() &&{
        cout << "data() &&" << endl;
        return move(values);
    }

private:
    DataType values;
};

Widget makeWidget(vector<double> v) {
    return Widget(v);
}

void demo3() {
    vector<double> num{10.0, 20.0};
    Widget w(num);
    auto vals = w.data();
    for (auto a: vals)
        cout << a << " ";
    cout << endl;
    auto vals2 = makeWidget(num).data();
    for (auto a: vals2)
        cout << a << " ";
    cout << endl;
}


int main() {
/* -----demo1: without override----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: with override----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: reference qualifier----- */
    cout << "--------demo3--------" << endl;
    demo3();
}
