## Çift Yönlü Bağlantılı Liste(Doubly Linked List)

Çift yönlü bağlı liste, tek yönlü bağlı listeden farklı olarak hem kendinden önceki düğüme de işaret eden veri yapılarıdır. 

#### Düğüm Yapısı

Düğüm, bir adet T türünden veri (data), iki adet T türünden işaretçi (*next) ve (*prev) barındırır. *next, bir sonraki düğümün adresini ve *prev bir önceki düğümün adresini tutar.

```cpp
template <typename T>
struct Node {
    Node<T>* next;
    Node<T>* prev;
    T data;

    Node(T _data) : data(_data), next(nullptr), prev(nullptr) {}
};
```


#### Tek Yönlü Bağlantılı Liste Sınıfı
Bu sınıf, düğümlerin yönetimini üstlenir ve baş(*head) ve kuyruk(*tail) düğümlerini içerir.
Sınıfın üye fonksiyonları şunlardır:

- Sona Ekleme
- Başa Ekleme
- Sondan Silme
- Baştan Silme
- Listeyi Temizleme
- Arama
- Takas
- Sıralama
- Listedeki Eleman Sayısı(size)
- Liste Kontrol
- Liste Görüntüleme


| İşlev | Big O | 
|-------------- | -------------- |
| Sona Ekleme | $O(1)$ |
| Başa Ekleme | $O(1)$ |
| Sondan Silme | $O(1)$ |
| Başdan Silme | $O(1)$ |
| Listeyi Temizleme | $O(n)$ |
| Arama | $O(n)$ |
| Takas | $O(1)$ |
| Sıralama | $O(n^2)$ |
| Listedeki Eleman Sayısı | $O(n)$ |
| Liste Kontrol | $O(1)$ |
| Liste Görüntüleme | $O(n)$ |

---

```cpp
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
```

---

#### Kurucu(Constructor)

İki adet kurucu üye bulunmaktadır. DoublyLinkedList nesnesi oluşturulurken, listenin ilk düğümü oluşturulur aksi taktirde boş bir işaretçi ile sınıf hayata gelir. Baş ve kuyruk işaretçileri aynı düğüme işaret eder.


```cpp
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = head;
}
//or
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T init_first_node) {
    head = new Node<T>(init_first_node);
    tail = head;
}
```

---

#### Sona Ekleme

Sona ekleme kuyruk işaretçisi üzerinden yapılır. $O(1)$ düzeyindedir. Dikkat edilmesi gereken yeni düğüm eski düğüme işaret etmelidir. 

```cpp
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
```

---

#### Başa Ekleme

Bu işlev, listenin başına yeni bir düğüm ekler. İlk seferde bir düğüm oluşturulur ve oluşturulan düğümün next'i, başı(head) işaret eder. Daha sonra yeni düğüm başa eklenir ve oluşturulan yeni düğüm artık listedeki başı gösterir.

```cpp
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
```

---

#### Arama

Aranan veri(_data) ile ilk eşleşen düğümün adresini, bulunmazsa nullptr döndürür.

```cpp
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
```

---

#### Başdan Silme

Baştan silmede iki farklı durum vardır. Birincisi baş düğümü bir listenin ikinci düğümüne taşımak ve listenin başındaki elemanı sisteme geri etmek. Dikkat edilmesi gereken ise ikinci durumdur, eğer sisteme geri verilen alan son düğüme aitse baş düğümle beraber kuyrukta nullptr olarak ayarlanmalıdır(revalue).

```cpp
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
```

---

#### Sondan Silme

Sondan silme işlevinde tek yönlü bağlı listelere göre avantaj yakaladığımız işlevlerdendir. Listede bir önceki düğüme doğru hareket edebilme becerisi, karmaşıklığı $O(n)$ düzeyinden $O(1)$ düzeyine indirger. Başdan silmede olduğu gibi iki farklı durum vardır.

```cpp
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
```

---

#### Listeyi Temizleme

Listedeki tüm elemanları dolaşarak son düğüm de dahil olmak üzere tüm düğümleri sisteme geri verir.

```cpp
template <typename T>
void DoublyLinkedList<T>::clear() {
    if (head == nullptr) return;

    while (head->next != nullptr) {
        head = head->next;
        delete head->prev;
    }

    delete head;
    head = nullptr;
    tail = nullptr;
}
```

---

#### Takas

Tek yönlü bağlı liste yazısında takas yöntemi için hangi algoritmanın tercih edilebileceğinden bahsedilmiştir. Burada verilerin değil doğrudan düğümlerin takaslanması söz konusudur. Lakin bir kaç sebepten dolayı gerçeklenmesi biraz karmaşık olabilir. Bunun için ayrıntılı bir açıklamaya ihtiyaç olduğunu varsayıyorum. İşte dikkat edilmesi gereken durumlar:

1. Takasın gerçekleşmemesi gereken durumlar:

- Listenin boş olma durumu
- Takaslanmak istenen düğümlerin aynı olma durumu
- Takaslanmak istenen düğümlerin nullptr olma durumu

Bu 3 durum için de işlev sonlandırılmalıdır, aksi halde erişmek istediği düğüme, program tarafından erişim mümkün olmadığından çökme meydana gelecektir.

2. Takas gerçekleşirken dikkat edilmesi gereken durumlar:

- Düğümlerin biri baş diğeri kuyruk olma durumu: Bu durumda baş ve kuyruk düğüm tekrar ayarlanmalı, yeni başın prev`i ve yeni kuyruğun next'i nullptr yapılmalıdır. 
- Düğümlerden birinin baş olma durumu: Takaslama işlevi yapıldıktan sonra baş düğüm yeniden ayarlanmalıdır ve prev`i nullptr yapılmalıdır.
- Düğümlerden birinin kuyruk olma durumu: Takaslama işlevi yapıldıktan sonra kuyruk düğümü yeniden ayarlanmalıdır ve next`i nullptr yapılmalıdır.
- Düğümlerin ardışık olma durumu: Bu durumda dikkat edilmediği taktirde liste n. düğüm n+1. düğüme, n+1. düğüm n. düğüme işaret etmesine sebep olunabilir.

```cpp
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
```

---

#### Sıralama

Bu işlev, verilen bir düzenleme seçeneği (azalan veya artan) kullanarak sıralama yapar. Sıralama seçeneği için SortOption adlı bir numaralandırma kullanılır.

```cpp
enum class SortOption
{
    less,
    greater
};
```
Sıralama işlemi [kabarcık sıralama algoritması](https://tr.wikipedia.org/wiki/Kabarc%C4%B1k_s%C4%B1ralamas%C4%B1) kullanılarak gerçekleştirilmiştir. Döngü her yinelenişinde, liste elemanlarının doğru sıralamada olup olmadığını kontrol etmek için elemanların değerleri karşılaştırılır. Bir takas işlemi gerçekleşmediyse, liste doğru sıralamada olduğu anlaşılır ve işlev sona erer.

```cpp
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
```

---

#### Listedeki Eleman Sayısı

Dizinin tüm düğümleri dolaşır ve her hareketinde count değişkenini bir artırır.

```cpp
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
```

#### Liste Kontrol

Listenin boş oup olmadığını kontrol eder.

```cpp
template <typename T>
bool DoublyLinkedList<T>::empty() {
    if (head && tail) return true;

    return false;
}
```

---

#### Yıkıcı(Destructor)

Dtor , listedeki tüm düğümlerin işgal ettiği belleği sisteme geri vererek serbest bırakır. Liste, baştan başlayarak yinelenir ve listenin sonuna ulaşana kadar tüm düğümler sisteme geri verilir. Eğer nesne doğrudan yok edilirse, new ile tahsis edilen bellek alanları sistemden geri verilmez ve programın yaşam süresi boyunca bellek sızıntısına neden olur.

```cpp
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
        delete head->prev;
    }
    if (head != nullptr) delete head;
}
```

<h4 align="center"><a href="/linked_list">< Önceki Sayfa | <a href="../circular_linked_list">Sonraki Sayfa ></a></a></h4>
