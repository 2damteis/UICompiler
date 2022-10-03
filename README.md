# UICompiler

Un pequeño programa de consola que actua como intermediario del traductor de PyQT. Permite su uso sobre directorios, realizando una compilación de los .ui recursiva sobre todos los ficheros del directorio y en directorios hijos. Además es seguro su uso sobre ficheros que no son .ui, evitando borrar su contenido.

uso:

> UIComp.exe RUTA_PYUIC RUTA_A_COMPILAR[-w[intervalo]]

RUTA_PYUIC: Ruta al ejecutable pyuic6.exe\n\
RUTA_A_COMPILAR : Ruta del fichero o directorio que se desea compilar\n\
-W: Modo "watch". Si se activa, el programa continuará en segundo plano comprobando a cada intervalo si los archivos han sido modificados. Si es así, los compila de nuevo.
intervalo: Intervalo en milisegundos trascurrido entre cada comprobación de los ficheros."

RUTA_PARA_COMPILAR puede ser un .ui o un directorio.
