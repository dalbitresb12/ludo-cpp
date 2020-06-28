// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <utils.h>
#include <menu.h>
#include <dice.h>
#include <movements.h>

using namespace std;
using namespace System;

/**
 * Game Module
 * This has all the logic for the entire game
 */
namespace Game {
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
                    Console::BackgroundColor = Movements::BoardColors[i][j];
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
        void Scoreboard(int &players, array<string, 4> &playerNames, int &current, array<ConsoleColor, 4> &playerColors, vector<pair<int, int>> &ranking, int &random, int timesPlayed[4], bool showSelection) {
            // Variable definition
            int boardWidth = 81;
            int scoreboardWidth = Console::WindowWidth - boardWidth;
            // Temporal string
            string str;
            // Sort rankings vector
            sort(ranking.begin(), ranking.end(), Utils::SortInRev);
            // Get dice
            vector<string> dice = Dice::GetAscii(random);

            Utils::Print::Centered("===== PARTIDA =====", false, scoreboardWidth, boardWidth, 2);

            Utils::Print::ClearLine(boardWidth, 4, scoreboardWidth);
            Console::ForegroundColor = playerColors[current];
            Utils::Print::Centered(string("Turno de ").append(playerNames[current]), true, scoreboardWidth, boardWidth, 4);
            Console::ResetColor();
            
            Utils::Print::Centered("===== DADO =====", true, scoreboardWidth, boardWidth, 6);
            for (int i = 0; i < size(dice); i++) {
                Utils::Print::Centered(dice[i], true, scoreboardWidth, boardWidth);
            }

            Utils::Print::ClearLine(boardWidth, 15, scoreboardWidth);
            Utils::Print::ClearLine(boardWidth, 16, scoreboardWidth);
            if (!showSelection) {
                Utils::Print::Centered("Presione la tecla ESPACIO", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("para girar el dado", true, scoreboardWidth, boardWidth, 16);
            } else {
                Utils::Print::Centered("Selecciona la ficha que deseas mover", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("usando las teclas 1, 2, 3 o 4", true, scoreboardWidth, boardWidth, 16);
            }

            Utils::Print::Centered("===== RANKING =====", true, scoreboardWidth, boardWidth, 18);
            for (int i = 0; i < players; i++) {
                str = "";
                str.append(to_string(i + 1)).append(". ").append(playerNames[ranking[i].second]);
                str.append(" - ").append(to_string(ranking[i].first));
                Utils::Print::ClearLine(boardWidth, Console::CursorTop + 1, scoreboardWidth);
                Console::ForegroundColor = playerColors[ranking[i].second];
                Utils::Print::Centered(str, false, scoreboardWidth, boardWidth, Console::CursorTop);
            }
            Console::ResetColor();

            Console::SetCursorPosition(Console::CursorLeft, Console::CursorTop + 2);
            Utils::Print::Centered("===== TURNOS JUGADOS =====", true, scoreboardWidth, boardWidth);
            for (int i = 0; i < players; i++) {
                str = "";
                str.append(to_string(i + 1)).append(". ").append(playerNames[i]);
                str.append(" - ").append(to_string(timesPlayed[i]));
                Utils::Print::ClearLine(boardWidth, Console::CursorTop + 1, scoreboardWidth);
                Console::ForegroundColor = playerColors[ranking[i].second];
                Utils::Print::Centered(str, false, scoreboardWidth, boardWidth, Console::CursorTop);
            }
            Console::ResetColor();
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
     * Game util to print a player based on coords and
     * keeping original background colors from board
     * 
     * @param {pair<int, int>} &playerCoords
     * @param {ConsoleColor} [playerColor = ConsoleColor::Black]
     */
    void SetPlayerPosition(pair<int, int> &playerCoords, int &playerNumber, const ConsoleColor &playerColor = ConsoleColor::Black) {
        int x = (5 * (playerCoords.first + 1)) + 2;
        int y = 2 * (playerCoords.second + 1);
        Console::BackgroundColor = Movements::BoardColors[playerCoords.second][playerCoords.first];
        if (playerColor == Movements::BoardColors[playerCoords.second][playerCoords.first]) {
            Console::ForegroundColor = ConsoleColor::Black;
        } else {
            Console::ForegroundColor = playerColor;
        }
        Console::SetCursorPosition(x, y);
        cout << playerNumber + 1;
        Console::SetCursorPosition(x, y + 1);
        cout << '^';
        Console::ResetColor();
    }

    /**
     * Comments pending
     */
    void SetNewCoords(pair<int, int> &playerCoords, int current) {
        for (int j = 0; j < 4; j++) {
            if (Movements::SpecialMovements[j].first == current) {
                if (Movements::SpecialMovements[j].second.first == playerCoords) {
                    playerCoords = Movements::SpecialMovements[j].second.second;
                    return;
                }
            }
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == playerCoords) {
                playerCoords = Movements::Movements[i].second;
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

        Utils::ClearScreen();
        Menu::Print::Logo();

        for (int i = 0; i < 4; i++) {
            Utils::Print::ClearLine(0, 9, Console::WindowWidth);
            Utils::Print::Centered(str, false, Console::WindowWidth, 0, 9);
            str.append(".");
            Sleep(1000);
        }
    }

    /**
     * Comments pending
     */
    bool SendPlayerToJail(pair<int, int> playerCoords[4][4], bool playersOut[4][4], int &selectedPlayer, int &currentTurn, int &players) {
        for (int i = 0; i < players; i++) {
            if (i != currentTurn) {
                pair<int, int> *p = find(begin(playerCoords[i]), end(playerCoords[i]), playerCoords[currentTurn][selectedPlayer]);
                if (p != end(playerCoords[i]) && *p == playerCoords[currentTurn][selectedPlayer]) {
                    int d = distance(begin(playerCoords[i]), p);
                    playerCoords[i][d] = Movements::InitialPositions[i][d];
                    playersOut[i][d] = false;
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Main function on Game Module
     */
    void Start() {
        // Just in case
        Utils::ClearScreen();

        // Variables definition
        // Two-dimension array for player coords
        pair<int, int> playerCoords[4][4];
        bool playersOut[4][4] = { {false}, {false}, {false}, {false} };
        // Array to store player names
        array<string, 4> playerNames;
        // Current turn
        int currentTurn = 0;
        // Game loop
        bool finished = false;
        // Used to know if player came out of jail on last turn
        bool playerCameOut = false;
        // Should reload board
        bool reload = false;
        // Selected player to move
        int selectedPlayer = 0;
        // Counter for 6s
        int sixCounter = 0;
        // Should render scoreboard
        bool renderScoreboard = true;
        // Times played counter
        int timesPlayed[4] = {0};
        // Save pressed key
        char key;
        // Random number for dice
        int random = 0;
        // Number of active players
        int activePlayers;
        // Vector to store rankings
        vector<pair<int, int>> ranking;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::Blue, ConsoleColor::DarkYellow };

        // Get number of players
        int players = GetPlayers();
        // Exit menu if ESC is pressed
        if (players == 0) return;

        // Set initial player positions
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                playerCoords[i][j] = Movements::InitialPositions[i][j];
            }
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

        // Print initial player positions
        for (int i = 0; i < players; i++) {
            for (int j = 0; j < 4; j++) {
                SetPlayerPosition(playerCoords[i][j], j, playerColors[i]);
            }
        }

        // Set possible keys a user can use during the game loop
        const int possibleKeysSize = 1;
        const char possibleKeys[possibleKeysSize] = {32};

        // Start game loop
        while (!finished) {
            Print::Scoreboard(players, playerNames, currentTurn, playerColors, ranking, random, timesPlayed, false);
            do {
                key = _getch();
            } while (!Utils::CheckIfInCharArray(key, possibleKeys, possibleKeysSize));

            if (Utils::CheckIfChar(key, 32)) {
                // Pre-calculate number of active players based on playersOut array
                activePlayers = count(begin(playersOut[currentTurn]), end(playersOut[currentTurn]), true);

                // Generate random number for current turn
                random = Utils::GetRandomNumber(1, 6);

                // Only run if player has more than 1 player on the board
                // or player got a six and has at least 1 player on the board
                if (activePlayers > 1 || (random == 6 && activePlayers > 0)) {
                    renderScoreboard = true;
                    do {
                        do {
                            if (renderScoreboard) {
                                renderScoreboard = false;
                                Print::Scoreboard(players, playerNames, currentTurn, playerColors, ranking, random, timesPlayed, true);
                            }
                            key = _getch();
                            switch (key) {
                                case '1':
                                    selectedPlayer = 0;
                                    break;
                                case '2':
                                    selectedPlayer = 1;
                                    break;
                                case '3':
                                    selectedPlayer = 2;
                                    break;
                                case '4':
                                    selectedPlayer = 3;
                                    break;
                                default:
                                    selectedPlayer = -1;
                                    break;
                            }
                        } while (!(selectedPlayer >= 0 && selectedPlayer <= 3));
                    } while ((!playersOut[currentTurn][selectedPlayer] && random != 6) && !(random == 6 && !playersOut[currentTurn][selectedPlayer]));
                } else if (activePlayers == 1) {
                    selectedPlayer = distance(begin(playersOut[currentTurn]), find(begin(playersOut[currentTurn]), end(playersOut[currentTurn]), true));
                } else {
                    selectedPlayer = 0;
                }

                // Counter for times played of every player
                timesPlayed[currentTurn]++;

                // If the player has had 3 six in a row, exit current loop
                if (sixCounter == 3) {
                    sixCounter = 0;
                    currentTurn++;
                    if (currentTurn == players) currentTurn = 0;
                    continue;
                }

                // Counter of 6's
                if (random == 6) {
                    sixCounter++;
                }

                // Only run if dice says 6
                // Gives the player the option to take a player out of jail
                if (random == 6 && activePlayers < 4 && !playersOut[currentTurn][selectedPlayer]) {
                    playerCameOut = true;
                    reload = true;
                    SetNewCoords(playerCoords[currentTurn][selectedPlayer], currentTurn);
                    playersOut[currentTurn][selectedPlayer] = true;
                    SendPlayerToJail(playerCoords, playersOut, selectedPlayer, currentTurn, players);
                }

                // Move the player the times the dice says and check if the new position
                // already has another player, then send it to jail
                // Only run if a player hasn't come out of jail in the previous turn
                if (activePlayers > 0 && !playerCameOut) {
                    reload = true;
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(playerCoords[currentTurn][selectedPlayer], currentTurn);
                    }
                    SendPlayerToJail(playerCoords, playersOut, selectedPlayer, currentTurn, players);
                }

                // Reload board only when a change has happened
                if (reload) {
                    Print::Board();
                    for (int i = 0; i < players; i++) {
                        for (int j = 0; j < 4; j++) {
                            SetPlayerPosition(playerCoords[i][j], j, playerColors[i]);
                        }
                    }
                }

                // Change turn to next person and reset six counter
                if (random != 6) {
                    sixCounter = 0;
                    currentTurn++;
                    if (currentTurn == players) currentTurn = 0;
                }
            }

            // Reset variables on every loop
            playerCameOut = false;
            selectedPlayer = 0;
            reload = false;
        }

        // Show winner banner

        _getch();
    }
}
