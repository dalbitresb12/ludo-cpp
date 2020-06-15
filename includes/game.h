// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <windows.h>
#include <conio.h>
#include <utils.h>
#include <menu.h>

using namespace std;
using namespace System;

/**
 * Game Module
 * This has all the logic for the entire game
 */
namespace Game {
    /**
     * Board colors definition
     * Two-dimension array 15x15
     */
    ConsoleColor BoardColors[15][15] = {
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed, ConsoleColor::DarkRed},
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkRed, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
    };

    /**
     * Printing utils on Game Module
     */
    namespace Print {
        /**
         * Print board based on two-dimensional color array
         */
        void Board() {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    Console::BackgroundColor = BoardColors[i][j];
                    for (int k = 0; k < 2; k++) {
                        for (int l = 0; l < 5; l++) {
                            Console::SetCursorPosition((5 * (j + 1)) + l, (2 * (i + 1)) + k);
                            cout << " ";
                        }
                    }
                    Console::ResetColor();
                }
            }
        }
    }

    /**
     * Sub-menu for getting the number of players.
     * Returns 0 if ESC is pressed.
     * 
     * @return {int} players
     */
    int GetPlayers() {
        vector<string> texts = {
            "",
            "Seleccione el número de jugadores:",
            "( ) 2 jugadores",
            "( ) 4 jugadores",
            "",
            "Use las flechas arriba y abajo para seleccionar",
            " Presione Enter para seleccionar la opción marcada",
            "Presione ESC para regresar al menú"
        };
        pair<int, int> ini = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))), 9);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2))) - 1, 8);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[3].length() / 2))) + 1, 11);

        Utils::ClearScreen();
        Menu::Print::Logo();
        Utils::Print::StringVector(texts, true);
        
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
     * Sub-menu for getting the player names
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
            Utils::Print::Centered("Ingrese el nombre del jugador " + to_string(i+1));
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
     * Game util to print a player based on coords and
     * keeping original background colors from board
     * 
     * @param {pair<int, int>} &playerCoords
     * @param {ConsoleColor} [playerColor = ConsoleColor::Black]
     */
    void SetPlayerPosition(pair<int, int> &playerCoords, ConsoleColor playerColor = ConsoleColor::Black) {
        int x = (5 * playerCoords.first) + 2;
        int y = 2 * playerCoords.second;
        Console::BackgroundColor = BoardColors[playerCoords.second - 1][playerCoords.first - 1];
        Console::ForegroundColor = playerColor;
        Console::SetCursorPosition(x, y);
        cout << 'O';
        Console::SetCursorPosition(x, y + 1);
        cout << '^';
        Console::ResetColor();
    }

    /**
     * Sub-menu for a loading screen
     */
    void LoadingScreen(int &players) {
        string str = "Preparando partida para ";
        str.append(to_string(players));
        str.append(" jugadores");

        for (int i = 0; i < 4; i++) {
            Utils::ClearScreen();
            Menu::Print::Logo();
            cout << "\n";
            Utils::Print::Centered(str);
            str.append(".");
            Sleep(1000);
        }
    }

    /**
     * Main function on Game Module
     */
    void Start() {
        // Just in case
        Utils::ClearScreen();

        // Variables definition
        // Two-dimension array for player coords
        pair<int, int> playerCoords[4][4] = {
            { make_pair(3, 3), make_pair(4, 3), make_pair(3, 4), make_pair(4, 4) },
            { make_pair(12, 3), make_pair(13, 3), make_pair(12, 4), make_pair(13, 4) },
            { make_pair(3, 12), make_pair(4, 12), make_pair(3, 13), make_pair(4, 13) },
            { make_pair(12, 12), make_pair(13, 12), make_pair(12, 13), make_pair(13, 13) }
        };
        // Array to store player names
        array<string, 4> playerNames;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::DarkYellow, ConsoleColor::Blue };

        // Get number of players
        int players = GetPlayers();
        // Exit menu if ESC is pressed
        if (players == 0) return;

        // Self-explanatory
        GetPlayerNames(playerNames, players);
        LoadingScreen(players);

        // Clear everything before printing board
        Utils::ClearScreen();
        Print::Board();

        // Print initial player positions
        for (int i = 0; i < players; i++) {
            for (int j = 0; j < 4; j++) {
                SetPlayerPosition(playerCoords[i][j], playerColors[i]);
            }
        }

        _getch();
    }
}
