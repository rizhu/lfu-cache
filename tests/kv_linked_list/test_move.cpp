#include "../../libs/kv_linked_list.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test_move_constructor() {
    using LL = KVLinkedList<string, vector<int>>;
    using Node_t = typename LL::Node_t;

    auto ll1 = LL();

    ll1.emplace_back("one", {0, 1});
    ll1.emplace_back("two", {0, 1, 2});
    ll1.emplace_back("three", {0, 1, 2, 3});
    ll1.emplace_back("four", {0, 1, 2, 3, 4});

    auto ll2(move(ll1));
    assert(ll2.size() == 4);

    auto node = ll2.front();
    vector<int> v;
    v = {0, 1};
    assert(node->key() == "one");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2};
    assert(node->key() == "two");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2, 3};
    assert(node->key() == "three");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2, 3, 4};
    assert(node->key() == "four");
    assert(node->value() == v);
    node = node->next();
    assert(node == ll2.end());

    assert(ll1.size() == 0);
}

void test_move_assignment() {
    using LL = KVLinkedList<string, vector<int>>;
    using Node_t = typename LL::Node_t;

    auto ll1 = LL();

    ll1.emplace_back("one", {0, 1});
    ll1.emplace_back("two", {0, 1, 2});
    ll1.emplace_back("three", {0, 1, 2, 3});
    ll1.emplace_back("four", {0, 1, 2, 3, 4});

    auto ll2 = LL();
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});
    ll2.emplace_front("", {{}});

    ll2 = move(ll1);
    assert(ll2.size() == 4);

    auto node = ll2.front();
    vector<int> v;
    v = {0, 1};
    assert(node->key() == "one");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2};
    assert(node->key() == "two");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2, 3};
    assert(node->key() == "three");
    assert(node->value() == v);
    node = node->next();
    v = {0, 1, 2, 3, 4};
    assert(node->key() == "four");
    assert(node->value() == v);
    node = node->next();
    assert(node == ll2.end());

    assert(ll1.size() == 0);
}

int main() {
    test_move_constructor();
    test_move_assignment();

    cout << "\033[1;4;32mtests/kv_linked_list/test_move: PASSED\033[0m" << endl;
}