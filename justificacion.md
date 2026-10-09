# Justificación de órdenes — Obligatorio 1

> **Instrucciones** (borrar esta sección antes de entregar): para cada ejercicio cuya
> letra plantea restricciones de órdenes (tiempo o espacio), justificar brevemente por
> qué la solución cumple, indicando qué estructuras de datos o algoritmos se utilizaron.
> Ejemplo: "La letra exige inserción en O(log n); usamos un min-heap sobre arreglo,
> donde flotar/hundir recorren a lo sumo la altura del árbol". Si un ejercicio no tiene
> restricciones de órdenes, indicarlo.

## Ejercicio 1
- La letra exige ALTA y BUSCAR en O(log K) y RANGO en O(log K + R), siendo K
  la cantidad de piezas registradas en la colección consultada y R la
  cantidad de piezas reportadas.
- Usé un árbol AVL (ArbolAVL<T>), instanciado una vez para monedas
  (long long) y otra para pinturas (string), como pide la letra: un
  único TAD, sin implementación distinta por colección. Al mantenerse
  balanceado (con rotaciones simples y dobles tras cada inserción), la
  altura del árbol queda en O(log K). ALTA y BUSCAR bajan por un único
  camino desde la raíz hasta el nodo correspondiente, sin recorrer el
  resto del árbol, por lo que son O(log K).
- RANGO recorre el árbol en orden pero podado: en cada nodo, solo baja a
  la izquierda si el extremo "desde" es menor a la clave del nodo, y solo
  baja a la derecha si "hasta" es mayor a esa clave. Esa poda descarta
  las ramas fuera del intervalo en O(log K), y el resto de las llamadas
  corresponde a los R nodos que efectivamente se reportan. Esto da
  O(log K + R) en total.

## Ejercicio 2
- Usé una tabla de hash abierta : un arreglo
  de buckets donde cada bucket es una lista enlazada de nodos con clave y
  contador. La clave de un cajón es un string de 26 caracteres con la cantidad
  de veces que aparece cada letra (obtenerClave). Dos palabras se componen con
  el mismo cajón cuando tienen las mismas letras la misma cantidad de veces, o
  sea, cuando dan la misma clave. Entonces todas las palabras de un cajón
  comparten un único nodo, y su contador dice cuántas son. Por eso ninguna
  operación depende de cuántas palabras comparten cajón: es un contador, no
  una lista que haya que recorrer.
- Registrar o consultar una palabra:
  - Armar la clave recorre la palabra una vez y toca 26 posiciones: O(L + 26)
    = O(L), porque el alfabeto es constante.
  - La función de hash recorre los 26 caracteres de la clave: O(1).
  - Buscar en el bucket recorre la lista comparando claves de 26 caracteres
    (O(1) cada comparación). El largo esperado de la lista es constante (ver
    factor de carga).
  - Insertar un nodo nuevo es agregarlo al inicio del bucket: O(1).
  Total O(L) promedio. Es promedio y no peor caso porque, si todas las claves
  cayeran en el mismo bucket, una operación costaría O(N); asumo que el hash
  dispersa bien las claves.
- Factor de carga: creo la tabla con un largo primo
  ≥ 1,5·N. Como leo N antes de registrar nada, puedo dimensionarla de entrada.
  Las claves distintas nunca superan N , así que λ ≤ N/(1,5·N). Está
  en el rango sano visto en clase, no hace falta rehash . 
  Buscar el primo cuesta O(√N)
  por candidato y hay pocos candidatos, despreciable frente a O(N).
- Última línea en O(1):
  - Cajones distintos: "cantElementos" se incrementa solo al crear un nodo
    nuevo y cantidadElementos() lo devuelve.
  - Cajón más grande: cada registro devuelve el contador actualizado de su
    cajón y en main lo comparo con "mayorCajon", O(1) extra por palabra.
  Al terminar imprimo esos dos valores sin recorrer la tabla ni las palabras.
- Total: N registros y Q consultas de O(L) promedio cada una (la suma de los
  L es el tamaño de la entrada), más O(N) para inicializar los buckets. Es
  lineal.

## Ejercicio 3
- Usé un Min Heap sobre un arreglo de long long con capacidad N. 
  Lo elegí porque en cada paso necesito sacar
  los dos archivos más chicos y volver a meter el nuevo; con un arreglo
  ordenado cada inserción costaría O(N) y el total O(N²).
- "insertar": pone el valor al final y lo hace flotar. Sube de a un nivel por
  iteración, a lo sumo la altura del heap: O(log N).
- "eliminarMinimo": lleva el último elemento a la raíz y lo hace hundir. Baja de
  a un nivel por iteración, comparando con dos hijos (O(1) por nivel), a lo
  sumo la altura: O(log N).
- La altura es O(log N) porque los elementos ocupan posiciones consecutivas del
  arreglo, sin huecos, así que los niveles se llenan de a uno.
- Algoritmo:
  1. Inserto los N tamaños: N · O(log N).
  2. Mientras quede más de un archivo: 2 eliminaciones + 1 inserción, O(log N),
     sumo los dos valores y acumulo el costo en O(1).
  3. Cada iteración saca 2 y mete 1, así que la cantidad baja de a uno: hay N-1
     iteraciones.
  Total: O(N log N) + (N-1) · O(log N) = O(N log N).
- Espacio: el heap arranca con N elementos y nunca crece, así que alcanza el
  arreglo de N posiciones. No uso otra estructura que crezca con N: O(N).
- Usé long long en el heap y en el acumulador porque el costo total puede
  superar los 32 bits.

## Ejercicio 4
- Sin restricciones de órdenes. / Justificación: ...

## Ejercicio 5
- Sin restricciones de órdenes. / Justificación: ...

