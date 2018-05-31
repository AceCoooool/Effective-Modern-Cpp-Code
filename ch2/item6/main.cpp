#include <iostream>
#include <valarray>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----vector<bool>::reference----- */
void demo1() {
    vector<bool> features{true, false, true, false, true, true};
    bool priority1 = features[2];
    auto priority2 = features[2];
    cout << "priorty1's type: " << type_id_with_cvr<decltype(priority1)>().pretty_name()
         << " , value: " << priority1 << endl;
    cout << "priorty2's type: " << type_id_with_cvr<decltype(priority2)>().pretty_name()
         << " , value: " << priority2 << endl;
}

/* -----matrix demo----- */
void demo2() {
    std::valarray<int> m1{2, 3, 4, 5}, m2{3, 4, 5, 6}, m3{5, 4, 1, 2};
    auto res = m1 + m2 + m3;
    auto res2 = static_cast<valarray<int>>(m1 + m2 + m3);
    // Note: this is error
//    for(auto t:res)
//        cout<<t<<" ";
    for (auto t:res2)
        cout << t << " ";
    cout << endl;
    cout << type_id_with_cvr<decltype(res)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(res2)>().pretty_name() << endl;
}

int main() {
/* -----vector<bool>::reference----- */
//    demo1();
/* -----matrix demo----- */
    demo2();
}
