#include <memory>

using namespace std;

template <typename K, typename V>
class KVNode {
public:
    using Node_t = KVNode<K, V>;
    using Node_ptr = shared_ptr<Node_t>;

    KVNode() { }
    KVNode(K key, V value) : _key(key), _value(value) { }

    K key() { return this->_key; }
    void set_key(K key) { this->_key = key; }

    V value() { return this->_value; }
    void set_value(V value) { this->_value = value; }

    size_t freq() { return this->_freq; }
    void use() { this->_freq++; }

    Node_ptr prev() { return this->_prev; }
    void set_prev(Node_ptr prev) { this->_prev = prev; }

    Node_ptr next() { return this->_next; }
    void set_next(Node_ptr next) { this->_next = next; }

private:
    K _key;
    V _value;
    Node_ptr _prev;
    Node_ptr _next;

    size_t _freq = 1;
};

template <typename K, typename V>
class KVLinkedList {
public:
    using Node_t = typename KVNode<K, V>::Node_t;
    using Node_ptr = typename KVNode<K, V>::Node_ptr;

    KVLinkedList() {
        this->_sentinel = make_shared<Node_t>();
        this->_sentinel->set_next(this->_sentinel);
        this->_sentinel->set_prev(this->_sentinel);
    }

    Node_ptr front() {
        return this->_sentinel->next();
    }

    Node_ptr back() {
        return this->_sentinel->prev();
    }

    Node_ptr end() {
        return this->_sentinel;
    }

    size_t size() {return this->_length; }

    void push_front(Node_ptr node) {
        auto front = this->_sentinel->next();

        front->set_prev(node);
        node->set_next(front);

        node->set_prev(this->_sentinel);
        this->_sentinel->set_next(node);

        _length++;
    }

    void emplace_front(K key, V value) {
        push_front(make_shared<Node_t>(key, value));
    }

    void pop_front() {
        auto to_delete = this->_sentinel->next();
        auto new_front = this->_sentinel->next()->next();
        this->_sentinel->set_next(new_front);
        new_front->set_prev(this->_sentinel);

        _length--;
    }

    void push_back(Node_ptr node) {
        auto back = this->_sentinel->prev();

        back->set_next(node);
        node->set_prev(back);

        node->set_next(this->_sentinel);
        this->_sentinel->set_prev(node);

        _length++;
    }

    void emplace_back(K key, V value) {
        push_back(make_shared<Node_t>(key, value));
    }

    void pop_back() {
        auto to_delete = this->_sentinel->prev();
        auto new_back = this->_sentinel->prev()->prev();
        this->_sentinel->set_prev(new_back);
        new_back->set_next(this->_sentinel);

        _length--;
    }
private:
    Node_ptr _sentinel;
    size_t _length = 0;
};
