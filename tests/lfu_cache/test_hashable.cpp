#include "../../libs/lfu_cache.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
    static_assert(Hashable<int>);
    static_assert(Hashable<double>);
    static_assert(Hashable<bool>);
    static_assert(Hashable<string>);
    cout << "\033[1;4;32mtests/lfu_cache/test_hashable: PASSED\033[0m" << endl;
}
