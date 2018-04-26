#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----iterator demo----- */
template<typename It>
void dwim(It b, It e) {
    while (b != e) {
        typename iterator_traits<It>::value_type currValue = *b;
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
auto dereUPLess = [](const std::unique_ptr<int> &p1, const std::unique_ptr<int> &p2) {
    return *p1 < *p2;
};

auto dereUPLess2 = [](const auto &p1, const auto &p2) {
    return *p1 < *p2;
};

std::function<bool(const std::unique_ptr<int> &, const std::unique_ptr<int> &)>
        dereUPLess3 = [](const std::unique_ptr<int> &p1, const std::unique_ptr<int> &p2) { return *p1 < *p2; };

void demo2() {
    auto a = 10, b = 20;
    unique_ptr<decltype(a)> pa(&a), pb(&b);
    auto res1 = dereUPLess(pa, pb);
    auto res2 = dereUPLess2(pa, pb);
    auto res3 = dereUPLess3(pa, pb);
    cout << "C++11: " << res1 << endl;
    cout << "C++14: " << res2 << endl;
    cout << "function: " << res3 << endl;
}

int main() {
/* -----iterator demo----- */
//    demo1();
/* -----lambda demo----- */
    demo2();
}
