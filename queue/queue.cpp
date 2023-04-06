#include <cassert>
#include <cstddef>
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
class Queue {
 public:
  Queue();
  void push(const T value);
  void pop();
  const std::optional<T> front() const;
  const std::optional<T> back() const;
  std::size_t size() const;
  bool empty() const;
  ~Queue();

 private:
  Node<T> *head;
  Node<T> *tail;
  std::size_t m_size;
};

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), m_size(0) {}

template <typename T>
void Queue<T>::push(const T value) {
  Node<T> *temp = new Node<T>(value);
  if (!head) {
    head = temp;
    tail = head;
  } else if (head == tail) {
    head->next = temp;
    tail = head->next;
    tail->prev = head;
  } else {
    tail->next = temp;
    temp->prev = tail;
    tail = tail->next;
  }
  m_size++;
}

template <typename T>
void Queue<T>::pop() {
  if (head == nullptr)
    return;
  else if (head->next == nullptr) {
    delete head;
    head = nullptr;
  } else {
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
  }
  m_size--;
}

template <typename T>
const std::optional<T> Queue<T>::front() const {
  if (head == nullptr) return std::nullopt;
  return head->data;
}
template <typename T>
const std::optional<T> Queue<T>::back() const {
  if (head == nullptr) return std::nullopt;
  return tail->data;
}

template <typename T>
std::size_t Queue<T>::size() const {
  return m_size;
}
template <typename T>
bool Queue<T>::empty() const {
  return m_size == 0;
}

template <typename T>
Queue<T>::~Queue() {
  Node<T> *temp = nullptr;
  while (head != nullptr) {
    temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {
  Queue<int> st;
  //->
  assert(st.empty() == true);
  assert(st.size() == 0);
  
  st.push(5);
  //-> 5
  assert(st.empty() == false);
  assert(st.size() == 1);
  assert(st.front().value() == 5);
  assert(st.back().value() == 5);
  
  st.push(9);
  st.push(7);
  //-> 7 - 9 - 5
  assert(st.empty() == false);
  assert(st.size() == 3);
  assert(st.front().value() == 5);
  assert(st.back().value() == 7);
  
  st.pop();
  //-> 7 - 9
  assert(st.empty() == false);
  assert(st.size() == 2);
  assert(st.front().has_value() == true);
  assert(st.back().has_value() == true);
  assert(st.front().value() == 9);
  assert(st.back().value() == 7);
  
  st.pop();
  st.pop();
  //->
  assert(st.empty() == true);
  assert(st.size() == 0);
  assert(st.front().has_value() == false);
  assert(st.back().has_value() == false);
}
