// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <vector>
#include <string>

using namespace std;

namespace Dice {
    vector<string> Dice_1 = {
        R"(    _______   )",
        R"(  /\       \  )",
        R"( /o \   o   \ )",
        R"(/   o\_______\)",
        R"(\o   /o      /)",
        R"( \o /   o   / )",
        R"(  \/______o/  )"
    };

    vector<string> Dice_2 = {
        R"(    _______   )",
        R"(  /\ o     \  )",
        R"( /o \       \ )",
        R"(/   o\______o\)",
        R"(\o   /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    vector<string> Dice_3 = {
        R"(    _______   )",
        R"(  /\ o     \  )",
        R"( /o \   o   \ )",
        R"(/    \______o\)",
        R"(\    /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    vector<string> Dice_4 = {
        R"(    _______   )",
        R"(  /\ o    o\  )",
        R"( /o \       \ )",
        R"(/    \o_____o\)",
        R"(\    /o     o/)",
        R"( \o /   o   / )",
        R"(  \/o_____o/  )"
    };

    vector<string> Dice_5 = {
        R"(    _______   )",
        R"(  /\ o    o\  )",
        R"( /o \   o   \ )",
        R"(/   o\o_____o\)",
        R"(\o   /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    vector<string> Dice_6 = {
        R"(    _______   )",
        R"(  /\ o  o o\  )",
        R"( /o \       \ )",
        R"(/    \o__o__o\)",
        R"(\    /o     o/)",
        R"( \o /   o   / )",
        R"(  \/o_____o/  )"
    };

    /**
     * Get ASCII art of specific dice
     * 
     * @param {int} [n = 6]
     * @return {vector<string>} dice
     */
    vector<string> GetAscii(int n = 0) {
        switch (n) {
            case 1: return Dice_1; break;
            case 2: return Dice_2; break;
            case 3: return Dice_3; break;
            case 4: return Dice_4; break;
            case 5: return Dice_5; break;
            case 6: return Dice_6; break;
            default: return Dice_1; break;
        }
    }
}