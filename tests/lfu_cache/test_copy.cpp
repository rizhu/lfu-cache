#include "../../libs/lfu_cache.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void test_lfu_cache_copy_constructor() {
    auto cache1 = LFUCache<int, int>(3);
    cache1.put(0, 0);
    cache1.put(1, 1);
    cache1.put(2, 2);

    auto cache2 = cache1;
    assert(cache2.size() == 3);
    assert(cache2.capacity() == 3);
    cache2.get(0);

    cache1.put(3, 3);
    cache2.put(3, 3);

    assert(cache1.get(1) == 1);
    assert(cache1.get(2) == 2);
    assert(cache1.get(3) == 3);
    bool except_thrown = false;
    try {
        cache1.get(0);
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);

    assert(cache2.get(2) == 2);
    assert(cache2.get(3) == 3);
    assert(cache2.get(0) == 0);
    except_thrown = false;
    try {
        cache2.get(1);
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);
}

void test_lfu_cache_copy_assignment() {
    auto cache1 = LFUCache<int, int>(3);
    cache1.put(0, 0);
    cache1.put(1, 1);
    cache1.put(2, 2);

    auto cache2 = LFUCache<int, int>(8);
    for (int i = 0; i < 8; i++) {
        cache2.put(i, i);
    }
    cache2 = cache1;
    assert(cache2.size() == 3);
    assert(cache2.capacity() == 3);
    cache2.get(0);

    cache1.put(3, 3);
    cache2.put(3, 3);

    assert(cache1.get(1) == 1);
    assert(cache1.get(2) == 2);
    assert(cache1.get(3) == 3);
    bool except_thrown = false;
    try {
        cache1.get(0);
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);

    assert(cache2.get(2) == 2);
    assert(cache2.get(3) == 3);
    assert(cache2.get(0) == 0);
    except_thrown = false;
    try {
        cache2.get(1);
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);
}

int main() {
    test_lfu_cache_copy_constructor();
    test_lfu_cache_copy_assignment();

    cout << "\033[1;4;32mtests/lfu_cache/test_copy: PASSED\033[0m" << endl;
}