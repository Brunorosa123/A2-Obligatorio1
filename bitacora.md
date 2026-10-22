# Bitácora — Obligatorio 1

**Integrantes:** Bruno Rosa (318321)

## 2026-09-02 — Bruno Rosa
- Lei la letra del obligatorio completa, comprendi lo que es la bitacora, autoria y justificaciòn .
- Lei nuevamente el ej1 hasta comprenderlo completamente
- Lo primero que note fue que tengo que crear un solo tad Avl para las dos colecciones pedidas,en uno tengo que guardar las pinturas de tipo string y en el otro las monedas de tipo long long, por eso el uso de template.
- Como el catalogo llega hasta 10^12 por lo que tengo que usar long long y no int para las monedas.
- Entendi lo que buscan hacer las operaciones y pase a pensar como implementar el Tad Avl guiandome en las ppts y el material disp.
-Hoy no use IA


## 2026-09-14 — Bruno Rosa
- Termine de implementar el TAD ArbolAVL en AvlImp.cpp, todo en un solo archivo
  sin separar en .h. Como la letra no exigia hacer .h me parecio mas simple hacerlo de esa forma.
- Decidi que rango() no imprima directo, sino que reciba una funcion para
  hacerlo, asi el TAD queda mas independiente, esto fue una recomendacion de la IA, ya que yo lo estaba imprimiendo direct de rango, pero me convencio finalmente dejarlo como la IA me recomendo.
- Probé los 4 casos de ejemplo de la letra y anduvieron bien.
- Uso de IA: Claude, para pensar y corregir alguna fuincion especifica del TAD y para debuggear.

## 2026-09-15 — Bruno Rosa
- Al escribir "rango" para el ejercicio 1, me di cuenta de que la salida
  cambia según la colección: monedas imprime un número, pinturas un
  título. Pero el enunciado exige un único TAD ArbolAVL<T> genérico,
  sin una implementación distinta por colección.
- Al principio pensé en poner un if adentro del árbol (algo como "si T
  es long long hacer esto, si es string hacer lo otro"), pero eso rompe
  la idea de que el árbol sea genérico y no sepa nada de monedas ni
  pinturas.
- Busqué cómo hacer que una clase genérica en C++ ejecute algo distinto
  según quién la usa, sin tener que saber de antemano qué es. Le consulté
  a Claude y me explicó el mecanismo de puntero a función
  (void (*visitar)(const T&)): la idea es que quien llama a "rango" le
  pasa la función de impresión (imprimirMoneda o imprimirPintura), y
  el árbol solo la ejecuta sin saber qué hace.
  -Lo entendi y me parecio la mejor opción dejarlo asi

## 2026-09-18 — Bruno Rosa  
- Compilé y probé todos los casos del ejercicio 1, pasaron todos.        
- Empecé el ejercicio 2 ,creé el OpenHash.cpp.       
- Para el TAD me guié por el código de hash cerrado de clase (esPrimo,
  primoSup, constructor con "esperados", destructor).                     
- Idea para identificar el cajón: dos palabras comparten cajón si tienen
  las mismas letras la misma cantidad de veces, así que la clave es el
  conteo de las 26 letras  

## 2026-09-22 — Bruno Rosa
- termine el ejercicio 2
- Decisión: la función de hash recorre toda la clave (26 caracteres) y no
  corta en 10 como en clase, porque todas las posiciones distinguen un
  cajón de otro; si no, cajones que difieren solo al final colisionarían. 
- Decisión: tabla de largo primo >= 1,5·N, así el factor de carga no pasa de
  ~0,67 (rango sano 0,5~0,7 de las diapositivas) y no hace falta rehash. Esto me lo
  aconsejo la IA y opte por dejalo al haberlo analisado
- El cajón más grande lo voy actualizando en main con el contador que
  devuelve cada registro, para que la última línea sea O(1).  

## 2026-09-27 — Bruno Rosa
- Empecé el ejercicio 3 , creé MinHeap.cpp, lei
  01_minheap.cpp de la clase 3 del repo para darme una idea de como hacer el tad.
- Cambié los valores de int a long long porque el costo total puede
  superar 32 bits.
- Pense en sumar los dos mínimos, acumular el costo y reinsertar la suma
  hasta que quede un solo archivo.

## 2026-10-09 — Bruno Rosa
- Volvi a ver la grabación de cuando presentan el obligatorio y vi la explicación del ej4 nuevamente.
- Empecé el ejercicio 4, estuve evaluando si el tad que ya tenia de Min Heap del ej3 me servia y ademas 
evalue si realizar un tad de grafos como el de la clase 6 para el manejo de dependencias de los modulos.

## 2026-10-10 — Bruno Rosa
- Segui pensando el ejercicio 4
- Para el ejercicio 4 el heap tiene que elegir entre los módulos listos primero
  el de menor prioridad y, si empatan, el de menor número. Mi MinHeap del
  ejercicio 3 guarda un solo long long, así que no puede comparar con dos
  criterios.
- Alternativas que consideré:
  - Usar el mismo MinHeap y codificar prioridad y módulo en un solo número
    (prioridad * base + módulo, con base = V + 1). No hay que tocar ningún
    TAD, pero es algo que consulte con ayuda de la IA y no me termino de convencer.
  - Hacer un heap que guarde pares (prioridad, módulo) y compare los dos campos.
  - Un heap que reciba una función de comparación. Lo descarté por ser más
    trabajo y más difícil de explicar.
- Decidí hacer un heap nuevo de pares porque expresa las dos reglas de la letra directamente 
  como un "if" de dos pasos, sin cuentas que explicar. Me baso en el Heap de la clase 4
  (clase-04-multiestructura), que ya desempata por un segundo campo; lo adapté
  de máximo a mínimo y reemplacé el ticket por un par (prioridad, módulo).
- Lo hice en un archivo aparte y no modifiqué MinHeap.cpp para no romper el
  ejercicio 3, que depende de que guarde un long long.

## 2026-10-13 — Bruno Rosa
- Comence a pensar el ejercicio 5 , cree el tad MFset.cpp y pase a crear las firmas de las funciones
  que creo que necesitaré para el ejercicio.
- Evalue si debía crear otro tad maás, pero noté que el tad MinHeapPar.cpp ya me sirve para reutilizarlo en 
el ejercicio. Puedo guardar el costo del sendero en prioridad y el número de sendero en numero. 
Capacidad E.
- Analice y opte por seguir el siguiente flujo:
  Aristas: tres arreglos en main (origen[], destino[] y costo[]), indexados por el número de sendero. No hace falta clase Arista ni GrafoLA: Kruskal trabaja con la lista de senderos y no con vecinos.
  Leeo los E senderos y lleno los tres arreglos, y meto cada uno al heap (costo, índice).
  Saco del más barato al más caro.
  Para cada uno, unir(origen, destino): si devuelve true, lo mantengo y sumo su costo (en long long), si devuelve false, lo descarto porque cerraría un ciclo.
  Al final, si mantuvo V - 1 senderos imprimo el costo, si no, imposible. Con V = 1 imprimo 0.

## 2026-10-14 — Bruno Rosa
- Termine el ejercicio 5. Al escribirlo vi que el arreglo costo[] que había
  planeado no hacía falta, porque el costo del sendero ya viaja en el heap
  (prioridad): me quedé con origen[] y destino[].
- Decidí acumular el costo total en un long long, porque con hasta 10^5
  refugios y costos de hasta 10^6 la suma puede superar los 32 bits.
- Pasan los 22 casos de la cátedra.

## 2026-10-21 — Bruno Rosa
- Hice una revisión general del estado del obligatorio antes de entregar,Compilé los 5 ejercicios
y probe todas las pruebas nuevamente. Todas pasaron.


