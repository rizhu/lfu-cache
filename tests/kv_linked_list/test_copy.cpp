#include "../../libs/kv_linked_list.hpp"

#include <iostream>

using namespace std;

void test_copy_constructor() {
    using LL = KVLinkedList<int, int>;
    using Node_t = typename LL::Node_t;

    auto ll1 = LL();

    ll1.emplace_back(1, 1);
    ll1.emplace_back(2, 2);
    ll1.emplace_back(3, 3);
    ll1.emplace_back(4, 4);

    LL ll2(ll1);
    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key());
        assert(original->value() == copy->value());
    }

    for (Node_t *node = ll2.front(); node != ll2.end(); node = node->next()) {
        node->set_key(node->key() - 1);
        node->set_value(node->value() + 1);
    }

    ll1.pop_back();
    ll2.emplace_back(4, 6);

    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key() + 1);
        assert(original->value() == copy->value() - 1);
    }

    assert(ll1.size() == 3);
    assert(ll2.size() == 5);
}

void test_copy_assignment_from_smaller() {
    using LL = KVLinkedList<int, int>;
    using Node_t = typename LL::Node_t;

    LL ll1 = LL();
    ll1.emplace_back(1, 1);
    ll1.emplace_back(2, 2);
    ll1.emplace_back(3, 3);
    ll1.emplace_back(4, 4);

    LL ll2;
    ll2.emplace_back(0, 0);
    ll2.emplace_back(1, 1);
    ll2.emplace_back(2, 2);
    int i = 0;
    for (Node_t *node = ll2.front(); node != ll2.end(); node = node->next()) {
        assert(node->key() == i);
        assert(node->value() == i);
        i++;
    }

    ll2 = ll1;
    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key());
        assert(original->value() == copy->value());
    }

    for (Node_t *node = ll2.front(); node != ll2.end(); node = node->next()) {
        node->set_key(node->key() - 1);
        node->set_value(node->value() + 1);
    }

    ll1.pop_back();
    ll2.emplace_back(4, 6);

    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key() + 1);
        assert(original->value() == copy->value() - 1);
    }

    assert(ll1.size() == 3);
    assert(ll2.size() == 5);
}

void test_copy_assignment_from_bigger() {
    using LL = KVLinkedList<int, int>;
    using Node_t = typename LL::Node_t;

    LL ll1 = LL();
    ll1.emplace_back(1, 1);
    ll1.emplace_back(2, 2);
    ll1.emplace_back(3, 3);
    ll1.emplace_back(4, 4);

    LL ll2;
    ll2.emplace_back(0, 0);
    ll2.emplace_back(1, 1);
    ll2.emplace_back(2, 2);
    ll2.emplace_back(3, 3);
    ll2.emplace_back(4, 4);
    ll2.emplace_back(5, 5);
    ll2.emplace_back(6, 6);
    int i = 0;
    for (Node_t *node = ll2.front(); node != ll2.end(); node = node->next()) {
        assert(node->key() == i);
        assert(node->value() == i);
        i++;
    }

    ll2 = ll1;
    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key());
        assert(original->value() == copy->value());
    }

    for (Node_t *node = ll2.front(); node != ll2.end(); node = node->next()) {
        node->set_key(node->key() - 1);
        node->set_value(node->value() + 1);
    }

    ll1.pop_back();
    ll2.emplace_back(4, 6);

    for (Node_t *original = ll1.front(), *copy = ll2.front();
        original != ll1.end() && copy != ll2.end();
        original = original->next(), copy = copy->next())
    {
        assert(original->key() == copy->key() + 1);
        assert(original->value() == copy->value() - 1);
    }

    assert(ll1.size() == 3);
    assert(ll2.size() == 5);
}

int main() {
    test_copy_constructor();
    test_copy_assignment_from_smaller();
    test_copy_assignment_from_bigger();

    cout << "\033[1;4;32mtests/kv_linked_list/test_copy: PASSED\033[0m" << endl;
}