#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: weak_ptr expired----- */
class Widget {
public:
    Widget() = default;

    Widget(int i) : id(i) {};

    ~Widget() = default;

private:
    int id;
};

void demo1() {
    auto spw = make_shared<Widget>();
    cout << "count(before weak): " << spw.use_count() << endl;
    weak_ptr<Widget> wpw(spw);
    cout << "count(after weak): " << spw.use_count() << endl;
    spw = nullptr;
    cout << "count(after delete): " << spw.use_count() << endl;
    if (wpw.expired())
        cout << "weak pointer is expired" << endl;
}

/* -----demo2: weak_ptr to shared_ptr----- */
void demo2() {
    auto spw = make_shared<Widget>();
    weak_ptr<Widget> wpw(spw);
    auto sp1 = wpw.lock();
    if (sp1)
        cout << "create sp1" << endl;
    cout << "count(create sp1): " << spw.use_count() << endl;
    auto sp2(spw);
    if (sp2)
        cout << "create sp2" << endl;
    cout << "count(create sp2): " << spw.use_count() << endl;
    spw = sp1 = sp2 = nullptr;
    auto sp3 = wpw.lock();
    if (sp3 == nullptr)
        cout << "delete success, now sp3 is null" << endl;
    cout << "count(delete all): " << spw.use_count() << endl;
}

using WidgetID = int;

shared_ptr<const Widget> loadWidget(WidgetID id) {
    cout << "load widget: " << id << endl;
    return make_shared<const Widget>(id);
}

shared_ptr<const Widget> fastLoadWidget(WidgetID id) {
    static unordered_map<WidgetID, weak_ptr<const Widget>> cache;
    auto objPtr = cache[id].lock();
    if (!objPtr) {
        objPtr = loadWidget(id);
        cache[id] = objPtr;
    }
    return objPtr;
}

void demo3() {
    vector<int> ids{1, 2, 4, 2, 1};
    vector<shared_ptr<const Widget>> tmp;
    for (auto id: ids) {
        tmp.push_back(fastLoadWidget(id));
        cout << "count: " << tmp.back().use_count() << endl;
    }
}

int main() {
/* -----demo1: weak_ptr expired----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: weak_ptr to shared_ptr----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: shared_from_this----- */
    cout << "--------demo3--------" << endl;
    demo3();
}

