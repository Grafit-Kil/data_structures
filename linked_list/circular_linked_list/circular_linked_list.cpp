#include <cstddef>
#include <iomanip>
#include <iostream>

template <typename T>
struct Node {
  Node<T> *next;
  Node<T> *prev;
  T data;
  Node(T _data) : data(_data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class CircularLinkedList {
 public:
  CircularLinkedList();
  CircularLinkedList(T init_first_node);
  void display();
  void add(const T _data);
  void add(Node<T> *_node);
  bool remove();
  bool remove(Node<T> *delenda);
  bool remove(const T delenda);
  Node<T> *find(const T _data);
  [[nodiscard]] Node<T> *detach_from_list(Node<T> *_node);
  void move_list_to_list(CircularLinkedList<T> &list);
  void clear();
  bool check_circular();
  std::size_t size();
  ~CircularLinkedList();

 private:
  Node<T> *iter;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : iter(nullptr) {}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(T init_first_node) {
  iter = new Node<T>(init_first_node);
}

template <typename T>
void CircularLinkedList<T>::display() {
  std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
  std::cout << std::setfill(' ');
  std::cout << "| " << std::setw(10) << "Address" << std::setw(7) << "| |";
  std::cout << std::setw(20) << "Data"
            << " |" << std::endl;
  std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
  std::cout << std::setfill(' ');
  if (iter) {
    Node<T> *temp_iter = iter;
    do {
      std::cout << "| " << std::setw(10) << temp_iter << "| |";
      std::cout << std::setw(20) << temp_iter->data << " |" << std::endl;
      temp_iter = temp_iter->next;
    } while (temp_iter != iter);
  }
  std::cout << "+" << std::setfill('-') << std::setw(42) << "+\n\n";
  std::cout << std::setfill(' ');
}

template <typename T>
void CircularLinkedList<T>::add(const T _data) {
  Node<T> *temp = new Node<T>(_data);
  if (iter == nullptr) {
    iter = temp;
    iter->next = iter;
    iter->prev = iter;
  } else if (iter->next == nullptr) {
    iter->next = temp;
    iter->prev = temp;
    temp->next = iter;
    temp->prev = iter;
  } else {
    Node<T> *next_temp = iter->next;
    iter->next = temp;
    temp->prev = iter;
    temp->next = next_temp;
    next_temp->prev = temp;
  }
}

template <typename T>
void CircularLinkedList<T>::add(Node<T> *_node) {
  if (!_node) return;
  if (iter == nullptr) {
    iter = _node;
    iter->next = iter;
    iter->prev = iter;
  } else if (iter->next == nullptr) {
    iter->next = _node;
    iter->prev = _node;
    _node->next = iter;
    _node->prev = iter;
  } else {
    Node<T> *next_temp = iter->next;
    iter->next = _node;
    _node->prev = iter;
    _node->next = next_temp;
    next_temp->prev = _node;
  }
}

template <typename T>
bool CircularLinkedList<T>::remove() {
  if (iter == nullptr) {
    return false;
  } else if (iter == iter->next) {
    delete iter;
    iter = nullptr;
  } else {
    Node<T> *temp = iter->next->next;
    delete iter->next;
    iter->next = temp;
    temp->prev = iter;
  }
  return true;
}

template <typename T>
bool CircularLinkedList<T>::remove(Node<T> *delenda) {
  if (!iter) return false;
  Node<T> *cmp_loop_end = iter->prev;
  do {
    if (iter == delenda) {
      Node<T> *temp = iter->next;
      iter = iter->prev;
      delete iter->next;
      iter->next = temp;
      temp->prev = iter;
      break;
    }

    iter = iter->next;
  } while (iter != cmp_loop_end);
  return true;
}

template <typename T>
bool CircularLinkedList<T>::remove(const T delenda) {
  if (!iter) return false;

  Node<T> *cmp_loop_end = iter->prev;

  do {
    if (iter->data == delenda) {
      Node<T> *temp = iter->next;
      iter = iter->prev;
      delete iter->next;
      iter->next = temp;
      temp->prev = iter;
      break;
    }

    iter = iter->next;
  } while (iter != cmp_loop_end);
  return true;
}

template <typename T>
Node<T> *CircularLinkedList<T>::find(const T _data) {
  if (!iter) return nullptr;

  Node<T> *cmp_loop_end = iter;
  do {
    iter = iter->next;
    if (iter->data == _data) return iter;
  } while (iter != cmp_loop_end);

  return nullptr;
}

template <typename T>
[[nodiscard]] Node<T> *CircularLinkedList<T>::detach_from_list(Node<T> *_node) {
  if (!_node || !iter) return nullptr;

  Node<T> *cmp_loop_end = iter;
  Node<T> *detached = nullptr;
  do {
    if (iter == _node) detached = _node;
    iter = iter->next;
  } while (iter != cmp_loop_end);

  if (!detached) {
  } else if (iter->next == nullptr) {
    detached = _node;
    iter = nullptr;
  } else {
    detached->next->prev = detached->prev;
    detached->prev->next = detached->next;
    iter = iter->next;
  }
  return detached;
}

template <typename T>
void CircularLinkedList<T>::move_list_to_list(CircularLinkedList<T> &list) {
  if (!list.iter) return;

  if (!iter) {
    iter = list.iter;
    list.iter = nullptr;
  } else {
    Node<T> *temp_list_p = list.iter->prev;
    Node<T> *temp_this_p = iter->next;

    iter->next = list.iter;
    list.iter->prev = iter;
    temp_list_p->next = temp_this_p;
    temp_this_p->prev = temp_list_p;
    list.iter = nullptr;
  }
}

template <typename T>
void CircularLinkedList<T>::clear() {
  if (iter == nullptr) {
  } else {
    Node<T> *cmp_loop_end = iter->prev;

    while (cmp_loop_end != iter) {
      iter = iter->next;
      delete iter->prev;
    }
    delete iter;
    iter = nullptr;
  }
}

template <typename T>
std::size_t CircularLinkedList<T>::size() {
  std::size_t count{0};

  if (iter == nullptr) return count;

  Node<T> *cmp_loop_end = iter->prev;

  count++;
  while (cmp_loop_end != iter) {
    count++;
    iter = iter->next;
  }

  return count;
}

template <typename T>
bool CircularLinkedList<T>::check_circular() {
  if (iter == nullptr) return true;

  Node<T> *cmp_loop_end = iter->prev;

  do {
    if (cmp_loop_end == iter) return true;
    iter = iter->next;
  } while (iter != nullptr);
  return false;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (iter != nullptr) {
    Node<T> *cmp_loop_end = iter->prev;

    while (cmp_loop_end != iter) {
      iter = iter->next;
      delete iter->prev;
    }
    delete iter;
  }
}

int main() {
  CircularLinkedList<int> list{};

  list.add(1);
  list.add(2);
  auto x = new Node<int>(3);
  list.add(x);
  list.add(4);
  list.add(5);
  list.display();

  list.remove();
  list.display();
  list.remove(x);
  list.display();

  auto y = list.find(4);
  std::cout << "Node y = " << y->data << "\n";

  auto z = list.detach_from_list(y);

  list.display();

  CircularLinkedList<int> list2{};

  list2.add(10);
  list2.add(20);
  list2.add(30);
  list2.add(40);

  list.move_list_to_list(list2);
  list.display();

  std::cout << "check circular >> " << list.check_circular() << "\n";
  std::cout << "size = " << list.size() << "\n";

  list.clear();
  list.display();

  std::cout << "check circular >> " << list.check_circular() << "\n";
  std::cout << "size = " << list.size() << "\n";
}
