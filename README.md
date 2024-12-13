# IMT2565FinalProyect

Este repositorio contiene la implementación de Dijkstra ocupando heaps y 
Fibonacci heaps.

## Archivos
- main.c: contiene el flujo del programa.
- heap.c: contiene la estructura de los heaps.
- fibonacci-heap-c: contiene la estructura de los fibonacci heaps.
- dijkstra.c: contiene el algoritmo de Dijkstra con fheaps y heaps.
- test-fibonacci-heap.c: contiene los test con los que se probó el correcto funcionamiento del fibonacci heap.

## Parámetros

En el archivo main.c están:
- bool fiboheap: true si se quiere ocupar los fheaps, false para ocupar los heaps.
- int MAX_DEGREE: el máximo grado del fheap.
- int start: nodo raíz.
- int end: opción para imprimir el camino más corto desde start a end

## Formato
El archivo con el grafo debe ser .txt y tener el siguiente formato:
``` 
|1| NÚMERO_DE_NODOS
|2| NÚMERO_DE_ARISTAS
|3| t(e_1) h(e_1) c(e_1) 
|4| t(e_2) h(e_2) c(e_2) 
|5| ...
|6| t(e_|E|) h(e_|E|) c(e_|E|) 
```
Los nodos están enumerados desde el 1 hasta el NÚMERO_DE_NODOS

## Ejecución

Se deben compilar los archivos .c y correr el archivo main dando dos argumentos 
``./main inputfile.txt outputfile.txt``