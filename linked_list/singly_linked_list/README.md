# Tek Yönlü Bağlantılı Liste(Singly Linked List)

Tek yönlü bağlantılı liste, verilere erişimin sadece düğümler(Node) üzerinde tek yönlü yapılabildiği veri yapılarıdır. Düğümler bellekte rastgele konumlarda yer alır ve erişim işlemi sadece baş düğümün adresine sahip olmakla mümkündür. Baş düğümün adresini kaybetmeden diğer düğümlere erişmek için bir yineleyiciye(iterator) ihtiyaç vardır.

#### Düğüm Yapısı

Düğüm, bir adet T türünden veri (data) ve bir adet T türünden işaretçi (*next) barındırır. *next, bir sonraki düğümün adresini tutar.

```cpp
template <typename T>
struct Node
{
    Node<T> *next;
    T data;

    Node() : data(0), next(nullptr) {}
    Node(T _data) : data(_data), next(nullptr) {}
};
```

#### Tek Yönlü Bağlantılı Liste Sınıfı
Bu sınıf, düğümlerin yönetimini üstlenir ve baş(*head) ve kuyruk(*tail) düğümlerini içerir.
Sınıfın üye fonksiyonları şunlardır:

- Sona Ekleme
- Başa Ekleme
- Sondan Silme
- Baştan Silme
- Sıralı Erişim ile Silme
- Arama
- Takas
- Sıralama
- Sıralı Erişim ile Eleman Almak
- Liste Görüntüleme

> Sırala erişimde, listenin herhangi bir elemanına erişim yolu ondan önce gelen elemanları ziyaret etmekle mümkündür.

| İşlev | Big O | 
|-------------- | -------------- |
| Sona Ekleme | O(1) |
| Başa Ekleme | O(1) |
| Sondan Silme | O(1) |
| Başdan Silme | O(1) |
| Sıralı Erişim ile Silme | O(n) |
| Arama | O(n) |
| Takas | O(n) |
| Sıralama | O(n^2) |
| Sıralı Erişim ile Eleman Almak | O(n) |
| Liste Görüntüleme | O(n) |

```cpp
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
```

---

#### Kurucu(Constructor)

Bir SinglyLinkedList nesnesi oluşturulurken, listenin ilk düğümü oluşturulur. Bu düğüm, baş(head) ve kuyruk(tail) işaretçileri tarafından gösterilir. Eğer liste sadece bir düğüm içeriyorsa, baş ve kuyruk işaretçileri aynı düğüme işaret eder.


```cpp
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const T init_first_value)
{
    head = new Node<T>(init_first_value);
    tail = head;
};
```

---

#### Sona Ekleme
Birçok öğretici, listenin sonuna eleman eklemeyi bir döngü kullanarak yapar. Bu yöntemde, listenin sonuna ulaşmak için her bir düğümü tek tek dolaşılır ve eleman sona eklendikten sonra döngü sonlandırılır.


```cpp
Node<T> *iter = head;

while(iter != nullptr){ // iter eğer nullptr(boş) ise döngü sonlanr.
  //code
  if(iter->next == nullptr){
    iter->next = new Node<T>(data);
    break;
  }
  iter = iter->next; // iter her seferinde bir sonraki düğüme ilerler.
  //code
}
```
Bu yöntem O(n) zaman karmaşıklığına sahiptir. Ancak, bir kuyruk (tail) değişkeni kullanarak bu işlem O(1) zaman karmaşıklığına düşürülebilir. Bu yapı, kullanım amacına göre şekillendirilebilir. Örneğin, son giren ilk çıkar(LIFO) veri yapısında kuyruk değişkeni gerekli olmayabilir. Fonksiyon aşağıdaki gibi tanımlanır:

```cpp
template <typename T>
void SinglyLinkedList<T>::push_back(const T _data)
{
  tail->next = new Node<T>(_data);
  tail = tail->next;
}
```

---

#### Başa Ekleme  

Bu işlev, listenin başına yeni bir düğüm ekler. İlk seferde bir düğüm oluşturulur ve oluşturulan düğümün next'i, başı(head) işaret eder. Daha sonra yeni düğüm başa eklenir ve oluşturulan yeni düğüm artık listedeki başı gösterir.

```cpp
template <typename T>
void SinglyLinkedList<T>::push_front(const T _data)
{

    Node<T> *new_head = new Node<T>(_data);
    new_head->next = head;
    head = new_head;
}
```

---

#### Arama

Bu işlev, listenin içindeki düğümlerin data özelliklerini kontrol ederek, _data değişkenine eşit olan ilk düğümün adresini döndürür. Eşitlik bulunamazsa, nullptr döndürür.

```cpp
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
```

---

#### Başdan Silme

Listedeki ilk düğümü kaldırır. İteratöre ek olarak, geçici bir işaretçi olan "temp" de oluşturulur. İteratör, baş düğümünden sonra gelen düğüme işaret ederken, temp işaretçisi de baş düğümüne işaret eder. Eğer baş düğüm doğrudan kaldırılırsa, listede hiçbir düğüm kalmayacağı için program hata verebilir. Eğer listede tek bir düğüm varsa, yani sadece baş düğümü varsa, hiçbir şey yapılmaz.

```cpp
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
```

---

#### Sondan Silme

Bu işlev, listenin son düğümünden bir önceki düğüme iteratör taşıyarak gerçekleştirilir. Daha sonra, kuyruk iteratöre atanır ve eski kuyruk silinir. Bu işlem sırasında, listede yalnızca tek bir düğümün olmadığından emin olunması gerekir.

```cpp
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
```

---

#### Sıralı Erişim ile Silme

Bu işlev, belirli bir veriye sahip olan düğümlerin kaldırılmasını sağlar. İlk olarak, listede yalnızca tek bir düğüm varsa işlem sonlandırılır. Belirli bir veriye sahip olan düğüm, listenin sonuna kadar gezilerek bulunur ve ilk rastlanan düğüm kaldırılarak işlem gerçekleştirilir.

```cpp
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
```

---

#### Takas

Takas işlevi iki farklı yöntem ile yapılabilir. Birinci yöntem doğrudan düğümün barındırdığı verileri takaslamaktır, ikinci yöntem ise düğümlerin listede sıralarını değiştirmektir. Birinci yöntemin gerçeklenmesi ikinci yönteme kıyasla daha basit görünsede durum her zaman böyle değildir. Örneğin düğümlerin başka listeler veya başka yapılar barındırdığı durumları göz önüne alalım, şöyle ki:

```cpp
struct Node{
    Node * next;
    int data[N];
    /*diğer veriler...*/
}
```
Bu durumda verileri takaslamak, verilerin boyutuna ve yapısal karmaşıklığına bağlı olarak oldukça maliyetli olabilir. Bu nedenle, düğümlerin takaslanması, daha verimli bir çözüm olabilir. Her iki yöntem de aşağıdaki kodlarla gerçeklenmiştir:


```cpp
template <typename T>
void SinglyLinkedList<T>::swap(Node<T> *first_element,
                               Node<T> *second_element)
{
    if (first_element == second_element)
        return;

    Node<T> *iter = head;

    /* Eğer takaslanmak istenen düğümlerden biri baş ya da kuyruk ile aynı ise doğrudan verileri takaslanyor.*/
    if (first_element == head || second_element == head ||
        first_element == tail || second_element == tail)
    {
        T temp_data = second_element->data;
        second_element->data = first_element->data;
        first_element->data = temp_data;
    }
    /* Eğer takaslanmak istenen düğümler aynı değil ve düğümler baş veya kuyruk ile aynı değilse düğümler takaslanıyor.
       İlk olarak takaslanmak istenen düğümlerin bir ilerisine işaret eden düğümler oluşturulur.
       Çünkü takaslama işlemi sırasında listenin devamına erişim bu şekilde sağlanmaktadır. 
       Daha sonra liste son halini alacak şekilde düğümler birbirine tekrar bağlanır ve işlem sonlanır.*/
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
Sıralama işlemi [kabarcık sıralama algoritması](https://tr.wikipedia.org/wiki/Kabarc%C4%B1k_s%C4%B1ralamas%C4%B1) kullanılarak gerçekleştirilmiştir. Döngü her yinelenişinde, liste elemanlarının doğru sıralamada olup olmadığını kontrol etmek için elemanların değerleri karşılaştırılır. Bir takas işlemi gerçekleşmediyse, liste doğru sıralamada olduğu anlaşılır ve işlev sona erer. Bu algoritma nispeten az düğüm sayısına sahip listeler için verimlidir ancak artan düğüm sayısı için başka sıralama algoritmaları tercih edilmelidir(Bu sadece bir örnek teşkil etmesi için yazılmıştır).

```cpp
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
```

---

#### Sıralı Erişim ile Eleman Almak

Belirli bir dizindeki düğümün verisini döndürmektedir. İşlevin aldığı argüman->(index), listenin baştan itibaren kaçıncı düğümün verisini almak istediğini belirtmektedir.Eğer istenilen sıra listenin mevcut uzunluğundan fazla ise 0 değerini döndürmektedir(Bu işlev test senaryoları oluşturabilmek için yazılmıştır, gerçeklenmesinde istisna fırlatılmalıdır ama belgenin odak noktası bu olmadığı için bu konuya değinilmemiştir). 

```cpp
template <typename T>
T SinglyLinkedList<T>::get_element(const size_t index) const
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
```

---

#### Yıkıcı(Destructor)

Bu fonksiyon, listedeki tüm düğümleri işgal ettiği belleği sisteme geri vererek serbest bırakır. Liste, baştan başlayarak yinelenir ve listenin sonuna ulaşana kadar tüm düğümler sisteme geri verilir. Eğer nesne doğrudan yok edilirse, new ile tahsis edilen bellek alanları sistemden geri verilmez ve programın yaşam süresi boyunca bellek sızıntısına neden olur.

```cpp
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    Node<T> *iter = head;
    Node<T> *delete_iter;
    while (iter)
    {
        delete_iter = iter;
        iter = iter->next;
        delete delete_iter;
    }
}
```

<h4 align="center"><a href="/linked_list">< Önceki Sayfa | <a href="../double_linked_list">Sonraki Sayfa ></a></a></h4>
