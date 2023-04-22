# Vektör(Vector)

![vector](img/vector.png)

Vektör yani dinamik diziler aynı türde verileri saklayan veri yapısıdır. Yapı temelde Diziye(Array) benzemektedir. Vectör`ü Diziden ayıran özellik, derleme zamanında sabit bir boyuta sahip olan statik dizilerin aksine, dinamik diziler programın gereksinimlerine bağlı olarak çalışma zamanında büyüyebilir veya küçülebilir. Bu esneklik sayesinde, tahsis edilen belleğin yeterliliği konusunda duyulan endişenin önüne geçer.

---

#### Sınıf Yapısı

Sınıf uygulaması resimde göründüğü gibi kapasite ve veri büyüklüğü ilişkisi üzerinden yönetilir. Büyüklük kapasiteyi aştığında yapı yeniden boyutlandırılır ve kapasite artırılır. Öğelere erişim [] operatorü ve atama işlemi = operatörü ile yapılır. 

| İşlev                      | Big O    |
| -------------------------- | -------- |
| Sona Ekleme                | $O(1)$   |
| Araya Sokma                | $O(n)$   |
| Silme                      | $O(n)$   |
| Takas                      | $O(1)$   |
| Sıralama                   | $O(n^2)$ |
| Tersine Çevirme            | $O(n)$   |
| Yeniden Boyutlandırma      | $O(n)$   |
| Yeniden Kapasitelendirme   | $O(n)$   |
| Listedeki Öğeleri Kaldırma | $O(1)$   |


#### Kurucular

```cpp
// Öntanımlı Kurucu
template <typename T>
Vector<T>::Vector() : m_capacity(0), m_size(0), data(nullptr) {}

// Parametreli Başlatıcı, Kapasaite parametre ile belilenir.
template <typename T>
Vector<T>::Vector(std::size_t capacity)
    : m_capacity(capacity), m_size(0), data(new T[capacity]) {}

// Parametreli Başlatıcı, Kapasite belirlenir ve kapasite fill_value ile başlatılır.
template <typename T>
Vector<T>::Vector(std::size_t capacity, T fill_value)
    : m_capacity(capacity), m_size(capacity), data(new T[capacity]) {
  for (std::size_t i = 0; i < capacity; i++) {
    data[i] = fill_value;
  }
}

// Parametreli Başlatıcı, Kapasite belirlenir ve first-last aralığı fill_value ile başlatılır.
template <typename T>
Vector<T>::Vector(std::size_t capacity, std::size_t first, std::size_t last,
                  T fill_value)
    : m_capacity(capacity), m_size(capacity), data(new T[capacity]) {
  for (std::size_t i = first; (i <= last) && (i <= capacity); i++) {
    data[i] = fill_value;
  }
}

// Liste Başlatıcı
template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : m_capacity(init.size()), m_size(init.size()), data(new T[init.size()]) {
  std::size_t i{0};
  for (auto &item : init) {
    data[i] = item;
    i++;
  }
}
```

#### Yeniden Kapasitelendirme

Vektöre yeni bir element eklendiğinde, mevcut öğe sayısı kapasiteye eşitse, yeni elementi yerleştirmek için vektörün yeniden boyutlandırılması gerekir. Sınıfın özel erişimli olan reallocate üye fonksiyonu, öğe sayısı kapasiteyi aştığında tetiklenir ve veri kabının her zaman bir önceki kapasitenin iki katı olacak şekilde yeniden boyutlandırılır. İki katı olması nedeni bir optimizasyon tekniğidir. Yeniden kapasitelendirme işleminde sırası ile vektör için yeni alan tahsis edilir, eski vektör yeni vektöre bire bir kopyalanır ve eski vektörün işgal ettiği bellek sisteme geri verilir. Bu süreç kopyalama ve bellek yönetimi işlemleri dolayısıyla maliyetlidir. Eğer her defasında eklenen element kadar alan tahsis edilmek istenirse, bu işlemin tekrar ve tekrar yapması gerektiği anlamına gelir ki bu vektörden beklenen performansın karşılanamayacağı durumlara sebebiyet verebilir. İki katı katı bir kural değil sadece genel eğilimdir. Sistemi isterleri doğrultusunda en uygun kat sayı belirlenir.

```cpp
template <typename T>
void Vector<T>::reallocate() {
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
```

#### Tersine Çevirme

Bu işlev vektörün ters sıralama gerektiren süreçler için gerekli olabilir. Örn: şifreleme, küçük/büyük sıralama, yeni bir dizilim elde etme ihtiyacı...

```cpp
template <typename T>
void Vector<T>::reverse() {
  for (std::size_t i = 0; i < (m_size / 2); i++) {
    swap(data[i], data[m_size - i - 1]);
  }
}
```

#### Yeniden Boyutlandırma

Yeniden boyutlandırma, vektörün m_size üyü değişkeninin yeniden ayarlanmasını sağlar. Yeniden kapasitelendirmeden farkı kapasiteyi küçültebilmesidir. Bu operasyon sırasında veri kaybı yaşanabilir. İhtiyaç duyulmayan belleğin geri verilmesi için kullanılabilir.

```cpp
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
```

#### Araya Ekleme ve Silme 

Araya ekleme ve silme işlemleri için dikkat edilmesi gereken nokta bu operasyon sırasında her bir elementin bir yana kaydırılmasıdır. Silme işleminde boyut değişmez.

```cpp
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
    reallocate();
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
```

#### Listedeki Öğeleri Kaldırma

Sınıfın erişilebilir boyutu sıfırlanır.

```cpp
template <typename T>
void Vector<T>::clear() {
  m_size = 0;
}
```

<h4 align="center"><a href="/array">< Önceki Sayfa | <a href="/stack">Sonraki Sayfa ></a></a></h4>