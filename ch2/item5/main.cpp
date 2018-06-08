#include <iostream>
#include <vector>
#include <memory>
#include <boost/type_index.hpp>
#include <unordered_map>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----iterator demo----- */
template<typename It>
void dwim(It b, It e) {
    while (b != e) {
        typename iterator_traits<It>::value_type currValue = *b;  // 写起来太繁琐
        cout << currValue << " ";
        ++b;
    }
    cout << endl;
}

template<typename It>
void dwin_auto(It b, It e) {
    while (b != e) {
        auto currValue = *b;
        cout << currValue << " ";
        ++b;
    }
    cout << endl;
}

void demo1() {
    vector<int> iter{2, 3, 5, 4, 1};
    dwim(iter.begin(), iter.end());
    dwin_auto(iter.begin(), iter.end());
}

/* -----lambda demo----- */
class Widget {
public:
    Widget() {};

    Widget(int i) : val(i) {}

    bool operator<(const Widget &w1) {
        return this->val < w1.val;
    }

private:
    int val;
};

// c++11
auto dereUPLess1 = [](const std::unique_ptr<Widget> &p1, const std::unique_ptr<Widget> &p2) {
    return *p1 < *p2;
};

// c++14
auto dereUPLess2 = [](const auto &p1, const auto &p2) {
    return *p1 < *p2;
};

// bad code --- not efficient and larger memory occupy
std::function<bool(const std::unique_ptr<Widget> &, const std::unique_ptr<Widget> &)>
        dereUPLess3 = [](const std::unique_ptr<Widget> &p1, const std::unique_ptr<Widget> &p2) { return *p1 < *p2; };

void demo2() {
    auto pa = make_unique<Widget>(2), pb = make_unique<Widget>(3);
//    unique_ptr<Widget> pa{new Widget(4)}, pb(new Widget(5));   // another form
    auto res1 = dereUPLess1(pa, pb);
    auto res2 = dereUPLess2(pa, pb);
    auto res3 = dereUPLess3(pa, pb);
    cout << "C++11: " << res1 << endl;
    cout << "C++14: " << res2 << endl;
    cout << "function: " << res3 << endl;
}

void demo3() {
    vector<int> v{1, 2, 3};
    auto sz = v.size();
    cout << type_id_with_cvr<decltype(sz)>().pretty_name() << endl;
    unordered_map<string, int> table{{"first",  1},
                                     {"second", 2}};
    // bad way
    for (const pair<string, int> &p: table) {
        cout << p.first << " : " << p.second << endl;
    }
    // good way
    for (const auto &p: table) {
        cout << p.first << " : " << p.second << " " << type_id_with_cvr<decltype(p)>().pretty_name() << endl;
    }
}

int main() {
/* -----iterator demo----- */
    cout << "------demo1------" << endl;
    demo1();
/* -----lambda demo----- */
    cout << "------demo2------" << endl;
    demo2();
/* -----explicit declaration----- */
    cout << "------demo3------" << endl;
    demo3();
}
