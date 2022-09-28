# UICompiler

Un pequeño programa de consola que actua como intermediario del traductor de PyQT. Permite su uso sobre directorios, realizando una compilación de los .ui recursiva sobre todos los ficheros del directorio y en directorios hijos. Además es seguro su uso sobre ficheros que no son .ui, evitando borrar su contenido.

uso: UiComp.exe RUTA_PYUIC RUTA_PARA_COMPILAR

RUTA_PARA_COMPILAR puede ser un .ui o un directorio.
