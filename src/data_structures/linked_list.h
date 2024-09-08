#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>

/**
 * @class DoublyLinkedList
 * @brief A template class for a doubly linked list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T>
class DoublyLinkedList {
private:
    /**
     * @struct Node
     * @brief A structure representing a node in the doubly linked list.
     */
    struct Node {
        T data;      ///< The data stored in the node
        Node* next;  ///< Pointer to the next node in the list
        Node* prev;  ///< Pointer to the previous node in the list

        /**
         * @brief Constructs a new Node.
         * @param value The value to be stored in the node.
         * @param nextNode Pointer to the next node (default is nullptr).
         * @param prevNode Pointer to the previous node (default is nullptr).
         */
        explicit Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
                : data(value), next(nextNode), prev(prevNode) {}
    };

    Node* head;  ///< Pointer to the first node in the list
    Node* tail;  ///< Pointer to the last node in the list
    size_t size_; ///< Number of elements in the list

public:
    /**
     * @class Iterator
     * @brief An iterator class for DoublyLinkedList.
     */
    class Iterator {
    private:
        Node* current;  ///< Pointer to the current node
        friend class DoublyLinkedList;  ///< DoublyLinkedList can access private members

    public:
        /// Iterator traits
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Constructs an Iterator.
         * @param node Pointer to the current node.
         */
        explicit Iterator(Node* node) : current(node) {}

        /**
         * @brief Dereference operator.
         * @return Reference to the data in the current node.
         * @throw std::runtime_error if dereferencing a null iterator.
         */
        reference operator*() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return current->data;
        }

        /**
         * @brief Arrow operator.
         * @return Pointer to the data in the current node.
         * @throw std::runtime_error if dereferencing a null iterator.
         */
        pointer operator->() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return &(current->data);
        }

        /**
         * @brief Pre-increment operator.
         * @return Reference to the incremented iterator.
         */
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * @return Iterator before increment.
         */
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Pre-decrement operator.
         * @return Reference to the decremented iterator.
         */
        Iterator& operator--() {
            if (current) current = current->prev;
            return *this;
        }

        /**
         * @brief Post-decrement operator.
         * @return Iterator before decrement.
         */
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Equality comparison operator.
         * @param other Another iterator to compare with.
         * @return true if iterators point to the same node, false otherwise.
         */
        bool operator==(const Iterator& other) const { return current == other.current; }

        /**
         * @brief Inequality comparison operator.
         * @param other Another iterator to compare with.
         * @return true if iterators point to different nodes, false otherwise.
         */
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    /**
     * @class ConstIterator
     * @brief A constant iterator class for DoublyLinkedList.
     */
    class ConstIterator {
    private:
        const Node* current;  ///< Pointer to the current node
        friend class DoublyLinkedList;  ///< DoublyLinkedList can access private members

    public:
        /// Iterator traits
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * @brief Constructs a ConstIterator.
         * @param node Pointer to the current node.
         */
        explicit ConstIterator(const Node* node) : current(node) {}

        /**
         * @brief Dereference operator.
         * @return Const reference to the data in the current node.
         * @throw std::runtime_error if dereferencing a null iterator.
         */
        reference operator*() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return current->data;
        }

        /**
         * @brief Arrow operator.
         * @return Const pointer to the data in the current node.
         * @throw std::runtime_error if dereferencing a null iterator.
         */
        pointer operator->() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return &(current->data);
        }

        /**
         * @brief Pre-increment operator.
         * @return Reference to the incremented iterator.
         */
        ConstIterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * @return ConstIterator before increment.
         */
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Pre-decrement operator.
         * @return Reference to the decremented iterator.
         */
        ConstIterator& operator--() {
            if (current) current = current->prev;
            return *this;
        }

        /**
         * @brief Post-decrement operator.
         * @return ConstIterator before decrement.
         */
        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Equality comparison operator.
         * @param other Another const iterator to compare with.
         * @return true if iterators point to the same node, false otherwise.
         */
        bool operator==(const ConstIterator& other) const { return current == other.current; }

        /**
         * @brief Inequality comparison operator.
         * @param other Another const iterator to compare with.
         * @return true if iterators point to different nodes, false otherwise.
         */
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }
    };

    /**
     * @brief Default constructor. Initializes an empty list.
     */
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    /**
     * @brief Copy constructor.
     * @param other The DoublyLinkedList to be copied.
     */
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size_(0) {
        for (const auto& item : other) {
            push_back(item);
        }
    }

    /**
     * @brief Copy assignment operator.
     * @param other The DoublyLinkedList to be assigned.
     * @return Reference to this DoublyLinkedList.
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            DoublyLinkedList tmp(other);
            std::swap(head, tmp.head);
            std::swap(tail, tmp.tail);
            std::swap(size_, tmp.size_);
        }
        return *this;
    }

    /**
     * @brief Move constructor.
     * @param other The DoublyLinkedList to be moved.
     */
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
            : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    /**
     * @brief Move assignment operator.
     * @param other The DoublyLinkedList to be move-assigned.
     * @return Reference to this DoublyLinkedList.
     */
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = other.tail = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Destructor. Clears the list.
     */
    ~DoublyLinkedList() {
        clear();
    }

    /**
     * @brief Returns a reference to the first element in the list.
     * @return Reference to the first element.
     * @throw std::runtime_error if the list is empty.
     */
    T& front() {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    /**
     * @brief Returns a const reference to the first element in the list.
     * @return Const reference to the first element.
     * @throw std::runtime_error if the list is empty.
     */
    const T& front() const {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    /**
     * @brief Returns a reference to the last element in the list.
     * @return Reference to the last element.
     * @throw std::runtime_error if the list is empty.
     */
    T& back() {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

    /**
     * @brief Returns a const reference to the last element in the list.
     * @return Const reference to the last element.
     * @throw std::runtime_error if the list is empty.
     */
    const T& back() const {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

    /**
     * @brief Checks if the list is empty.
     * @return true if the list is empty, false otherwise.
     */
    [[nodiscard]] bool empty() const { return size_ == 0; }

    /**
     * @brief Returns the number of elements in the list.
     * @return The number of elements.
     */
    [[nodiscard]] size_t size() const { return size_; }

    /**
     * @brief Clears the contents of the list.
     */
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    /**
     * @brief Inserts an element at the beginning of the list.
     * @param value The value to be inserted.
     */
    void push_front(const T& value) {
        Node* new_node = new Node(value, head);
        if (empty()) {
            tail = new_node;
        } else {
            head->prev = new_node;
        }
        head = new_node;
        ++size_;
    }

    /**
     * @brief Inserts an element at the end of the list.
     * @param value The value to be inserted.
     */
    void push_back(const T& value) {
        Node* new_node = new Node(value, nullptr, tail);
        if (empty()) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
        ++size_;
    }

    /**
     * @brief Removes the first element of the list.
     * @throw std::runtime_error if the list is empty.
     */
    void pop_front() {
        if (empty()) throw std::runtime_error("Pop from empty list");
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --size_;
    }

    /**
     * @brief Removes the last element of the list.
     * @throw std::runtime_error if the list is empty.
     */
    void pop_back() {
        if (empty()) throw std::runtime_error("Pop from empty list");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --size_;
    }

    /**
     * @brief Inserts an element at the specified position.
     * @param pos Iterator to the position before which the element will be inserted.
     * @param value The value to be inserted.
     * @return Iterator pointing to the newly inserted element.
     */
    Iterator insert(Iterator pos, const T& value) {
        if (pos == begin()) {
            push_front(value);
            return begin();
        } else if (pos == end()) {
            push_back(value);
            return Iterator(tail);
        } else {
            Node* new_node = new Node(value, pos.current, pos.current->prev);
            pos.current->prev->next = new_node;
            pos.current->prev = new_node;
            ++size_;
            return Iterator(new_node);
        }
    }

    /**
     * @brief Removes the element at the specified position.
     * @param pos Iterator to the element to be removed.
     * @return Iterator pointing to the element following the erased element.
     * @throw std::runtime_error if trying to erase end iterator.
     */
    Iterator erase(Iterator pos) {
        if (pos == end()) throw std::runtime_error("Cannot erase end iterator");
        if (pos == begin()) {
            pop_front();
            return begin();
        }
        Node* to_delete = pos.current;
        to_delete->prev->next = to_delete->next;
        if (to_delete->next) {
            to_delete->next->prev = to_delete->prev;
        } else {
            tail = to_delete->prev;
        }
        Iterator next(to_delete->next);
        delete to_delete;
        --size_;
        return next;
    }

    /**
     * @brief Returns an iterator to the beginning of the list.
     * @return Iterator to the first element.
     */
    Iterator begin() { return Iterator(head); }

    /**
     * @brief Returns an iterator to the end of the list.
     * @return Iterator to the element following the last element.
     */
    Iterator end() { return Iterator(nullptr); }

    /**
     * @brief Returns a const iterator to the beginning of the list.
     * @return Const iterator to the first element.
     */
    ConstIterator begin() const { return ConstIterator(head); }

    /**
     * @brief Returns a const iterator to the end of the list.
     * @return Const iterator to the element following the last element.
     */
    ConstIterator end() const { return ConstIterator(nullptr); }

    /**
     * @brief Returns a const iterator to the beginning of the list.
     * @return Const iterator to the first element.
     */
    ConstIterator cbegin() const { return ConstIterator(head); }

    /**
     * @brief Returns a const iterator to the end of the list.
     * @return Const iterator to the element following the last element.
     */
    ConstIterator cend() const { return ConstIterator(nullptr); }

    /**
     * @brief Compares two DoublyLinkedList objects for equality.
     * @param other The DoublyLinkedList to compare with.
     * @return true if the lists are equal, false otherwise.
     */
    bool operator==(const DoublyLinkedList& other) const {
        if (size_ != other.size_) return false;
        auto it1 = begin();
        auto it2 = other.begin();
        while (it1 != end()) {
            if (*it1 != *it2) return false;
            ++it1;
            ++it2;
        }
        return true;
    }

    /**
     * @brief Compares two DoublyLinkedList objects for inequality.
     * @param other The DoublyLinkedList to compare with.
     * @return true if the lists are not equal, false otherwise.
     */
    bool operator!=(const DoublyLinkedList& other) const {
        return !(*this == other);
    }

    /**
     * @brief Prints the contents of the list to the standard output.
     */
    void print() const {
        for (const auto& item : *this) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

#endif // DOUBLY_LINKED_LIST_H