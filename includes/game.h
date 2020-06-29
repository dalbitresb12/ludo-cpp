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
         * @param current The current player (the active player).
         * @param playerColors An array that has the colors of each player.
         * @param ranking An array that has the current ranking.
         * @param random The generated number used to print the dice.
         * @param timesPlayed An array that has the number of times every player has played.
         * @param showSelection True if the scoreboard should prompt to select a token to move, otherwise false.
         */
        void Scoreboard(int &players, array<string, 4> &playerNames, int &current, array<ConsoleColor, 4> &playerColors, array<pair<int, int>, 4> &ranking, int &random, int timesPlayed[4], bool showSelection) {
            // The width of the board
            int boardWidth = 81;
            // The width the scoreboard can use
            int scoreboardWidth = Console::WindowWidth - boardWidth;
            // Auxiliary string
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
     * @param playerColor The color of the player.
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
     * @brief Finds the next position corresponding to the current position of a token and assign it.
     * 
     * @param tokenCoords The current token coords, passed as a reference.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param selectedToken The selected token that will move.
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
     * @param playerTokens An array that has the coords of each token of every player.
     * @param tokensOut An array that has whether a token has already come out of jail.
     * @param selectedTokens The selected token that will move.
     * @param current The current turn (the active player).
     * @param players The number of players in the current game.
     * @return True if a token was sent to jail, otherwise false.
     */
    bool SendTokenToJail(pair<int, int> playerTokens[4][4], bool tokensOut[4][4], int &selectedTokens, int &current, int &players) {
        for (int i = 0; i < players; i++) {
            if (i != current) {
                pair<int, int> *p = find(begin(playerTokens[i]), end(playerTokens[i]), playerTokens[current][selectedTokens]);
                if (p != end(playerTokens[i]) && *p == playerTokens[current][selectedTokens]) {
                    int d = distance(begin(playerTokens[i]), p);
                    playerTokens[i][d] = Movements::InitialPositions[i][d];
                    tokensOut[i][d] = false;
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Calculate movements left for a token to enter the safe zone.
     * 
     * @param tokenCoords An array that has the coords of each token of an specific player.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param current The current turn (the active player).
     * @param selectedToken The selected token that will move.
     * @return The number of movements for a token.
     */
    int GetMovementsLeft(pair<int, int> tokenCoords[4], bool savedTokens[4], int &current, int &selectedToken) {
        if (savedTokens[selectedToken]) {
            switch (current) {
            case 0:
                return abs(Movements::FinalPositions[current].first - tokenCoords[selectedToken].first);
                break;
            case 1:
                return abs(Movements::FinalPositions[current].second - tokenCoords[selectedToken].second);
                break;
            case 2:
                return abs(Movements::FinalPositions[current].first - tokenCoords[selectedToken].first);
                break;
            case 3:
                return abs(Movements::FinalPositions[current].second - tokenCoords[selectedToken].second);
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
     * @param tokenCoords An array that has the coords of each token of an specific player.
     * @param savedTokens An array that has the tokens a player has already saved (almost finishing).
     * @param tokensOut An array that has whether a token has already come out of jail.
     * @param tokensFinished An array that has whether a token has already won.
     * @param current The current turn (the active player).
     * @param random The number generated randomly for the dice.
     * @return The number of tokens a player can move.
     */
    int GetMovableTokens(pair<int, int> tokenCoords[4], bool savedTokens[4], bool tokensOut[4], bool tokensFinished[4], int &current, int &random) {
        int movable = 0;
        for (int i = 0; i < 4; i++) {
            if (savedTokens[i]) { if (GetMovementsLeft(tokenCoords, savedTokens, current, i) >= random) movable++; }
            else if (random == 6 && !tokensFinished[i]) movable++;
            else if (random != 6 && tokensOut[i] && !tokensFinished[i]) movable++;
        }
        return movable;
    }

    /**
     * @brief Main function of the game logic.
     */
    void Start() {
        // Two-dimension array for each players' tokens
        pair<int, int> tokenCoords[4][4];
        // Save the state of each players' tokens (if it's out or not)
        bool tokensOut[4][4] = { {false}, {false}, {false}, {false} };
        // Array to store player names
        array<string, 4> playerNames;
        // Current player (the active player)
        int currentPlayer = 0;
        // Used to know if the token of a player just came out of jail on last turn
        bool tokenCameOut = false;
        // Should reload board
        bool reload = false;
        // Selected token to move
        int selectedToken = 0;
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
        // Number of active tokens
        int activeTokens;
        // Should skip current turn
        bool skipTurn = false;
        // Array to store rankings
        array<pair<int, int>, 4> playerRanking;
        // Save token state of each player (if it has finished its path or not)
        bool tokensFinished[4][4] = { {false}, {false}, {false}, {false} };
        // Tokens in finish line (the ones that are safe)
        bool savedTokens[4][4] = { {false}, {false}, {false}, {false} };
        // Movements left for a player to win
        int movementsLeft;
        // Array for player colors
        array<ConsoleColor, 4> playerColors = { ConsoleColor::Green, ConsoleColor::DarkRed, ConsoleColor::Blue, ConsoleColor::DarkYellow };

        // Get number of players
        int players = Menu::GetPlayers();
        // Exit menu if ESC is pressed
        if (players == 0) return;

        // Set initial token positions
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tokenCoords[i][j] = Movements::InitialPositions[i][j];
            }
        }

        // Set initial ranking based on number of players
        for (int i = 0; i < players; i++) {
            playerRanking[i] = make_pair(0, i);
        }

        // Self-explanatory
        Menu::GetPlayerNames(playerNames, players);
        Menu::LoadingScreen(players);

        // Clear everything before printing board
        Utils::ClearScreen();
        Print::Board();

        // Print initial token positions
        for (int i = 0; i < players; i++) {
            for (int j = 0; j < 4; j++) {
                SetTokenPosition(tokenCoords[i][j], j, playerColors[i]);
            }
        }

        // Start game loop
        while (true) {
            Print::Scoreboard(players, playerNames, currentPlayer, playerColors, playerRanking, random, timesPlayed, false);

            do {
                key = _getch();
            } while (!Utils::CheckIfChar(key, 32));

            if (Utils::CheckIfChar(key, 32)) {
                // Pre-calculate number of active tokens based on tokens out
                activeTokens = count(begin(tokensOut[currentPlayer]), end(tokensOut[currentPlayer]), true);

                // Generate random number for current player
                random = Utils::GetRandomNumber(1, 6);

                // Counter for times played of every player
                timesPlayed[currentPlayer]++;

                // Counter of 6's
                if (random == 6) {
                    sixCounter++;
                }

                // If the player has had 3 six in a row, skip turn
                if (sixCounter == 3) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                    continue;
                }

                // Set initial movements left on every loop
                movementsLeft = -1;

                // Only run if player has more than 1 player on the board
                // or player got a six and has at least 1 player on the board
                if (GetMovableTokens(tokenCoords[currentPlayer], savedTokens[currentPlayer], tokensOut[currentPlayer], tokensFinished[currentPlayer], currentPlayer, random) > 1) {
                    // Re-render scoreboard only on first loop
                    renderScoreboard = true;
                    do {
                        do {
                            if (renderScoreboard) {
                                renderScoreboard = false;
                                Print::Scoreboard(players, playerNames, currentPlayer, playerColors, playerRanking, random, timesPlayed, true);
                            }
                            key = _getch();
                            switch (key) {
                                case '1':
                                    selectedToken = 0;
                                    break;
                                case '2':
                                    selectedToken = 1;
                                    break;
                                case '3':
                                    selectedToken = 2;
                                    break;
                                case '4':
                                    selectedToken = 3;
                                    break;
                                default:
                                    selectedToken = -1;
                                    break;
                            }
                        } while (!(selectedToken >= 0 && selectedToken <= 3));

                        // Calculate the number of movements left
                        if (savedTokens[currentPlayer][selectedToken])
                            movementsLeft = GetMovementsLeft(tokenCoords[currentPlayer], savedTokens[currentPlayer], currentPlayer, selectedToken);
                    
                    } while (!((tokensOut[currentPlayer][selectedToken] && random != 6 && !savedTokens[currentPlayer][selectedToken]) || (random == 6 && !savedTokens[currentPlayer][selectedToken]) || (savedTokens[currentPlayer][selectedToken] && movementsLeft >= random) || (tokensFinished[currentPlayer][selectedToken] && !savedTokens[currentPlayer][selectedToken])));
                } else if (activeTokens == 1) {
                    // Select the only active token that the player has
                    selectedToken = distance(begin(tokensOut[currentPlayer]), find(begin(tokensOut[currentPlayer]), end(tokensOut[currentPlayer]), true));
                } else {
                    // Select the first token that hasn't already finished
                    selectedToken = distance(begin(tokensFinished[currentPlayer]), find(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), false));
                }

                // Calculate the number of movements left if not set before
                if (movementsLeft == -1)
                    movementsLeft = GetMovementsLeft(tokenCoords[currentPlayer], savedTokens[currentPlayer], currentPlayer, selectedToken);
                
                // Check if a player wants to move a token to a position where he has already a token of its own
                pair<int, int> newPossibleCoords = tokenCoords[currentPlayer][selectedToken];
                if (tokensOut[currentPlayer][selectedToken]) {
                    for (int i = 0; i < random; i++) {
                        newPossibleCoords = GetNewCoords(newPossibleCoords, currentPlayer);
                    }
                } else newPossibleCoords = GetNewCoords(newPossibleCoords, currentPlayer);
                for (int i = 0; i < 4; i++) {
                    if (tokenCoords[currentPlayer][i] == newPossibleCoords && !tokensFinished[currentPlayer][i]) {
                        skipTurn = true;
                    }
                }
                if (skipTurn) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                    skipTurn = false;
                    continue;
                }

                // Only run when token is in safe zone (almost finishing)
                if (savedTokens[currentPlayer][selectedToken] && activeTokens > 0 && movementsLeft >= random) {
                    // Queue the reload
                    reload = true;
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    }
                    if (movementsLeft == random) {
                        tokensFinished[currentPlayer][selectedToken] = true;
                        for (int i = 0; i < players; i++) {
                            if (playerRanking[i].second == currentPlayer) {
                                playerRanking[i].first = count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true);
                            }
                        }
                        tokensOut[currentPlayer][selectedToken] = false;
                    }
                }

                // Only run if dice got 6 and the token selected is inside of jail
                if (random == 6 && activeTokens < 4 && !tokensOut[currentPlayer][selectedToken] && !savedTokens[currentPlayer][selectedToken]) {
                    // Set that a token has just came out
                    tokenCameOut = true;
                    // Queue the reload
                    reload = true;
                    SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    tokensOut[currentPlayer][selectedToken] = true;
                    SendTokenToJail(tokenCoords, tokensOut, selectedToken, currentPlayer, players);
                }

                // Move the player the times the dice says and check if the new position
                // already has another player's token, then send it to jail if there is
                // Only run if a token hasn't just come out of jail
                if (activeTokens > 0 && !tokenCameOut && !savedTokens[currentPlayer][selectedToken]) {
                    // Queue the reload
                    reload = true;
                    // Check if the token is about to enter the safe zone and with a 6 can win
                    if (Movements::SpecialMovements[currentPlayer].first == tokenCoords[currentPlayer][selectedToken] && random == 6) {
                        tokensFinished[currentPlayer][selectedToken] = true;
                        for (int i = 0; i < players; i++) {
                            if (playerRanking[i].second == currentPlayer) {
                                playerRanking[i].first = count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true);
                            }
                        }
                        tokensOut[currentPlayer][selectedToken] = false;
                    }
                    for (int i = 0; i < random; i++) {
                        SetNewCoords(tokenCoords[currentPlayer][selectedToken], savedTokens[currentPlayer], selectedToken, currentPlayer);
                    }
                    if (!savedTokens[currentPlayer][selectedToken])
                        SendTokenToJail(tokenCoords, tokensOut, selectedToken, currentPlayer, players);
                }

                // Reload board and token positions only when a change has been queued previously 
                if (reload) {
                    Print::Board();
                    for (int i = 0; i < players; i++) {
                        for (int j = 0; j < 4; j++) {
                            SetTokenPosition(tokenCoords[i][j], j, playerColors[i]);
                        }
                    }
                }

                // Exit loop if current player won
                if (count(begin(tokensFinished[currentPlayer]), end(tokensFinished[currentPlayer]), true) == 4) break;

                // Change turn to next person and reset six counter
                if (random != 6) {
                    sixCounter = 0;
                    currentPlayer++;
                    if (currentPlayer == players) currentPlayer = 0;
                }
            }

            // Reset variables on every loop
            tokenCameOut = false;
            selectedToken = 0;
            reload = false;
        }
        
        // Show winner and then return to main menu
        Menu::ShowWinner(playerNames[currentPlayer], playerColors[currentPlayer]);
    }
}
