// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;
using namespace System;

/**
 * Utils Module
 * Functions used across the entire project
 */
namespace Utils {
    /**
     * Clear screen with fill character
     * 
     * @param {char} [fill = ' ']
     */
    void ClearScreen(char fill = ' ') {
        // Set initial coords on Console
        COORD tl = {0,0};
        // Variable to save Console buffer data
        CONSOLE_SCREEN_BUFFER_INFO s;
        // Get console output handle
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        // Save screen buffer info to previously declared variable
        GetConsoleScreenBufferInfo(console, &s);
        // Calculate the cells that we need to write to (the entire screen)
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        // Fill the calculated cells with the fill char on the output handle.
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        // Fill the calculated cells with the original attributes
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        // Reset cursor position to initial (0, 0)
        SetConsoleCursorPosition(console, tl);
    }

    /**
     * Starts a selection from initial in range min-max
     * 
     * @param {char} c
     * @param {pair<int, int>} initial
     * @param {pair<int, int>} min
     * @param {pair<int, int>} max
     * @param {bool} [esc = false]
     * @return {pair<int, int>} current
     */
    pair<int, int> Selection(char c, pair<int, int> initial, pair<int, int> min, pair<int, int> max, bool esc = false) {
        int ARRIBA = 72;
        int ABAJO = 80;
        int IZQUIERDA = 75;
        int DERECHA = 77;
        int ENTER = 13;
        int ESCAPE = 27;

        int x = initial.first, y = initial.second;
        char key;
        Console::SetCursorPosition(x, y);
        cout << c;

        while (true) {
            key = _getch();
            Console::SetCursorPosition(x, y);
            cout << " ";
            if (key == ABAJO) {
                y++;
                if (y == max.second)
                    y--;
            }
            if (key == ARRIBA) {
                y--;
                if (y == min.second)
                    y++;
            }
            if (key == IZQUIERDA) {
                x--;
                if (x == min.first)
                    x++;
            }
            if (key == DERECHA) {
                x++;
                if (x == max.first)
                    x--;
            }
            if (key == ENTER) {
                return make_pair(x, y);
            }
            if (esc && key == ESCAPE) {
                return make_pair(0, 0);
            }
            Console::SetCursorPosition(x, y);
            cout << c;
        }
    }

    /**
     * Wait until escape key is pressed by user
     */
    void WaitEscape() {
        int ESCAPE = 27;
        char key;
        while (true) {
            key = _getch();
            if (key == ESCAPE) {
                return;
            }
        }
    }

    /**
     * Check if a char variable is equal to another char
     * 
     * @param {char} &key
     * @param {char} c
     * @return {bool} true or false
     */
    bool CheckIfChar(char &key, char c) {
        return (int)key == (int)c;
    }

    /**
     * Check if the key is one of the keys in the array
     * 
     * @param {char} &key
     * @param {const char} keys[]
     * @param {const int} &size
     */
    bool CheckIfInCharArray(char &key, const char keys[], const int &size) {
        for (int i = 0; i < size; i++) {
            if (keys[i] == key) return true;
        }
        return false;
    }

    /**
     * Get a random number between min and max
     * 
     * @param {int} min
     * @param {int} max
     * @return {int} value
     */
    int GetRandomNumber(int min, int max) {
        return rand() % max + min;
    }

    /**
     * Sort an array or vector of pairs by first element
     * of pair using sort() in descending order
     */
    bool SortInRev(pair<int, int> &a, pair<int, int> &b) {
        return a.first > b.first;
    }

    /**
     * Printing utils
     */
    namespace Print {
        /**
         * Center text in screen
         * 
         * @param {string} text
         * @param {bool} [newline = true]
         * @param {int} [width = Console::WindowWidth]
         * @param {int} [startX = 0]
         * @param {int} [startY = Console::CursorTop]
         */
        void Centered(string text, bool newline = true, int width = Console::WindowWidth, int startX = 0, int startY = Console::CursorTop) {
            Console::SetCursorPosition(startX + ((width - text.length()) / 2), startY);
            cout << text;
            if (newline) cout << "\n";
        }

        /**
         * Clear specific line from Console
         * 
         * @param {int} x
         * @param {int} y
         * @param {int} width
         */
        void ClearLine(int x, int y, int width) {
            Console::ResetColor();
            Console::SetCursorPosition(x, y);
            for (int i = 0; i < width; i++) {
                cout << " ";
            }
            Console::SetCursorPosition(x, y);
        }

        /**
         * Print every object in vector
         * 
         * @param {vector<string>} t
         * @param {bool} [center = false]
         */
        void StringVector(vector<string> &t, bool center = false) {
            for (int i = 0; i < size(t); i++) {
                if (center) Print::Centered(t[i]);
                else cout << t[i] << "\n";
            }
        }
    }
}