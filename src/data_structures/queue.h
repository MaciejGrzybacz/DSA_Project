/**
 * @file Queue.h
 * @brief Definition of the Queue class template using LinkedList<T> as internal structure.
 *
 * This Queue implementation leverages a custom LinkedList<T> and provides
 * essential queue operations with various important applications in computer science:
 *
 * 1. Task Scheduling:
 *    - Used in operating systems for process scheduling.
 *    - Manages print job spooling in printer systems.
 *
 * 2. Breadth-First Search (BFS):
 *    - Fundamental in graph traversal algorithms.
 *    - Used in shortest path finding in unweighted graphs.
 *
 * 3. Buffering:
 *    - Manages data buffers in various applications, including multimedia streaming.
 *    - Handles asynchronous data transfer between processes.
 *
 * 4. Cache Implementation:
 *    - Used in implementing LRU (Least Recently Used) caches.
 *
 * 5. Event Handling:
 *    - Manages event queues in user interfaces and simulations.
 *
 * 6. Message Passing:
 *    - Facilitates communication between threads or processes in concurrent systems.
 *
 * 7. Algorithms:
 *    - Used in various algorithms like tree level-order traversal.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"
#include <stdexcept>

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list;

public:
    /**
     * @brief Constructs an empty queue.
     */
    Queue() = default;

    /**
     * @brief Adds an item to the back of the queue.
     * @param item The item to be added to the queue.
     */
    void enqueue(const T& item) {
        list.push_back(item);
    }

    /**
     * @brief Removes the item at the front of the queue.
     * @throw std::runtime_error if the queue is empty.
     */
    void dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        list.pop_front();
    }

    /**
     * @brief Returns a reference to the front item of the queue.
     * @return Reference to the front item.
     * @throw std::runtime_error if the queue is empty.
     */
    T& front() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return list.front();
    }

    /**
     * @brief Returns a const reference to the front item of the queue.
     * @return Const reference to the front item.
     * @throw std::runtime_error if the queue is empty.
     */
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return list.front();
    }

    /**
     * @brief Checks if the queue is empty.
     * @return true if the queue is empty, false otherwise.
     */
    bool empty() const {
        return list.empty();
    }

    /**
     * @brief Returns the number of items in the queue.
     * @return The queue's size.
     */
    size_t size() const {
        return list.size();
    }
};

#endif // QUEUE_H