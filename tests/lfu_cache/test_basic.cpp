#include "../../libs/lfu_cache.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    /* Create cache of size 3 */
    auto cache = LFUCache<string, int>(3);
    assert(cache.size() == 0);

    /* 
        Add { "one" : 1 } 
        Cache: {
            { "one" : 1, freq = 1 },
        }
    */
    cache.put("one", 1);
    assert(cache.get("one") == 1);
    assert(cache.size() == 1);

    /* 
        + Add { "two" : 2 } 
        Cache: {
            { "one" : 1, freq = 1 },
            { "two" : 2, freq = 1 } 
        }
    */
    cache.put("two", 2);
    assert(cache.get("two") == 2);
    assert(cache.size() == 2);

    /* 
        + Add { "three" : 3 } 
        Cache: {
            { "one" : 1, freq = 1 },
            { "two" : 2, freq = 1 } ,
            { "three" : 3, freq = 1 }
        }
    */
    cache.put("three", 3);
    assert(cache.get("three") == 3);
    assert(cache.size() == 3);

    /* 
        + Add { "four" : 4 }
        - Evict { "one" : 1 } by LRU tiebreak policy
        Cache: {
            { "two" : 2, freq = 1 } ,
            { "three" : 3, freq = 1 },
            { "four" : 4, freq = 1 }
        }
    */
    cache.put("four", 4);
    assert(cache.get("four") == 4);
    assert(cache.size() == 3);
    /*
        { "one" : 1 } should have been evicted
    */
    bool except_thrown = false;
    try {
        cache.get("one");
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);

    /* 
        * Add { "two" : 2 } 2 times
        Cache: {
            { "three" : 3, freq = 1 },
            { "four" : 4, freq = 1 },
            { "two" : 2, freq = 3 } 
        }
    */
    cache.get("two");
    cache.get("two");

    /* 
        + Add { "five" : 5 }
        - Evict { "three" : 3 } by LFU policy
        Cache: {
            { "four" : 4, freq = 1 },
            { "five" : 5, freq = 1 },
            { "two" : 2, freq = 3 } 
        }
    */
    cache.put("five", 5);
    assert(cache.get("four") == 4);
    assert(cache.get("five") == 5);
    assert(cache.get("two") == 2);
    assert(cache.size() == 3);
    /*
        { "three" : 3 } should have been evicted
    */
    except_thrown = false;
    try {
        cache.get("three");
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);
    /*
        { "one" : 1 } should be long gone
    */
    except_thrown = false;
    try {
        cache.get("one");
    } catch (const out_of_range& e) {
        except_thrown = true;
    }
    assert(except_thrown);


    cout << "\033[1;4;32mtests/lfu_cache/test_basic: PASSED\033[0m" << endl;
}
