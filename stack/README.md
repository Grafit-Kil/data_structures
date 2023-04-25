# Yığın(Stack)

![img](/stack/img/stack.png)

Yığın, son giren ilk çıkar (LIFO) prensibine dayanan bir veri yapısıdır. Bu veri yapısının gerçekleştirilmesinde birden fazla yöntem kullanılabilir. Yığın genellikle ekleme, kaldırma ve en son eklenen elemana erişim işlevlerini içerir. Yığın, son eklenen eleman dışında hiçbir elemana doğrudan erişime izin vermez. Bu, yığının doğasına aykırıdır. Yığın veri yapısı, işlev çağrı yığınları, geri alma işlemleri, hafıza yönetimi ve benzeri uygulamalarda yaygın olarak kullanılmaktadır. Vektör/dinamik dizi ve bağlı listeler, yığın veri yapısını gerçekleştirmek için farklı yaklaşımlar sunmaktadır. Dinamik diziler, bağlı liste uygulamasına kıyasla daha az bellek tüketmesine karşın yeniden bellek tahsisi(Reallocation) çalışma zamanı maliyetine sahiptir. Başka bir uygulama ise sabit boyutlu diziler(Array) ile uygulanmasıdır. Sabit boyutu sayesinde işaretçi için ayrılan bellek ve yeniden tahsis maliyetinden kurtarırken, diğer yandan çalışma zamanında ki esnekliği yok etmektedir. Bu yazıda Vektör ve Bağlı Liste ile nasıl uygulandığına yer verilmiştir.

| İşlev              | Big O  |
| ------------------ | ------ |
| Ekleme             | $O(1)$ |
| Kaldırma           | $O(1)$ |
| Tepe Değere Erişim | $O(1)$ |
| Boyut              | $O(1)$ |

---

#### Dinamik Diziler ile Yığın Sınıfı

```cpp
template <typename T>
class Stack {
 public:
  Stack();
  Stack(std::size_t capacity);
  void push(const T value);
  std::optional<T> pop();
  bool empty();
  std::size_t size() const;
  const T &top() const;

 private:
  void recapacity();

  std::size_t m_capacity;
  std::size_t m_size;
  std::unique_ptr<T[]> data;
};
```

#### Çift Yönlü Bağlı Liste ile Yığın Sınıfı 

```cpp
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
```

#### Ekleme

Bu işlev, yığının tepesine yeni bir element ekler. Bağlı Liste uygulamasında, her yeni element için fazladan `sizeof(T*) * 2` bayt alan tahsis edilirken Dinamik dizilerde ise kapasite her dolduğunda mevcut element kadar koplayalama maliyeti söz konusudur. 

```cpp
// Dinamik Dizi
template <typename T>
void Stack<T>::push(const T value) {
  if (m_size == m_capacity) {
    recapacity();
  }
  data[m_size] = value;
  m_size++;
}
// Çift Yönlü Bağlı Liste
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
```

#### Kaldırma

Kaldırma(Pop) işlevi, listeye en son eklenen element için bir operasyondur. Uygualama C++17 ile standartlara ile dahil olan [optional](https://en.cppreference.com/w/cpp/utility/optional) başlık dosyasında bulunan `std::optional` şablon(Template) yapısı kullanılarak gerçeklenmiştir. Optional bir işlevin geri dönüş değeri olup olmadığını belirlememizi sağlar. Kaldırma işlevini kullanmadan önce elemente erişip gereken işlemleri yaptılır. Burada element kaldırılır ve kaldırılan değerin bir kopyası geri döndürülür.

> **NOT:** Bu yöntem sadece düşünsel bir yoldur. Kopyalanması maliyetli türler için böyle bir kod fazladan maliyet demektir.

```cpp
// Dinamik Dizi
template <typename T>
std::optional<T> Stack<T>::pop() {
  T temp;
  if (m_size != 0) {
    temp = data[m_size - 1];
    m_size--;
    return temp;
  }
  return std::nullopt;
}

// Çift Yönlü Bağlı Liste
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
```

#### Tepe Değere Erişim

Listenin tepesindeki(son giren) elementi döndürür.

```cpp
// Dinamik Dizi
template <typename T>
const T &Stack<T>::top() const {
  return data[m_size - 1];
}

// Çift Yönlü Bağlı Liste
template <typename T>
const std::optional<T> Stack<T>::top() const {
  if (head == nullptr) return std::nullopt;
  return head->data;
}
```

<h4 align="center"><a href="/vector">< Önceki Sayfa | <a href="/queue">Sonraki Sayfa ></a></a></h4>