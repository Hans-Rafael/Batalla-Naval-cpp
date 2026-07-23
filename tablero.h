#pragma once
/* avisa que compile solo una vez en lugar de
#ifndef MI_CLASE_H
#define MI_CLASE_H
// código del archivo .h

#endif*/

const int TAM = 3;
const int NUM_Barcos = 3;

void inicializarTablero(int tablero[TAM][TAM]);
void mostrarTablero(int tablero[TAM][TAM], bool ocultar = false);
void colocarBarcos(int tablero[TAM][TAM]);
void colocarBarcosOponente(int tablero[TAM][TAM]);
bool quedanBarcos(int tablero[TAM][TAM]);
bool realizarDisparo(int tablero[TAM][TAM], int x, int y);
bool realizarDisparoIa(int tablero[TAM][TAM]);

// --- COLORES ANSI ---
// Uso: cout << VERDE << "texto" << RESET;  <- siempre terminar con RESET para no "manchar" la consola
// Ejemplo: cout << RED << "X" << RESET << " impacto!";
// IMPORTANTE: enableAnsiColors() en main.cpp ya los activa en Windows, no hay que hacer nada más
#define RESET "\033[0m"   // Vuelve al color por defecto
#define BLUE "\033[34m"   // Agua inexplorada (~)
#define GREEN "\033[32m"  // Barco a flote (B)
#define RED "\033[31m"    // Impacto (X)
#define YELLOW "\033[33m" // Fallo / agua disparada (O)
#define CYAN "\033[36m"   // Uso general / títulos
#define MAGENTA "\033[35m" // Uso general / marco de tablero

