# Bağlantılı Liste(Linked List)

Bağlantılı Liste, her bir düğümün başka bir düğüme referans olduğu veri yapısıdır. Bu veri yapıları, dinamik boyut, verimli ekleme ve çıkartma gibi bazı avantajlar sağlar, sıralı erişim vardır, düğümler arasında gezinebilmek için en az bir işaretçi(pointer) gerektirir ve gerçeklenmesinde kaynak sızıntısına sebep olabilecek programlama hataları gibi bazı tehlikeleri de içerir. Birçok farklı bağlantılı liste yapısı mevcuttur. İşte sık karşılaşılan bazı yapılar:

- Tek Yönlü Bağlantılı Liste(Singly Linked List): Tek yönlü hareketin mümkün olduğu veri yapısıdır.
- Çift Yönlü Bağlantılı Liste(Doubly linked list): Çift yönlü hareketin mümkün olduğu veri yapısıdır. 
- Dairesel Bağlantılı Liste(Circular linked List): Listenin son öğesinin ilk öğesine işaret ettiği, tek veya çift yönlü harekete imkan veren veri yapısıdır. 
- Sıralanmış Bağlantılı Liste(Sorted Linked List): Bir ölçüte göre verilerin sıralı bulunduğu veri yapısıdır.
- Hibrit Bağlantılı Liste(Hybrid Linked List): Birden fazla bağlantılı liste türünün özelliklerini barındıran, ihtiyaç doğrultusunda farklı bağlantılı listelerin özelliklerini alarak sahip olunan zayıf yönleri en az indirmeyi hedefleyen veri yapılarıdır.
- Atlamalı Bağlantılı Liste(Skip Linked List): Listede etkili bir şekilde arama, ekleme ve silme işlemine olanak sağlar. Temel işlevler O(n) değil, O(log n)`dir. 
- (Unrolled Linked List): Bir dizi(array) ve bağlantılı listeyi beraber kullanan yapıdır. Bağlantılı listenin faydalarını korurken verileri toplu bir şekilde saklayıp ek yükten kurtulmayı hedefler.

Tipik olarak bağlantılı listelerin temel işlevleri; düğümler arasında gezinebilme(traversing), ekleme ve silme işlemleridir. bağlantılı listelere müzik çalarlar, internet gezintisinde ardışık girdiğimiz web siteleri arasında dolaşma, dosya sistemleri ve metin düzenleyicilerde geri alma/yeniden yapma(undo/redo) işlemlerinde uygulanabilir yapılardır.

<h4 align="center"><a href="../giris">< Önceki Sayfa | <a href="singly_linked_list/">Sonraki Sayfa ></a></a></h4>
