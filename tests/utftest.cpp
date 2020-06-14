#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

int main() {
    vector<string> texts = {
        string("Hola qué tal muy buenas tardes"),
        string("Chévere manin"),
        "Chévere manin"
    };
    cout << texts[0].length() << endl;
    cout << texts[1].length() << endl;
    cout << texts[2].length() << endl;

    _getch();
    return 0;
}