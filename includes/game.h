// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
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
         * @brief Print the board using the defined layout.
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
         * @brief Print scoreboard without re-rendering board.
         * 
         * @param players The number of players.
         * @param playerNames An array that has the names of each player.
         * @param current The current turn.
         * @param playerColors An array that has the colors of each player.
         * @param ranking An array that has the current ranking.
         * @param random The generated number used to print the dice.
         */
        void Scoreboard(int &players, array<string, 4> &playerNames, int &current, array<ConsoleColor, 4> &playerColors, array<pair<int, int>, 4> &ranking, int &random, int timesPlayed[4], bool showSelection) {
            // The width of the board
            int boardWidth = 81;
            // The width the scoreboard can use
            int scoreboardWidth = Console::WindowWidth - boardWidth;
            // Temporal string
            string str;

            // Sort rankings array
            sort(ranking.begin(), ranking.end(), Utils::SortInRev);
            // Get dice
            array<string, 7> dice = Dice::GetAscii(random);

            // Header
            Utils::Print::Centered("===== PARTIDA =====", false, scoreboardWidth, boardWidth, 2);

            // Show who's turn is
            Utils::Print::ClearLine(boardWidth, 4, scoreboardWidth);
            Console::ForegroundColor = playerColors[current];
            Utils::Print::Centered(string("Turno de ").append(playerNames[current]), true, scoreboardWidth, boardWidth, 4);
            Console::ResetColor();
            
            // Print the dice
            Utils::Print::Centered("===== DADO =====", true, scoreboardWidth, boardWidth, 6);
            for (int i = 0; i < size(dice); i++) {
                Utils::Print::Centered(dice[i], true, scoreboardWidth, boardWidth);
            }

            // Print instructions
            Utils::Print::ClearLine(boardWidth, 15, scoreboardWidth);
            Utils::Print::ClearLine(boardWidth, 16, scoreboardWidth);
            if (!showSelection) {
                Utils::Print::Centered("Presione la tecla ESPACIO", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("para girar el dado", true, scoreboardWidth, boardWidth, 16);
            } else {
                Utils::Print::Centered("Selecciona la ficha que deseas mover", true, scoreboardWidth, boardWidth, 15);
                Utils::Print::Centered("usando las teclas 1, 2, 3 o 4", true, scoreboardWidth, boardWidth, 16);
            }

            // Print ranking
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

            // Print the turns each players has already played
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
     * Print a player based on coords and keeping original background colors from board.
     * 
     * @param playerCoords The coords in which the player should be printed.
     * @param playerNumber The number of the player to be printed.
     * @param playerColor An array that has the colors of each player.
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
     * @brief Finds the next position corresponding to the current position of a player and assign it.
     * 
     * @param playerCoords The current player coords, passed as a reference.
     * @param savedPlayers current players' saved players.
     * @param selectedPlayer The selected player that will move.
     * @param current The current turn.
     */
    void SetNewCoords(pair<int, int> &playerCoords, bool savedPlayers[4], int &selectedPlayer, int &current) {
        if (Movements::SpecialMovements[current].first == playerCoords) {
            playerCoords = Movements::SpecialMovements[current].second;
            savedPlayers[selectedPlayer] = true;
            return;
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == playerCoords) {
                playerCoords = Movements::Movements[i].second;
                return;
            }
        }
    }

    /**
     * Comments pending
     * TODO
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
     * Calculate movements left to win
     * TODO OPTIMIZE ARGUMENTS
     */
    int GetMovementsLeft(pair<int, int> playerCoords[4], bool savedPlayers[4], int &currentTurn, int &selectedPlayer) {
        if (savedPlayers[selectedPlayer]) {
            switch (currentTurn) {
            case 0:
                return abs(Movements::FinalPositions[currentTurn].first - playerCoords[selectedPlayer].first);
                break;
            case 1:
                return abs(Movements::FinalPositions[currentTurn].second - playerCoords[selectedPlayer].second);
                break;
            case 2:
                return abs(Movements::FinalPositions[currentTurn].first - playerCoords[selectedPlayer].first);
                break;
            case 3:
                return abs(Movements::FinalPositions[currentTurn].second - playerCoords[selectedPlayer].second);
                break;
            default:
                return 0;
                break;
            }
        }
        return 0;
    }

    int GetMovablePlayers(pair<int, int> playerCoords[4], bool savedPlayers[4], bool playersOut[4], bool playersFinished[4], int &current, int &selectedPlayer, int &random) {
        int movable = 0;
        for (int i = 0; i < 4; i++) {
            if (savedPlayers[i]) { if (GetMovementsLeft(playerCoords, savedPlayers, current, i) >= random) movable++; }
            else if (random == 6 && !playersFinished[i]) movable++;
            else if (random != 6 && playersOut[i] && !playersFinished[i]) movable++;
        }
        return movable;
    }

    /**
     * @brief Main function on Game Module
     * TODO
     */
    void Start() {
        // Variables definition
        // Two-dimension array for player coords
        pair<int, int> playerCoords[4][4];
        // Save active players from each player
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
        // Array to store rankings
        array<pair<int, int>, 4> ranking;
        // Save players who have won
        bool playersFinished[4][4] = { {false}, {false}, {false}, {false} };
        // Players in finish line (the ones that are safe)
        bool savedPlayers[4][4] = { {false}, {false}, {false}, {false} };
        // Movements left for a player to win
        int movementsLeft;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::Blue, ConsoleColor::DarkYellow };

        // Get number of players
        int players = Menu::GetPlayers();
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
            ranking[i] = make_pair(0, i);
        }

        // Self-explanatory
        Menu::GetPlayerNames(playerNames, players);
        Menu::LoadingScreen(players);

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

                movementsLeft = -1;

                // Only run if player has more than 1 player on the board
                // or player got a six and has at least 1 player on the board
                if (GetMovablePlayers(playerCoords[currentTurn], savedPlayers[currentTurn], playersOut[currentTurn], playersFinished[currentTurn], currentTurn, selectedPlayer, random) > 1) {
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

                        if (savedPlayers[currentTurn][selectedPlayer])
                            movementsLeft = GetMovementsLeft(playerCoords[currentTurn], savedPlayers[currentTurn], currentTurn, selectedPlayer);
                    
                    } while (!((playersOut[currentTurn][selectedPlayer] && random != 6 && !savedPlayers[currentTurn][selectedPlayer]) || (random == 6 && !savedPlayers[currentTurn][selectedPlayer]) || (savedPlayers[currentTurn][selectedPlayer] && movementsLeft >= random) || (playersFinished[currentTurn][selectedPlayer] && !savedPlayers[currentTurn][selectedPlayer])));
                } else if (activePlayers == 1) {
                    selectedPlayer = distance(begin(playersOut[currentTurn]), find(begin(playersOut[currentTurn]), end(playersOut[currentTurn]), true));
                } else {
                    selectedPlayer = distance(begin(playersFinished[currentTurn]), find(begin(playersFinished[currentTurn]), end(playersFinished[currentTurn]), false));
                }

                if (movementsLeft == -1)
                    movementsLeft = GetMovementsLeft(playerCoords[currentTurn], savedPlayers[currentTurn], currentTurn, selectedPlayer);

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

                // Player enters safe zone
                if (savedPlayers[currentTurn][selectedPlayer] && activePlayers > 0 && movementsLeft >= random) {
                    reload = true;
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(playerCoords[currentTurn][selectedPlayer], savedPlayers[currentTurn], selectedPlayer, currentTurn);
                    }
                    if (movementsLeft == random) {
                        playersFinished[currentTurn][selectedPlayer] = true;
                        for (int i = 0; i < players; i++) {
                            if (ranking[i].second == currentTurn) {
                                ranking[i].first = count(begin(playersFinished[currentTurn]), end(playersFinished[currentTurn]), true);
                            }
                        }
                        playersOut[currentTurn][selectedPlayer] = false;
                    }
                }

                // Only run if dice says 6
                // Gives the player the option to take a player out of jail
                if (random == 6 && activePlayers < 4 && !playersOut[currentTurn][selectedPlayer] && !savedPlayers[currentTurn][selectedPlayer]) {
                    playerCameOut = true;
                    reload = true;
                    SetNewCoords(playerCoords[currentTurn][selectedPlayer], savedPlayers[currentTurn], selectedPlayer, currentTurn);
                    playersOut[currentTurn][selectedPlayer] = true;
                    SendPlayerToJail(playerCoords, playersOut, selectedPlayer, currentTurn, players);
                }

                // Move the player the times the dice says and check if the new position
                // already has another player, then send it to jail
                // Only run if a player hasn't come out of jail in the previous turn
                if (activePlayers > 0 && !playerCameOut && !savedPlayers[currentTurn][selectedPlayer]) {
                    reload = true;
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(playerCoords[currentTurn][selectedPlayer], savedPlayers[currentTurn], selectedPlayer, currentTurn);
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

                // Exit loop if current player won
                if (count(begin(playersFinished[currentTurn]), end(playersFinished[currentTurn]), true) == 4) break;

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
        
        // Show winner
        Menu::ShowWinner(playerNames[currentTurn], playerColors[currentTurn]);
    }
}
