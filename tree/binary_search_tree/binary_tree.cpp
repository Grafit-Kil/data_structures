#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <vector>

template <typename T>
struct Node {
  T data;
  Node<T> *left;
  Node<T> *right;

  Node(T _data) : data(_data), left(nullptr), right(nullptr){};
};

template <typename T>
class BST {
 public:
  BST();
  void insert(const T value);
  const std::optional<T> min() const;
  const std::optional<T> max() const;
  const bool search(const T value) const;
  const std::size_t depth() const;
  const std::size_t size() const;
  const std::vector<T> inorder() const;
  const std::vector<T> preorder() const;
  const std::vector<T> postorder() const;

  void remove(const T delenda);
  void print() const;
  ~BST();

 private:
  Node<T> *root;
  std::size_t m_size;

  void print_recursive(Node<T> *base_iter) const;
};

template <typename T>
BST<T>::BST() : root(nullptr), m_size(0) {}

template <typename T>
void BST<T>::insert(const T value) {
  Node<T> *new_node = new Node<T>(value);
  if (root == nullptr) {
    root = new_node;
    m_size++;
    return;
  }
  Node<T> *iter = root;
  int depth = 1;
  while (true) {
    if (value < iter->data) {
      if (iter->left == nullptr) {
        iter->left = new_node;
        m_size++;
        break;
      }
      iter = iter->left;
    } else if (value > iter->data) {
      if (iter->right == nullptr) {
        iter->right = new_node;
        m_size++;
        break;
      }
      iter = iter->right;
    } else {
      delete new_node;
      break;
    }
  }
}

template <typename T>
const std::size_t BST<T>::depth() const {
  std::function<std::size_t(Node<T> *)> depth_counter = [&](Node<T> *iter) {
    if (iter == nullptr) {
      return static_cast<std::size_t>(0);
    }

    std::size_t left_depth = depth_counter(iter->left);
    std::size_t right_depth = depth_counter(iter->right);

    return std::max(left_depth, right_depth) + 1;
  };

  return depth_counter(root);
}

template <typename T>
const std::size_t BST<T>::size() const {
  return m_size;
}

template <typename T>
const std::optional<T> BST<T>::min() const {
  Node<T> *iter = root;
  while (iter) {
    if (iter->left == nullptr) return iter->data;
    iter = iter->left;
  }

  return std::nullopt;
}

template <typename T>
const std::optional<T> BST<T>::max() const {
  Node<T> *iter = root;
  while (iter) {
    if (iter->right == nullptr) return iter->data;
    iter = iter->right;
  }

  return std::nullopt;
}

template <typename T>
const bool BST<T>::search(const T value) const {
  Node<T> *iter = root;
  while (iter != nullptr) {
    if (iter->data == value) {
      return true;
    } else if (value < iter->data) {
      iter = iter->left;
    } else if (value > iter->data) {
      iter = iter->right;
    } else {
      break;
    }
  }
  return false;
}

template <typename T>
void BST<T>::remove(const T delenda) {
  Node<T> *parent = nullptr;
  Node<T> *iter = root;
  while (iter != nullptr && iter->data != delenda) {
    parent = iter;
    if (delenda < iter->data) {
      iter = iter->left;
    } else {
      iter = iter->right;
    }
  }

  if (iter == nullptr) {
    return;
  }

  if (iter->left == nullptr && iter->right == nullptr) {
    if (iter == root) {
      root = nullptr;
    } else if (parent->left == iter) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
    delete iter;
    m_size--;
  } else if (iter->left == nullptr || iter->right == nullptr) {
    Node<T> *child = iter->left ? iter->left : iter->right;
    if (iter == root) {
      root = child;
    } else if (parent->left == iter) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    delete iter;
    m_size--;
  } else {
    Node<T> *successor_parent = iter;
    Node<T> *successor = iter->right;
    while (successor->left != nullptr) {
      successor_parent = successor;
      successor = successor->left;
    }
    iter->data = successor->data;
    if (successor_parent == iter) {
      successor_parent->right = successor->right;
    } else {
      successor_parent->left = successor->right;
    }
    delete successor;
    m_size--;
  }
}

template <typename T>
void BST<T>::print() const {
  if (root == nullptr) return;

  Node<T> *iter = root;
  print_recursive(iter);
}

template <typename T>
void BST<T>::print_recursive(Node<T> *base_iter) const {
  if (base_iter == nullptr) {
    return;
  }

  print_recursive(base_iter->left);
  std::cout << base_iter->data << " - ";
  print_recursive(base_iter->right);
}

template <typename T>
const std::vector<T> BST<T>::inorder() const {
  std::vector<T> order_vec{};
  if (root == nullptr) {
    return order_vec;
  }
  std::function<void(Node<T> *)> inorder_helper = [&](Node<T> *iter) {
    if (iter == nullptr) {
      return;
    }
    inorder_helper(iter->left);
    order_vec.push_back(iter->data);
    inorder_helper(iter->right);
  };
  inorder_helper(root->left);
  order_vec.push_back(root->data);
  inorder_helper(root->right);

  return order_vec;
}

template <typename T>
const std::vector<T> BST<T>::preorder() const {
  std::vector<T> order_vec{};

  std::function<void(Node<T> *)> inorder_helper = [&](Node<T> *iter) {
    if (iter == nullptr) {
      return;
    }
    order_vec.push_back(iter->data);
    inorder_helper(iter->left);
    inorder_helper(iter->right);
  };
  inorder_helper(root);

  return order_vec;
}

template <typename T>
const std::vector<T> BST<T>::postorder() const {
  std::vector<T> order_vec{};

  std::function<void(Node<T> *)> inorder_helper = [&](Node<T> *iter) {
    if (iter == nullptr) {
      return;
    }
    inorder_helper(iter->left);
    inorder_helper(iter->right);
    order_vec.push_back(iter->data);
  };
  inorder_helper(root);

  return order_vec;
}

template <typename T>
BST<T>::~BST() {
  std::function<void(Node<T> *)> remove_helper = [&](Node<T> *iter) {
    if (iter == nullptr) {
      return;
    }
    remove_helper(iter->left);
    remove_helper(iter->right);
    delete iter;
  };
  remove_helper(root);
}

// ################################# TEST ######################################

namespace test {

void test_insert() {
  BST<int> tree;
  tree.insert(5);
  assert(tree.size() == 1);
  assert(tree.depth() == 1);
  tree.insert(2);
  assert(tree.size() == 2);
  assert(tree.depth() == 2);
  tree.insert(7);
  assert(tree.size() == 3);
  assert(tree.depth() == 2);
  tree.insert(1);
  assert(tree.size() == 4);
  assert(tree.depth() == 3);
  tree.insert(3);
  assert(tree.size() == 5);
  assert(tree.depth() == 3);
  tree.insert(6);
  assert(tree.size() == 6);
  assert(tree.depth() == 3);
  tree.insert(8);
  assert(tree.size() == 7);
  assert(tree.depth() == 3);
}

void test_search() {
  BST<int> tree;
  tree.insert(5);
  tree.insert(2);
  tree.insert(7);
  tree.insert(1);
  tree.insert(3);
  tree.insert(6);
  tree.insert(8);
  assert(tree.search(5) == true);
  assert(tree.search(2) == true);
  assert(tree.search(7) == true);
  assert(tree.search(1) == true);
  assert(tree.search(3) == true);
  assert(tree.search(6) == true);
  assert(tree.search(8) == true);
  assert(tree.search(0) == false);
  assert(tree.search(4) == false);
  assert(tree.search(9) == false);
}

void test_min_max() {
  BST<int> tree;

  tree.insert(5);
  assert(tree.min().value() == 5);
  assert(tree.max().value() == 5);
  tree.insert(2);
  assert(tree.min().value() == 2);
  assert(tree.max().value() == 5);
  tree.insert(7);
  assert(tree.min().value() == 2);
  assert(tree.max().value() == 7);
  tree.insert(1);
  assert(tree.min().value() == 1);
  assert(tree.max().value() == 7);
  tree.insert(3);
  assert(tree.min().value() == 1);
  assert(tree.max().value() == 7);
  tree.insert(6);
  assert(tree.min().value() == 1);
  assert(tree.max().value() == 7);
  tree.insert(8);
  assert(tree.min().value() == 1);
  assert(tree.max().value() == 8);
}

void test_remove() {
  BST<int> t;

  t.insert(5);
  t.insert(2);
  t.insert(1);
  t.insert(4);
  t.insert(3);
  t.insert(7);
  t.insert(6);
  t.insert(8);

  t.remove(1);
  assert(t.size() == 7);
  assert(t.search(1) == false);
  assert(t.search(2) == true);

  t.remove(4);
  assert(t.size() == 6);
  assert(t.search(4) == false);
  assert(t.search(2) == true);
  assert(t.search(3) == true);

  t.remove(2);
  assert(t.size() == 5);
  assert(t.search(2) == false);
  assert(t.search(3) == true);
  assert(t.search(5) == true);

  t.remove(5);
  assert(t.size() == 4);
  assert(t.search(5) == false);
  assert(t.search(6) == true);
  assert(t.search(8) == true);
}

void test_orders() {
  std::array<int, 15> test_arr{50, 35, 75, 25, 44, 65, 78, 20,
                               30, 36, 47, 55, 70, 77, 90};

  std::array<int, 15> test_in{20, 25, 30, 35, 36, 44, 47, 50,
                              55, 65, 70, 75, 77, 78, 90};

  std::array<int, 15> test_pre{50, 35, 25, 20, 30, 44, 36, 47,
                               75, 65, 55, 70, 78, 77, 90};

  std::array<int, 15> test_post{20, 30, 25, 36, 47, 44, 35, 55,
                                70, 65, 77, 90, 78, 75, 50};

  BST<int> bst;

  for (auto &i : test_arr) {
    bst.insert(i);
  }

  auto inorder = bst.inorder();
  assert(inorder.size() == test_in.size());
  for (std::size_t i = 0; i < test_in.size(); i++) {
    assert(inorder[i] == test_in[i]);
  }

  auto preorder = bst.preorder();
  assert(preorder.size() == test_pre.size());
  for (std::size_t i = 0; i < test_pre.size(); i++) {
    assert(preorder[i] == test_pre[i]);
  }

  auto postorder = bst.postorder();
  assert(postorder.size() == test_post.size());
  for (std::size_t i = 0; i < test_post.size(); i++) {
    assert(postorder[i] == test_post[i]);
  }
}

}  // namespace test

// ################################# TEST ######################################

int main() {
  test::test_insert();
  test::test_min_max();
  test::test_remove();
  test::test_search();
  test::test_orders();

  BST<int> bst;

  int choice;
  int value;

  while (true) {
    std::cout << "1-> Insert\n";
    std::cout << "2-> Remove\n";
    std::cout << "3-> Search\n";
    std::cout << "4-> Min\n";
    std::cout << "5-> Max\n";
    std::cout << "6-> Inorder\n";
    std::cout << "7-> Preorder\n";
    std::cout << "8-> Postorder\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cin >> value;
        bst.insert(value);
        break;
      case 2:
        std::cin >> value;
        bst.remove(value);
        break;
      case 3:
        std::cin >> value;
        std::cout << bst.search(value) ? "Found.\n" : "Not Found.\n";
        break;
      case 4: {
        auto find = bst.min();
        if (find.has_value())
          std::cout << find.value() << "\n";
        else
          std::cout << "Tree Is Empty.\n";
      } break;
      case 5: {
        auto find = bst.max();
        if (find.has_value())
          std::cout << find.value() << "\n";
        else
          std::cout << "Tree Is Empty.\n";
      } break;
      case 6: {
        for (auto &i : bst.inorder()) {
          std::cout << i << " - ";
        }
        std::cout << "\n";
      } break;
      case 7: {
        for (auto &i : bst.preorder()) {
          std::cout << i << " - ";
        }
        std::cout << "\n";
      } break;
      case 8: {
        for (auto &i : bst.postorder()) {
          std::cout << i << " - ";
        }
        std::cout << "\n";
      } break;
      default:
        std::cout << "No Choice\n";
        break;
    }
    std::cout << "\n";
    bst.print();
    std::cout << "\n";
  }
}
