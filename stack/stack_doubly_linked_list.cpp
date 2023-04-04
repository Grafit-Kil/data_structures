#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>

template <typename T>
struct Node {
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node(T _data) : data(_data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class Stack {
 public:
  Stack();
  void push(const T value);
  const std::optional<T> pop();
  const std::optional<T> top() const;
  std::size_t size() const;
  bool empty() const;
  ~Stack();

 private:
  Node<T> *head;
  std::size_t m_size;
};

template <typename T>
Stack<T>::Stack() : head(nullptr), m_size(0) {}

template <typename T>
void Stack<T>::push(const T value) {
  Node<T> *temp = new Node<T>(value);
  if (head == nullptr) {
    head = temp;
  } else {
    temp->next = head;
    head->prev = temp;
    head = temp;
  }
  m_size++;
}

template <typename T>
const std::optional<T> Stack<T>::pop() {
  T temp_data;
  if (head == nullptr) {
    return std::nullopt;
  } else if (head->next == nullptr) {
    temp_data = head->data;
    delete head;
    head = nullptr;
    m_size--;
  } else {
    temp_data = head->data;
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    m_size--;
  }
  return temp_data;
}

template <typename T>
const std::optional<T> Stack<T>::top() const {
  if (head == nullptr) return std::nullopt;
  return head->data;
}
template <typename T>
std::size_t Stack<T>::size() const {
  return m_size;
}
template <typename T>
bool Stack<T>::empty() const {
  return m_size == 0;
}

template <typename T>
Stack<T>::~Stack() {
  Node<T> *temp = nullptr;
  while (head != nullptr) {
    temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {
  Stack<int> st;
  assert(st.size() == 0);
  assert(st.empty());

  st.push(3);
  st.push(7);
  st.push(5);

  assert(st.size() == 3);
  assert(!st.empty());
  assert(st.top().value() == 5);

  st.pop();
  assert(st.size() == 2);
  assert(!st.empty());
  assert(st.top().value() == 7);

  st.pop();
  st.pop();
  assert(st.size() == 0);
  assert(st.empty());
  assert(!st.top().has_value());
}
