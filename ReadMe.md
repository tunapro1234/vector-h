# Basit bir vektör implementasyonu (C89)
Sınavlardan sonra debug ve release için ikiye ayırabilirim
<br>

Bir iki özellik daha eklenebilir (merge sort).

<br>
vektörün kapasitesi dolunca kapasiteyi reallocla 2 katına çıkarıyor
<br>

## Kullanım
```c
#include "vector.h"

create_vector_t(int);

int main(){
    /* kapasitesi 10 * 4 olan bir vektör oluşturduk */
    vector_int_t v1 = vector_int_init(10);
    vector_int_push_back(&v1, 20);
    printf("%d\n", *vector_int_get(&v1, 0));
    return 0;
}
```
vector_t(type) tan sonra ; gerekmiyor ama olsun.

sonradan oluşturulan structlar için de çalışır herhalde.

## Fonksiyonlar

#### vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity);
heapte vector oluşturur 

#### vector_##TYPE##_t vector_##TYPE##_init(size_t capacity);
3 pointer kopyalasak nolur sanki
 
#### void* vector_##TYPE##_destroy(vector_##TYPE##_t *self);
free(self->start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 
#### size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self);
vektörün kapasitesinin kaç elemanlık olduğu
 
#### size_t vector_##TYPE##_length(const vector_##TYPE##_t *self);
vektörün içinde kaç eleman olduğu
 
#### size_t vector_##TYPE##_size(const vector_##TYPE##_t *self);
vektörün içinde kaç eleman olduğu ama daha seksi
 
#### vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self);
vektörü heape taşır (eski vektör yok ediliyor)
 
#### vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self);
vektörü stacka taşır gibi bir şey
 
#### vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self);
vektörü kopyalar, yeni kopya heapte
 
#### vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self);
vektörü kopyalar
 
#### bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self);
vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 
#### bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data);
 	vektörün sonuna eleman ekler
 
#### bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data);
vektörün sonuna eleman ekler, pointer alıyor
 
#### TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index);
vektörün indexinci elemanının pointerını döndürür
 
#### TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index);
vektörün indexinci elemanının değerini döndürür

<br> 
 
#### void vector_##TYPE##_bubble_sort(vector_##TYPE##_t *self, TYPE* (*key_func)(TYPE*, TYPE*));
elemanları bubble sort algoritması ile sırala (büyük olan elemanı belirlemek için fonksiyon pointerı alıyor)
 
#### void vector_##TYPE##_swap(vector_##TYPE##_t *self, size_t index1, size_t index2);
iki indeksteki elemanları değiştirir
 
#### bool vector_##TYPE##_insert_p(vector_##TYPE##_t *self, size_t index, TYPE *value);
verilen adresteki datayı verilen indekse kopyalar
 
#### bool vector_##TYPE##_insert(vector_##TYPE##_t *self, size_t index, TYPE value);
verilen datayı indekse kopyalar
 
#### void vector_##TYPE##_shift_r(vector_##TYPE##_t *self);
vektörün elemanlarını sağa kaydırır (sonuncu eleman başa geliyor)
 
#### void vector_##TYPE##_shift_l(vector_##TYPE##_t *self);
vektörün elemanlarını sola kaydırır (baştaki eleman sola geliyor)
 
#### void vector_##TYPE##_reverse(vector_##TYPE##_t *self);
vektörü ters döndürür
 


