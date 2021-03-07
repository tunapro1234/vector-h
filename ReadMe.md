# Basit bir vektör implementasyonu
Sınavlardan sonra debug ve release için ikiye ayırabilirim
<br>

daha eklenebilecek çok özellik var (indexe ekleme, ters çevirme, sıralama) yapar mıyım bilmiyorum.

sıralama gibi bir özelliği eklemek için operator overloading güzel olurdu ama onun yerine key alacakmışım gibi görünüyor
`bool vector_##TYPE##_sort(vector_##TYPE##_t *self, TYPE* (*key_func)(TYPE*, TYPE*));`

bununla birlikte swap fonksiyonu da güzel giderdi. Özellikleri ekledikten sonra kullanması eğlenceli olabilir

<br>
vektörün kapasitesi dolunca kapasiteyi reallocla 2 katına çıkarıyor
<br>

## Kullanım
```c
#include "vector.h"

vector_t(int);

int main(){
    /* kapasitesi 10 * 4 olan bir vektör oluşturduk*/
    vector_int_t v1 = vector_int_init(10);
    vector_int_push_back(&v1, 20);
    printf("%d\n", *vector_int_get(&v1, 0));
    return 0;
}
```
vector_t(type) tan sonra ; gerekmiyor ama olsun.

sonradan oluşturulan structlar için de çalışır herhalde.







