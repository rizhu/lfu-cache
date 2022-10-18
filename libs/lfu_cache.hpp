#include "kv_linked_list.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

template <typename T>
concept Hashable =
    requires (T t) {
        { hash<T>{}(t) } -> convertible_to<size_t>;
};

template <Hashable K, typename V>
class LFUCache {
public:
    using Node_ptr = typename KVLinkedList<K, V>::Node_ptr;
    using LL = KVLinkedList<K, V>;

    LFUCache(size_t capacity) : _capacity(capacity) { }

    V get(K key) {
        if (this->_key_value_map.count(key) == 0) {
            throw out_of_range("Key not found.");
        }
        this->_use(key);
        return this->_key_value_map[key]->value();
    }

    void put(K key, V value) {
        if (this->_key_value_map.count(key) > 0) {
            this->_use(key);
            _key_value_map[key]->set_value(value);
            return;
        }
        
        if (this->_contains == this->_capacity) {
            K evict_key = _freq_map[_min_freq].back()->key();
            _freq_map[_min_freq].pop_back();
            _key_value_map.erase(evict_key);
            this->_contains--;
        }

        this->_freq_map[1].emplace_front(key, value);
        this->_key_value_map[key] = this->_freq_map[1].front();

        this->_min_freq = 1;
        this->_contains++;
    }

    size_t size() {
        return this->_contains;
    }

private:
    void _use(K key) {
        Node_ptr node_ptr = this->_key_value_map[key];

        Node_ptr behind = node_ptr->prev();
        Node_ptr ahead = node_ptr->next();

        behind->set_next(ahead);
        ahead->set_prev(behind);

        node_ptr->use();
        if (node_ptr->freq() - 1 == this->_min_freq && behind->next() == behind) {
            this->_min_freq++;
        }
        this->_freq_map[node_ptr->freq()].push_front(node_ptr);
    }

    unordered_map<K, Node_ptr> _key_value_map;
    unordered_map<int, LL> _freq_map;

    size_t _capacity;
    
    size_t _contains = 0;
    size_t _min_freq = 0;
};