# Veri Yapıları Nedir? 

Veri yapıları: Belirli bir düzende veriyi **depolama(Storing)** , veriye **erişim(Retrieving)** , veriyi **düzenleme(Organizing)** ve veriyi **işleme(Processing)** için tasarlanır. Birçok yaygın veri yapısı vardır; Dizi(Array), Ağaç(Tree), Çizge(Graph), Hash Table... Yaygın yapıların birçoğu modern dillerde yerleşik olarak bulunmakta veya dil toplulukları tarafından desteklenmektedir. C++ için bkz: [Standard Template Library(STL)](https://en.cppreference.com/w/cpp/container). Bu yapıların hepsi birbirine karşı üstün olduğu noktalar vardır. Yapı, sistemin isterlerine göre tasarlanır. Amaç en uygun yapıyı elde etmektir. Ölçütler aşağıdaki başlıklar şeklinde tanımlanabilir:

- ***Ölçeklenebilirlik(Scalable)*** : Artan veri miktarı için veriyi verimli bir şekilde işleyebilme.

- ***Performans(Performance)*** : Veriler üzerinde gerçekleştirilen manipülasyonların(Data manipulation) verimliliği.

- ***Depolama(Storage)*** : Verileri sonradan kullanabilmek için ayrılan alan verimliliği.

- ***Karmaşıklık(Complexity)*** : Yapı ile etkileşime girerken gerçekleşen her bir süreç için gereken kaynağın matematiksel çözümlenmesi.

> **Note**: Hash Table tamlamasının kaynaklarda türkçe karşılığı malesef yok.

---

"Kodun, veriye göre tasarlanmasını şiddetle tavsiye ediyorum, yapılan tam tersi olsada ve bence git'in oldukça başarılı olmasının nedenlerinden biri de budur... Aslında iddia ettiğim bir şey var: kötü bir programcı ile iyi bir programcı arasındaki fark, kodun mu yoksa veri yapıları ve onların ilişkilerini mi daha önemli olduklarını görmeleridir. Kötü programcılar kodla, iyi programcılar veri yapıları ve onların ilişkileri ile ilgilenirler."

<div style="text-align: right; color:#352335 ; font-weight:bold;">Linus Torvalds <a href="https://lwn.net/Articles/193245/">29 Temmuz 2006</a></div>

---

# Algoritma Analizi

Algoritma analizi bir işlevin çalışma süresinin başından sonuna kadar gereken depolama, zaman ve diğer tüm kaynakların incelenerek sürecin karmaşıklık ve kaynak tüketimi hesaplamalarının yapılması, bu hesaplamalar sonucunda algoritmanın, sonlu girdi durumu için verimliliği ortaya konmasıdır. Açığa çıkarılmış tüm bilgi doğrultusunda yapılan karşılaştırmaların sonucunda en uygun seçeneğe ulaşılabilir. Karşılaştırmalar üç ana başlık altında yapılır:

- **En kötü durum analizi(Worst-case analysis):**
  *Girdi kümesindeki bütün değişkenler için en masraflı senaryo maliyetidir.*
- **Ortalama durum analizi(Avarage-case analysis):**
  *bir algoritmanın rastgele dağılmış girdilerle performansını analiz etmeyi amaçlayan bir yöntemdir. Bu analizde, girdilerin ortalama maliyeti hesaplanmak yerine, girdilerin rastgele bir örneklemi üzerinde hesaplama yapılır.*
- **En iyi durum analizi(Best-case analysis):**
  *Girdi kümesindeki değişkenlerin herbirinin işlenme süresince karşılaşılan en düşük maliyetdir.*

Bu aşamada karşımıza bilgisayar bilimlerinde son derece önemli olan iki kavram ortaya çıkar; **zaman karmaşıklığı(Time complexity)** ve **alan karmaşıklığı(Space complexity)**. Zaman karmaşıklığı gerçek zamanlı sistemler(Real-time systems), gömülü sistemler(Embedded systems) ve makine öğrenmesi(Machine Learning) uygulama alanlarında ön plandadır. Örneğin oyunlar, kontrol sistemleri, arama algoritmaları ve sıralama algoritmları. Alan karmaşıklığında ise durum daha farklıdır. Çünkü işlem ve hafıza gücünün son derece arttığı bu dönemde bile bazı sistemler, günümüzdeki teknolojilere kıyasla daha zayıftır. Özellikle havacılık ve uzay alanında kullanılan teknoloji, sertifikasyon gibi nedenlerden dolayı hala 90'lı yılların sonunda üretilmiş, yer yer içerisinde 5-20 mb boyutlarında olan teknolojileri kullanmaktadır. Bu gibi sistemlerde alan ve zaman karmaşıklığı son derece önem arz etmektedir. İster analiz aşamasında tüm zaman ve alan isterleri neredeyse kesin sınarlar ile belirlenir. Veri yapılarının tasarımı, gerçeklenecek algoritmaların zaman ve alan karmaşıklığının üzerinde etkilidir. 

## $Big-O \ Notation$

Bir işlevin veya sistemin artan veri miktarına orantılı olarak maliyet değişimi göstergesidir. Big-O, işlevin/sistemin ne kadar maliyetli olduğunu doğrudan açıklamayı değil matematiksel düzeyde anlayışın ve iletişimin kolaylaşmasını sağlar.

- **Big O (O):** Algoritmanın çalışma veya alan karmaşıklığının üst sınırını(en kötü durum) gösterir.
- **Big Omega $(\Omega)$:** Algoritmanın çalışma veya alan karmaşıklığının alt sınırını(en iyi durum) gösterir.
- **Big Theta $(\Theta)$:** Algoritmanın çalışma veya alan karmaşıklığının ortalamasını gösterir.

> **Note**: Big-O Notation`nun türkçeye çevirisi[^1]: "Büyük O gösterimi" olarak yapılmış ama bu ifadenin yeterince açıklayıcı olduğunu düşünmüyorum, bu yüzden doğrudan ingilizcesini kullanmayı tercih ettim.

[^1]: [Vikipedi-Büyük O gösterimi](https://tr.wikipedia.org/wiki/B%C3%BCy%C3%BCk_O_g%C3%B6sterimi).

#### Karmaşıklık Düzeyleri

Karmaşıklık düzeyleri en azdan en çoğa doğru aşağıda ufak kod parçacıklarıyla gösterilmiştir:

> **Note**: $n$ => Veri miktarı.


| Karmaşıklık | $n = 10, \space p = 4$ | $n = 100, \space p = 4$ |
|----------|----------|----------|
| **Sabit(Constant): $O(1)$**| $1$ | $1$ |
| **Logaritmik(Logarithmic): $O(log \space n)$** | 3 | 6|
| **Karekök(Square Root): $O(\sqrt{n})$** | 3 | 10 |
| **Doğrusal(Linear): $O(n)$** | 10 | 100 |
| **Doğrusal-Logaritmik(Linearithmic): $O(n \space log \space n)$** | 20 | 400 |
| **İkinci Dereceden(Quadratic): $O(n^2)$** | 100 | 10000 |
| **Polinomsal(Polynomial): $(n^p)$** | 10000 | 100000000  |
| **Üstel(Exponential): $(2^n)$** | 1024  | 1.2676506e+30 |
| **Faktöriyel(Factorial): $O(n!)$** | 3628800 | 9.332622e+157 |

---

- **Sabit(Constant): $O(1)$**

O(1) karmaşıklığı veri miktarından bağımsızdır ve en verimli düzeydir.
> $\(f(x) = 2\) \space \space \space \space \space   => O(1)$
```cpp
int foo(int bar, int baz){
    int qux = bar + baz;
    qux += bar - baz;
    return qux;
}
```

- **Logaritmik(Logarithmic): $O(log \space n)$**

Karmaşıklık düzeyi logaritmik orantıya sahip olaması artan veri miktarından çok az etkilenmesini sağlar. Maliyet açısından oldukça verimlidir. Sıralı veri yapılarında arama işlemleri gibi uygulamalarda sıklıkla karşılaşılır. bkz: [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)
> $\(f(x) = log2(x) + 1\) \space \space \space \space \space   => O(log \space n)$
```cpp
void foo(int bar){
    while (bar > 0){  
        bar /= 2;  
    }
    std::cout << bar << std::endl;
}
```

- **Karekök(Square Root): $O(\sqrt{n})$**

O(√n) karmaşıklık düzeyi, veri miktarı artışına kıyasla daha yavaş bir artış gösterir. Bu, veri miktarının tamamının işlenmemesi durumlarında karşımıza çıkabilir. Örneğin, yalnızca belirli bir özelliğe sahip verilerin aranması veya benzer verilerin de dahil edilmesi durumlarında kullanılabilir.
> $\(f(x) = \sqrt{n} + 1 \) \space \space \space \space \space   => O(\sqrt{n})$
```cpp
int foo(const std::vector<int> &vec, int bar){
    for(std::size_t i = 0; i < std::sqrt(vec.size()); i++){
        if(vec[i] == bar)
            retrun i;
    }
    return -1
}
```

- **Doğrusal(Linear): $O(n)$**

O(n) karmaşıklığında maliyet, veri miktarı ile ters orantılıdır.
> $\(f(x) = x + 1\) \space \space \space \space \space   => O(n)$

```cpp
int foo(std::vector<int> &vec){

    int bar = 0;
    for(const auto &i : vec){
        bar += i;
    }
    --bar;
    
    return bar;
}
```

- **Doğrusal-Logaritmik(Linearithmic): $O(n \space log \space n)$**

Maliyet, veri miktarının doğrusal artmasına rağmen logaritmik bir oranda artar ve verimliliğini koruyabilir.
> $\(f(x) = x * log2(x)\) \space \space \space \space \space   => O(n log \space n)$

``` cpp
void foo(std::vector<int> &vec){
    for (std::size_t i = 0; i < vec.size(); i++) {
        for (std::size_t j = 1; j < vec.size(); j *= 2) {
            vec[i] += vec[j];
        }
    }
}
```

- **İkinci Dereceden(Quadratic): $O(n^2)$**

Doğrusal yapılara kıyasla çok daha hızlı büyür. Maliyet, veri miktarı artışından karesel olarak etkilenir. İç içe döngülerde(nested loop) sıkça rastladığımız bir karmaşıklıktır. Her iç içe döngü $O(n^2)$ değildir.
> $\(f(x) = x^2\) \space \space \space \space \space   => O(n^2)$
```cpp
void foo(std::vector<int> &vec){
    for(std::size_t i = 0; i < vec.size(); i++){
        for(std::size_t j = 0; j < vec.size(); j++){
            vec.psuh_back(j);
        }
    }  
}
```

- **Polinomsal(Polynomial): $(n^p)$**

Polinomsal büyüme, veri mikarı ve verinin nasıl işlendiğiyle ilişkilidir. Algoritmanın nasıl gerçeklendiği ile alakalıdır. Aslında ikinci dereceden ve kübik( $O(n^3)$ ) düzeylerinide kapsar. Karmaşıklık düzeyi $O(1)$ ile $O(\infty)$ arasında olabilir.
> $\(f(x) = x^y + ...\) \space \space \space \space \space   => O(n^p)$
```cpp
void foo(std::vector<int> &vec){
    for (std::size_t i = 0; i < vec.size(); i++) {
        for (std::size_t j = 0; j < vec.size(); j++) {
            for (std::size_t k = 0; k < vec.size(); k++) {
                for (std::size_t x = 0; x < vec.size(); x++) {
                ...                               
                }
            }
        }
    }
}
```

- **Üstel(Exponential): $(2^n)$**

Veri miktarı ve işlem sayısı çok daha hızlı artar. Bkz: [Hücre Bölünmesi](https://www.youtube.com/watch?v=SEejivHRIbE)
> $\(f(x) = 2^x + 2\) \space \space \space \space \space   => O(2^n)$
```cpp
void foo(int bar, int baz) {
  std::size_t count = 0;
  for(std::size_t i = 0; i < std::pow(bar,baz); i++){
    count++;
  }
  std::cout << count << std::endl;
}
```

- **Faktöriyel(Factorial): $O(n!)$**

Faktöriyel karmaşıklığı az veri miktarı ile çalışsa bile zaman ve alan tüketimi devasadır. 
$5! = 120$ \
$10! = 3628800$ \
$15! = 1307674368000$ \
$20! = 2432902008176640000$

> $\(f(x) = x!\) \space \space \space \space \space   => O(n!)$
```cpp
void foo(int bar) {
    for(unsigned int i = 0; i < bar; i++){
       foo(bar - 1);
    }
}
```

<h4 align="center"><a href="/">< Önceki Sayfa | <a href="../linked_list">Sonraki Sayfa ></a></a></h4>
