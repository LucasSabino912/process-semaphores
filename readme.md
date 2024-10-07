# Grupo 25: Laboratorio 2 de Sistemas Operativos.
## Integrantes:
- Thomas **Bunzli**
- Jose **Castro**
- Gabriel **Franicevich**
- Lucas **Sabino**


## Descripción
Este repositorio contiene un emulador de xv6, sumadas 4 nuevas syscalls y el programa ***pingpong*** que consta de 2 procesos, *ping* y *pong* muestra uno como proceso activo mientras el otro es pausado y luego se intercambian los roles.
Usa
## Ejecución

- Para abrir xv6 lo que hay que hacer es:
```bash
make
```

- Para ejecutar pingpong:
```bash
pingpong {int}
```

- Funcion sorpresa:
```bash
peladoValdez
```

## Funciones 

La única función extra que creamos fue "sem_en". Lo que hace es encontrar el primer semáforo libre y retornar el número del semaforo correspondiente.
Para eso utiliza la función sem_open (que retorna -1 si un semáforo está ocupado, o 1 si está libre) hasta que encuentra un semáforo libre.
En el resto de las funciones, fuimos haciendo pequeños cambios hasta lograr el funcionamiento correcto.


## Problemas que tuvimos
Nos costaron más que nada los errores chicos, tales como retornar -1 en la función sem_encontrar, en lugar de el número del semáforo encontrado.

Siguiendo con los errores chicos, decidimos eliminar muchas warnings, porque había varias inútiles, y que rompían el funcionamiento del programa. Un ejemplo de warnings "inútiles" era la que utilizabamos en sem_open cuando abría un semáforo que ya estaba en uso(no tiene sentido, ya que si queríamos abrir más de un semáforo, siempre saltaba esta warning).

Un gran problema que tuvimos, fue que no podíamos encontrar por qué sem_encontrar no ejecutaba. El error terminó siendo que no estaba agregado a todas las carpetas que debería, y para agregarlo, lo que hicimos fue usar la función "grep" para ver en que archivos faltaba.

Otro gran problema fue la función sem_up, que por despiste, en vez de despertar las funciones, el programa hacía sleep. Esto nos llevó un par de horas arreglarlo, ya que pensábamos que lo que estaba mal era la lógica del ping pong y no el archivo semaforos.

El último gran problema fue ping pong y ver cómo tratar y separar tanto el hijo como el padre. Lo que más nos llamó la atención fue la gran diferencia que puede haber al cambiar el orden de los sem_up con los sem_down.
