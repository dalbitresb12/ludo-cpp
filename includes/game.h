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
#include <dice.h>

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
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Gray, ConsoleColor::DarkRed, ConsoleColor::Gray, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Green, ConsoleColor::Gray, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Gray, ConsoleColor::DarkYellow, ConsoleColor::Gray, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::White},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
        {ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::DarkYellow, ConsoleColor::White, ConsoleColor::White, ConsoleColor::White, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue, ConsoleColor::Blue},
    };

    pair<pair<int, int>, pair<int,int>> Movements[88] = {
    make_pair(make_pair(6, 0), make_pair(7, 0)),
    make_pair(make_pair(6, 1), make_pair(6, 0)),
    make_pair(make_pair(6, 2), make_pair(6, 1)),
    make_pair(make_pair(6, 3), make_pair(6, 2)),
    make_pair(make_pair(6, 4), make_pair(6, 3)),
    make_pair(make_pair(6, 5), make_pair(6, 4)),
    make_pair(make_pair(6, 9), make_pair(5, 8)),
    make_pair(make_pair(6, 10), make_pair(6, 9)),
    make_pair(make_pair(6, 11), make_pair(6, 10)),
    make_pair(make_pair(6, 12), make_pair(6, 11)),
    make_pair(make_pair(6, 13), make_pair(6, 12)),
    make_pair(make_pair(6, 14), make_pair(6, 13)),
    make_pair(make_pair(7, 9), make_pair(7, 8)),
    make_pair(make_pair(7, 10), make_pair(7, 9)),
    make_pair(make_pair(7, 11), make_pair(7, 10)),
    make_pair(make_pair(7, 12), make_pair(7, 11)),
    make_pair(make_pair(7, 13), make_pair(7, 12)),
    make_pair(make_pair(7, 14), make_pair(6, 14)),
    make_pair(make_pair(7, 0), make_pair(8, 0)),
    make_pair(make_pair(7, 1), make_pair(7, 2)),
    make_pair(make_pair(7, 2), make_pair(7, 3)),
    make_pair(make_pair(7, 3), make_pair(7, 4)),
    make_pair(make_pair(7, 4), make_pair(7, 5)),
    make_pair(make_pair(7, 5), make_pair(7, 6)),
    make_pair(make_pair(8, 0), make_pair(8, 1)),
    make_pair(make_pair(8, 1), make_pair(8, 2)),
    make_pair(make_pair(8, 2), make_pair(8, 3)),
    make_pair(make_pair(8, 3), make_pair(8, 4)),
    make_pair(make_pair(8, 4), make_pair(8, 5)),
    make_pair(make_pair(8, 5), make_pair(9, 6)),
    make_pair(make_pair(8, 9), make_pair(8, 10)),
    make_pair(make_pair(8, 10), make_pair(8, 11)),
    make_pair(make_pair(8, 11), make_pair(8, 12)),
    make_pair(make_pair(8, 12), make_pair(8, 13)),
    make_pair(make_pair(8, 13), make_pair(8, 14)),
    make_pair(make_pair(8, 14), make_pair(7, 14)),
    make_pair(make_pair(9, 6), make_pair(10, 6)),	make_pair(make_pair(10, 6), make_pair(11, 6)),	make_pair(make_pair(11, 6), make_pair(12, 6)),	make_pair(make_pair(12, 6), make_pair(13, 6)),	make_pair(make_pair(13, 6), make_pair(14, 6)),	make_pair(make_pair(14, 6), make_pair(14, 7)),
    make_pair(make_pair(9, 7), make_pair(8, 7)),	make_pair(make_pair(10, 7), make_pair(9, 7)),	make_pair(make_pair(11, 7), make_pair(10, 7)),	make_pair(make_pair(12, 7), make_pair(11, 7)),	make_pair(make_pair(13, 7), make_pair(12, 7)),	make_pair(make_pair(14, 7), make_pair(14, 8)),
    make_pair(make_pair(9, 8), make_pair(8, 9)),	make_pair(make_pair(10, 8), make_pair(9, 8)),	make_pair(make_pair(11, 8), make_pair(10, 8)),	make_pair(make_pair(12, 8), make_pair(11, 8)),	make_pair(make_pair(13, 8), make_pair(12, 8)),	make_pair(make_pair(14, 8), make_pair(13, 8)),
    make_pair(make_pair(0, 6), make_pair(1, 6)),	make_pair(make_pair(1, 6), make_pair(2, 6)),	make_pair(make_pair(2, 6), make_pair(3, 6)),	make_pair(make_pair(3, 6), make_pair(4, 6)),	make_pair(make_pair(4, 6), make_pair(5, 6)),	make_pair(make_pair(5, 6), make_pair(6, 5)),
    make_pair(make_pair(0, 7), make_pair(0, 6)),	make_pair(make_pair(1, 7), make_pair(2, 7)),	make_pair(make_pair(2, 7), make_pair(3, 7)),	make_pair(make_pair(3, 7), make_pair(4, 7)),	make_pair(make_pair(4, 7), make_pair(5, 7)),	make_pair(make_pair(5, 7), make_pair(6, 7)),
    make_pair(make_pair(0, 8), make_pair(0, 7)),	make_pair(make_pair(1, 8), make_pair(0, 8)),	make_pair(make_pair(2, 8), make_pair(1, 8)),	make_pair(make_pair(3, 8), make_pair(2, 8)),	make_pair(make_pair(4, 8), make_pair(3, 8)),	make_pair(make_pair(5, 8), make_pair(4, 8)),
    make_pair(make_pair(3,3), make_pair(1,6)),	make_pair(make_pair(4,3), make_pair(1,6)),
    make_pair(make_pair(3,4), make_pair(1,6)),	make_pair(make_pair(4,4), make_pair(1,6)),
    make_pair(make_pair(3,12), make_pair(6,13)),	make_pair(make_pair(4,12), make_pair(6,13)),
    make_pair(make_pair(3,13), make_pair(6,13)),	make_pair(make_pair(4,13), make_pair(6,13)),
    make_pair(make_pair(12,3), make_pair(8,1)),	make_pair(make_pair(13,3), make_pair(8,1)),
    make_pair(make_pair(12,4), make_pair(8,1)),	make_pair(make_pair(13,4), make_pair(8,1)),
    make_pair(make_pair(12,12), make_pair(12,8)),	make_pair(make_pair(13,12), make_pair(12,8)),
    make_pair(make_pair(12,13), make_pair(12,8)),	make_pair(make_pair(13,13), make_pair(12,8))
    };

    pair<int, pair<pair<int, int>, pair<int, int>>> SpecialMovements[4] = {
        make_pair(0, make_pair(make_pair(0, 7), make_pair(1, 7))),
        make_pair(1, make_pair(make_pair(7, 0), make_pair(7, 1))),
        make_pair(2, make_pair(make_pair(14, 7), make_pair(13, 7))),
        make_pair(3, make_pair(make_pair(7, 14), make_pair(7, 13)))
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

        /**
         * Print scoreboard without re-rendering board
         * based on arguments.
         * 
         * @param {int} &players
         * @param {array<string, 4>} &playerNames
         * @param {int} &current
         * @param {array<ConsoleColor, 4>} &playerColors
         * @param {vector<pair<int, int>>} &ranking
         * @param {int} &random
         */
        void Scoreboard(int &players, array<string, 4> &playerNames, int &current, array<ConsoleColor, 4> &playerColors, vector<pair<int, int>> &ranking, int &random) {
            // Variable definition
            int boardWidth = 81;
            int scoreboardWidth = Console::WindowWidth - boardWidth;
            string str;
            vector<string> main = { "===== PARTIDA =====", "", string("Turno de ").append(playerNames[current]) };
            vector<string> dice = Dice::GetAscii(random);

            // Sort and add rankings to vector
            sort(ranking.begin(), ranking.end(), Utils::SortInRev);
            main.push_back("");
            main.push_back("===== RANKING =====");
            main.push_back("");
            for (int i = 0; i < players; i++) {
                str = "";
                str.append(to_string(i + 1)).append(". ").append(playerNames[ranking[i].second]);
                str.append(" - ").append(to_string(ranking[i].first));
                main.push_back(str);
            }
            
            // Reset scoreboard
            Console::ResetColor();
            for (int i = 0; i < Console::WindowHeight - 1; i++) {
                Console::SetCursorPosition(boardWidth, i);
                for (int j = 0; j < scoreboardWidth; j++) {
                    cout << " ";
                }
            }

            // Append last part of scoreboard
            main.push_back("");
            main.push_back("===== DADO =====");

            // Print texts vector centered on the right side of the board
            Console::SetCursorPosition(boardWidth, 2);
            for (int i = 0; i < size(main); i++) {
                Console::SetCursorPosition(boardWidth + ((scoreboardWidth - main[i].length()) / 2), Console::CursorTop);
                if (i == 2) Console::ForegroundColor = playerColors[current];
                else if (i >= 6 && i < (6 + players)) {
                    Console::ForegroundColor = playerColors[ranking[i - 6].second];
                }
                cout << main[i] << "\n";
                Console::ResetColor();
            }

            // Print Dice after scoreboard
            Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 1);
            for (int i = 0; i < size(dice); i++) {
                Console::SetCursorPosition(boardWidth + ((scoreboardWidth - dice[i].length()) / 2), Console::CursorTop);
                cout << dice[i] << "\n";
            }
            
            // Print last set of strings
            vector<string> last = {
                "Presione la tecla R",
                "para girar el dado"
            };
            Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 2);
            for (int i = 0; i < size(last); i++) {
                Console::SetCursorPosition(boardWidth + ((scoreboardWidth - last[i].length()) / 2), Console::CursorTop);
                cout << last[i] << "\n";
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
        if (playerColor == BoardColors[playerCoords.second - 1][playerCoords.first - 1]) {
            Console::ForegroundColor = ConsoleColor::Black;
        } else {
            Console::ForegroundColor = playerColor;
        }
        Console::SetCursorPosition(x, y);
        cout << 'O';
        Console::SetCursorPosition(x, y + 1);
        cout << '^';
        Console::ResetColor();
    }

    void SetNewCoords(pair<int, int> &playerCoords, int current) {
        for (int j = 0; j < 4; j++) {
            if (SpecialMovements[j].first == current) {
                if (SpecialMovements[j].second.first == playerCoords) {
                    playerCoords = SpecialMovements[j].second.second;
                    return;
                }
            }
        }
        for (int i = 0; i < 88; i++) {
            if (Movements[i].first == playerCoords) {
                playerCoords = Movements[i].second;
                return;
            }
        }
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
            { make_pair(12, 12), make_pair(13, 12), make_pair(12, 13), make_pair(13, 13) },
            { make_pair(3, 12), make_pair(4, 12), make_pair(3, 13), make_pair(4, 13) }
        };
        // Array to store player names
        array<string, 4> playerNames;
        // Current turn
        int currentTurn = 0;
        // Game loop
        bool finished = false;
        // Save pressed key
        char key;
        // Random number for dice
        int random = 0;
        // Vector for number of tokens left 
        vector<int> playerTokens;
        // Vector to store rankings
        vector<pair<int, int>> ranking;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::Blue, ConsoleColor::DarkYellow };

        // Get number of players
        int players = GetPlayers();
        // Exit menu if ESC is pressed
        if (players == 0) return;

        // Set initial player tokens based on number of players
        for (int i = 0; i < players; i++) {
            playerTokens.push_back(0);
        }

        // Set initial ranking based on number of players
        for (int i = 0; i < players; i++) {
            ranking.push_back(make_pair(0, i));
        }

        // Self-explanatory
        GetPlayerNames(playerNames, players);
        LoadingScreen(players);

        // Clear everything before printing board
        Utils::ClearScreen();
        Print::Board();

        // Print initial scoreboard
        Print::Scoreboard(players, playerNames, currentTurn, playerColors, ranking, random);

        // Print initial player positions
        for (int i = 0; i < players; i++) {
            for (int j = 0; j < 4; j++) {
                SetPlayerPosition(playerCoords[i][j], playerColors[i]);
            }
        }

        // Start game loop
        while (!finished) {
            key = _getch();
            if (Utils::CheckIfChar('R', key) || Utils::CheckIfChar('r', key)) {
                random = Utils::GetRandomNumber(1, 6);
                if (random == 6) {
                    if (playerTokens[currentTurn] < 4) {
                        SetNewCoords(playerCoords[currentTurn][playerTokens[currentTurn]], currentTurn);
                        playerTokens[currentTurn]++;
                    } else {
                        SetNewCoords(playerCoords[currentTurn][0], currentTurn);
                    }
                } else {
                    SetNewCoords(playerCoords[currentTurn][0], currentTurn);
                }
            }
            currentTurn++;
            if (currentTurn == players) currentTurn = 0;
            Utils::ClearScreen();
            Print::Board();
            for (int i = 0; i < players; i++) {
                for (int j = 0; j < 4; j++) {
                    SetPlayerPosition(playerCoords[i][j], playerColors[i]);
                }
            }
            Print::Scoreboard(players, playerNames, currentTurn, playerColors, ranking, random);
        }

        // Winner

        _getch();
    }
}
