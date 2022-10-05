# UICompiler

Un pequeño programa de consola que actua como intermediario del traductor de PyQT. Permite su uso sobre directorios, realizando una compilación de los .ui recursiva sobre todos los ficheros del directorio y en directorios hijos. Además es seguro su uso sobre ficheros que no son .ui, evitando borrar su contenido.

## Uso desde terminal

```sh
$ UIComp.exe RUTA_PYUIC RUTA_A_COMPILAR [-l RUTA_QTDESIGNER RUTA_ARCHIVO [intervalo]]
```

**RUTA_PYUIC:** Ruta al ejecutable pyuic6.exe (
**RUTA_A_COMPILAR:** Ruta del fichero o directorio que se desea compilar\
**-l:** Modo "link"\
**RUTA_QTDESIGNER:** Ruta del designer.exe\
**RUTA_ARCHIVO:** Ruta del archivo .py o .uy actualmente seleccionado\
**intervalo:** Intervalo en milisegundos trascurrido entre cada comprobación de los ficheros

Lo ideal es usarlo como herramienta externa en PyCharm, de modo que la ruta a compilar sea `$ProjectFileDir$`, y la ruta del archivo seleccionado `$FilePath$`.

## Uso en PyCharm

En los ajustes (`Control+Alt+S`) añadir como External Tool con los siquientes parámetros:

- **Program:** Ruta absoluta a UIComp_x64.exe
- **Arguments:** `"CAMBIAME_RUTA_PYUIC" "$ProjectFileDir$" -l "CAMBIAME_RUTA_QTDESIGNER" "$FilePath$"`
- **Working directory:** `$ProjectFileDir$`

Es aconsejable en  "Advanced Settings" del editor de herramienta externa deshabilitar "Open console for tool output" para evitar que abra la consola cada vez que ejecutamos la herramienta.

**IMPORTANTE**: Las rutas en los argumentos deben estar entre comillas dobles para evitar posibles problemas por haber espacios en medio.
