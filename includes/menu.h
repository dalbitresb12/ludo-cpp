// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <array>
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
         * @brief Print game logo. This logo has 7 lines.
         * 
         * @param center If the logo should be centered.
         */
        void Logo(bool center = true) {
            string logo[] = {
                R"( __       __  __  ____    _____      )",
                R"(/\ \     /\ \/\ \/\  _`\ /\  __`\    )",
                R"(\ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   )",
                R"( \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  )",
                R"(  \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ )",
                R"(   \ \____/ \ \_____\ \____/\ \_____\)",
                R"(    \/___/   \/_____/\/___/  \/_____/)"
            };
            Utils::Print::StringArray(logo, 7, center);
        }
    }

    /**
     * @brief Prompts user to select an option from the main menu.
     * 
     * @return The option that was selected.
     */
    int Main() {
        string texts[] = {
            "( ) Iniciar partida",
            "( ) Instrucciones  ",
            "( ) Creditos       ",
            "( ) Salir          ",
            "",
            "Use las flechas arriba y abajo para seleccionar",
            " Presione Enter para seleccionar la opción marcada"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        pair<int, int> ini = make_pair((Console::WindowWidth / 2 - ((texts[1].length() / 2))), 11);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[1].length() / 2))) - 1, 10);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[4].length() / 2))) + 1, 15);

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n\n\n\n";
        Utils::Print::StringArray(texts, size, true);

        pair<int, int> selection = Utils::Selection('*', ini, min, max);

        return selection.second - 10;
    }

    /**
     * @brief Shows the instructions menu.
     */
    void Instructions() {
        string texts[] = {
            "===== REGLAS DEL JUEGO =====",
            "",
            "- Se juega con un dado de seis caras y el objetivo es",
            "trasladar las 4 fichas desde la cárcel o partida a la casa", 
            "o meta.",
            "- A cada jugador en su turno, le corresponde lanzar el",
            "dado y mover sus fichas si le corresponde. El seis del",
            "dado sirve como salida. Se utiliza para sacar fichas de",
            "la cárcel y se obtiene un turno extra (lanza de nuevo",
            "el dado).",
            "",
            "- Las fichas se mueven según el puntaje del dado. Si un",
            "jugador obtiene tres veces seguidas seis se le castiga y",
            "pierde su turno.",
            "",
            "- Un jugador puede capturar (expulsar y poner en la cárcel) las",
            "fichas de un contrincante, si en su turno ocupa la casilla de este último.", 
            "Ningún jugador puede tener más de una ficha en cada casilla, si en un turno", 
            "se saca un número que da como destino una casilla con una ficha propia,no",
            "se puede mover y se pierde el turno.",
            "",
            "- Cuando una ficha llega a la vertical de color está seguro, es decir ningún", 
            "contrincante puede capturarla. Sin embargo, debe llegar a la casa o meta con la",
            "cuenta exacta, de lo contrario tiene que moverse dentro de la vertical de color según", 
            "lo indicado por el dado.",
            "",
            "- El juego finaliza cuando uno de los jugadores ha colocado las 4 fichas en la casa o meta.",
            "","",
            "Presione ESC para regresar al menú"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        
        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringArray(texts, size, true);
        Utils::WaitEscape();
    }

    /**
     * @brief Shows the credits menu.
     */
    void Credits() {
        string texts[] = {
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
        int size = sizeof(texts) / sizeof(texts[0]);

        Utils::ClearScreen();
        Menu::Print::Logo();
        cout << "\n";
        Utils::Print::StringArray(texts, size, true);
        Utils::WaitEscape();
    }

    /**
     * @brief Sub-menu for getting the number of players.
     * 
     * @return The number of players selected. Returns 0 if ESC is pressed.
     */
    int GetPlayers() {
        string texts[] = {
            "",
            "Seleccione el número de jugadores:",
            "( ) 2 jugadores",
            "( ) 4 jugadores",
            "",
            "Use las flechas arriba y abajo para seleccionar",
            " Presione Enter para seleccionar la opción marcada",
            "Presione ESC para regresar al menú"
        };
        int size = sizeof(texts) / sizeof(texts[0]);
        pair<int, int> ini = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))), 9);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))) - 1, 8);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[3].length() / 2))) + 1, 11);

        Utils::ClearScreen();
        Menu::Print::Logo();
        Utils::Print::StringArray(texts, size, true);
        
        pair<int, int> players = Utils::Selection('*', ini, min, max, true);
        
        if (players.first == 0 && players.second == 0) {
            return 0;
        }

        switch (players.second) {
            case 9: return 2;
            case 10: return 4;
            default: return 0;
        }
    }

    /**
     * @brief Sub-menu for getting the player names
     * 
     * @param playerNames The array to store each player name.
     * @param players The number of players that were seleted.
     */
    void GetPlayerNames(array<string, 4> &playerNames, int &players) {
        int DEL = 8;
        int ENTER = 13;
        string name;
        char key;
        for (int i = 0; i < players; i++) {
            Utils::ClearScreen();
            Menu::Print::Logo();
            cout << "\n";
            Utils::Print::Centered(string("Ingrese el nombre del jugador ").append(to_string(i+1)));
            cout << "\n\n";
            Utils::Print::Centered("Presione Enter para confirmar nombre");
            Utils::Print::Centered("El límite de caracteres es 20");
            while (true) {
                Console::SetCursorPosition(44, 9);
                for (int i = 0; i < 40; i++) {
                    cout << " ";
                }
                Console::SetCursorPosition(((Console::WindowWidth / 2) - (name.length() / 2)), 9);
                Utils::Print::Centered(name);
                key = _getch();
                if (key == DEL && name.length() > 0) {
                    name.pop_back();
                } else if (key == ENTER) {
                    if (name.length() > 0) {
                        playerNames[i] = name;
                        name = "";
                        break;
                    }
                } else {
                    if (name.length() <= 20) {
                        name.push_back(key);
                    }
                }
            }
        }
    }

    /**
     * @brief Sub-menu for a loading screen
     * 
     * @param players The number of players to show.
     */
    void LoadingScreen(int &players) {
        string str = "Preparando partida para ";
        str.append(to_string(players));
        str.append(" jugadores");

        Utils::ClearScreen();
        Menu::Print::Logo();

        for (int i = 0; i < 4; i++) {
            Utils::Print::ClearLine(0, 9, Console::WindowWidth);
            Utils::Print::Centered(str, false, Console::WindowWidth, 0, 9);
            str.append(".");
            Sleep(1000);
        }
    }
}