/**
 * @file Stack.h
 * @brief Definition of the Stack class template using LinkedList<T> as internal structure.
 *
 * This Stack implementation leverages a custom LinkedList<T> and provides
 * essential stack operations with various important applications in computer science:
 *
 * 1. Function Call Management:
 *    - Stores return addresses and local variables in program execution.
 *    - Crucial for implementing recursion in programming languages.
 *
 * 2. Expression Parsing and Evaluation:
 *    - Used in converting infix expressions to postfix notation (RPN).
 *    - Facilitates evaluation of postfix expressions.
 *
 * 3. Graph Algorithms:
 *    - Implements Depth-First Search (DFS) traversal.
 *    - Aids in cycle detection within graphs.
 *
 * 4. Undo Functionality:
 *    - Maintains history of operations in applications like text editors.
 *
 * 5. Parsing and Compilation:
 *    - Assists in syntax analysis during the compilation process.
 *    - Validates matching of parentheses and tags in various languages.
 *
 * 6. Algorithm Implementation:
 *    - Used in certain sorting algorithms, such as QuickSort.
 *
 * 7. Browser History:
 *    - Implements the "Back" button functionality in web browsers.
 */

#ifndef STACK_H
#define STACK_H

#include "linked_list.h"
#include <stdexcept>

template <typename T>
class Stack {
private:
    DoublyLinkedList<T> list;

public:
    /**
     * @brief Constructs an empty stack.
     */
    Stack() = default;

    /**
     * @brief Pushes an item onto the top of the stack.
     * @param item The item to be pushed onto the stack.
     */
    void push(const T& item) {
        list.push_front(item);
    }

    /**
     * @brief Removes the item at the top of the stack.
     * @throw std::runtime_error if the stack is empty.
     */
    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        list.pop_front();
    }

    /**
     * @brief Returns a reference to the top item of the stack.
     * @return Reference to the top item.
     * @throw std::runtime_error if the stack is empty.
     */
    T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return list.front();
    }

    /**
     * @brief Returns a const reference to the top item of the stack.
     * @return Const reference to the top item.
     * @throw std::runtime_error if the stack is empty.
     */
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return list.front();
    }

    /**
     * @brief Checks if the stack is empty.
     * @return true if the stack is empty, false otherwise.
     */
    bool empty() const {
        return list.empty();
    }

    /**
     * @brief Returns the number of items in the stack.
     * @return The stack's size.
     */
    size_t size() const {
        return list.size();
    }
};

#endif // STACK_H