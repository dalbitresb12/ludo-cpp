// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
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
     * @brief Clear screen with fill character.
     * 
     * @param fill The character to use as a fill.
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
     * @brief Starts a selection from initial in the range of min-max.
     * 
     * @param c The character to be printed as the selector.
     * @param initial The initial pair of coords when the function starts.
     * @param min The min pair of coords in which the user can move the character.
     * @param max The max pair of coords in which the user can move the character.
     * @param esc If the function should accept ESC to exit.
     * @return The current pair of coords in which the user pressed ENTER.
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
     * @brief Wait until ESCAPE key is pressed by user.
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
     * @brief Check if a char variable is equal to another char.
     * 
     * @param key The variable of the key the user pressed.
     * @param c The expected key to be pressed.
     * @return True if both are the same, otherwise false.
     */
    bool CheckIfChar(char &key, char c) {
        return (int)key == (int)c;
    }

    /**
     * @brief Generate a random number between min and max using rand().
     * 
     * @param min The min value to generate.
     * @param max The max value to generate.
     * @return The generated value.
     */
    int GetRandomNumber(int min, int max) {
        return rand() % max + min;
    }

    /**
     * @brief Sort an array of pairs by first element of pair using sort() in descending order.
     * 
     * @param a The first pair.
     * @param b The second pair.
     */
    bool SortInRev(pair<int, int> &a, pair<int, int> &b) {
        return a.first > b.first;
    }

    /**
     * Printing utils
     */
    namespace Print {
        /**
         * @brief Center string in screen window or an specific width.
         * 
         * @param text The string to print.
         * @param newLine If we should print a new line after the printed text.
         * @param width The width of the window or space in which the text should be centered.
         * @param startX The starting position on the x-axis.
         * @param startY The starting position on the y-axis.
         */
        void Centered(string text, bool newLine = true, int width = Console::WindowWidth, int startX = 0, int startY = Console::CursorTop) {
            Console::SetCursorPosition(startX + ((width - text.length()) / 2), startY);
            cout << text;
            if (newLine) cout << "\n";
        }

        /**
         * @brief Clear specific line from Console.
         * 
         * @param x The starting position on the x-axis.
         * @param y The starting position on the y-axis.
         * @param width The width of the line to clear.
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
         * @brief Prints every string object in an array.
         * 
         * @param msg The string array to print.
         * @param size The size of the array.
         * @param center If the printing should be centered.
         */
        void StringArray(string msg[], int size, bool center = false) {
            for (int i = 0; i < size; i++) {
                if (center) Print::Centered(msg[i]);
                else cout << msg[i] << "\n";
            }
        }
    }
}