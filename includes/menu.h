// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <utils.h>

using namespace std;
using namespace System;

/**
 * Menu Module
 * This has the entire logic for the main menu
 */
namespace Menu {
    namespace Print {
        /**
         * Print game logo
         * This logo has 7 lines
         * 
         * @param {bool} [center = true]
         */
        void Logo(bool center = true) {
            vector<string> logo = {
                R"( __       __  __  ____    _____      )",
                R"(/\ \     /\ \/\ \/\  _`\ /\  __`\    )",
                R"(\ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   )",
                R"( \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  )",
                R"(  \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ )",
                R"(   \ \____/ \ \_____\ \____/\ \_____\)",
                R"(    \/___/   \/_____/\/___/  \/_____/)"
            };
            Utils::Print::StringVector(logo, center);
        }
    }

    /**
     * Main menu
     * 
     * @return {int} option
     */
    int Main() {
        vector<string> texts = {
            "( ) Iniciar partida",
            "( ) Instrucciones  ",
            "( ) Creditos       ",
            "( ) Salir          ",
            "",
            "Use las flechas arriba y abajo para seleccionar",
            " Presione Enter para seleccionar la opción marcada"
        };
        pair<int, int> ini = make_pair((Console::WindowWidth / 2 - ((texts[1].length() / 2))), 11);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[1].length() / 2))) - 1, 10);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[4].length() / 2))) + 1, 15);

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n\n\n\n";
        Utils::Print::StringVector(texts, true);

        pair<int, int> selection = Utils::Selection('*', ini, min, max);

        return selection.second - 10;
    }

    /**
     * Instructions sub-menu
     */
    void Instructions() {
        vector<string> texts = {
            "===== REGLAS DEL JUEGO =====",
            "- Se juega con un dado de seis caras y el objetivo es",
            "  trasladar las 4 fichas desde la cárcel o partida a la casa", 
            "  o meta.",
            "- A cada jugador en su turno, le corresponde lanzar el",
            "  dado y mover sus fichas si le corresponde. El seis del",
            "  dado sirve como salida. Se utiliza para sacar fichas de",
            "  la cárcel y se obtiene un turno extra (lanza de nuevo",
            " el dado).",
            "- Las fichas se mueven según el puntaje del dado. Si un",
            "  jugador obtiene tres veces seguidas seis se le castiga y",
            "  pierde su turno.",
            "- Un jugador puede capturar (expulsar y poner en la cárcel) las",
            "  fichas de un contrincante, si en su turno ocupa la casilla de este último.", 
            "  Ningún jugador puede tener más de una ficha en cada casilla, si en un turno", 
            "  se saca un número que da como destino una casilla con una ficha propia,no",
            "  se puede mover y se pierde el turno.\n"
            "- Cuando una ficha llega a la vertical de color está seguro, es decir ningún", 
            "  contrincante puede capturarla. Sin embargo, debe llegar a la casa o meta con la",
            "  cuenta exacta, de lo contrario tiene que moverse dentro de la vertical de color según", 
            "  lo indicado por el dado.",
            "- El juego finaliza cuando uno de los jugadores ha colocado las 4 fichas en la casa o meta.",
            " ===== MUCHA SUERTE Y DIVERSIÓN ===== "
            "Presione ESC para regresar al menú"
        };
        
        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringVector(texts, true);
        Utils::WaitEscape();
    }

    /**
     * Credits sub-menu
     */
    void Credits() {
        vector<string> texts = {
            "===== CRÉDITOS =====",
            "",
            "Trabajo realizado por:",
            "Diego Albitres Blondet",
            "Ángel Omar Meneses Torres",
            "",
            "Carrera: Ingeniería de Software",
            "Curso: Programación I",
            "Ciclo: 2020-I",
            "Sección: WV1B",
            "",
            "Presione ESC para regresar al menú"
        };

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringVector(texts, true);
        Utils::WaitEscape();
    }
}