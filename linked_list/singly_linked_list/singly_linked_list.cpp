#include <cassert> // assert
#include <cstddef> //std::size_t
#include <iostream> // I/O
#include <iomanip> // for std::setw, std::setfill
#include <vector> // for std::vector
#include <random> // for mersenne twister engine
#include <chrono> // for seed and run time calc
#include <iterator> //std::begin, std::end
#include <algorithm> // std::sort

enum class SortOption
{
    less,
    greater
};

template <typename T>
struct Node
{
    Node<T> *next;
    T data;
    Node() : data(0), next(nullptr) {}
    Node(T _data) : data(_data), next(nullptr) {}
    Node(Node *n_cpy) : data(n_cpy->data), next(n_cpy->next) {}
};

template <typename T>
class SinglyLinkedList
{
public:
    SinglyLinkedList(const T);
    ~SinglyLinkedList();
    void push_back(const T);
    void display();
    void push_front(const T);
    Node<T> *find(const T);
    void pop_back();
    void pop_front();
    void remove(const T);
    void sort(SortOption);
    T get_element(const size_t);

private:
    Node<T> *head;
    Node<T> *tail;

    void swap(Node<T> *, Node<T> *);
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const T init_first_value)
{
    head = new Node<T>(init_first_value);
    tail = head;
};

template <typename T>
void SinglyLinkedList<T>::push_back(const T _data)
{
    tail->next = new Node<T>(_data);
    tail = tail->next;
}

template <typename T>
void SinglyLinkedList<T>::push_front(const T _data)
{

    Node<T> *new_head = new Node<T>(_data);
    new_head->next = head;
    head = new_head;
}

/* Based on first match */
template <typename T>
Node<T> *SinglyLinkedList<T>::find(const T _data)
{
    Node<T> *iter = head;
    while (iter)
    {
        if (iter->data == _data)
        {
            return iter;
        }
        iter = iter->next;
    }
    return nullptr;
}

/* If there is only one node in the list, it does nothing. */
template <typename T>
void SinglyLinkedList<T>::pop_front()
{
    if(head->next == nullptr)
        return;

    Node<T> *iter = head;
    Node<T> *temp = head;
    head = iter->next;
    temp->next = nullptr;
    delete temp;
}

/* If there is only one node in the list, it does nothing. */
template <typename T>
void SinglyLinkedList<T>::pop_back()
{
    Node<T> *iter = head;
    while (iter->next)
    {
        if (iter->next == tail)
        {
            tail = iter;
            delete iter->next;
            iter->next = nullptr;
            break;
        }
        iter = iter->next;
    }
}
/* Based on first match */
template <typename T>
void SinglyLinkedList<T>::remove(const T _data)
{

    if (head->next == nullptr)
        return;

    if (head->data == _data)
    {
        pop_front();
        return;
    }

    Node<T> *iter = head;
    while (iter->next != nullptr && iter->next->data != _data)
        iter = iter->next;

    if (iter->next == nullptr)
        return;

    Node<T> *temp = iter->next;

    if (temp == tail)
    {
        pop_back();
        return;
    }
    iter->next = temp->next;
    delete temp;
}

template <typename T>
void SinglyLinkedList<T>::display()
{
    std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
    std::cout << std::setfill(' ');
    std::cout << "| " << std::setw(10) << "Address" << std::setw(7) << "| |";
    std::cout << std::setw(20) << "Data" << " |" << std::endl;
    std::cout << "+" << std::setfill('-') << std::setw(41) << "+\n";
    std::cout << std::setfill(' ');

    Node<T> *iter = head;
    while (iter)
    {
        std::cout << "| " << std::setw(10) << iter << "| |";
        std::cout << std::setw(20) << iter->data << " |" << std::endl;
        iter = iter->next;
    }

    std::cout << "+" << std::setfill('-') << std::setw(42) << "+\n\n";
    std::cout << std::setfill(' ');
}

/* If the head or tail is to be swapped, the data is swapped. */
template <typename T>
void SinglyLinkedList<T>::swap(Node<T> *first_element,
                               Node<T> *second_element)
{
    if (first_element == second_element)
        return;

    Node<T> *iter = head;

    if (first_element == head || second_element == head ||
        first_element == tail || second_element == tail)
    {
        T temp_data = second_element->data;
        second_element->data = first_element->data;
        first_element->data = temp_data;
    }
    else
    {
        Node<T> *temp_next_of_first = first_element->next;
        Node<T> *temp_next_of_second = second_element->next;

        while (iter->next != first_element)
        {
            iter = iter->next;
        }

        first_element->next = temp_next_of_second;
        iter->next = second_element;
        second_element->next = temp_next_of_first;

        while (temp_next_of_first->next)
        {
            if (temp_next_of_first->next == second_element)
            {
                temp_next_of_first->next = first_element;
                break;
            }
            temp_next_of_first = temp_next_of_first->next;
        }
    }
}

template <typename T>
void SinglyLinkedList<T>::sort(SortOption opt)
{
    if (!head->next)
        return;

    Node<T> *iter = head;

    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        while (iter->next)
        {
            if (opt == SortOption::less && iter->data > iter->next->data)
            {
                swap(iter, iter->next);
                swapped = true;
            }
            else if (opt == SortOption::greater &&
                     iter->data < iter->next->data)
            {
                swap(iter, iter->next);
                swapped = true;
            }
            iter = iter->next;
        }
        iter = head;
    }
}
/* Returns the data of the index'th node, otherwise 0. */
template <typename T>
T SinglyLinkedList<T>::get_element(const size_t index)
{
    Node<T> *iter = head;

    size_t count{0};
    while (iter)
    {
        if (count == index)
            return iter->data;

        count++;
        iter = iter->next;
    }
    return 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    size_t count{1};
    Node<T> *iter = head;
    Node<T> *delete_iter;
    while (iter)
    {
        delete_iter = iter;
        iter = iter->next;
        delete delete_iter;
        count++;
    }
}

// ############################################################################
// ################################### TEST ###################################
// ############################################################################

class RunTimeCalculator
{
public:
    void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }
    void end()
    {
        end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<
                                std::chrono::duration<
                                    double, std::ratio<1>>>(end_time - start_time)
                                .count();

        std::cout << "Elapsed_time: " << elapsed_time << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

template <typename T>
T random_data(T begin_of_range, T end_of_range)
{
    std::mt19937 mt{static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count())};

    std::uniform_int_distribution<T> rnd{begin_of_range, end_of_range};

    return rnd(mt);
}

void TEST_PUSH_BACK()
{
    RunTimeCalculator timer;
    timer.start();
    unsigned int n = 1000;

    std::cout << "[TEST PUSH_BACK ˙|. ";

    SinglyLinkedList<int> list{1};
    std::vector<int> random_vec{1};

    for (size_t i = 1; i < n; i++)
    {
        random_vec.push_back(random_data(999'000, 1'999'000));
    }

    for (size_t i = 1; i < random_vec.size() - 1; i++)
    {
        list.push_back(random_vec[i]);
    }

    for (size_t i = 0; i < random_vec.size() - 1; i++)
    {
        assert(list.get_element(i) == random_vec[i] && "push_back() ERROR!\n");
    }

    std::cout << "OK] "
              << "n = " << n << " ";
    timer.end();
}

void TEST_PUSH_FRONT()
{
    RunTimeCalculator timer;
    timer.start();
    std::cout << "[TEST PUSH_FRONT ˙|. ";

    SinglyLinkedList<int> list{1};
    std::vector<int> random_vec{1};
    unsigned int n = 1000;
    for (size_t i = 1; i < n; i++)
    {
        random_vec.push_back(random_data(0, 999'999));
    }

    for (size_t i = 1; i < random_vec.size(); i++)
    {
        list.push_front(random_vec[i]);
    }
    std::reverse(std::begin(random_vec), std::end(random_vec));

    for (size_t i = 0; i < random_vec.size() - 1; i++)
    {
        assert(list.get_element(i) == random_vec[i] && "push_front() ERROR!\n");
    }

    std::cout << "OK] "
              << "n = " << n << " ";
    timer.end();
}

void TEST_FIND()
{

    std::cout << "[TEST FIND ˙|. ";

    SinglyLinkedList<float> list{120.3f};
    list.push_back(23.4f);
    list.push_back(23.7f);
    list.push_back(45.12f);
    list.push_back(38.89f);

    Node<float> *found_test_n1 = list.find(120.3f); // head
    Node<float> *found_test_n2 = list.find(45.12f);
    Node<float> *found_test_n3 = list.find(38.89f); // tail
    Node<float> *found_test_n4 = list.find(33.2f);  // nullptr

    assert(found_test_n1 != nullptr && "find() ERROR!");
    assert(found_test_n1->data == 120.3f && "find() ERROR!");
    assert(found_test_n1->next != nullptr && "find() ERROR!");

    assert(found_test_n2 != nullptr && "find() ERROR!");
    assert(found_test_n2->data == 45.12f && "find() ERROR!");
    assert(found_test_n2->next != nullptr && "find() ERROR!");

    assert(found_test_n3 != nullptr && "find() ERROR!");
    assert(found_test_n3->data == 38.89f && "find() ERROR!");
    assert(found_test_n3->next == nullptr && "find() ERROR!");

    assert(found_test_n4 == nullptr && "find() ERROR!");

    std::cout << "OK]\n";
}

void TEST_POP_BACK()
{
    std::cout << "[TEST POP_BACK ˙|. ";
    SinglyLinkedList<int> list(1);
    list.push_back(2);
    list.push_back(4);
    list.push_back(5);

    list.pop_back();
    assert(list.find(5) == nullptr && "pop_back() ERROR!");
    list.pop_back();
    assert(list.find(4) == nullptr && "pop_back() ERROR!");

    Node<int> *s1 = list.find(1);
    Node<int> *s2 = list.find(2);
    assert(s1->next == s2 && s2->next == nullptr && "pop_back() ERROR!");

    std::cout << "OK]\n";
}

void TEST_POP_FRONT()
{
    std::cout << "[TEST POP_FRONT ˙|. ";

    SinglyLinkedList<int> list(5);
    list.push_back(3);
    list.push_back(8);
    list.push_back(4);

    list.pop_front();
    assert(list.get_element(0) == 3 && "pop_front() ERROR!");
    assert(list.get_element(1) == 8 && "pop_front() ERROR!");
    assert(list.get_element(2) == 4 && "pop_front() ERROR!");

    list.pop_front();
    assert(list.get_element(0) == 8 && "pop_front() ERROR!");
    assert(list.get_element(1) == 4 && "pop_front() ERROR!");

    list.pop_front();
    assert(list.get_element(0) == 4 && "pop_front() ERROR!");

    list.push_back(100);
    list.push_back(200);
    list.push_back(300);
    list.push_back(400);
    list.push_back(1500);

    assert(list.get_element(3) == 300 && "pop_front() ERROR!");
    assert(list.get_element(5) == 1500 && "pop_front() ERROR!");

    std::cout << "OK]\n";
}

void TEST_REMOVE()
{

    std::cout << "[TEST REMOVE ˙|. ";
    SinglyLinkedList<int> list{1};

    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);

    list.remove(3);
    assert(list.get_element(2) == 4 && "remove() ERROR!");
    list.remove(4);
    assert(list.get_element(2) == 5 && "remove() ERROR!");

    list.remove(1);
    assert(list.get_element(0) == 2 && "remove() ERROR!");
    list.remove(8);

    std::cout << "OK]\n";
}

void TEST_SORT()
{
    RunTimeCalculator timer;
    timer.start();
    std::cout << "[TEST SORT ˙|. ";

    SinglyLinkedList<int> list{1};

    std::vector<int> random_vec{1};
    unsigned int n = 500;
    for (size_t i = 1; i < n; i++)
    {
        random_vec.push_back(random_data(999'000, 1'999'000));
    }

    for (size_t i = 1; i < random_vec.size(); i++)
    {
        list.push_back(random_vec[i]);
    }

    std::sort(std::begin(random_vec), std::end(random_vec));
    list.sort(SortOption::less);
    for (size_t i = 0; i < random_vec.size() - 1; i++)
    {
        assert(list.get_element(i) == random_vec[i] && "sort() ERROR!");
    }

    std::sort(std::begin(random_vec), std::end(random_vec), std::greater<int>());
    list.sort(SortOption::greater);

    for (size_t i = 0; i < random_vec.size() - 1; i++)
    {
        assert(list.get_element(i) == random_vec[i] && "sort() ERROR!");
    }

    std::cout << "OK] "
              << "n = " << n << " ";
    timer.end();
}

void TEST()
{
    TEST_PUSH_BACK();
    TEST_PUSH_FRONT();
    TEST_FIND();
    TEST_POP_BACK();
    TEST_POP_FRONT();
    TEST_REMOVE();
    TEST_SORT();
}
int main()
{
    // TEST();

    bool app = true;
    int choice = 0;
    int value = 0;
    SinglyLinkedList<int> list{1};

    while (app)
    {
        list.display();

        std::cout << "1 - Push Back\n";
        std::cout << "2 - Push Front\n";
        std::cout << "3 - Find\n";
        std::cout << "4 - Pop Back\n";
        std::cout << "5 - Pop Front\n";
        std::cout << "6 - Remove \n";
        std::cout << "7 - Sort \n";
        std::cout << "8 - Exit \n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice)
        {
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
            std::cout << "Enter Value: ";
            std::cin >> value;
            list.remove(value);
            break;
        case 7:
            std::cout << "1  Descending Sort \n2 - Ascending Sort Descending Sort : ";
            value = 0;
            std::cin >> value;
            if (value == 1)
                list.sort(SortOption::greater);
            else if(value == 2)
                list.sort(SortOption::less);
            else
                std::cout << "Invalid Option\n";
            break;
        case 8:
            app = false;
            break;

        default:
            std::cout << "Invalid Option\n";
            break;
        }
    }
}
