#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;
using namespace System;

int main() {
    ConsoleColor Colors[16] = { ConsoleColor::Black, ConsoleColor::Blue, ConsoleColor::Cyan, ConsoleColor::DarkBlue, ConsoleColor::DarkCyan, ConsoleColor::DarkGray, ConsoleColor::DarkGreen, ConsoleColor::DarkMagenta, ConsoleColor::DarkRed, ConsoleColor::DarkYellow, ConsoleColor::Gray, ConsoleColor::Green, ConsoleColor::Magenta, ConsoleColor::Red, ConsoleColor::White, ConsoleColor::Yellow };

    for (int i = 0; i < 16; i++) {
        Console::BackgroundColor = Colors[i];
        if (i != 0) Console::ForegroundColor = ConsoleColor::Black;
        cout << setfill(' ') << setw(Console::WindowWidth - 1) << i << "\n";
        Console::ResetColor();
    }

    Console::ResetColor();
    _getch();
}