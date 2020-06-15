# Ludo en C++

Trabajo final de fin de curso de Programación I de la carrera de Ingeniería de Software de la UPC.

## Objetivos del trabajo 🚀

- **ABET – EAC - Student Outcome 1**: La capacidad de identificar, formular y resolver problemas complejos de ingeniería mediante la aplicación de los principios de la ingeniería, la ciencia y las matemáticas.
- **ABET – CAC - Student Outcome 1**: Analizar un problema de computación complejo y aplicar principios de computación y otras disciplinas relevantes para identificar soluciones.

## Pre-Requisitos 📋

- _Microsoft Visual C++ 2019 - Build Tools_

### Ajustes del compilador ⚙️

- CLI/CLR (```/clr```)
- Name EXE File (```/Fe```)
- Include Paths (```/I ${workspaceFolder}\includes\```)
- Object File Name (```/Fo${workspaceFolder}\build\obj\```)
- File Path (```${workspaceFolder}\main.cpp```)

### Ajustes del _linker_ ⚙️

- Linker (```/link```)
- ```user32.lib```
- Output Path (```/out:${workspaceFolder}\build\main.exe```)

## Archivos necesarios para la ejecución 🛠️

### **Archivo principal:**

- **_main.cpp_**: Contiene la lógica inicial del programa.

### **Archivos de cabecera:**

- **_includes/menu.h_**: Contiene la lógica para los diferentes menúes del programa.
- **_includes/game.h_**: Contiene la lógica para el juego.
- **_includes/utils.h_**: Contiene funciones utilizadas en diversas ocasiones en todo el programa.

## Documentación de apoyo 📚

- [Microsoft C++, C, and Assembler documentation](https://docs.microsoft.com/en-us/cpp/?view=vs-2019)

## Autores ✒️

- Diego Albitres Blondet - ([GitHub](https://github.com/dalbitresb12))
- Ángel Omar Meneses Torres - ([GitHub](https://github.com/amenes12))

## Licencia 📄

Este proyecto está bajo la Licencia **GNU General Public License v3.0** - mira el archivo [LICENSE.md](LICENSE.md) para más detalles.
