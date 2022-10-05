# UICompiler

Un pequeño programa de consola que actua como intermediario del traductor de PyQT. Permite su uso sobre directorios, realizando una compilación de los .ui recursiva sobre todos los ficheros del directorio y en directorios hijos. Además es seguro su uso sobre ficheros que no son .ui, evitando borrar su contenido.

uso:

> UIComp.exe RUTA_PYUIC RUTA_A_COMPILAR[-l RUTA_QTDESIGNER RUTA_ARCHIVO [intervalo]]

> **RUTA_PYUIC:** Ruta al ejecutable pyuic6.exe\
> **RUTA_A_COMPILAR:** Ruta del fichero o directorio que se desea compilar\
> **-l:** Modo "link"\
> **RUTA_QTDESIGNER:** Ruta del designer.exe\
> **RUTA_ARCHIVO:** Ruta del archivo .py o .uy actualmente seleccionado\
> **intervalo:** Intervalo en milisegundos trascurrido entre cada comprobación de los ficheros

Lo ideal es usarlo como herramienta externa en pycharm, de modo que la ruta a compilar sea $ProjectFileDir$ y la ruta del archivo seleccionado, $FilePath$.

Ejemplo de uso como herramienta externa en pycharm:

> **Program:** Ruta completa al UIComp_x64.exe\
> **Arguments:** "RUTA_PYUIC" "$ProjectFileDir$" -l "RUTA_QTDESIGNER" "$FilePath$"\
> **Working directory:** $ProjectFileDir$

NOTA: Poner las rutas en los argumentos entre comillas dobles, de modo que si hubiese espacios en ellas, no sería un problema.
