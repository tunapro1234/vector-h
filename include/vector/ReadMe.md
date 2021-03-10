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

create_vector_t(int_t, int);

int main(){
    /* kapasitesi 10 * 4 olan bir vektör oluşturduk */
    vector_int_t v1 = vector_int_t_init(10);
    vector_int_t_push_back(&v1, 20);
    printf("%d\n", *vector_int_t_get(&v1, 0));
    return 0;
}
```
create_vector_t(type) tan sonra ; gerekmiyor ama olsun. (Artık gerekiyor)

sonradan oluşturulan structlar için de çalışır herhalde. (Çalışıyor)

## Fonksiyonlar

#### vector_##NAME##_t* vector_##NAME##_init_h(size_t capacity);
heapte vector oluşturur 

#### vector_##NAME##_t vector_##NAME##_init(size_t capacity);
3 pointer kopyalasak nolur sanki
 
#### void* vector_##NAME##_destroy(vector_##NAME##_t *self);
free(self->start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 
#### size_t vector_##NAME##_capacity(const vector_##NAME##_t *self);
vektörün kapasitesinin kaç elemanlık olduğu
 
#### size_t vector_##NAME##_length(const vector_##NAME##_t *self);
vektörün içinde kaç eleman olduğu
 
#### size_t vector_##NAME##_size(const vector_##NAME##_t *self);
vektörün içinde kaç eleman olduğu ama daha seksi
 
#### vector_##NAME##_t* vector_##NAME##_move_h(vector_##NAME##_t *self);
vektörü heape taşır (eski vektör yok ediliyor)
 
#### vector_##NAME##_t vector_##NAME##_move(vector_##NAME##_t *self);
vektörü stacka taşır gibi bir şey
 
#### vector_##NAME##_t* vector_##NAME##_copy_h(const vector_##NAME##_t *self);
vektörü kopyalar, yeni kopya heapte
 
#### vector_##NAME##_t vector_##NAME##_copy(const vector_##NAME##_t *self);
vektörü kopyalar
 
#### bool vector_##NAME##_extend_capacity(vector_##NAME##_t *self);
vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 
#### bool vector_##NAME##_push_back(vector_##NAME##_t *self, TYPE data);
vektörün sonuna eleman ekler
 
#### bool vector_##NAME##_p_push_back(vector_##NAME##_t *self, TYPE *data);
vektörün sonuna eleman ekler, pointer alıyor
 
#### TYPE *vector_##NAME##_get(vector_##NAME##_t *self, size_t index);
vektörün indexinci elemanının pointerını döndürür
 
#### TYPE vector_##NAME##_read(const vector_##NAME##_t *self, size_t index);
vektörün indexinci elemanının değerini döndürür

<br> 
 
#### void vector_##NAME##_bubble_sort(vector_##NAME##_t *self, TYPE* (*key_func)(TYPE*, TYPE*));
elemanları bubble sort algoritması ile sırala (büyük olan elemanı belirlemek için fonksiyon pointerı alıyor)
 
#### void vector_##NAME##_swap(vector_##NAME##_t *self, size_t index1, size_t index2);
iki indeksteki elemanları değiştirir
 
#### bool vector_##NAME##_insert_p(vector_##NAME##_t *self, size_t index, TYPE *value);
verilen adresteki datayı verilen indekse kopyalar
 
#### bool vector_##NAME##_insert(vector_##NAME##_t *self, size_t index, TYPE value);
verilen datayı indekse kopyalar
 
#### void vector_##NAME##_shift_r(vector_##NAME##_t *self);
vektörün elemanlarını sağa kaydırır (sonuncu eleman başa geliyor)
 
#### void vector_##NAME##_shift_l(vector_##NAME##_t *self);
vektörün elemanlarını sola kaydırır (baştaki eleman sola geliyor)
 
#### void vector_##NAME##_reverse(vector_##NAME##_t *self);
vektörü ters döndürür
 


