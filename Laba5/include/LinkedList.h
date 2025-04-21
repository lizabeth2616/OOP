#include "Allocator.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        Node(const T &value) : data(value) {}
    public:
        T data;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
    };
    using Allocator = std::pmr::polymorphic_allocator<Node>;
public:
    class Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
    public:
        explicit Iterator(std::shared_ptr<Node> node) : data(node) {}
        reference operator*() const { return data->data; }
        pointer operator->() { return &(data->data); }
        Iterator& operator++() {
            data = data->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        Iterator &operator--() {
            data = data->prev;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }
        std::shared_ptr<Node> Data() const { return data; }
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.data != b.data;
        }
        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.data == b.data;
        }
    private:
        std::shared_ptr<Node> data;
    };
    class ConstIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
    public:
        explicit ConstIterator(std::shared_ptr<Node> node) : data(node) {}
        const reference operator*() const { return data->data; }
        const pointer operator->() { return &(data->data); }
        ConstIterator& operator++() {
            data = data->next;
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        ConstIterator& operator--() {
            data = data->prev;
            return *this;
        }
        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }
        const std::shared_ptr<Node>& Data() const { return data; }
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) {
            return a.data != b.data;
        }
        friend bool operator==(const ConstIterator& a, const ConstIterator& b) {
            return a.data == b.data;
        }
    private:
        std::shared_ptr<Node> data;
    };
public:
    LinkedList(const Allocator &alloc = Allocator{}) : allocator(alloc) {}
    void push_back(const T &value) {
        auto node = std::allocate_shared<Node>(allocator, value);
        if (!tail) {
            head = tail = node;
        } 
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    void push_front(const T &value) {
        auto node = std::allocate_shared<Node>(allocator, value);
        if (!head) {
            head = tail = node;
        } 
        else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }
    void pop_back() {
        if (empty()) {
            throw std::runtime_error("pop_back() called on empty list");
        }
        if (tail == head) {
            head.reset();
            tail.reset();
        } 
        else {
            tail = tail->prev.lock();
            tail->next.reset();
        }
    }
    void pop_front() {
        if (empty()) {
            throw std::runtime_error("pop_front() called on empty list");
        }
        if (tail == head) {
            head.reset();
            tail.reset();
        } else
        {
            head = head->next;
            head->prev.reset();
        }
    }
    T& at(size_t index) {
        auto it = begin();
        size_t count = 0;
        for (; it != end(); ++it, ++count) {
            if (count == index) {
                return *it;
            }
        }
        throw std::out_of_range("List out of range");
    }
    void insert(size_t index, const T &value) {
        if (index == 0) {
            push_front(value);
            return;
        }

        auto it = begin();
        size_t count = 0;
        for (; it != end(); ++it, ++count) {
            if (count == index - 1) {
                auto data = it.Data();
                auto node = std::allocate_shared<Node>(allocator, value);
                node->next = data->next;
                node->prev = data;

                if (data->next) {
                    data->next->prev = node;
                } else {
                    tail = node;
                }
                data->next = node;
                return;
            }
        }

        if (count == index) {
            push_back(value);
            return;
        }

        throw std::out_of_range("Index out of range");
    }

    void erase(size_t index) {
        if (index == 0) {
            pop_front();
            return;
        }

        auto it = begin();
        size_t count = 0;
        for (; it != end(); ++it, ++count) {
            if (count == index) {
                auto data = it.Data(); 
                auto prev_node = data->prev.lock();
                auto next_node = data->next;

                prev_node->next = next_node;
                if (next_node) {
                    next_node->prev = prev_node;
                } else {
                    tail = prev_node;
                }
                return;
            }
        }

        throw std::out_of_range("Index out of range");
    }
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }
    bool empty() const { return !head; }
    size_t size() const {
        size_t count = 0;
        for (auto it = head; it; it = it->next)
            count++;
        return count;
    }
private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    Allocator allocator;
};