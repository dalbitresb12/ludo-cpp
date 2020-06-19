// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <windows.h>

using namespace std;
using namespace System;

/**
 * Movements Utils
 */
namespace Movements {
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

    /**
     * Movements definitions
     * Relationship between initial pos and final pos
     */
    pair<pair<int, int>, pair<int, int>> Movements[88] = {
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
        make_pair(make_pair(9, 6), make_pair(10, 6)), make_pair(make_pair(10, 6), make_pair(11, 6)), make_pair(make_pair(11, 6), make_pair(12, 6)), make_pair(make_pair(12, 6), make_pair(13, 6)), make_pair(make_pair(13, 6), make_pair(14, 6)), make_pair(make_pair(14, 6), make_pair(14, 7)),
        make_pair(make_pair(9, 7), make_pair(8, 7)), make_pair(make_pair(10, 7), make_pair(9, 7)), make_pair(make_pair(11, 7), make_pair(10, 7)), make_pair(make_pair(12, 7), make_pair(11, 7)), make_pair(make_pair(13, 7), make_pair(12, 7)), make_pair(make_pair(14, 7), make_pair(14, 8)),
        make_pair(make_pair(9, 8), make_pair(8, 9)), make_pair(make_pair(10, 8), make_pair(9, 8)), make_pair(make_pair(11, 8), make_pair(10, 8)), make_pair(make_pair(12, 8), make_pair(11, 8)), make_pair(make_pair(13, 8), make_pair(12, 8)), make_pair(make_pair(14, 8), make_pair(13, 8)),
        make_pair(make_pair(0, 6), make_pair(1, 6)), make_pair(make_pair(1, 6), make_pair(2, 6)), make_pair(make_pair(2, 6), make_pair(3, 6)), make_pair(make_pair(3, 6), make_pair(4, 6)), make_pair(make_pair(4, 6), make_pair(5, 6)), make_pair(make_pair(5, 6), make_pair(6, 5)),
        make_pair(make_pair(0, 7), make_pair(0, 6)), make_pair(make_pair(1, 7), make_pair(2, 7)), make_pair(make_pair(2, 7), make_pair(3, 7)), make_pair(make_pair(3, 7), make_pair(4, 7)), make_pair(make_pair(4, 7), make_pair(5, 7)), make_pair(make_pair(5, 7), make_pair(6, 7)),
        make_pair(make_pair(0, 8), make_pair(0, 7)), make_pair(make_pair(1, 8), make_pair(0, 8)), make_pair(make_pair(2, 8), make_pair(1, 8)), make_pair(make_pair(3, 8), make_pair(2, 8)), make_pair(make_pair(4, 8), make_pair(3, 8)), make_pair(make_pair(5, 8), make_pair(4, 8)),
        make_pair(make_pair(2, 2), make_pair(1, 6)), make_pair(make_pair(3, 2), make_pair(1, 6)),
        make_pair(make_pair(2, 3), make_pair(1, 6)), make_pair(make_pair(3, 3), make_pair(1, 6)),
        make_pair(make_pair(2, 11), make_pair(6, 13)), make_pair(make_pair(3, 11), make_pair(6, 13)),
        make_pair(make_pair(2, 12), make_pair(6, 13)), make_pair(make_pair(3, 12), make_pair(6, 13)),
        make_pair(make_pair(11, 2), make_pair(8, 1)), make_pair(make_pair(12, 2), make_pair(8, 1)),
        make_pair(make_pair(11, 3), make_pair(8, 1)), make_pair(make_pair(12, 3), make_pair(8, 1)),
        make_pair(make_pair(11, 11), make_pair(13, 8)), make_pair(make_pair(12, 11), make_pair(13, 8)),
        make_pair(make_pair(11, 12), make_pair(13, 8)), make_pair(make_pair(12, 12), make_pair(13, 8))
    };

    /**
     * Special movements according to player color
     * @see playerColors array on game.h
     */
    pair<int, pair<pair<int, int>, pair<int, int>>> SpecialMovements[4] = {
        make_pair(0, make_pair(make_pair(0, 7), make_pair(1, 7))),
        make_pair(1, make_pair(make_pair(7, 0), make_pair(7, 1))),
        make_pair(2, make_pair(make_pair(14, 7), make_pair(13, 7))),
        make_pair(3, make_pair(make_pair(7, 14), make_pair(7, 13)))
    };
}