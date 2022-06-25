#include <iostream>

// funcion RAND
#include <stdlib.h>
#include <time.h>

// STRINGS
#include <cstring>
#include <string>

// rand
#include <cstdlib>
#include <cstdio>

// idioma español
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

using namespace std;

#include "funciones.h"
#include "rlutil.h"

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL)); // Declaro RAND

    // DECLARO CANTIDAD DE RONDAS.
    const int RONDAS = 5;

    // DECLARO VECTORES de los NOMBRES DE LOS JUGADORES
    string vNombreJugador[2];

    // TRUFAS DE JUGADORES
    int vPuntajeTrufas[2][RONDAS] = {};

    // PUNTOS DE VICTORIA
    int vPDV[2] = {};
    int vOinks[2] = {};

    // DECLARO VECTOR para determinar si han jugado su turno en la ronda.
    bool vJugoRonda[2][RONDAS] = {};

    // Declaro variables para guardar los nombres de los jugadores y el del jugador actual
    string nombreJug1, nombreJug2;
    int jugadorActual;

    // DECLARO Variable para cantidad de dados
    int cantDados = 2;

    // DECLARO Vector y variable para contar mayor cant. de lanzamientos
    int mayorCantLanzamientos[2] = {}; // cant de lanzamientos

    // DECLARO VARIABLE para estadísticas
    string nombreMaxPDV;
    int cantMaxPDV = 0;

    // defensa
    int jugHumcerdo;
    int recompensaHumcerdo;
    bool humcerdo = 0;

    int opcion; // En esta variable se guardará la opción elegida del menú principal.
    char opSalida;
    mostrarMenuPrincipal(opcion); // Muestra menú principal y permite al usuario elegir una opción
    validarOpcionMenu(opcion); // validar que sí o sí se elija una opción válida



     while(opcion == 1 || opcion == 2 || opcion == 3 || opcion == 0) {
        switch(opcion) {
            case 1:
                // FUNCION Pedir nombres
                pidoNombres(nombreJug1, nombreJug2);
                // GUARDO los nombres en las variables locales
                vNombreJugador[0] = nombreJug1;
                vNombreJugador[1] = nombreJug2;

                // <<< ---------- COMIENZO ELEGIR PRIMER TURNO ---------- >>>
                rlutil::cls();
                elegirPrimerTurno(nombreJug1, nombreJug2, jugadorActual);
                // <<< ---------- FIN DE ELEGIR PRIMER TURNO ---------- >>>

                // <<< ---------- COMIENZO RONDAS ---------- >>>
                for(int i=0; i<RONDAS; i++) {
                    int contLanzamientos = 0;
                    // FUNCION LANZAMIENTO 1 jugador<--------------  PRINCIPAL
                    lanzamientoJug(cantDados, jugadorActual, i, contLanzamientos, mayorCantLanzamientos, vPuntajeTrufas, vNombreJugador, vJugoRonda, vOinks, vPDV, jugHumcerdo, recompensaHumcerdo, humcerdo);
                    // ----------------------------------------------------------------------------------------------
                    contLanzamientos = 0;
                    // FUNCION LANZAMIENTO 2 jugador<--------------  PRINCIPAL
                    lanzamientoJug(cantDados, jugadorActual, i, contLanzamientos, mayorCantLanzamientos, vPuntajeTrufas, vNombreJugador, vJugoRonda, vOinks, vPDV, jugHumcerdo, recompensaHumcerdo, humcerdo);
                } // TERMINAN LAS RONDAS!!


                // ------------------------------- HITOS ------------------------------------
                finalJuego(mayorCantLanzamientos, vPuntajeTrufas, vNombreJugador, vOinks, vPDV, nombreMaxPDV, cantMaxPDV, jugHumcerdo, recompensaHumcerdo);
                reiniciarDatosJuego(vPuntajeTrufas, vNombreJugador, vJugoRonda, vPDV, vOinks, mayorCantLanzamientos, cantDados);
            break;

            case 2:
                mostrarEstadisticas(nombreMaxPDV, cantMaxPDV);
            break;

            case 3:
                mostrarCerditos();
            break;

            case 0:
                confirmarSalirJuego(opSalida);
                if(opSalida == 'S') {
                    return 0;
                }
            break;
        }
        mostrarMenuPrincipal(opcion); // Muestra menú principal y permite al usuario elegir una opción
        validarOpcionMenu(opcion); // validar que sí o sí se elija una opción válida
    }
    return 0;
}
