# Justificación de órdenes — Obligatorio 1

## Ejercicio 1
- La letra exige ALTA y BUSCAR en O(log K) y RANGO en O(log K + R), siendo K
  la cantidad de piezas registradas en la colección consultada y R la
  cantidad de piezas reportadas.
- Usé un árbol AVL (ArbolAVL<T>), instanciado una vez para monedas
  (long long) y otra para pinturas (string), como pide la letra, un
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
- Usé una tabla de hash abierta , un arreglo
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
- Usé el algoritmo de Kahn visto en la clase 6, con un heap de mínimos
  (MinHeapPar) y una lista de adyacencia (GrafoLA). Sirve Kahn porque cada módulo
  lleva la cuenta de las dependencias que le faltan (su grado de entrada). Cuando llega a 0 el módulo
  está listo, y si hay un ciclo esos módulos nunca llegan a 0, así que detecto el
  ciclo comparando cuántos salieron con V.
- Para elegir el próximo módulo uso un heap, porque sacar el mínimo de los
  listos cuesta O(log V). Recorrer todos los listos en cada paso sería O(V) por
  paso y O(V²) en total. El heap guarda pares (prioridad, número) porque el orden
  tiene dos criterios: primero la menor prioridad y, si empatan, el menor número.
  El "MinHeap" del ejercicio 3 guarda un solo "long long" y no sirve para eso, así
  que hice un heap nuevo para no tocar el del ejercicio 3.
- Representé el grafo con una lista de adyacencia y no con una matriz, porque una 
  matriz de V x V ocuparía O(V²) de espacio, mucho más que el O(V + A) que se pide.
- Armar el grafo: leer las prioridades es O(V). Por cada dependencia agrego la
  arista al inicio de la lista del origen (O(1), sin recorrer la lista) y sumo
  uno al grado del destino. Si la agregara al final, tendría que recorrer la
  lista cada vez y se me iría de orden. En total son O(V + A).
- Al principio meto al heap los módulos con grado 0, son a lo sumo V inserciones
  de O(log V).
- El heap es un árbol con los elementos en posiciones seguidas del arreglo, así
  que su altura es O(log V). Flotar y hundir suben o bajan de a un nivel, por lo
  que insertar y sacar son O(log V).
- Bucle principal: cada módulo entra al heap una sola vez (cuando su grado llega a
  0, y el grado solo baja) y sale una sola vez, así que son a lo sumo V entradas y
  V salidas de O(log V): O(V log V). Al sacar un módulo recorro su lista de
  dependientes, y como cada arista está en la lista de un solo origen, recorro
  cada arista una sola vez en todo el programa: O(A).
- Guardo el orden en un arreglo y no lo imprimo a medida que sale, porque si hay
  un ciclo la letra pide imprimir solo "imposible" y ningún módulo. Al final
  comparo "cantOrden" con V (O(1)): si son iguales imprimo los V módulos (O(V)),
  y si no, "imposible".
- Total de tiempo: O(V + A) + O(V log V) = O((V + A) log V).
- Espacio: la lista de adyacencia (V + 1 punteros y A aristas), tres arreglos de
  tamaño V y el heap de capacidad V. En total O(V + A).

## Ejercicio 5
- Usé Kruskal con un heap (MinHeapPar), que guarda (costo, número de sendero),
  y conjuntos disjuntos MFSet. Elegí el heap porque Kruskal necesita recorrer
  los senderos del más barato al más caro, y con el heap solo extraigo los que
  necesito, siempre el menor en O(log E), porque corto al tener V - 1 senderos
  elegidos.
- Con V = 1 imprimo 0 sin hacer nada más, en O(1).
- Leer los E senderos: guardo origen y destino en dos arreglos indexados por el
  número de sendero, y meto (costo, número) al heap. Son E inserciones de
  O(log E): O(E log E).
- Bucle principal: saco senderos del heap de a uno, como mucho E extracciones de
  O(log E): O(E log E). Corto apenas tengo V - 1 senderos elegidos, porque un
  árbol que conecta V refugios tiene exactamente V - 1. En el peor caso igual
  extraigo los E (por ejemplo, si el grafo no es conexo), así que el orden no
  cambia: el corte solo evita trabajo de más.
- Por cada sendero uso unir, que pregunta si los extremos ya están conectados
  y, si no, los junta. Uso las dos optimizaciones que pide la letra:
  compresión de caminos (al buscar el representante, todo el camino queda
  colgando de la raíz) y unión por altura (el árbol más bajo cuelga del más
  alto). Con las dos, la altura de los árboles es O(log V) y cada operación
  cuesta casi O(1), así que no agrega orden por encima del heap.
- Crear el MFSet cuesta O(V). Cuando el grafo es conexo,  así que ese
  costo queda dentro de O(E); si el grafo no tiene senderos suficientes para
  conectar a todos, la respuesta es "imposible" y ese costo es lo único que
  queda por encima de la lectura de los E senderos.
- Total de tiempo: O(E log E) por las inserciones y las extracciones del heap,
  más casi O(E) por las operaciones del MFSet y O(V) por crearlo. En todos los
  casos con solución, O(E log E).
- Espacio: el heap (capacidad E), los arreglos de origen y destino (E cada uno)
  y el MFSet (dos arreglos de V + 1). La recursión de "representante" usa una
  pila de O(log V), por la altura de los árboles. En total O(V + E).
- El costo total lo acumulo en un long long, porque con hasta 10^5 refugios y
  costos de hasta 10^6 la suma puede superar los 32 bits.
