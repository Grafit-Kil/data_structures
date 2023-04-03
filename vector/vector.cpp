#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>

template <typename T>
class Vector {
 public:
  Vector();
  Vector(std::size_t capacity);
  Vector(std::size_t capacity, T fill_value);
  Vector(std::size_t capacity, std::size_t first, std::size_t last,
         T fill_value);
  Vector(std::initializer_list<T> list);

  T &operator[](size_t index);
  Vector &operator=(const Vector<T> &other);
  const bool empty() const;
  std::size_t size();
  std::size_t capacity() const;
  void push_back(const T value);
  void insert(const std::size_t index, const T value);
  void erase(const std::size_t index);
  [[nodiscard]] const T &begin() const;
  [[nodiscard]] const T &end() const;
  void swap(T &first, T &last);
  void sort();
  void reverse();
  void resize(std::size_t new_size);
  void clear();

 private:
  void recapacity();

  std::size_t m_capacity;
  std::size_t m_size;
  std::unique_ptr<T[]> data;
};

template <typename T>
Vector<T>::Vector() : m_capacity(0), m_size(0), data(nullptr) {}

template <typename T>
Vector<T>::Vector(std::size_t capacity)
    : m_capacity(capacity), m_size(0), data(new T[capacity]) {}

template <typename T>
Vector<T>::Vector(std::size_t capacity, T fill_value)
    : m_capacity(capacity), m_size(capacity), data(new T[capacity]) {
  for (std::size_t i = 0; i < capacity; i++) {
    data[i] = fill_value;
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : m_capacity(init.size()), m_size(init.size()), data(new T[init.size()]) {
  std::size_t i{0};
  for (auto &item : init) {
    data[i] = item;
    i++;
  }
}

template <typename T>
Vector<T>::Vector(std::size_t capacity, std::size_t first, std::size_t last,
                  T fill_value)
    : m_capacity(capacity), m_size(capacity), data(new T[capacity]) {
  for (std::size_t i = first; (i <= last) && (i <= capacity); i++) {
    data[i] = fill_value;
  }
}

template <typename T>
T &Vector<T>::operator[](size_t index) {
  return data[index];
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
  if (this != &other) {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    data = std::make_unique<T[]>(m_capacity);
    std::copy(other.data.get(), other.data.get() + m_size, data.get());
  }
  return *this;
}

template <typename T>
std::size_t Vector<T>::size() {
  return m_size;
}

template <typename T>
std::size_t Vector<T>::capacity() const {
  return m_capacity;
}

template <typename T>
[[nodiscard]] const T &Vector<T>::begin() const {
  return data[0];
}

template <typename T>
[[nodiscard]] const T &Vector<T>::end() const {
  return data[m_size];
}

template <typename T>
void Vector<T>::resize(std::size_t new_size) {
  T *temp = new T[new_size];
  for (std::size_t i = 0; (i < m_size) && (i < new_size); i++) {
    temp[i] = data[i];
  }
  data.reset(temp);
  m_capacity = new_size;
  if (m_size > new_size) m_size = new_size;
}

template <typename T>
void Vector<T>::recapacity() {
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

template <typename T>
void Vector<T>::push_back(const T value) {
  if (size() == capacity()) {
    recapacity();
  }
  data[size()] = value;
  m_size++;
}

template <typename T>
void Vector<T>::erase(const std::size_t index) {
  if (index > m_size) return;

  for (std::size_t i = index; i < m_size; i++) {
    data[i] = data[i + 1];
  }
  m_size--;
}

template <typename T>
void Vector<T>::insert(const std::size_t index, const T value) {
  if (index > m_size) return;

  if (size() == capacity()) {
    recapacity();
  }
  for (std::size_t i = m_size; i >= 0; i--) {
    if (i == index) {
      data[i] = value;
      break;
    }
    data[i] = data[i - 1];
  }
  m_size++;
}

template <typename T>
const bool Vector<T>::empty() const {
  if (m_size == 0) return true;

  return false;
}

template <typename T>
void Vector<T>::swap(T &first, T &last) {
  auto temp = first;
  first = last;
  last = temp;
}

template <typename T>
void Vector<T>::sort() {
  std::size_t index;
  for (size_t i = 0; i < size() - 1; i++) {
    index = i;
    for (size_t j = i; j < size(); j++) {
      if (data[index] > data[j]) index = j;
    }
    std::swap(data[i], data[index]);
  }
}

template <typename T>
void Vector<T>::reverse() {
  for (std::size_t i = 0; i < (m_size / 2); i++) {
    swap(data[i], data[m_size - i - 1]);
  }
}

template <typename T>
void Vector<T>::clear() {
  m_size = 0;
}

int main() {
  Vector<int> vec;
  assert(vec.capacity() == 0);
  assert(vec.size() == 0);
  assert(vec.empty() == 1);

  Vector<int> vec_cap(50);
  assert(vec_cap.capacity() == 50);
  assert(vec_cap.size() == 0);
  assert(vec_cap.empty() == 1);

  Vector<int> vec_fill(50, 3);
  assert(vec_fill.capacity() == 50);
  assert(vec_fill.size() == 50);
  assert(vec_fill.empty() == 0);
  for (std::size_t i = 0; i < vec_fill.size(); i++) {
    assert(vec_fill[i] == 3);
  }

  Vector<int> vec_range_fill(50, 10, 25, 3);
  assert(vec_range_fill.capacity() == 50);
  assert(vec_range_fill.size() == 50);
  assert(vec_range_fill.empty() == 0);
  for (std::size_t i = 0; i < vec_range_fill.size(); i++) {
    if ((i >= 10) && (i <= 25)) assert(vec_range_fill[i] == 3);
  }

  Vector<Vector<int>> vec_2d{{3, 5, 7, 3}, {3, 6, 4, 4, 4}, {8, 9}};
  assert(vec_2d.capacity() == 3);
  assert(vec_2d[0].capacity() == 4);
  assert(vec_2d[1].capacity() == 5);
  assert(vec_2d[2].capacity() == 2);
  assert(vec_2d.size() == 3);
  assert(vec_2d[0].size() == 4);
  assert(vec_2d[1].size() == 5);
  assert(vec_2d[2].size() == 2);

  Vector<int> vec_pb{1, 3, 7, 5, 9};
  vec_pb.push_back(8);
  assert(vec_pb[5] == 8);

  Vector<int> vec_ins{1, 3, 7, 5, 9};
  assert(vec_ins.capacity() == 5);
  assert(vec_ins.size() == 5);
  vec_ins.insert(2, 8);
  assert(vec_ins[2] == 8);
  assert(vec_ins[5] == 9);
  assert(vec_ins.capacity() == 10);
  assert(vec_ins.size() == 6);

  Vector<std::string> vec_srt{"akif",  "ziya",   "yahya", "orhan",
                              "necip", "mehmet", "halide"};
  vec_srt.sort();

  assert(vec_srt[0] == "akif");
  assert(vec_srt[1] == "halide");
  assert(vec_srt[6] == "ziya");

  Vector<int> vec_rev{1, 3, 7, 5, 9};
  vec_rev.reverse();
  assert(vec_rev[0] == 9);
  assert(vec_rev[1] == 5);
  assert(vec_rev[4] == 1);

  Vector<int> vec_clr{1, 3, 7, 5, 9};
  vec_clr.clear();
  assert(vec_clr.capacity() == 5);
  assert(vec_clr.size() == 0);

  Vector<int> vec_ers{1, 3, 7, 5, 9};
  vec_ers.erase(1);
  assert(vec_ers.capacity() == 5);
  assert(vec_ers.size() == 4);
  assert(vec_ers[1] == 7);

  Vector<int> vec_res{1, 3, 7, 5, 9};
  assert(vec_res.capacity() == 5);
  vec_res.resize(25);
  assert(vec_res.capacity() == 25);
}
