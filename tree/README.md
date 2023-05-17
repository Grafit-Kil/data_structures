# Ağaç(Tree)

Ağaçlar, düğümlerle birbirine bağlanan ve hiyerarşik bir yapı oluşturan veri yapılarıdır. Ağaçlar, hiçbir düğümün bir üst düğüme bağlamadığı acyclic (döngüsüz) yapılar olarak tanımlanır. Yani, bir ağaç veri yapısı kendini tekrar etmez ve yapısı üzerinde tek seferde sonsuz hareket mümkün değildir. Yapı, bir kök düğüm(root node) ve düğümleri takip eden çocuklardan(child) oluşur. Düğümün son bulduğu noktalar diğer bir deyişle çocuğu bulunmayan atalr, yaprak(leaf) düğüm olarak adlandırılır. Bkz:

```cpp
1------->  7
        /  |  \  
2--->  9   0  15   
      /|        \  
3--> 3 1         21
                 |\ 
4--------------> 5 17

---------------------------------------------------
Bu Ağaç yapısınının özellikleri
- Kök Düğüm => 1 adet {7}
- Çocuk Düğüm => n-1 adet {3,1,9,0,5,17,21,15}
- Ata Düğüm => 5 adet {7,9,15,21}
- Yaprak Düğüm => 5 adet {3,1,0,5,17}
- Derinilk => 4
```

---

#### Diğer Ağaç Yapıları

Her biri başka bir faydaya odaklanmış farklı ağaç türleri vardır. İşte bazı türler:

- **İkili Arama Ağacı(Binary Search Tree):** Sol çocuğun ata düğümden küçük, sağ çocuğun ise ata düğümden büyük olduğu ve bir atanın en fazla iki çocuğa sahip olduğu yapıdır.

```cpp
/* Bu elemanlar sırası ile listeye eklenmiştir! */
Elemanlar: 22 90 59 35 73 53 82 9 60 63 80 33 13

1-------> 22
       /      \
2---> 9        90
       \       /
3----> 13    59
          /      \
4------> 35       73
       /    \   /    \
5---> 33    53  60    82
                 \    /
6--------------> 63  80

```

- **AVL(Georgy Adelson-Velsky ve Evgenii Landis):** Ağacın derinliği eklenen her element ve çıkarılan her element için dengelendiği ikili ağaç yapısıdır. Ağacın sağ ve sol alt ağaçları için derinlik farkının en fazla bir olduğunu garanti eder.

```cpp
/* Bu elemanlar sırası ile listeye eklenmiştir! */
Elemanlar: 22 90 59 35 73 53 82 9 60 63 80 33 13

1----------> 59
         /        \
2-----> 22          73
      / \         /  \
3--> 9   35      63   82
      \   \     /    /  \
4----> 13  53  60  80    90
                   
```

- **Kırmızı-Siyah Ağaç(Red-Black Tree):** Kırmızı-Siyah Ağaç, sıralı düzende olan ve AVL gibi dengeli bir yapıdır. Daha çok arama ve ekleme odaklı olmasına rağmen genel amaçlar için de kullanılır. AVL'den farkı ise denge unsuru ikili (0-1/Kırmızı-Siyah) sistemle sağlanır ve AVL yapısının sahip olduğu her ekleme ve çıkarma işleminden sonra ağacın düzenlenme durumu söz konusu değildir.

```cpp
/* Bu elemanlar sırası ile listeye eklenmiştir! */
Elemanlar: 22 90 59 35 73 53 82 9 60 63 80 33 13

S = Siyah
K = Kırmızı

1-----------------> 59|S
                 /        \
2----------> 35|S         82|S|
            /    \         /    \
3-----> 22|K    53|S     63|K   90|S|
      /     \           /    \
4--> 9|S    33|S      60|S   73|S
        \                        \
5------> 13|K                    80|K
```

- **B-Tree:** B-Tree, sabit bir derinliğe sahip bir veri yapısıdır. Her ata düğüm, istenilen sayıda çocuğa sahip olabilir (bu sayı, gereksinimlere bağlı olarak belirlenir). B-Tree'nin arama, ekleme ve silme işlemlerinin çalışma zamanı tutarlıdır ve bu işlemlerin karmaşıklığı O(logn) olarak ifade edilir. Bu özelliği, B-Tree'nin çekici kılmasına katkıda bulunur. Sabit derinliğe sahip olması, herhangi bir düğüme erişilmeye çalışıldığında oluşabilecek maksimum maliyetin belirli olduğu anlamına gelir.

```cpp
/* Bu elemanlar sırası ile listeye eklenmiştir! */
Elemanlar: 22 90 59 35 73 53 82 9 60 63 80 33 13
Derinlik => 3

            +---------------59---------------+
            |                                |
   +-----[22,35]-----+              +-----[63,82]-----+
   |        |        |              |        |        |
[9, 13]   [33]      [53]          [60]    [73,80]    [90]
```

- **Ayarlı Ağaç(Splay Tree):** Ayarlı ağaç yapısının odak noktası arama işlemidir. Aranan öğeler kök düğüme daha yakın olacak şekilde tekrar düzenlenirler. Şayet sık aranan verilere erişimin vurgulandığı bir yapıya ihtiyaç varsa tercih edilebilecek yapılardandır. Aksi halde ayarlama işlemi maliyeti diğer yapılara kıyasla verim düşmesine sebep olur.

> Not: "Splay Tree" için, zaten kısıtlı olan kaynaklarda "Yayvan Ağaç" gibi bir çevir yapılmış. Bu çeviri, ağacın yapısı ile uyuşmamaktadır.

<h4 align="center"><a href="/queue">< Önceki Sayfa | <a href="/tree/binary_search_tree">Sonraki Sayfa ></a></a></h4>