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
 * This contains the entire logic for the main menu
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
            "( ) Salir          "
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

    void Instructions() {
        vector<string> texts = {
            "===== REGLAS DEL JUEGO =====",
            "Escribir reglas xd",
            "",
            "Presione ESC para regresar al menú"
        };
        
        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringVector(texts, true);
        Utils::WaitEscape();
    }

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