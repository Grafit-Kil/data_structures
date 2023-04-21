#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

template <typename T, std::size_t N>
class Array {
 private:
  std::unique_ptr<T[]> data;

 public:
  Array();
  Array(const Array &obj);
  Array(std::initializer_list<T> init);
  Array &operator=(const Array &obj);
  bool operator==(const Array &rhs);
  bool operator!=(const Array &rhs);

  [[nodiscard]] T &operator[](size_t index);
  [[nodiscard]] const T &operator[](size_t index) const;

  std::size_t size() const;
  [[nodiscard]] T &begin() const;
  [[nodiscard]] T &end() const;
  const bool empty() const;
  void fill(T fill_value);
  void fill(T &first, T &last, T fiil_value);
  void swap(T &first, T &last);
  void sort();
  T *search(T value) const;
};

template <typename T, std::size_t N>
Array<T, N>::Array() : data(new T[N + 1]) {}

template <typename T, std::size_t N>
Array<T, N>::Array(const Array &obj) : data(new T[N]) {
  for (std::size_t i = 0; i < N; i++) {
    this->data[i] = obj.data[i];
  }
}

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<T> init_list) : data(new T[N]) {
  size_t i = 0;
  for (auto &item : init_list) {
    data[i] = item;
    i++;
    if (i == N) break;
  }
}

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &obj) {
  if(this == &obj) {return *this;}
  std::copy(obj.data.get(), obj.data.get() + N, this->data.get());
  return *this;
}

template <typename T, std::size_t N>
[[nodiscard]] T &Array<T, N>::operator[](size_t index) {
  return data[index];
}

template <typename T, std::size_t N>
[[nodiscard]] const T &Array<T, N>::operator[](size_t index) const {
  return data[index];
}

template <typename T, std::size_t N>
bool Array<T, N>::operator!=(const Array &rhs) {
  if (this->size() != rhs.size()) return true;

  for (std::size_t i = 0; i != this->size(); i++) {
    if (this->data[i] != rhs.data[i]) return true;
  }
  return false;
}

template <typename T, std::size_t N>
bool Array<T, N>::operator==(const Array &rhs) {
  if (this->size() != rhs.size()) return false;

  for (std::size_t i = 0; i != this->size(); i++) {
    if (this->data[i] != rhs.data[i]) return false;
  }
  return true;
}

template <typename T, std::size_t N>
std::size_t Array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
[[nodiscard]] T &Array<T, N>::begin() const {
  return data[0];
}

template <typename T, std::size_t N>
[[nodiscard]] T &Array<T, N>::end() const {
  return data[N];
}

template <typename T, std::size_t N>
const bool Array<T, N>::empty() const {
  if (N == 0) return true;

  return false;
}

template <typename T, std::size_t N>
void Array<T, N>::fill(T fill_value) {
  for (std::size_t i = 0; i != size(); i++) {
    data[i] = fill_value;
  }
}

template <typename T, std::size_t N>
void Array<T, N>::fill(T &first, T &last, T fill_value) {
  for (auto *i = &first; i != (&last + 1); i++) {
    *i = fill_value;
  }
}

template <typename T, std::size_t N>
void Array<T, N>::swap(T &first, T &last) {
  auto temp = first;
  first = last;
  last = temp;
}

template <typename T, std::size_t N>
void Array<T, N>::sort() {
  std::size_t index;
  for (size_t i = 0; i < size() - 1; i++) {
    index = i;
    for (size_t j = i; j < size(); j++) {
      if (data[index] < data[j]) index = j;
    }
    std::swap(data[i], data[index]);
  }
}

template <typename T, std::size_t N>
T *Array<T, N>::search(T value) const {
  if (N == 0) return nullptr;

  for (size_t i = 0; i < N; i++) {
    if (data[i] == value) return &data[i];
  }

  return nullptr;
}

int main() {
  Array<double, 5> test_array0;
  assert(test_array0.size() == 5);

  Array<int, 7> test_array1{1, 3, 2, 6, 4, 7, 0};
  assert(test_array1.size() == 7);
  assert(test_array1[0] == 1);
  assert(test_array1[3] == 6);
  assert(test_array1[6] == 0);

  Array<Array<int, 3>, 3> test_array2{{1, 3, 2}, {6, 4, 7}, {9, 5, 8}};
  assert(test_array2.size() == 3);
  assert(test_array2[0][0] == 1);
  assert(test_array2[0][2] == 2);
  assert(test_array2[1][1] == 4);
  assert(test_array2[2][0] == 9);
  assert(test_array2[2][2] == 8);

  Array<int, 7> test_array3{1, 3, 2, 6, 4, 7, 0};
  Array<int, 7> test_array4{1, 3, 2, 6, 4, 7, 0};
  Array<int, 7> test_array5{1, 3, 2, 6, 4, 5, 0};
  assert(test_array3 == test_array4);
  assert(test_array3 != test_array5);

  Array<int, 7> test_array6{7, 3, 2, 6, 1, 7, 9};
  assert(test_array6.begin() == 7);
  assert(*(&test_array6.end() - 1) == 9);

  Array<int, 7> test_array7{1, 3, 2, 6, 1, 7, 16};
  test_array7.fill(9);
  for (auto i = 0; i < test_array7.size(); i++) {
    assert(test_array7[i] == 9);
  }

  test_array7.fill(test_array7[2], test_array7[5], 3);
  assert(test_array7[1] == 9);
  assert(test_array7[2] == 3);
  assert(test_array7[4] == 3);
  assert(test_array7[5] == 3);
  assert(test_array7[6] == 9);

  Array<int, 7> test_array8{7, 3, 2, 6, 1, 7, 9};
  assert(*test_array8.search(3) == test_array8[1]);

  Array<int, 7> test_array9{7, 3, 2, 6, 1, 7, 9};
  assert(test_array9.empty() == false);
  Array<int, 0> test_array10;
  assert(test_array10.empty() == true);

  Array<int, 7> test_array11{7, 3, 2, 6, 1, 7, 9};
  test_array11.sort();
  for (auto i = 0; i < test_array11.size() - 1; i++) {
    assert(test_array11[i] >= test_array11[i + 1]);
  }
}
