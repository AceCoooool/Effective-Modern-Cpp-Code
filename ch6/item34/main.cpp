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

/* -----demo1: lambda form vs bind form (1)----- */
using Time = chrono::steady_clock::time_point;
enum class Sound {
    Beep, Siren, Whistle
};

using Duration = chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {
    auto time = chrono::system_clock::to_time_t(chrono::system_clock::now()
                                                + (t - chrono::steady_clock::now()));
    cout << put_time(localtime(&time), "%F %T") << endl;
    cout << "sound: " << static_cast<int>(s) << endl;
    cout << "duration: " << d.count() << endl;
}

void demo1() {
    auto setsoundL = [](Sound s) { setAlarm(chrono::steady_clock::now() + chrono::hours(1), s, chrono::seconds(30)); };
    setsoundL(Sound::Beep);
}

using AlarmType = void (*)(Time t, Sound s, Duration d);
using namespace placeholders;

void demo2() {
    auto setsoundB = bind(static_cast<AlarmType >(setAlarm), bind(plus<>(), chrono::steady_clock::now(), 1h), _1, 30s);
    setsoundB(Sound::Beep);
}

/* -----demo2: lambda form vs bind form (2)----- */
void demo3() {
    auto lowVal = 5, highVal = 10;
    auto betweenL = [lowVal, highVal](const auto &val) { return lowVal <= val && val <= highVal; };
    cout << "between(5,10) (lambda form): " << betweenL(9) << endl;
    auto betweenB = bind(logical_and<bool>(), bind(less_equal<int>(), lowVal, _1),
                         bind(less_equal<int>(), _1, highVal));
    cout << "between(5,10) (bind form): " << betweenB(9) << endl;
}

int main() {
/* -----demo1: lambda form vs bind form (1)----- */
    cout << "--------demo1--------" << endl;
    demo1();
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo2: lambda form vs bind form (2)----- */
    cout << "--------demo3--------" << endl;
    demo3();
}

