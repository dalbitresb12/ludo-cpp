// Prevent redefinition
// See: https://stackoverflow.com/a/13124002
#pragma once

#include <string>

using namespace std;

/**
 * Dice Utils
 */
namespace Dice {
    array<string, 7> Dice_1 = {
        R"(    _______   )",
        R"(  /\       \  )",
        R"( /o \   o   \ )",
        R"(/   o\_______\)",
        R"(\o   /o      /)",
        R"( \o /   o   / )",
        R"(  \/______o/  )"
    };

    array<string, 7> Dice_2 = {
        R"(    _______   )",
        R"(  /\ o     \  )",
        R"( /o \       \ )",
        R"(/   o\______o\)",
        R"(\o   /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    array<string, 7> Dice_3 = {
        R"(    _______   )",
        R"(  /\ o     \  )",
        R"( /o \   o   \ )",
        R"(/    \______o\)",
        R"(\    /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    array<string, 7> Dice_4 = {
        R"(    _______   )",
        R"(  /\ o    o\  )",
        R"( /o \       \ )",
        R"(/    \o_____o\)",
        R"(\    /o     o/)",
        R"( \o /   o   / )",
        R"(  \/o_____o/  )"
    };

    array<string, 7> Dice_5 = {
        R"(    _______   )",
        R"(  /\ o    o\  )",
        R"( /o \   o   \ )",
        R"(/   o\o_____o\)",
        R"(\o   /       /)",
        R"( \o /   o   / )",
        R"(  \/_______/  )"
    };

    array<string, 7> Dice_6 = {
        R"(    _______   )",
        R"(  /\ o  o o\  )",
        R"( /o \       \ )",
        R"(/    \o__o__o\)",
        R"(\    /o     o/)",
        R"( \o /   o   / )",
        R"(  \/o_____o/  )"
    };

    /**
     * @brief Get ASCII art of a dice from a random number.
     * 
     * @param random The number the dice should show.
     * @return The dice string array. 
     */
    array<string, 7> GetAscii(int random = 0) {
        switch (random) {
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