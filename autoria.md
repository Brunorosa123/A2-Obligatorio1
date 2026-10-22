# Declaración de autoría — Obligatorio 1

## Ejercicio 1
- El TAD ArbolAVL AvlImp.cpp esta basado en el patron de insercion recursiva,
  las rotaciones (simples y dobles) y el manejo del campo altura visto en
  01_avl_insercion.cpp (material de la primera clase de AVL, clase-01-avl-main).
  - Diseño de rango(): originalmente lo tenia imprimiendo con cout directo
  adentro del TAD. La IA me sugirio pasar una funcion (callback) en vez de
  imprimir directo, para que el arbol no dependa del formato de salida de
  este ejercicio puntual. Lo evalue y decidi dejarlo asi.

## Ejercicio 2
- Para hacer el TAD OpenHash (tads/OpenHash.cpp) me basé en lo visto en el curso
  y en parte en clase-02-hash-cerrado-main. Aunque es hash cerrado, me sirvió
  para estas partes: esPrimo y primoSup, el constructor con "esperados", la
  función de hash, cantElementos con cantidadElementos() y el destructor. 
  Lo adapté a hash abierto con una lista enlazada por posición, según las diapositivas de Tablas de Hash.
- Uso de IA: me aconsejó dimensionar la tabla con un
  largo primo >= 1,5·N para mantener el factor de carga en ~0,67 sin rehash.
  Lo analicé y decidí dejarlo 

## Ejercicio 3
- TAD MinHeap basado en 01_minheap.cpp de la clase 3
  (clase-03-heap-main). Lo tome como guia y adapte los valores segun lo que necesitaba.
- pase de int a long long porque el costo total puede superar 32 bits.
- Cambié las fórmulas de padre, hijo izquierdo e hijo derecho respecto de
  clase en base 1 ya que así me resulta mejor para entenderlo.
- Uso de IA: me señaló que mis fórmulas eran de base 1 sobre un arreglo
  que arrancaba en 0 y me pasó la versión corregida, que revisé y apliqué.

## Ejercicio 4
- Algoritmo de Kahn basado en kahn.cpp de la clase 6 (clase-06-kahn-main).
  Lo adapté: en lugar de la cola (Cola.h) uso un heap de mínimos (MinHeapPar),
  porque entre los módulos listos tengo que sacar primero el de menor prioridad
  y, si empatan, el de menor número. Además guardo el orden en un arreglo y
  comparo cuántos salieron con V para detectar el ciclo e imprimir "imposible".
- TAD Grafo (tads/Graph.cpp) basado en Grafo.h de la clase 6 (clase-06-kahn-main):
  la clase Arista, la lista de adyacencia GrafoLA, agregarArista con inserción
  al inicio y vecinosNodo. Adaptado: quité el costo de la arista y la búsqueda de
  repetidos (para que agregar sea O(1)), usé n + 1 posiciones para numerar los
  nodos desde 1 y agregué el destructor.
- TAD MinHeapPar (tads/MinHeapPar.cpp) basado en el Heap de la clase 4
  (clase-04-multiestructura, main.cpp). Adaptado, de máximo a mínimo, con un par
  (prioridad, número) en lugar del ticket y con flotar y hundir con while.
- Uso de IA:
  - Me explicó la idea del ejercicio (Kahn con un heap) y las alternativas para
    ordenar por dos criterios (clave codificada, heap de pares, comparador).
    Decidí hacer un heap de pares (ver bitácora del 2026-10-10).

## Ejercicio 5
- Algoritmo de Kruskal basado en kruskal.cpp de la clase 7 (clase-07-kruskal-main):
  el bucle que saca el sendero mínimo, une los extremos si no cierra ciclo y corta
  al tener V - 1 senderos. Adaptado: el heap guarda (costo, número de sendero) y
  origen y destino van en dos arreglos, el costo total es long long y agregué el
  caso V = 1 y la salida "imposible".
- TAD MFSet (tads/MFset.cpp) basado en MFSet.h de la clase 7. Adaptado: la
  unión pasa de por tamaño a por altura, los elementos se numeran desde 1 y
  se agregó el destructor.
- Reutilicé el MinHeapPar del ejercicio 4 (costo en "prioridad", número de
  sendero en "numero").
- Uso de IA : me ayudo a entender el plan del ejercicio y corregirme algunos detalles del
main que no me dejaba pasar todas las pruebas.

