#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack() : std::vector<T>() {} // Default constructor

    ~Stack() {} // Destructor

    bool empty() const {
        return std::vector<T>::empty(); // Use vector's empty() method
    }

    size_t size() const {
        return std::vector<T>::size(); // Use vector's size() method
    }

    void push(const T& item) {
        std::vector<T>::push_back(item); // Use vector's push_back() method
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack underflow"); // Throw exception if stack is empty
        }
        std::vector<T>::pop_back(); // Use vector's pop_back() method
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack underflow"); // Throw exception if stack is empty
        }
        return std::vector<T>::back(); // Use vector's back() method
    }
    // Add other members only if necessary
};


#endif