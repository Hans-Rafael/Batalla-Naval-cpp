#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Tableros globales: accesibles desde cualquier funcion de este archivo
int tableroJugador[TAM][TAM];
int tableroOponente[TAM][TAM];
bool turnoJugadorActivo = true; // true = turno jugador, false = turno computadora

void limpiarConsola()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*=================================
          Integrante 1
===================================*/
// Muestra ambos tableros, pide coordenadas al jugador y dispara
// al tablero del oponente con realizarDisparo()
// Avisar si fue impacto o agua segun el valor que devuelve realizarDisparo()
void turnoJugador()
{
    int x, y;
    bool disparoValido = false;
    limpiarConsola();
    while (!disparoValido)
    {
        cout << "\n--- Tu turno ---\n";
        // mostrar tablero propio (sin ocultar)
        cout << "Tu tablero:\n";
        mostrarTablero(tableroJugador, false);
        // mostrar tablero enemigo (ocultando barcos)
        cout << "Tablero enemigo:\n";
        mostrarTablero(tableroOponente, true);
        // pedir coordenadas x e y al jugador
        cout << "Ingresa coordenadas para disparar:\n";
        cout << "Fila X: ";
        cin >> x;
        cout << "Columna Y: ";
        cin >> y;
        if (x >= 0 && x < TAM && y >= 0 && y < TAM && tableroOponente[x][y] != 2 && tableroOponente[x][y] != 3)
        {

            if (realizarDisparo(tableroOponente, x, y) == false)
            {
                disparoValido = true;
                turnoJugadorActivo = false; // Cambiar turno a la computadora
                limpiarConsola();
                cout << "Presiona Enter para continuar...\n";
                cin.ignore();
                cin.get();
            }
            else
            {
                disparoValido = true;
                limpiarConsola();
            }
        }
        else
        {
            limpiarConsola();
            cout << RED;
            cout << "Coordenadas invalidas. Intenta de nuevo.\n";
            cout << RESET;
        }
    }
}

/*=================================
          Integrante 2
===================================*/
// Dispara aleatoriamente sobre el tablero del jugador con realizarDisparoIa()
// Mostrar mensaje indicando si la IA impacto o fallo
void turnoComputadora()
{
    cout << "\n--- Turno de la computadora ---\n";

    // llamar realizarDisparoIa(tableroJugador)
    // si devuelve true  -> "La computadora impacto uno de tus barcos!"
    // si devuelve false -> "La computadora fallo!"
    realizarDisparoIa(tableroJugador);
    turnoJugadorActivo = true;
    cout << "Presiona Enter para continuar...\n";
    cin.ignore();
    cin.get();
}

/*=================================
          Integrante 1
===================================*/
// Prepara el juego y alterna turnos hasta que a alguien se le acaben los barcos
void jugar()
{
    srand(time(0)); // Inicializar semilla para numeros aleatorios
    // inicializar ambos tableros con inicializarTablero()
    inicializarTablero(tableroJugador);
    inicializarTablero(tableroOponente);

    // colocar barcos del jugador con colocarBarcos()
    cout << "Turno del jugador para colocar " << NUM_Barcos << " barcos.\n";
    colocarBarcos(tableroJugador);
    turnoJugadorActivo = false; // Cambiar turno a la computadora
    // colocar barcos del oponente con colocarBarcosOponente()
    colocarBarcosOponente(tableroOponente);
    turnoJugadorActivo = true; // Cambiar turno al jugador

    // mientras queden barcos en ambos tableros (quedanBarcos())
    while (quedanBarcos(tableroJugador) && quedanBarcos(tableroOponente))
    {
        limpiarConsola();
        // si es turno del jugador -> turnoJugador()
        if (turnoJugadorActivo)
        {
            turnoJugador();
        }
        else
        {
            turnoComputadora();
        }
    }

    // Integrante 2: mostrar tableros finales
    // si quedanBarcos(tableroJugador) -> el jugador gano
    // si no                           -> la computadora gano
    // esperar Enter para continuar: cin.ignore(); cin.get();
    limpiarConsola();
    mostrarTablero(tableroJugador, false);
    mostrarTablero(tableroOponente, false);
    if (quedanBarcos(tableroJugador))
        cout << "¡Ganaste!\n";
    else
        cout << "La computadora gano.\n";
    cin.ignore();
    cin.get();
}

/*=================================
          Integrante 2
===================================*/
// Muestra el menu y ejecuta la opcion elegida
void menu()
{
    int opcion;

    do
    {
        cout << "\n======= Menu =======\n";
        cout << "1. Jugar\n";
        cout << "2. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // llamar jugar()
            jugar();
            break;
        case 2:
            cout << "Gracias por jugar!\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 2);
}
