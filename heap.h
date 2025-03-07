#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int m_ary;
  PComparator comp;
  void trickleUp(size_t idx);
  void trickleDown(size_t idx);
  size_t parent(size_t idx) const;
  size_t firstChild(size_t idx) const;



};

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");


  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  data[0] = data.back();
  data.pop_back();
  
  if (!empty()) {
    trickleDown(0);
  }


}

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
  : m_ary(m), comp(c)
{
  // Ensure m is at least 2
  if (m < 2) {
    m_ary = 2;
  }
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
  // Vector will automatically deallocate memory
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::parent(size_t idx) const
{
  return (idx - 1) / m_ary;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::firstChild(size_t idx) const
{
  return m_ary * idx + 1;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(size_t idx)
{
  // Calculate parent index
  size_t parentIdx = parent(idx);
  
  // Base case: reached the root or parent has higher priority
  if (idx == 0 || !comp(data[idx], data[parentIdx])) {
    return;
  }
  
  // Swap with parent and continue trickle up
  std::swap(data[idx], data[parentIdx]);
  trickleUp(parentIdx);
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(size_t idx)
{
  size_t firstChildIdx = firstChild(idx);
    if (firstChildIdx >= data.size()) {
        return; // No children
    }
    
    size_t highestPriorityChildIdx = firstChildIdx;
    size_t lastPossibleChildIdx = std::min(firstChildIdx + m_ary - 1, data.size() - 1);
    
    for (size_t i = firstChildIdx + 1; i <= lastPossibleChildIdx; ++i) {
        if (comp(data[i], data[highestPriorityChildIdx])) {
            highestPriorityChildIdx = i;
        }
    }
    
    if (comp(data[highestPriorityChildIdx], data[idx])) {
        std::swap(data[idx], data[highestPriorityChildIdx]);
        trickleDown(highestPriorityChildIdx);
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  // Add item to the end
  data.push_back(item);
  
  // Trickle up to maintain heap property
  trickleUp(data.size() - 1);
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return data.size();
}

#endif

