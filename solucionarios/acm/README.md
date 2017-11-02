# REGIONAL ACM-ICPC

La ACM-ICPC es la competencia de programación (on-site) más importante para alumnos universitarios.

Se realizan regionales (a nosotros nos toca SOUTHAMERICA-SOUTH (Argentina, Bolivia, Chile, Peru, Paraguay, Uruguay), donde los mejores equipos clasifican a la final, que se realiza en algún lugar del mundo (los sitios van cambiando año a año).

Cada regional tiene diferentes sedes (por país).

El sistema de clasificación depende de cada Región.

**SOUTHAMERICA-SOUTH** tiene 5 cupos (los 5 primeros que no sean de una misma facultad). 

Y luego hay 2 cupos a nivel SUPER-REGIONAL Latinoamerica, que se entregan luego de dar todos los cupos para cada Regional.

Uno es para el mejor equipo, que es de un país que no recibio cupo.

Y el segundo es para el mejor equipo (a nivel Latinoamerica), que todavia no clasifico.

[Más información en el sitio de ACM-ICPC](https://icpc.baylor.edu/)

### Cantidad de Problemas y temas comunes
*Aclaración: esto es algo observado por quien escribe en las regionales 2015-2016, por lo que puede ser no del todo exacto. Tomarlo como una idea, de lo que se van a encontrar*

Los problemas normalmente son **11**.

Los temas/dificultades comúnes son:
* **Easy/Trivial** siempre hay un problema pavo que cualquiera que sepa programar lo puede hacer. Aunque, por estar apurados, es el que más RTE o errores de compilación tiene.
* **AdHoc/Implementación** un problema que luego de pensarlo un poco sale fácil, ya sea utilizando la estructura de datos de la STL adecuada, o directamente programando lo que pide el problema.
* **Greedy**
* **Programación Dinamica**
* **Grafos**
* **Matemática** 
* **Geometría**
* **Flujo**
De estos últimos temas se pueden encontrar problemas que se solucionan con un algoritmo o idea de esos temas.

O es más común que sea, mezclando temas de ambos, tener que utilizar una dinámica, luego de calcular algo.

Para una mejor idea de cuales son los temas... **ENTRENAR REALIZANDO LAS REGIONALES ANTERIORES!**

## Entorno Bombonera (o... que tiene la VM?)

En las regionales en Argentina (y creo que el resto de los países en Latinoamerica tambien lo usan), se utiliza el sistema BOCA como juez, y la máquina virtual [Bombonera](http://www.bombonera.org/) para que utilicen los equipos.

*NOTA DEL AUTOR: Lo que sigue en las siguientes líneas es un poco de memoria de las regionales del 2015 y 2016, por lo que puede tener algunos errores.*

Para que no se choquen con el entorno paso a nombrar algunas de sus características:

### Sistema Operativo: Ubuntu 16.04
Esto es lo primero que se chocan los equipos acostumbrados a usar Windows, si nunca usaron un Ubuntu, les recomiendo usarlo antes, para al menos saber con lo que se van a encontrar.

### Compiladores
Para compilar Linux viene por defecto con ***gcc*** y ***g++*** (compiladores C y C++ respectivamente).
Importante: si queremos compilar en C++11, normalmente en la versión de g++ que tiene Ubuntu no funciona la option `-std=c++11`, pero funciona `-std=c++0x`.
```shell
g++ -std=c++0x {file} -o {compiled_file}
```
Para **python** está su versión **2.7**, pero creo que últimamente tambien se encuentra su versión **3.x**.

Nunca metimos un problema con **Java**, así que no puedo confirmar sus compiladores, pero creería que se utiliza *OpenJDK*.

Si quieren utilizar ***Pascal***, me apiado en sus almas (?).

### Editores e IDES
Tienen varias opciones, voy a nombrar las que utilizamos nosotros, seguramente queden algunas afuera. Tengan en cuenta que todo lo que instala Ubuntu por defecto, sigue estando.

* [**GEDIT**](https://wiki.gnome.org/Apps/Gedit) el editor de texto visual por defecto que tiene Ubuntu. Es solo eso, editar texto. Seguramente este `nano` y `vim` accesible por la consola.
* [**Sublime Text**](https://www.sublimetext.com/) editor de texto moderno, permite compilar, autocompletado, etc. Personalmente, es mi favorito para utilizar con C++. Tengan en cuenta al querer compilar en C++11 lo que dije más arriba, para su ayuda, pueden generar con [este archivo]( elrejunte/sublime_snippets/C++11.sublime-build) una nueva opción de build. (Tools->Build System->New Build System).
* [**Geany**](https://www.geany.org/) es una editor de texto con algunas de las características de Sublime, tiene algunos botones más visuales, se pude decir que se parece un poco a Zinjai. Tiene mejores herramientas de debuggin que Sublime Text.
* [**Eclipse**](https://www.eclipse.org/) el IDE mas utilizada para Java, se que funciona para *C++* y *Python*, pero no lo he utilizado nunca con esos lenguajes. No puedo confirmar que versión van a tener instalada.

Esos son los que me acuerdo, cosas que puede ser que estén pero no estoy seguro: CodeBlocks y NetBeans.

Estoy seguro que en la página de Bombonera hay un archivo `install.sh` con todo el software que instala. 
