#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <boost/type_index.hpp>


using namespace std;
using boost::typeindex::type_id_with_cvr;

/*------------demo1: callable object--------------*/
void func() {
    cout << "call void func()" << endl;
}

struct Foo {
    void operator()() {
        cout << "call Foo object" << endl;
    }
};

struct Bar {
    using fr_t = void (*)();

    static void func() {
        cout << "call Bar object" << endl;
    }

    operator fr_t() {
        return func;
    }
};

struct A {
    int a_;

    void mem_func() {
        cout << "call A::mem_func" << endl;
    }
};

void demo1() {
    void (*func_ptr)() = &func;   // 1.函数指针
    func_ptr();
    Foo foo;        // 2.仿函数
    foo();
    Bar bar;        // 3.可被转换为函数指针的类对象
    bar();
    void (A::*mem_func_ptr)() = &A::mem_func;  // 4.类成员函数指针
    int A::*mem_obj_ptr = &A::a_;
    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;
};

/*------------demo2: function--------------*/
void func1() {
    cout << __FUNCTION__ << endl;
}

class Foo1 {
public:
    static int foo_func(int a) {
        cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

class Bar1 {
public:
    int operator()(int a) {
        cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

void demo2() {
    // 绑定一个普通函数
    function<void(void)> fr1 = func1;
    fr1();
    // 绑定一个类的静态成员函数
    function<int(int)> fr2 = Foo1::foo_func;
    cout << fr2(123) << endl;
    // 绑定一个仿函数
    Bar1 bar;
    fr2 = bar;
    cout << fr2(123) << endl;
}

/*------------demo3: function as callback--------------*/
class A2 {
    function<void()> callback_;
public:
    A2(const function<void()> &f) : callback_(f) {
    }

    void notify() {
        callback_();
    }
};

class Foo2 {
public:
    void operator()() {
        cout << __FUNCTION__ << endl;
    }
};

void demo3() {
    Foo2 foo;
    A2 aa(foo);
    aa.notify();
}

/*------------demo4: function as param--------------*/
void call_when_even4(int x, const function<void(int)> &f) {
    if (!(x & 1))
        f(x);
}

void output4(int x) {
    cout << x << " ";
}

void demo4() {
    for (auto i = 0; i < 10; ++i)
        call_when_even4(i, output4);
    cout << endl;
}

/*------------demo5: bind basic--------------*/
void call_when_even5(int x, const function<void(int)> &f) {
    if (!(x & 1))
        f(x);
}

void output5(int x) {
    cout << x << " ";
}

void output_add_2(int x) {
    cout << x + 2 << " ";
}

void demo5() {
    auto fr = bind(output5, placeholders::_1);
    for (auto i = 0; i < 10; ++i)
        call_when_even5(i, fr);
    cout << endl;
    auto fr2 = bind(output_add_2, placeholders::_1);
    for (auto i = 0; i < 10; ++i)
        call_when_even5(i, fr2);
    cout << endl;
}

/*------------demo6: bind placeholders--------------*/
void output6(int x, int y) {
    cout << x << " " << y << endl;
}

void demo6() {
    bind(output6, 1, 2)();
    bind(output6, placeholders::_1, 2)(1);
    bind(output6, 2, placeholders::_1)(1);
    // Note error
//    bind(output6, 2, placeholders::_2)(1);
    bind(output6, 2, placeholders::_2)(1, 2);  //placeholder::_1"被吃了"
    bind(output6, placeholders::_1, placeholders::_2)(1, 2);
    bind(output6, placeholders::_2, placeholders::_1)(1, 2);
}

/*------------demo7: bind+function--------------*/
class A7 {
public:
    int i_ = 0;

    void output(int x, int y) {
        cout << x << " " << y << endl;
    }
};

void demo7() {
    A7 a;
    function<void(int, int)> fr = bind(&A7::output, &a, placeholders::_1, placeholders::_2);
    fr(1, 2);

    function<int &()> fr_i = bind(&A7::i_, &a);
    fr_i() = 123;
    cout << "i_: " << a.i_ << endl;
}

/*------------demo8: bind+bind--------------*/
void demo8() {
    auto f = bind(logical_and<bool>(), bind(greater<int>(), placeholders::_1, 5),
                  bind(less_equal<int>(), placeholders::_1, 10));
    vector<int> v{-1, 4, 20, 10, 6, 9};
    auto cnt = count_if(v.begin(), v.end(), f);
    cout << "count: " << cnt << endl;
}


int main() {
/*------------demo1: callable object--------------*/
    cout << "------demo1------" << endl;
    demo1();
/*------------demo2: function--------------*/
    cout << "------demo2------" << endl;
    demo2();
/*------------demo3: function as callback--------------*/
    cout << "------demo3------" << endl;
    demo3();
/*------------demo4: function as param--------------*/
    cout << "------demo4------" << endl;
    demo4();
/*------------demo5: bind basic--------------*/
    cout << "------demo5------" << endl;
    demo5();
/*------------demo6: bind placeholders--------------*/
    cout << "------demo6------" << endl;
    demo6();
/*------------demo7: bind+function--------------*/
    cout << "------demo7------" << endl;
    demo7();
/*------------demo8: bind+bind--------------*/
    cout << "------demo8------" << endl;
    demo8();
}
