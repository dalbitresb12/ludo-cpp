// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

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
        COORD tl = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
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
     * Printing utils
     */
    namespace Print {
        /**
         * Center text in screen
         * 
         * @param {string} text
         */
        void Centered(string text) {
            Console::SetCursorPosition((Console::WindowWidth - text.length()) / 2, Console::CursorTop);
            cout << text << "\n";
        }

        /**
         * Print every object in vector
         * 
         * @param {vector<string>} t
         * @param {bool} [center = false]
         */
        void StringVector(vector<string> t, bool center = false) {
            for (int i = 0; i < size(t); i++) {
                if (center) Print::Centered(t[i]);
                else cout << t[i] << "\n";
            }
        }
    }
}