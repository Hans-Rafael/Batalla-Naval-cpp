#include "tablero.h"
#include <iostream>

using namespace std;

// Valores del tablero:
// 0 = agua sin disparar
// 1 = barco
// 2 = barco impactado (X)
// 3 = agua disparada (O)

/*=================================
          Integrante 2
===================================*/
// Recorre toda la grilla y pone 0 en cada celda
void inicializarTablero(int tablero[TAM][TAM])
{
    // dos for anidados: uno para filas, otro para columnas
    // tablero[i][j] = ...
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tablero[i][j] = 0;
        }
    }
}

/*=================================
          Integrante 1
===================================*/
// Imprime el tablero con numeros de fila/columna
// Si ocultar == true, los barcos enemigos se muestran como ~
void mostrarTablero(int tablero[TAM][TAM], bool ocultar)
{
    // 1. Imprimir cabecera con los numeros de columna
    cout << endl
         << "    ";
    for (int i = 0; i < TAM; i++)
    {
        cout <<CYAN << i <<RESET << " ";
    }
    cout << endl;
    // 2. Recorrer filas
    for (int i = 0; i < TAM; i++)
    {
        cout <<MAGENTA << i << " |"<< RESET;
        // 3. Recorrer columnas
        for (int j = 0; j < TAM; j++)
        {
            if (ocultar && tablero[i][j] == 1)
            {
                cout << BLUE;
                cout << " ~";
                cout << RESET;
            }
            else if (tablero[i][j] == 1)
            {
                cout << GREEN;
                cout << " B";
                cout << RESET;
            }
            else if (tablero[i][j] == 2)
            {
                // usar color rojo para X
                cout << RED;
                cout << " X";
                cout << RESET;
            }
            else if (tablero[i][j] == 3)
            {

                cout << YELLOW;
                cout << " O";
                cout << RESET;
            }
            else
            {
                cout << BLUE;
                cout << " ~";
                cout << RESET;
            }
        }
        cout << endl;
    }
}

/*=================================
          Integrante 1
===================================*/
// Pide coordenadas al jugador y coloca NUM_Barcos barcos en su tablero
void colocarBarcos(int tablero[TAM][TAM])
{
    int x, y;

    for (int i = 0; i < NUM_Barcos; i++)
    {
        bool colocada = false;
        while (!colocada)
        {
            mostrarTablero(tablero);
            cout << "Coloca tu barco numero: " << i + 1 << " (Fila X): ";
            // leer x
            cin >> x;
            cout << "Coloca tu barco numero: " << i + 1 << " (Columna Y): ";
            cin >> y;
            // validar que x e y esten dentro del rango [0, TAM)
            if (x >= 0 && x < TAM && y >= 0 && y < TAM && tablero[x][y] == 0)
            {
                tablero[x][y] = 1;
                colocada = true;
            }
            else
            {
                cout << "Posición inválida. Intenta de nuevo.\n";
            }
            // si es válido: poner 1 en tablero[x][y] y colocada = true
            // si no: "Posición inválida"
        }
    }
}

/*=================================
          Integrante 2
===================================*/
// Genera posiciones aleatorias para los barcos del oponente
void colocarBarcosOponente(int tablero[TAM][TAM])
{
    for (int i = 0; i < NUM_Barcos; i++)
    {
        int x, y;

        do
        {
            // x = numero aleatorio entre 0 y TAM-1
            x = rand() % TAM;
            // y = numero aleatorio entre 0 y TAM-1
            y = rand() % TAM;
        } while (tablero[x][y] == 1); // repetir si hay un barco en esa posicion

        // colocar barco en tablero[x][y]
        tablero[x][y] = 1;
    }
}

/*=================================
          Integrante 1
===================================*/
// Recorre el tablero buscando algun 1 (barco sin hundir)
// Devuelve true si encontro uno, false si no quedan barcos
bool quedanBarcos(int tablero[TAM][TAM])
{
    // dos for anidados
    // si tablero[i][j] == 1 -> return true
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (tablero[i][j] == 1)
            {
                return true;
            }
        }
    }
    return false;
}

/*=================================
          Integrante 1
===================================*/
// Dispara en la casilla (x, y) del tablero enemigo
// Valores del tablero:
// 0 = agua sin disparar
// 1 = barco
// 2 = barco impactado (X)
// 3 = agua disparada (O)
bool realizarDisparo(int tablero[TAM][TAM], int x, int y)
{
    if (tablero[x][y] == 1)
    {
        tablero[x][y] = 2;
        cout << "\n Impacto! \n" << endl;
        return true;
    }
    else if (tablero[x][y] == 0)
    {
        tablero[x][y] = 3;
        cout << "\n Agua! \n" << endl;
        return false;
    }
    else
    {
        cout << "\n Ya disparaste en esta casilla. \n" << endl;
        return false;
    }
}

/*=================================
          Integrante 2
===================================*/
// La IA elige coordenadas aleatorias hasta encontrar una celda valida
// (solo puede disparar a celdas con valor 0 o 1)
// Devuelve true si impacto un barco, false si fue agua
bool realizarDisparoIa(int tablero[TAM][TAM])
{
    int x, y;

    do
    {
        // generar x e y aleatorios
        x = rand() % TAM;
        y = rand() % TAM;
    } while (!(tablero[x][y] == 0 || tablero[x][y] == 1));

    // si impacto: marcar 2 y retornar true
    // si agua:   marcar 3 y retornar false
    if (tablero[x][y] == 1)
    {
        tablero[x][y] = 2;
        cout << "\n La computadora impactó uno de tus barcos! \n" << endl;
        return true;
    }
    else
    {
        tablero[x][y] = 3;
        cout << "\n La computadora falló! \n" << endl;
        return false;
    }
}
