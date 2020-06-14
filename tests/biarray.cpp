#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <array>

using namespace std;

int main() {
    array<array<int, 6>, 4> matriz;

    cout << matriz[0][0];

    matriz[0][0] = 12;
    matriz[0][1] = 13;

    cout << matriz[0][0];
}