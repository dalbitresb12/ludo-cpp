#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "es_PE.UTF-8");

    vector<string> logo = {
        R"( __       __  __  ____    _____      )",
        R"(/\ \     /\ \/\ \/\  _`\ /\  __`\    )",
        R"(\ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   )",
        R"( \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  )",
        R"(  \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ )",
        R"(   \ \____/ \ \_____\ \____/\ \_____\)",
        R"(    \/___/   \/_____/\/___/  \/_____/)"
    };

    cout << R"( __       __  __  ____    _____      )" << "\n";
    cout << R"(/\ \     /\ \/\ \/\  _`\ /\  __`\    )" << "\n";
    cout << R"(\ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   )" << "\n";
    cout << R"( \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  )" << "\n";
    cout << R"(  \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ )" << "\n";
    cout << R"(   \ \____/ \ \_____\ \____/\ \_____\)" << "\n";
    cout << R"(    \/___/   \/_____/\/___/  \/_____/)" << "\n";

    _getch();
    return 0;
}