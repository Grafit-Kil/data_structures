#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

template <typename T> class Stack {
public:
  Stack();
  Stack(std::size_t capacity);
  void push(const T value);
  T pop();
  bool empty();
  std::size_t size() const;
  const T &top() const;

private:
  void recapacity();

  std::size_t m_capacity;
  std::size_t m_size;
  std::unique_ptr<T[]> data;
};

template <typename T>
Stack<T>::Stack() : m_capacity(0), m_size(0), data(nullptr) {}

template <typename T>
Stack<T>::Stack(std::size_t capacity)
    : m_capacity(capacity), m_size(0), data(new T[capacity]) {}

template <typename T> void Stack<T>::recapacity() {
  T *temp = nullptr;
  if (m_capacity != 0) {
    temp = new T[m_capacity * 2];
    m_capacity *= 2;
  } else {
    temp = new T[1];
    m_capacity = 1;
  }
  for (std::size_t i = 0; i < m_size; i++) {
    temp[i] = data[i];
  }
  data.reset(temp);
}

template <typename T> void Stack<T>::push(const T value) {
  if (m_size == m_capacity) {
    recapacity();
  }
  data[m_size] = value;
  m_size++;
}

template <typename T> T Stack<T>::pop() {
  T temp;
  if (m_size != 0) {
    temp = data[m_size - 1];
    m_size--;
    return temp;
  }
  return static_cast<T>(0);
}

template <typename T> bool Stack<T>::empty() {
  if (m_size)
    return false;

  return true;
}

template <typename T> std::size_t Stack<T>::size() const { return m_size; }
template <typename T> const T &Stack<T>::top() const {
  return data[m_size - 1];
}
int main() {
  Stack<char> st;
  assert(st.empty() == 1);
  assert(st.size() == 0);
  st.push('t');
  st.push('u');
  assert(st.empty() == 0);
  assert(st.size() == 2);
  st.push('r');
  st.push('k');
  assert(st.top() == 'k');
  st.pop();
  assert(st.top() == 'r');
  assert(st.empty() == 0);
  assert(st.size() == 3);
  st.pop();
  st.pop();
  st.pop();
  assert(st.empty() == 1);
  assert(st.size() == 0);
}
