#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;
using namespace System;

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

void movimiento() {
	int x = 5, y = 5;
	char key;
	Console::SetCursorPosition(x, y);
	cout << "*";
	while (true) {
		key = _getch();
		Console::SetCursorPosition(x, y);
		cout << " ";
		if (key == ARRIBA) {
			y--;
			if (y == 0)
				y--;
		}
		if (key == ABAJO) {
			y++;
			if (y == 25)
				y--;
		}
        if (key == IZQUIERDA) {
            x--;
            if (x == 0)
                x++;
        }
        if (key == DERECHA) {
            x++;
            if (x == 80)
                x--;
        }
		Console::SetCursorPosition(x, y);
		cout << "*";
	}

}

int main() {
	movimiento();
	_getch();
}