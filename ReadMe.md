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
    /* kapasitesi 10 * 4 olan bir vektör oluşturduk*/
    vector_int_t v1 = vector_int_init(10);
    vector_int_push_back(&v1, 20);
    printf("%d\n", *vector_int_get(&v1, 0));
    return 0;
}
```
vector_t(type) tan sonra ; gerekmiyor ama olsun.

sonradan oluşturulan structlar için de çalışır herhalde.



