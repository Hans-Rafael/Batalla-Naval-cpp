#include "juego.h"
#include "tablero.h"
#include <iostream>
using namespace std;

int main()
{
    limpiarConsola();
    cout <<GREEN << "\n ~~Batalla Naval~~\n" << RESET;
    cout <<CYAN << "~~~~~~~~~~~~~~~~~~~\n" << RESET;

    menu();

    return 0;
}
