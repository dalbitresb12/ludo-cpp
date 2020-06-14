// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <windows.h>
#include <utils.h>
#include <menu.h>

using namespace std;
using namespace System;

namespace Game {
    void Start(int players) {
        Utils::ClearScreen();
        array<array<pair<int, int>, 4>, 4> player_positions;
    }

    int GetPlayers() {
        vector<string> texts = {
            "",
            "Seleccione el número de jugadores:",
            "( ) 2 jugadores",
            "( ) 4 jugadores",
            "",
            "Use las flechas arriba y abajo para seleccionar",
            " Presione Enter para seleccionar la opción marcada"
        };
        pair<int, int> ini = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2) - 1)), 9);
        pair<int, int> min = make_pair(((Console::WindowWidth / 2) - ((texts[2].length() / 2) - 1)) - 1, 8);
        pair<int, int> max = make_pair(((Console::WindowWidth / 2) - ((texts[3].length() / 2) - 1)) + 1, 11);

        Utils::ClearScreen();
        Menu::Print::Logo();
        Utils::Print::StringVector(texts, true);
        
        pair<int, int> players = Utils::Selection('*', ini, min, max);
        
        switch (players.second) {
            case 2: return 2;
            case 3: return 4;
            default: return 0;
        }
    }
}