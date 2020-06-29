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
     * @brief Print a token on the board based on coords.
     * 
     * @param tokenCoords The coords in which the token should be printed.
     * @param tokenNumber The number of the token to be printed.
     * @param playerColor An array that has the colors of each player.
     */
    void SetTokenPosition(pair<int, int> &tokenCoords, int &tokenNumber, const ConsoleColor &playerColor = ConsoleColor::Black) {
        int x = (5 * (tokenCoords.first + 1)) + 2;
        int y = 2 * (tokenCoords.second + 1);
        Console::BackgroundColor = playerColor;
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(x, y);
        cout << tokenNumber + 1;
        Console::SetCursorPosition(x, y + 1);
        cout << '^';
        Console::ResetColor();
    }

    /**
     * @brief Finds the next position corresponding to the current position of a player and assign it.
     * 
     * @param tokenCoords The current token coords, passed as a reference.
     * @param savedTokens The current players' saved tokens.
     * @param selectedToken The selected player that will move.
     * @param current The current player (the active player).
     * @param random The number generated randomly for the dice.
     */
    void SetNewCoords(pair<int, int> &tokenCoords, bool savedTokens[4], int &selectedToken, int &current) {
        if (Movements::SpecialMovements[current].first == tokenCoords) {
            tokenCoords = Movements::SpecialMovements[current].second;
            savedTokens[selectedToken] = true;
            return;
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == tokenCoords) {
                tokenCoords = Movements::Movements[i].second;
                return;
            }
        }
    }

    /**
     * @brief Finds the next position corresponding to the current position of a token and returns it.
     * 
     * @param tokenCoords The current token coords, passed as a reference.
     * @param current The current player (the active player).
     * @return The new position of a token.
     */

    pair<int, int> GetNewCoords(pair<int, int> &tokenCoords, int &current) {
        if (Movements::SpecialMovements[current].first == tokenCoords) {
            return Movements::SpecialMovements[current].second;
        }
        for (int i = 0; i < 88; i++) {
            if (Movements::Movements[i].first == tokenCoords) {
                return Movements::Movements[i].second;
            }
        }
        return make_pair(0, 0);
    }

    /**
     * @brief Checks whether a token must go to jail again because an enemy token ocupied its position.
     * 
     * @param playerCoords An array that has the coords of each token of an specific player.
     * @param playersOut An array that has whether a token has already come out of jail.
     * @param selectedPlayer The selected player that will move.
     * @param current The current turn (the active player).
     * @param players The number of players in the current game.
     * @return True if a token was sent to jail, otherwise false.
     */
    bool SendTokenToJail(pair<int, int> playerCoords[4][4], bool playersOut[4][4], int &selectedPlayer, int &current, int &players) {
        for (int i = 0; i < players; i++) {
            if (i != current) {
                pair<int, int> *p = find(begin(playerCoords[i]), end(playerCoords[i]), playerCoords[current][selectedPlayer]);
                if (p != end(playerCoords[i]) && *p == playerCoords[current][selectedPlayer]) {
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
     * @brief Calculate movements left for a token to enter the safe zone.
     * 
     * @param playerCoords An array that has the coords of each token of an specific player.
     * @param savedPlayers An array that has the tokens a player has already saved (almost finishing).
     * @param current The current turn (the active player).
     * @param selectedPlayer The selected player that will move.
     * @return The number of movements for a token.
     */
    int GetMovementsLeft(pair<int, int> playerCoords[4], bool savedPlayers[4], int &current, int &selectedPlayer) {
        if (savedPlayers[selectedPlayer]) {
            switch (current) {
            case 0:
                return abs(Movements::FinalPositions[current].first - playerCoords[selectedPlayer].first);
                break;
            case 1:
                return abs(Movements::FinalPositions[current].second - playerCoords[selectedPlayer].second);
                break;
            case 2:
                return abs(Movements::FinalPositions[current].first - playerCoords[selectedPlayer].first);
                break;
            case 3:
                return abs(Movements::FinalPositions[current].second - playerCoords[selectedPlayer].second);
                break;
            default:
                return 0;
                break;
            }
        }
        return 0;
    }

    /**
     * @brief Calculate the number of tokens a player has available to move.
     * 
     * @param playerCoords An array that has the coords of each token of an specific player.
     * @param savedPlayers An array that has the tokens a player has already saved (almost finishing).
     * @param playersOut An array that has whether a token has already come out of jail.
     * @param playersFinished An array that has whether a token has already won.
     * @param current The current turn (the active player).
     * @param random The number generated randomly for the dice.
     * @return The number of tokens a player can move.
     */
    int GetMovableTokens(pair<int, int> playerCoords[4], bool savedPlayers[4], bool playersOut[4], bool playersFinished[4], int &current, int &random) {
        int movable = 0;
        for (int i = 0; i < 4; i++) {
            if (savedPlayers[i]) { if (GetMovementsLeft(playerCoords, savedPlayers, current, i) >= random) movable++; }
            else if (random == 6 && !playersFinished[i]) movable++;
            else if (random != 6 && playersOut[i] && !playersFinished[i]) movable++;
        }
        return movable;
    }

    /**
     * @brief Main function of the game logic.
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
        // Should skip current turn
        bool skipTurn = false;
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
                SetTokenPosition(playerCoords[i][j], j, playerColors[i]);
            }
        }

        // Set possible keys a user can use during the game loop
        const int possibleKeysSize = 3;
        const char possibleKeys[possibleKeysSize] = {32, 'D', 'd'};

        // Start game loop
        while (!finished) {
            Print::Scoreboard(players, playerNames, currentTurn, playerColors, ranking, random, timesPlayed, false);

            do {
                key = _getch();
            } while (!Utils::CheckIfInCharArray(key, possibleKeys, possibleKeysSize));

            if (Utils::CheckIfChar(key, 32) || Utils::CheckIfChar(key, 'd') || Utils::CheckIfChar(key, 'D')) {
                // Pre-calculate number of active players based on playersOut array
                activePlayers = count(begin(playersOut[currentTurn]), end(playersOut[currentTurn]), true);

                // Generate random number for current turn
                if (Utils::CheckIfChar(key, 'D') || Utils::CheckIfChar(key, 'd')) {
                    Utils::Print::ClearLine(5, 32, 20);
                    Console::SetCursorPosition(5, 32);
                    cout << "waiting for key";
                    random = (int)_getch() - 48;
                    Utils::Print::ClearLine(5, 32, 20);
                } else {
                    random = Utils::GetRandomNumber(1, 6);
                }

                // Counter for times played of every player
                timesPlayed[currentTurn]++;

                // Counter of 6's
                if (random == 6) {
                    sixCounter++;
                }

                // If the player has had 3 six in a row, exit current loop
                if (sixCounter == 3) {
                    sixCounter = 0;
                    currentTurn++;
                    if (currentTurn == players) currentTurn = 0;
                    continue;
                }

                // Set initial movements left on every loop
                movementsLeft = -1;

                // Only run if player has more than 1 player on the board
                // or player got a six and has at least 1 player on the board
                if (GetMovableTokens(playerCoords[currentTurn], savedPlayers[currentTurn], playersOut[currentTurn], playersFinished[currentTurn], currentTurn, random) > 1) {
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

                // Set movements left if not set before
                if (movementsLeft == -1)
                    movementsLeft = GetMovementsLeft(playerCoords[currentTurn], savedPlayers[currentTurn], currentTurn, selectedPlayer);
                
                // Check if a player wants to move a token to a position where has already a token of its own
                pair<int, int> newPossibleCoords = playerCoords[currentTurn][selectedPlayer];
                if (playersOut[currentTurn][selectedPlayer]) {
                    for (int i = 0; i < random; i++) {
                        newPossibleCoords = GetNewCoords(newPossibleCoords, currentTurn);
                    }
                } else newPossibleCoords = GetNewCoords(newPossibleCoords, currentTurn);
                for (int i = 0; i < 4; i++) {
                    if (playerCoords[currentTurn][i] == newPossibleCoords && !playersFinished[currentTurn][i]) {
                        skipTurn = true;
                    }
                }
                if (skipTurn) {
                    sixCounter = 0;
                    currentTurn++;
                    if (currentTurn == players) currentTurn = 0;
                    skipTurn = false;
                    continue;
                }

                // Only run when token is in safe zone
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
                    SendTokenToJail(playerCoords, playersOut, selectedPlayer, currentTurn, players);
                }

                // Move the player the times the dice says and check if the new position
                // already has another player, then send it to jail
                // Only run if a player hasn't come out of jail in the previous turn
                if (activePlayers > 0 && !playerCameOut && !savedPlayers[currentTurn][selectedPlayer]) {
                    reload = true;
                    if (Movements::SpecialMovements[currentTurn].first == playerCoords[currentTurn][selectedPlayer] && random == 6) {
                        playersFinished[currentTurn][selectedPlayer] = true;
                        for (int i = 0; i < players; i++) {
                            if (ranking[i].second == currentTurn) {
                                ranking[i].first = count(begin(playersFinished[currentTurn]), end(playersFinished[currentTurn]), true);
                            }
                        }
                        playersOut[currentTurn][selectedPlayer] = false;
                    }
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(playerCoords[currentTurn][selectedPlayer], savedPlayers[currentTurn], selectedPlayer, currentTurn);
                    }
                    if (!savedPlayers[currentTurn][selectedPlayer])
                        SendTokenToJail(playerCoords, playersOut, selectedPlayer, currentTurn, players);
                }

                // Reload board only when a change has happened
                if (reload) {
                    Print::Board();
                    for (int i = 0; i < players; i++) {
                        for (int j = 0; j < 4; j++) {
                            SetTokenPosition(playerCoords[i][j], j, playerColors[i]);
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
