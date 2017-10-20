# Solucionarios

Esta carpeta es para ir subiendo solucionarios de las competencias que hagamos. Un solucionario es una explicación simple de la solución implementada en el problema.
Siempre tratar de hablar de código lo menos posible, pero entendiendo la solución de manera *abstracta*.

## Formato a utilizar con Markdown `.md`

```markdown
# Nombre de la competencia
[nombre del link](link a la competencia o problemas)

## Problema 1/A - Nombre del Problema
Breve explicación de la solución del problema.
Complejidad de la solución.

## Problema 2/B - Nombre del Problema
Breve explicación de la solución del problema.
Complejidad de la solución.

```
Y así con todos los problemas.
[Guia Rapida de Markdown](https://help.github.com/articles/creating-and-highlighting-code-blocks/)


## Agregando código al `.md`

Para agregar partes de código y que sea más legible lo ideal es ponerlo de la siguiente manera.
```markdown
    ```{lenguaje}
    pedazos de codigo
    mas codigo.
    etc.
    ```
```
Se muestra un ejemplo.

### Ejemplo con C++
```markdown
    ```c++
    #include <math.h>
    for(int i=0;i < n; i++){
        s
    }
    ```
```
Que se ve de la siguiente manera:
```c++
  #include <math.h>
  for(int i=0;i < n; i++){
      s
  }
```

## Notas

* En caso de existir más de una solución, no tener miedo de explicarla.

* Si encontraron la solución en otro solucionario en ingles. Traducir y linkear.

