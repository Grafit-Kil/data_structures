#include <iomanip>
#include <iostream>

/*Sort Options*/
enum class SortOption { less, greater };

template <typename T>
struct Node {
    Node<T>* next;
    Node<T>* prev;
    T data;

    Node(T _data) : data(_data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
   public:
    DoublyLinkedList();
    DoublyLinkedList(T init_first_node);
    void display();
    void push_back(const T _data);
    void push_front(const T _data);
    void pop_back();
    void pop_front();
    void clear();
    std::size_t size();
    bool empty();
    Node<T>* find(const T _data);
    void swap(Node<T>* first, Node<T>* second);
    void sort(SortOption ch);
    ~DoublyLinkedList();

   private:
    Node<T>* head;
    Node<T>* tail;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = head;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T init_first_node) {
    head = new Node<T>(init_first_node);
    tail = head;
}

template <typename T>
void DoublyLinkedList<T>::display() {
    std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
    std::cout << std::setfill(' ');
    std::cout << "| " << std::setw(10) << "Address" << std::setw(7) << "| |";
    std::cout << std::setw(20) << "Data"
              << " |" << std::endl;
    std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
    std::cout << std::setfill(' ');

    Node<T>* iter = head;
    while (iter) {
        std::cout << "| " << std::setw(10) << iter << "| |";
        std::cout << std::setw(20) << iter->data << " |" << std::endl;
        iter = iter->next;
    }

    std::cout << "+" << std::setfill('-') << std::setw(42) << "+\n\n";
    std::cout << std::setfill(' ');
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T _data) {
    if (head == nullptr) {
        head = new Node<T>(_data);
        tail = head;
    } else {
        tail->next = new Node<T>(_data);
        tail->next->prev = tail;
        tail = tail->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T _data) {
    if (head == nullptr) {
        head = new Node<T>(_data);
        tail = head;
    } else {
        head->prev = new Node<T>(_data);
        head->prev->next = head;
        head = head->prev;
    }
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
    if (head == nullptr) {
        return;
    } else if (head->next != nullptr) {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    } else {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
    if (tail == nullptr) {
        return;
    } else if (tail->prev != nullptr) {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    } else {
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    if (head == nullptr) return;

    while (head->next != nullptr) {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }

    delete head;
    head = nullptr;
    tail = nullptr;
}

template <typename T>
std::size_t DoublyLinkedList<T>::size() {
    std::size_t list_size{0};
    Node<T>* iter = head;
    while (iter) {
        list_size++;
        iter = iter->next;
    }
    return list_size;
}

template <typename T>
bool DoublyLinkedList<T>::empty() {
    if (head && tail) return true;

    return false;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::find(const T _data) {
    if (!empty()) return nullptr;

    Node<T>* iter = head;
    while (iter != nullptr) {
        if (iter->data == _data) return iter;
        iter = iter->next;
    }
    return nullptr;
}

template <typename T>
void DoublyLinkedList<T>::swap(Node<T>* first, Node<T>* second) {
    if (!empty()) return;
    if (first == second) return;
    if (!(first && second)) return;
    if ((first == head || second == head) &&
        (second == tail || first == tail)) {
        if (first == tail) {
            first = head;
            second = tail;
        }
        Node<T>* f_next = first->next;
        Node<T>* s_prev = second->prev;

        first->prev = second->prev;
        second->prev = nullptr;
        second->next = first->next;
        first->next = nullptr;

        f_next->prev = second;
        s_prev->next = first;

        Node<T>* temp = head;
        head = tail;
        tail = head;
    } else if (first == head || second == head) {
        if (second == head) {
            Node<T>* temp = second;
            second = first;
            first = temp;
        }

        if (first->next == second || second->next == first) {
            second->prev = nullptr;
            first->next = second->next;
            second->next->prev = first;
            second->next = first;
            first->prev = second;
            head = second;
        } else {
            Node<T>* f_next = first->next;

            first->next = second->next;
            first->prev = second->prev;
            second->prev->next = first;
            second->next->prev = first;

            second->prev = nullptr;
            second->next = f_next;
            f_next->prev = second;
            head = second;
        }
    } else if (first == tail || second == tail) {
        if (first == tail) {
            Node<T>* temp = second;
            second = first;
            first = temp;
        }
        if (first->next == second || second->next == first) {
            first->next = nullptr;
            second->prev = first->prev;
            first->prev->next = second;
            first->prev = second;
            second->next = first;
            tail = first;
        } else {
            Node<T>* s_prev = second->prev;
            second->next = first->next;
            second->prev = first->prev;
            first->next->prev = second;
            first->prev->next = second;
            s_prev->next = first;
            first->prev = s_prev;
            first->next = nullptr;
        }
    }
    /*Swap for consecutive nodes*/
    else if (first->next == second || second->next == first) {
        /*The node found firstly in the list must be first.*/
        if (second->next == first) {
            Node<T>* temp = second;
            second = first;
            first = temp;
        }
        Node<T>* f_prev = first->prev;
        Node<T>* s_next = second->next;
        first->next = second->next;
        second->prev = first->prev;
        second->next = first;
        first->prev = second;

        f_prev->next = second;
        s_next->prev = first;
        // return;
    } else {
        Node<T>* f_next = first->next;
        Node<T>* f_prev = first->prev;
        Node<T>* s_next = second->next;
        Node<T>* s_prev = second->prev;

        first->next = s_next;
        first->prev = s_prev;
        second->next = f_next;
        second->prev = f_prev;

        f_prev->next = second;
        f_next->prev = second;

        s_prev->next = first;
        s_next->prev = first;
    }
}
template <typename T>
void DoublyLinkedList<T>::sort(SortOption opt) {
    if (!empty()) return;

    Node<T>* iter = head;
    bool check_sort = true;
    while (check_sort) {
        check_sort = false;
        iter = head;
        while (iter->next) {
            if (SortOption::greater == opt && iter->next->data > iter->data) {
                swap(iter, iter->next);
                check_sort = true;
            } else if (SortOption::less == opt &&
                       iter->next->data < iter->data) {
                swap(iter, iter->next);
                check_sort = true;
            } else {
                iter = iter->next;
            }
        }
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
        delete head->prev;
    }
    if (head != nullptr) delete head;
}

int main() {
    bool event = true;
    int choice = 0;
    int value = 0;
    DoublyLinkedList<int> list{};

    while (event) {
        list.display();

        std::cout << "1 - Push Back\n";
        std::cout << "2 - Push Front\n";
        std::cout << "3 - Find\n";
        std::cout << "4 - Pop Back\n";
        std::cout << "5 - Pop Front\n";
        std::cout << "6 - +clear\n";
        std::cout << "7 - Sort\n";
        std::cout << "8 - Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Value: ";
                std::cin >> value;
                list.push_back(value);
                break;
            case 2:
                std::cout << "Enter Value: ";
                std::cin >> value;
                list.push_front(value);
                break;
            case 3:
                std::cout << "Enter Value: ";
                std::cin >> value;
                if (list.find(value))
                    std::cout << "Fount\n\n";
                else
                    std::cout << "Not Fount\n\n";
                break;
            case 4:
                list.pop_back();
                break;
            case 5:
                list.pop_front();
                break;
            case 6:
                list.clear();
                break;
            case 7:
                std::cout << "1  Descending Sort \n2 - Ascending Sort "
                             "Descending Sort : ";
                value = 0;
                std::cin >> value;
                if (value == 1)
                    list.sort(SortOption::greater);
                else if (value == 2)
                    list.sort(SortOption::less);
                else
                    std::cout << "Invalid Option\n";
                break;
            case 8:
                event = false;
                break;

            default:
                std::cout << "Invalid Option\n";
                break;
        }
        std::cout << "\n";
        std::cout << std::setfill('-') << std::setw(43) << "\n";
        std::cout << std::setfill(' ');
    }
}
