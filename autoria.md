# Declaración de autoría — Obligatorio 1

> **Instrucciones** (borrar esta sección antes de entregar): declarar para cada ejercicio
> las fuentes utilizadas: código discutido o desarrollado en clase, recursos web (con URL)
> y uso de herramientas de IA generativa (herramienta, consulta y uso dado, según los
> lineamientos de Uso de IA de la letra). Si no se usaron fuentes externas, indicarlo
> explícitamente. Los fragmentos de terceros o generados por IA deben además señalarse
> con comentarios en el código fuente. La omisión de fuentes puede considerarse plagio.

## Ejercicio 1
- Implementación íntegramente propia, sin fuentes externas.
- El TAD ArbolAVL (avl.cpp) esta basado en el patron de insercion recursiva,
  las rotaciones (simples y dobles) y el manejo del campo altura visto en
  01_avl_insercion.cpp (material de la primera clase de AVL, clase-01-avl-main).
  - Diseño de rango(): originalmente lo tenia imprimiendo con cout directo
  adentro del TAD. La IA me sugirio pasar una funcion (callback) en vez de
  imprimir directo, para que el arbol no dependa del formato de salida de
  este ejercicio puntual. Lo evalue y decidi dejarlo asi.

## Ejercicio 2
- Implementación íntegramente propia, sin fuentes externas.
- Uso de IA: me aconsejó dimensionar la tabla con un
  largo primo >= 1,5·N para mantener el factor de carga en ~0,67 sin rehash.
  Lo analicé y decidí dejarlo 

## Ejercicio 3
- TAD MinHeap basado en 01_minheap.cpp de la clase 3
  (clase-03-heap-main). Lo tome como guia y adapte los valores segun lo que necesitaba.
- pase de int a long long porque el costo total puede superar 32 bits.
- Cambié las fórmulas de padre, hijo izquierdo e hijo derecho respecto de
  clase (pos/2, 2*pos y 2*pos+1 en lugar de (pos-1)/2, 2*pos+1 y 2*pos+2), ya que así
  me resulta mejor para entenderlo.

  

## Ejercicio 4
- Implementación íntegramente propia, sin fuentes externas.

## Ejercicio 5
- Implementación íntegramente propia, sin fuentes externas.

