## Gabriel Spranger Rojas - 201710406
**Compilar:** `g++ -std=c++17 main.cpp`

## Análisis

Todas las operaciones implementadas del _Double Linked List_, corren en `O(1)`, dado que se hace un trabajo constante que no depende del número de elementos en la lista.

En el caso del cache, hay dos operaciones importantes: `cache[key] = value` y `cache.find(key)`. La primera, corre en tiempo constante. La segunda también, aunque en tiempo promedio, esto se debe a que si existen colisiones, se tendrá que iterar por cada elemento del bucket; sin embargo, esto es muy raro. 

## Fundamentación

En esta implementación del **LRU y FIFO cache**, se usó un hash table (`std::unordered_map`) y una lista doblemente enlazada. El key insertado en el cache, pasaba por el hash y este devolvia un value, el cual era la dirección del nodo de la lista doblemente enlazada que contiene el key-value. La lista doblemente enlazada se actualiza de tal manera que el valor más usado (_Most Recently Used_) es igual al _head_ de la lista y el valor menos usado (_Least Recently Used_) es igual al _tail_ de la lista. Las operaciones necesarias para mantener ese orden en la lista doblemente enlazada es `deleteByAddress` (`O(1)`) y `pushFront` (`O(1)`). El acceso a la dirección del nodo en la lista doblemente enlazada se hace en `O(1)`, ya que es un _hash table_ y como el valor que se encuentra en el _bucket_ respectivo es la dirección de un nodo, el acceso al nodo también se hace en `O(1)`, ya que es un acceso directo. De esta manera, todas las operaciones sobre el cache se mantienen en tiempo constante, manteniendo la eficiencia que se necesita.
