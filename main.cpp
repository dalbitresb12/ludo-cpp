/**
 *     __       __  __  ____    _____      
 *    /\ \     /\ \/\ \/\  _`\ /\  __`\    
 *    \ \ \    \ \ \ \ \ \ \/\ \ \ \/\ \   
 *     \ \ \  __\ \ \ \ \ \ \ \ \ \ \ \ \  
 *      \ \ \L\ \\ \ \_\ \ \ \_\ \ \ \_\ \ 
 *       \ \____/ \ \_____\ \____/\ \_____\
 *        \/___/   \/_____/\/___/  \/_____/
 *                                         
 *    Implementación del videojuego 'Ludo' en C++
 *    Hecho por Diego Albitres y Ángel Meneses
 *    Curso: Programación I
 *    Ciclo: 2020-I
 *    Sección: WV1B
 */
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <utils.h>
#include <menu.h>
#include <game.h>

#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 40

using namespace std;
using namespace System;

int main() {
    // Start random seed
    srand(time(NULL));
    // Set locale to use UTF-8 characters
    setlocale(LC_ALL, "es_PE.UTF-8");
    // Set console window size
    Console::SetWindowSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    
    // Initialize loop variable
    bool loop = true;

    // Just in case
    Utils::ClearScreen();
    
    // Start menu loop
    while (loop) {
        // Get selection from main menu
        int option = Menu::Main();

        switch (option) {
            case 1:
                Game::Start();
                break;
            case 2: 
                Menu::Instructions();
                break;
            case 3:
                Menu::Credits();
                break;
            case 4:
                loop = false;
                break;
        }
    }

    // Wait for any key to exit
    Utils::ClearScreen();
    Menu::Print::Logo();
    cout << "\n";
    Utils::Print::Centered("Presione cualquier tecla para salir");
    _getch();
    exit(0);
}