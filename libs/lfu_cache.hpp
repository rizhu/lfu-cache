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
    using LL = KVLinkedList<K, V>;
    using Node_t = typename LL::Node_t;

    explicit LFUCache(size_t capacity) : _capacity(capacity) { }
    ~LFUCache() {
        this->_freq_map.clear();
        this->_key_value_map.clear();
    }

    LFUCache(const LFUCache<K, V>& other) {
        this->_freq_map = other._freq_map;
        for (const auto& [k, ll] : this->_freq_map) {
            for (auto node = ll.front(); node != ll.end(); node = node->next()) {
                this->_key_value_map[node->key()] = node;
            }
        }

        this->_capacity = other.capacity();
        this->_contains = other.size();
        this->_min_freq = other._min_freq;
    }
    LFUCache<K, V>& operator=(const LFUCache<K, V>& other) {
        this->_key_value_map.clear();
        this->_freq_map.clear();

        this->_freq_map = other._freq_map;
        for (const auto& [k, ll] : this->_freq_map) {
            for (auto node = ll.front(); node != ll.end(); node = node->next()) {
                this->_key_value_map[node->key()] = node;
            }
        }

        this->_capacity = other.capacity();
        this->_contains = other.size();
        this->_min_freq = other._min_freq;

        return *this;
    }

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

    size_t capacity() const noexcept { return this->_capacity; }
    size_t size() const noexcept { return this->_contains; }

private:
    void _use(K key) {
        Node_t* node = this->_key_value_map[key];

        Node_t* behind = node->prev();
        Node_t* ahead = node->next();

        behind->set_next(ahead);
        ahead->set_prev(behind);

        node->use();
        if (node->freq() - 1 == this->_min_freq && behind->next() == behind) {
            this->_freq_map.erase(this->_min_freq);
            this->_min_freq++;
        }
        this->_freq_map[node->freq()].push_front(node);
    }

    unordered_map<K, Node_t*> _key_value_map;
    unordered_map<size_t, LL> _freq_map;

    size_t _capacity;

    size_t _contains = 0;
    size_t _min_freq = 0;
};
