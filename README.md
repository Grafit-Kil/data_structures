# VERİ YAPILARI(DATA STRUCTURES)
---

## İçindekiler 

1. [Ön söz](#1-ön-söz)
   1. [Kullanınlan Araçlar ve Ortam](#başlarken)
2. [Veri Yapıları Nedir?](./giris/README.md/#veri-yapıları-nedir)
   1. [Algoritma Analizi](./giris/README.md/#algoritma-analizi)
3. [Bağlı Liste(Linked List)](./linked_list)
    1. [Tek Yönlü Bağlı Liste(Singly Linked List)](./linked_list/singly_linked_list)

---

## 1. Ön Söz

Bu belgenin ortaya çıkış amacı, veri yapıları konusundaki birçok belgenin dağınık olması ve çalışmalarım sırasında kullandığım birçok belgenin genel bir bakış kazanmak için yeterince açık olmamasıdır. Bu belge oluşturulurken birçok kaynağa başvurulmuştur ve her bir belge, liste ya da dipnot olarak paylaşılmıştır. Belgeleme çalışmasının yararlı olduğunu düşünüyorum ve öğrendiklerimi başka insanlarla paylaşmak istiyorum. Ancak, belirtmeliyim ki, sunum tamamen şahsi tasavvurumu yansıtmaktadır ve bu yüzden bu belge doğrudan referans olarak kullanılması hedeflenmez. Yanlışlar, eksiklikler veya iyileştirme konularında kendinizi katkı yapmaktan alıkoymayın. Belge, veri yapılarına giriş yapmadan önce ortam kurulumu ve kullanımı hakkında kısa bir rehber içermektedir. Umarım bu belge veri yapılarını keşfetme yolculuğunuzda size yararlı olur. İyi okumalar.

-------------------------
# Başlarken

## Kullanınlan Araçlar ve Ortam

Başlamadan önce, içerik hazırlanırken kullanlan bazı kaynak ve araçlardan bahsetmeliyim. Her bir yapının gerçeklenmesi(implementation) ve bazı kod parçacıklarının yazımı C++ ile yapılmaktadır. Programdaki bellek tahsisi(allocate), bellek sızıntısı(memory leak) ve ayrıntılı görselleştirimi için valgrind kullanılmaktadır. Testler Linux altında GNU/GCC ile yapılmaktadır, kodlar taşınabilir(portable) olma gayesi taşımaz. [Godbolt](https://godbolt.org/) ile veya yerel ortamda test edebilirsiniz. 

- Linux
- C++ (C++20) 
- GNU/GCC
- Valgrind

---
### GNU/GCC 

####  Ubuntu

```bash
sudo apt install build-essential
sudo apt-get install valgrind
```
#### Arch Linux

```bash
sudo pacman -S gcc
sudo pacman -S valgrind
```

#### Fedora

```bash
sudo dnf install gcc-c++
sudo dnf install valgrind # NOT: dnf ile sorun yaşamanız halinde veritabanını yum ile güncelleniyiz.
``` 
---

### Test

```cpp
/* test.cpp */
#include <iostream>

int main(){
	
	int *p1 = new int; 
	std::cout<<"*p1(sizeof(int)) [Tahsis edildi]\n";
	int *p2 = new int; 
	std::cout<<"*p2(sizeof(int)) [Tahsis edildi]\n";
	
	delete p1; 
	std::cout<<"*p1 [Sisteme geri verildi]\n";
	
	std::cout<<"*p2 artik baska bir bellek adresini gosteriyor ve p2 nin gosterdigi eski adresi kaybettik bkz: MEMORY LEAK\n";
	int foo{1};
	p2 = &foo;
	// artik p2 baska bir bellek adresini gosteriyor ilk tahsis ettigimiz adresi kaybettik.
	// p2 nin gosterdigi alan sisteme geri iade edilmedi bkz: memory leak 
	return 0;
}
```

##### Derleme ve Çalıştırma

```bash
g++ -o test test.cpp
./test
```
##### Çıktı:

```bash                                                 
*p1(int) [Tahsis edildi]
*p2(int) [Tahsis edildi]
*p1 [Sisteme geri verildi]
*p2 artik baska bir bellek adresini gosteriyor ve p2 nin gosterdigi eski adresi kaybettik bkz: MEMORY LEAK
```
##### Valgrind

```bash
valgrind --leak-check=full -s --track-origins=yes ./test
```
##### Valgrind çıktısı:

```bash
==18880== Memcheck, a memory error detector
==18880== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==18880== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==18880== Command: ./test
==18880== 
*p1(int) [Tahsis edildi]
*p2(int) [Tahsis edildi]
*p1 [Sisteme geri verildi]
*p2 artik baska bir bellek adresini gosteriyor ve p2 nin gosterdigi eski adresi kaybettik
==18880== 
==18880== HEAP SUMMARY:
==18880==     in use at exit: 4 bytes in 1 blocks
==18880==   total heap usage: 4 allocs, 3 frees, 73,736 bytes allocated
==18880== 
==18880== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==18880==    at 0x4843003: operator new(unsigned long) (vg_replace_malloc.c:422)
==18880==    by 0x1091E9: main (in /home/dosya_yolu/test)
==18880== 
==18880== LEAK SUMMARY:
==18880==    definitely lost: 4 bytes in 1 blocks
==18880==    indirectly lost: 0 bytes in 0 blocks
==18880==      possibly lost: 0 bytes in 0 blocks
==18880==    still reachable: 0 bytes in 0 blocks
==18880==         suppressed: 0 bytes in 0 blocks
==18880== 
==18880== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

***:warning: Burada 4 alan tahsisi(4 allocs) yapıldığı ve sadece 3` ü sisteme geri verildiğini ifade ediyor. Bu durum bellek sızıntıdır(memory leak).***
> \==18880==   total heap usage: 4 allocs, 3 frees, 73,736 bytes allocated


***:warning: Burada ise sızıntının olduğu yeri vermektedir(bizim durumumuzda main içerisinde).***
> \==18880==    by 0x1091E9: main (in /home/dosya_yolu/test)

<h4 align="center"><a href="./giris">Sonraki Sayfa ></a></h4>