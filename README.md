# Ludo en C++

Trabajo final de fin de curso de Programación I de la carrera de Ingeniería de Software de la UPC.

## Objetivos del trabajo 🚀

- **ABET – EAC - Student Outcome 1**: La capacidad de identificar, formular y resolver problemas complejos de ingeniería mediante la aplicación de los principios de la ingeniería, la ciencia y las matemáticas.
- **ABET – CAC - Student Outcome 1**: Analizar un problema de computación complejo y aplicar principios de computación y otras disciplinas relevantes para identificar soluciones.

## Pre-Requisitos 📋

- [_Microsoft Visual C++ 2019 - Build Tools_](https://aka.ms/buildtools)

### Ajustes del compilador ⚙️

- CLI/CLR (```/clr```)
- Name EXE File (```/Fe```)
- Include Paths (```/I ${workspaceFolder}/includes/```)
- Object File Name (```/Fo${workspaceFolder}/build/obj/```)
- File Path (```${workspaceFolder}/main.cpp```)

### Ajustes del _linker_ ⚙️

- Linker (```/link```)
- ```user32.lib```
- Output Path (```/out:${workspaceFolder}/build/main.exe```)

## Proceso de Ejecución ⚙️

Se pueden utilizar los archivos binarios precompilados, disponibles en GitHub como _releases_.

Para compilar el proyecto, se puede usar **_Makefile.bat_**, este se encargará de buscar las herramientas de compilación de Visual Studio 2019 y realizará las verificaciones necesarias a los archivos del proyecto para iniciar la compilación.

El resultado de la compilación siempre estará dentro de la carpeta ```build/```.

## Archivos necesarios para la ejecución 🛠️

### **Archivo principal:**

- **_main.cpp_**: Contiene la lógica inicial del programa.

### **Archivos de cabecera:**

- **_includes/menu.h_**: Contiene la lógica para los diferentes menúes del programa.
- **_includes/game.h_**: Contiene la lógica para el juego.
- **_includes/utils.h_**: Contiene funciones utilizadas en diversas ocasiones en todo el programa.
- **_includes/dice.h_**: Contiene las cadenas de texto necesarias para imprimir las 6 versiones del dado.
- **_includes/movements.h_**: Contiene los mapas de colores y los mapas de movimiento que las fichas deben seguir.

## Archivos Adicionales 📁

- **_Makefile.bat_**: Inicia la compilación del proyecto después de realizar verificaciones iniciales.
- **_GetHashes.bat_**: Obtiene los _hashes_ SHA1 de cada archivo esencial del proyecto utilizando la herramienta de Windows _CertUtil_.
- **_.vscode/c_cpp_properties.json_**: Contiene la configuración utilizada para la extensión [_C/C++_](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) de [_Visual Studio Code_](https://code.visualstudio.com/).
- **_.vscode/tasks.json_**: Contiene la configuración de las tareas utilizadas para la compilación del proyecto en [_Visual Studio Code_](https://code.visualstudio.com/).
- **_.vscode/launch.json_**: Contiene la configuración de las tareas utilizadas para el _debug_ del proyecto en [_Visual Studio Code_](https://code.visualstudio.com/).

## Documentación de apoyo 📚

- [Microsoft C++, C, and Assembler documentation](https://docs.microsoft.com/en-us/cpp/?view=vs-2019)
- [C++ Reference](https://www.cplusplus.com/reference/)

## Autores ✒️

- Diego Albitres Blondet - ([GitHub](https://github.com/dalbitresb12))
- Ángel Omar Meneses Torres - ([GitHub](https://github.com/amenes12))

## Licencia 📄

Este proyecto está bajo la Licencia **GNU General Public License v3.0** - mira el archivo [LICENSE](LICENSE) para más detalles.
