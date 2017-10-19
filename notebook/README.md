# {notebooke_name}

Notebook del Equipo TheRejointSet (antiguamente El Rejunte) para utilizar en competencias de Programación.
Conjunto de código, estructuras y funciones útiles. Y tambien algunos solucionarios.
Le ~~robamos~~ debemos mucho al notebook [El Diego](https://github.com/mvpossum/eldiego) de Caloventor en Dos (equipo de la UNR).

# Instrucciones para agregar material al Notebook.

## Agregar una sección

1. Crear carpeta con título de la sección.
2. Crear archivo `.tex` dentro de la carpeta, con el nombre de la sección. Por ejemplo: `seccion/seccion.tex`.
3. Este archivo `.tex` debe tener una estructura similar a los archivos de las otras secciones. De no saber hacerlo, dejarlo vacío.
4. Agregar en el archivo `notebook.tex`:
```latex
\input{./secciones/seccion/seccion.tex}
```

## Agregar código a una sección, Agregar una sub-sección.

1. Crear archivo con la extensión correspondiente. Por ej: `.cpp` o `.py`.
2. Agregar en el archivo de la seccion `seccion.tex` el codigo Tex correspondiente para agregarlo. ***NOTA: Siempre tomar como ejemplo los archivos ya generados. Si no se lo sabe hacer, dejar al menos el archivo fuente.***

## Link útil

[Tutoriales de Latex](https://www.latex-tutorial.com/tutorials/)
