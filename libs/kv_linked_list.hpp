#include <iostream>
#include <memory>

using namespace std;

template <typename K, typename V>
class KVNode {
public:
    using Node_t = KVNode<K, V>;

    KVNode() { }
    KVNode(K key, V value) : _key(key), _value(value) { }

    K key() const { return this->_key; }
    void set_key(K key) { this->_key = key; }

    V value() const { return this->_value; }
    void set_value(V value) { this->_value = value; }

    size_t freq() const { return this->_freq; }
    void use() { this->_freq++; }

    Node_t* prev() const { return this->_prev; }
    void set_prev(Node_t* prev) { this->_prev = prev; }

    Node_t* next() const { return this->_next; }
    void set_next(Node_t* next) { this->_next = next; }

private:
    K _key;
    V _value;

    Node_t* _prev = nullptr;
    Node_t* _next = nullptr;
    size_t _freq = 1;
};

template <typename K, typename V>
class KVLinkedList {
public:
    using Node = KVNode<K, V>;
    using Node_t = typename Node::Node_t;

    KVLinkedList() {
        this->_sentinel = new Node_t();
        this->_sentinel->set_next(this->_sentinel);
        this->_sentinel->set_prev(this->_sentinel);
    }
    ~KVLinkedList() {
        Node_t *node = this->front(), *next_node = nullptr;
        while (node != this->end()) {
            next_node = node->next();
            node->set_prev(nullptr);
            node->set_next(nullptr);
            delete node;
            node = next_node;
        }
        this->_sentinel->set_next(nullptr);
        this->_sentinel->set_prev(nullptr);
        delete this->_sentinel;
    }

    KVLinkedList(const KVLinkedList<K, V>& other) {
        this->_sentinel = new Node_t();
        Node_t *prev = this->_sentinel, *node = this->_sentinel;

        for (Node_t *other_node = other.front();
            other_node != other.end();
            other_node = other_node->next())
        {
            node = new Node_t(other_node->key(), other_node->value());
            node->set_prev(prev);
            prev->set_next(node);
            prev = node;
        }

        node->set_next(this->_sentinel);
        this->_sentinel->set_prev(node);
        this->_length = other.size();
    }
    KVLinkedList<K, V> operator=(const KVLinkedList<K, V>& other) {
        Node_t *node = this->front(), *prev = this->_sentinel;
        for (Node_t *other_node = other.front();
            node != this->end() && other_node != other.end();
            other_node = other_node->next())
        {
            if (node != nullptr) {
                node->set_key(other_node->key());
                node->set_value(other_node->value());
            } else {
                node = new Node(other_node->key(), other_node->value());
                node->set_prev(prev);
                prev->set_next(node);
            }
            prev = node;
            node = node->next();
        }
        prev->set_next(this->end());
        this->_sentinel->set_prev(prev);
        while (node != nullptr && node != this->end()) {
            Node_t *next_node = node->next();
            delete node;
            node = next_node;
        }
        this->_length = other.size();
        return *this;
    }

    Node_t* front() const {
        return this->_sentinel->next();
    }

    Node_t* back() const {
        return this->_sentinel->prev();
    }

    Node_t* end() const {
        return this->_sentinel;
    }

    size_t size() const {return this->_length; }

    void push_front(Node_t* node) {
        auto front = this->_sentinel->next();

        front->set_prev(node);
        node->set_next(front);

        node->set_prev(this->_sentinel);
        this->_sentinel->set_next(node);

        _length++;
    }

    void emplace_front(K key, V value) {
        push_front(new Node_t(key, value));
    }

    void pop_front() {
        auto to_delete = this->_sentinel->next();
        auto new_front = this->_sentinel->next()->next();
        this->_sentinel->set_next(new_front);
        new_front->set_prev(this->_sentinel);

        _length--;
    }

    void push_back(Node_t* node) {
        auto back = this->_sentinel->prev();

        back->set_next(node);
        node->set_prev(back);

        node->set_next(this->_sentinel);
        this->_sentinel->set_prev(node);

        _length++;
    }

    void emplace_back(K key, V value) {
        push_back(new Node_t(key, value));
    }

    void pop_back() {
        auto to_delete = this->_sentinel->prev();
        auto new_back = this->_sentinel->prev()->prev();
        this->_sentinel->set_prev(new_back);
        new_back->set_next(this->_sentinel);

        _length--;
    }

private:
    Node_t* _sentinel;
    
    size_t _length = 0;
};
