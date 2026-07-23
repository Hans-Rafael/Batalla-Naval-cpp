#include "tablero.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Tableros globales: accesibles desde cualquier funcion de este archivo
int tableroJugador[TAM][TAM];
int tableroOponente[TAM][TAM];
bool turnoJugadorActivo = true; // true = turno jugador, false = turno computadora

void pausar()
{
    cout << "Presiona Enter para continuar...\n";
    cin.ignore();
    cin.get();
}

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
                // limpiarConsola();
                pausar();
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
    // pausar();
    // cout << "Presiona Enter 2 veces para confirmar y continuar...\n";
    // cin.ignore();
    // cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void turnoJugadorContraJugador(int jugador)
{
    int (*tableroPropio)[TAM] = jugador == 1 ? tableroJugador : tableroOponente;
    int (*tableroEnemigo)[TAM] = jugador == 1 ? tableroOponente : tableroJugador;
    int x, y;
    bool disparoValido = false;

    limpiarConsola();
    while (!disparoValido)
    {
        cout << "\n--- Turno del jugador " << jugador << " ---\n";
        cout << "Tu tablero:\n";
        mostrarTablero(tableroPropio, false);
        cout << "Tablero enemigo:\n";
        mostrarTablero(tableroEnemigo, true);
        cout << "Ingresa coordenadas para disparar:\n";
        cout << "Fila X: ";
        cin >> x;
        cout << "Columna Y: ";
        cin >> y;

        if (x >= 0 && x < TAM && y >= 0 && y < TAM &&
            tableroEnemigo[x][y] != 2 && tableroEnemigo[x][y] != 3)
        {
            if (realizarDisparo(tableroEnemigo, x, y))
            {
                disparoValido = true;
                limpiarConsola();
            }
            else
            {
                disparoValido = true;
                turnoJugadorActivo = !turnoJugadorActivo;
                pausar();
            }
        }
        else
        {
            limpiarConsola();
            cout << RED << "Coordenadas invalidas. Intenta de nuevo.\n"
                 << RESET;
        }
    }
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

void jugarDosJugadores()
{
    inicializarTablero(tableroJugador);
    inicializarTablero(tableroOponente);
    turnoJugadorActivo = true;

    cout << "\nTurno del jugador 1 para colocar " << NUM_Barcos << " barcos.\n";
    colocarBarcos(tableroJugador);
    pausar();

    limpiarConsola();
    cout << "\nTurno del jugador 2 para colocar " << NUM_Barcos << " barcos.\n";
    colocarBarcos(tableroOponente);
    pausar();

    while (quedanBarcos(tableroJugador) && quedanBarcos(tableroOponente))
    {
        if (turnoJugadorActivo)
            turnoJugadorContraJugador(1);
        else
            turnoJugadorContraJugador(2);
    }

    limpiarConsola();
    cout << "Tablero final del jugador 1:\n";
    mostrarTablero(tableroJugador, false);
    cout << "Tablero final del jugador 2:\n";
    mostrarTablero(tableroOponente, false);

    if (quedanBarcos(tableroJugador))
        cout << "\nGano el jugador 1!\n";
    else
        cout << "\nGano el jugador 2!\n";
    pausar();
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
        cout << "1. Jugar contra la computadora\n";
        cout << "2. Jugar contra otra persona\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            jugar();
            break;
        case 2:
            jugarDosJugadores();
            break;
        case 3:
            cout << "Gracias por jugar!\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 3);
}
