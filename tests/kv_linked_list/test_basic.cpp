#include "../../libs/kv_linked_list.hpp"

#include <cassert>
#include <iostream>

using namespace std;

int main() {
    auto ll = KVLinkedList<int, int>();
    
    ll.emplace_back(1, 2);
    ll.emplace_front(0, 1);
    ll.emplace_back(2, 3);

    int i = 0;
    for (auto node = ll.front(); node != ll.end(); node = node->next()) {
        assert(node->key() == i++);
        assert(node->value() == i);
    }

    assert(ll.size() == 3);
    ll.pop_back();
    assert(ll.size() == 2);
    ll.pop_front();
    assert(ll.size() == 1);
    ll.pop_back();
    assert(ll.size() == 0);
    assert(ll.front() == ll.end() && ll.front() == ll.back() && ll.back() == ll.end());

    cout << "\033[1;4;32mtests/kv_linked_list/test_basic: PASSED\033[0m" << endl;
}