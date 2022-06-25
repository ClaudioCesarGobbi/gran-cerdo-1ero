#include <iostream>

// funcion RAND
#include <stdlib.h>
#include <time.h>

// STRINGS
#include <cstring>
#include <string>

#include <cstdlib>
#include <cstdio>

// idioma español
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

using namespace std;

#include "funciones.h"
#include "rlutil.h"
//-------------------------------------------------------------------------------------------------

// FUNCIONES EXTRAS

//-------------------------------------------------------------------------------------------------


// Acá una función para mostrar las estadísticas

void mostrarEstadisticas(string &nombre, int &cantPDV) {
    char op;
    if(cantPDV == 0) {
        cout << "Aún no se registró información de jugadores." << endl;
    } else {
        cout << nombre << " ha acumulado un total de " << cantPDV << " PDV, convirtiéndose en el jugador con mayor cantidad de PDV." << endl;
    }
    volverAlMenu(op);
}

void mostrarCerditos() {
    cout << endl << "CRÉDITOS" << endl;
    lineaAncho();
    cout << "EQUIPO: Chapificados" << endl;
    cout << "Legajo 26027 - Juan Pablo Moris" << endl;
    char op;
    volverAlMenu(op);
}

void volverAlMenu(char &op) {
    cout << "Ingrese 'M' para volver al menú principal: ";
    cin >> op;
    verificarOpMenu(op);
}

char verificarOpMenu(char &op) {
    if(op == 'M') {
        return op;
    } else if(op != 'M') {
        while(op != 'M') {
            cout << "Ingrese 'M' para volver al menú principal: ";
            cin >> op;
        }
    }
    return op;
}

void confirmarSalirJuego(char &car) {
    cout << "¿Desea salir del juego? (S/N): ";
    cin >> car;
    // verificar que sea una opción correcta
    verificarSalida(car);
}

char verificarSalida(char &car) {

    if(car == 'S' || car == 'N') {
        if(car == 'N') {
            cout << "Volverá al menú principal... " << endl;
        }
        return car;
    } else if(car != 'S' || car != 'N') {
        while(car != 'S' && car !='N') {
            cout << "¿Desea salir del juego? (S/N): ";
            cin >> car;
        }
    }
    return car;
}

void presionarTecla() {
    cout << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    rlutil::anykey();
}

//-------------------------------------------------------------------------------------------------

// FUNCIONES COMIENZO DEL JUEGO

//-------------------------------------------------------------------------------------------------
string nombreJug(string vec[], int numJ) {
    string name = vec[numJ];
    return name;
}

void pidoNombres(string &jug1, string &jug2) {
    // PIDO NOMBRES
    cout << "Antes de comenzar el juego, indique los jugadores:" << endl;
    cout << "Nombre del jugador #1: ";
    getline(cin, jug1);

    cout << "Nombre del jugador #2: ";
    getline(cin, jug2);

    cout << endl << endl;
}

void elegirPrimerTurno(string &jug1, string &jug2, int &jugActual) {
    char op;
    int dado1, dado2, dado3;
    int dadoMax1, dadoMax2;
    int cantDados = 2;
    int puntajeJug1 = 0, puntajeJug2 = 0;
    titulo();
    cout << "Se determinará quién realiza el primer lanzamiento del juego, el que obtenga mayor puntaje comienza primero. " << endl;
    cout << jug1 << " (Jugador #1)" << endl;
    tiroObligatorio(op);
    if(op == 'S') {
        // función para tirar los dados (en principio 2)
        lanzamientoDados(cantDados, dado1, dado2, dado3);
        puntajeJug1 = dado1 + dado2;
        /*
        cout << endl;
        cout << "Resultado Dado 1: " << dado1 << endl;
        cout << "Resultado Dado 2: " << dado2 << endl;
        cout << endl;
        */

        if(dado1 >= dado2) {
            dadoMax1 = dado1;
        } else if(dado2 >= dado1) {
            dadoMax1 = dado2;
        }
    }
    cin.ignore();

    cout << endl;
    cout << jug2 << " (Jugador #2)" << endl;
    tiroObligatorio(op);
    if(op == 'S') {
        // función para tirar los dados (en principio 2)
        lanzamientoDados(cantDados, dado1, dado2, dado3);
        puntajeJug2 = dado1 + dado2;

        if(dado1 >= dado2) {
            dadoMax2 = dado1;
        } else if(dado2 >= dado1) {
            dadoMax2 = dado2;
        }
    }
    cin.ignore();

    cout << endl;
    // DETERMINO QUIÉN ARRANCA
    if(puntajeJug1 > puntajeJug2) {
        cout << "Primer turno para " << jug1 << " (Jugador #1)" << endl;
        jugActual = 0;
    } else if(puntajeJug2 > puntajeJug1) {
        cout << "Primer turno para " << jug2 << " (Jugador #2)" << endl;
        jugActual = 1;
    } else if(puntajeJug1 == puntajeJug2) {
        // VERIFICAR SI HAY EMPATE!!!
        cout << jug1 << " y " << jug2 << " obtuvieron el mismo puntaje." << endl;
        cout << "El dado más alto determinará el primer turno." << endl;
        if(dadoMax1 > dadoMax2) {
            jugActual = 0;
            cout << "Primer turno para " << jug1 << " (Jugador #1)" << endl;
        } else if(dadoMax2 > dadoMax1) {
            jugActual = 1;
            cout << "Primer turno para " << jug2 << " (Jugador #2)" << endl;
        } else if(dadoMax1 == dadoMax2) {
            cout << endl << "Ambos dados son iguales" << endl;
            repetirPrimerTiro(jug1, jug2, jugActual, op, dado1, dado2, puntajeJug1, puntajeJug2, dadoMax1, dadoMax2);
        }
    }
    cout << "El juego del Gran Cerdo comienza en breve... no peques de ambicioso.";
    rlutil::msleep(3000);
    rlutil::cls();
}

void repetirPrimerTiro(string &jug1, string &jug2, int &jugActual, char &op, int &dado1, int &dado2, int &puntajeJug1, int &puntajeJug2, int &dadoMax1, int &dadoMax2) {
    cout << "Debe repetirse nuevamente el tiro para decidir el primer lanzamiento. " << endl;
    int dado3 = 1;
    int cantDados = 2;
    while(puntajeJug1 == puntajeJug2 && dadoMax1 == dadoMax2) {

        cout << jug1 << " (Jugador #1)" << endl;
        tiroObligatorio(op);
        if(op == 'S') {
            // función para tirar los dados (en principio 2)
            /*
            cout << endl;
            cout << "Resultado Dado 1: " << dado1 << endl;
            cout << "Resultado Dado 2: " << dado2 << endl;
            cout << endl;
            */
            lanzamientoDados(cantDados, dado1, dado2, dado3);
            puntajeJug1 = dado1 + dado2;

            if(dado1 >= dado2) {
                dadoMax1 = dado1;
            } else if(dado2 >= dado1) {
                dadoMax1 = dado2;
            }
        }
        cin.ignore();

        cout << endl;
        cout << jug2 << " (Jugador #2)" << endl;
        tiroObligatorio(op);
        if(op == 'S') {
            // función para tirar los dados (en principio 2)

            lanzamientoDados(cantDados, dado1, dado2, dado3);
            puntajeJug2 = dado1 + dado2;

            /*
            cout << endl;
            cout << "Resultado Dado 1: " << dado1 << endl;
            cout << "Resultado Dado 2: " << dado2 << endl;
            cout << endl;
            */

            if(dado1 >= dado2) {
                dadoMax2 = dado1;
            } else if(dado2 >= dado1) {
                dadoMax2 = dado2;
            }
        }
        cin.ignore();

        // DETERMINO QUIÉN ARRANCA
        if(puntajeJug1 > puntajeJug2) {
            cout << "Primer turno para " << jug1 << " (Jugador #1)" << endl;
            jugActual = 0;
        } else if(puntajeJug2 > puntajeJug1) {
            cout << "Primer turno para " << jug2 << " (Jugador #2)" << endl;
            jugActual = 1;
        } else if(puntajeJug1 == puntajeJug2) {
            // VERIFICAR SI HAY EMPATE!!!
            cout << jug1 << " y " << jug2 << " obtuvieron el mismo puntaje." << endl;
            cout << "El dado más alto determinará el primer turno." << endl;
            if(dadoMax1 > dadoMax2) {
                jugActual = 0;
                cout << "Primer turno para " << jug1 << " (Jugador #1)" << endl;
            } else if(dadoMax2 > dadoMax1) {
                jugActual = 1;
                cout << "Primer turno para " << jug2 << " (Jugador #2)" << endl;
            }
        }
    }
    presionarTecla();
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES MENU PRINCIPAL

//-------------------------------------------------------------------------------------------------
void mostrarMenuPrincipal(int &op) {
    cout << endl;
    rlutil::cls();
    titulo();
    cout << "Por favor elija una opción:" << endl;
    cout << "1 - JUGAR" << endl;
    cout << "2 - ESTADÍSTICAS" << endl;
    cout << "3 - CERDITOS" << endl;
    cout << "0 - SALIR DEL JUEGO" << endl;
    cout << "Opcion #";
    cin >> op;
    cin.ignore();
}

void validarOpcionMenu(int &op) {

    if(op < 0 || op > 3) { // si no se selecciona la opción correcta, while hasta que elija la correcta.
        while(op < 0 || op > 3) {
            cout << endl;
            rlutil::cls();
            titulo();
            cout << "Por favor elija una opción CORRECTA:" << endl;
            cout << "1 - JUGAR" << endl;
            cout << "2 - ESTADÍSTICAS" << endl;
            cout << "3 - CERDITOS" << endl;
            cout << "0 - SALIR DEL JUEGO" << endl;
            cout << "Opcion #";
            cin >> op;
            cin.ignore();
        }
    }
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES TIRADA DE DADOS

//-------------------------------------------------------------------------------------------------
void lanzamientoDados(int &cantDados, int &dado1, int &dado2, int &dado3) {
    cout << "Agitando los dados..." << endl;
    rlutil::msleep(1500);
    if(cantDados == 2) {
        dado1 = tirarDados();
        dado2 = tirarDados();
        /*
        cout << endl;
        cout << "Resultado Dado 1: " << dado1 << endl;
        cout << "Resultado Dado 2: " << dado2 << endl;
        cout << endl;
        */
        dibujarDado(dado1);
        dibujarDado(dado2);
    }
    if(cantDados == 3) {
        dado1 = tirarDados();
        dado2 = tirarDados();
        dado3 = tirarDados();
        /*
        cout << endl;
        cout << "Resultado Dado 1: " << dado1 << endl;
        cout << "Resultado Dado 2: " << dado2 << endl;
        cout << "Resultado Dado 3: " << dado3 << endl;
        cout << endl;
        */
        dibujarDado(dado1);
        dibujarDado(dado2);
        dibujarDado(dado3);
    }
}

/// Genera un dado al azar y devuelve el resultado de la suma.
int tirarDados() {
    int numero;
    generarRandom(numero);
    return numero;
}

void generarRandom(int &num) {
    num = rand()%6 + 1;
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES DE COMPROBACIÓN

//-------------------------------------------------------------------------------------------------
void confirmarLanzamiento(char &car) {
    cout << "¿Desea tirar los dados? (S/N): ";
    cin >> car;
    // verificar que sea una opción correcta
    verificarOp(car);
}

char verificarOp(char &car) {

    if(car == 'S' || car == 'N') {
        if(car == 'N') {
            cout << "Ha decidido no tirar los dados. " << endl;
            rlutil::msleep(3000);
        }
        return car;
    } else if(car != 'S' || car != 'N') {
        while(car != 'S' && car !='N') {
            cout << "¿Desea tirar los dados? (S/N): ";
            cin >> car;
        }
    }
    return car;
}

bool sePlanta(char &car) {
    if(car == 'N') {
        return 1;
    } else {
        return 0;
    }
}

void tiroObligatorio(char &car) {
    cout << "Presione (S) para lanzar los dados: ";
    cin >> car;
    // verificar que sea una opción correcta
    verificarOpObligatoria(car);
}

char verificarOpObligatoria(char &car) {
    if(car == 'S') {
        return car;
    } else if(car != 'S') {
        while(car != 'S') {
            cout << "El tiro es obligatorio." << endl << "Ingrese (S) para lanzar los dados: ";
            cin >> car;
        }
    }
    return car;
}

bool comprobarCantTrufas(int vec[][5], int cantTrufas) {
    bool res;
    int cantA = 0;
    int cantB = 0;

    for(int i=0; i<5; i++) {
        cantA+=vec[0][i];
        cantB+=vec[1][i];
    }

    if(cantA >= cantTrufas && cantB >= cantTrufas) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

//-------------------------------------------------------------------------------------------------

// FUNCIONES PARA TURNO JUGADORES

//-------------------------------------------------------------------------------------------------

void lanzamientoJug(int &cantDados, int &nroJug, int &nroRonda, int &lanzamientos, int mayorCantLanzamientos[], int vec[][5], string vecNom[], bool vTurno[][5], int vOinks[], int vPDV[], int &jugHumcerdo, int &recompensaHumcerdo, bool &humcerdo) {

    // FUNCION MOSTRAR PUNTOS
    mostrarPuntajes(vecNom, vec);
    // FUNCION MOSTRAR DATOS RONDA
    mostrarDatosRonda(vecNom, vec, nroJug, nroRonda, lanzamientos);

    char sigue;
    confirmarLanzamiento(sigue);
    // ----------------- DECLARACION VARIABLE DADOS -----------------
    int dado1, dado2, dado3;
    bool cedeTurno = 0;
    while(sigue == 'S' && cedeTurno == 0) {
        // ----------------- PROCESOS -----------------
        if(comprobarCantTrufas(vec, 50)) {
            cantDados = 3;
        }
        bool obligadoaTirar = 0;
        lanzamientos++;
        // COMIENZO LANZAMIENTOS
        cout << "Lanzamiento #" << lanzamientos << endl;
        lanzamientoDados(cantDados, dado1, dado2, dado3);

        if(humcerdo == 0) {
            if(humcerdoPrimo(cantDados, dado1, dado2, dado3)) {
                if(cantDados == 2) {
                    cout << "OK" << endl;
                    humcerdo = 1;
                    jugHumcerdo = nroJug;
                    recompensaHumcerdo = 5;
                    cout << "¡" << vecNom[nroJug] << " ha realizado un Humcerdo por sacar todos los dados con números primos!" << endl;
                } else if(cantDados == 3) {
                    cout << "OK" << endl;
                    humcerdo = 1;
                    jugHumcerdo = nroJug;
                    recompensaHumcerdo = 7;
                    cout << "¡" << vecNom[nroJug] << " ha realizado un Humcerdo por sacar todos los dados con números primos!" << endl;
                }
            }
        }
            // REGLA A - SUMAR TRUFAS - Si son distintos y no son Ases (1)
            if(sonDistintosNiAses(cantDados, dado1, dado2, dado3)) {
                int suma;
                if(cantDados == 2) {
                    suma = dado1 + dado2;
                    sumarTrufasRonda(nroRonda, nroJug, vec, suma); // SUMA LOS PUNOS AL NRO. DE RONDA
                } else if(cantDados == 3) {
                    suma = dado1 + dado2 + dado3;
                    sumarTrufasRonda(nroRonda, nroJug, vec, suma); // SUMA LOS PUNOS AL NRO. DE RONDA
                }
                cout << "¡" << vecNom[nroJug] << " ha sumado " << suma << " trufas!" << endl;
            }

            // REGLA B - REALIZA UN OINK - Si son las caras iguales y no son Ases (1)
            if(realizaOink(cantDados, dado1, dado2, dado3)) {
                int suma;
                if(cantDados == 2) {
                    suma = dado1 * 2 + dado2 * 2;
                    sumarTrufasRonda(nroRonda, nroJug, vec, suma); // SUMA LOS PUNOS AL NRO. DE RONDA
                } else if(cantDados == 3) {
                    suma = dado1 * 2 + dado2 * 2 + dado3 * 2;
                    sumarTrufasRonda(nroRonda, nroJug, vec, suma); // SUMA LOS PUNOS AL NRO. DE RONDA
                }
                vOinks[nroJug]++;
                obligadoaTirar = 1;
                cout << "¡" << vecNom[nroJug] << " realizó un OINK acumulando " << suma << " trufas!" << endl;
            }

            // REGLA C - Si las caras son distintas y alguna de ellas es un As (1)
            if(sonDistintasHayAs(cantDados, dado1, dado2, dado3)) {
                if(cantDados == 2 || cantDados == 3) {
                    int trufas = vec[nroJug][nroRonda];
                    quitarTrufasRonda(nroRonda, nroJug, vec, trufas);
                    cedeTurno = 1;
                    cout << "¡" << vecNom[nroJug] << " pierde su turno y también las " << trufas << " trufas de esta ronda!" << endl;
                }
            }

            // REGLA D - Se hunde en el barro si dos dados son iguales y son ases
            if(seHundeEnElBarro(cantDados, dado1, dado2, dado3)) {
                if(cantDados == 2 || cantDados == 3) {
                    int trufas = 0;
                    for(int i=0; i<=nroRonda; i++) {
                        trufas+=vec[nroJug][i];
                    }
                    quitarTrufasRonda(nroRonda, nroJug, vec, trufas);
                    if(cantDados == 2) {
                        cout << "A partir de este momento los lanzamientos serán con 3 dados." << endl;
                    }
                    cedeTurno = 1;
                    cantDados = 3;
                    cout << "¡" << vecNom[nroJug] << " se HUNDE EN EL BARRO, pierde su turno y también las " << trufas << " trufas acumuladas hasta el momento!" << endl;
                }
            }

            // REGLA E - Si se juega con tres dados y son todos iguales y
            //           son ases, pierde todos los puntos acumulados y los cede al otro cerdo
            if(cantDados == 3 && sonTodosAses(dado1, dado2, dado3)) {
                int trufas = 0;
                int proxJug = determinarProxTurno(nroJug);
                for(int i=0; i<=nroRonda; i++) {
                    trufas+=vec[nroJug][i];
                }
                quitarTrufasRonda(nroRonda, nroJug, vec, trufas);
                sumarTrufasRonda(nroRonda, proxJug, vec, trufas);
                cedeTurno = 1;
                cout << "¡" << vecNom[nroJug] << " pierde su turno y también las " << trufas << " trufas acumuladas hasta el momento!" << endl;
                cout << "¡" << vecNom[proxJug] << " se beneficia acumulando " << trufas << " trufas!" << endl;
            }

        // ----------------- PROCESOS -----------------
        presionarTecla();
        rlutil::cls();
        // ----------------- VOLVER A PREGUNTAR TIRADA DE DADOS -----------------
        if(cedeTurno == 0) {
            // INFORMA PUNTAJE ACUMULADO
            mostrarPuntajes(vecNom, vec);
            // MUESTRA DATOS DE LA RONDA
            mostrarDatosRonda(vecNom, vec, nroJug, nroRonda, lanzamientos);

            // CONFIRMAR LANZAMIENTO
            if(obligadoaTirar == 0) {
                confirmarLanzamiento(sigue);
                if(sePlanta(sigue)) {
                    cedeTurno = 1;
                }
            }
            if(obligadoaTirar == 1) {
                tiroObligatorio(sigue);
            }
        }
        // ----------------- VOLVER A PREGUNTAR TIRADA DE DADOS -----------------
    }
    calcularMayorLanzamientos(lanzamientos, mayorCantLanzamientos, nroJug);
    cambioTurno(nroJug, determinarProxTurno(nroJug), nroRonda, vTurno);
}

int determinarProxTurno(int &jugadorActual) {
    int otroJug;
    if(jugadorActual == 0) {
        otroJug = 1;
    } else if(jugadorActual == 1) {
        otroJug = 0;
    }
    return otroJug;
}

void cambioTurno(int &jugadorActual, int otroJug, int &nroRonda, bool vTurno[][5]) {
    rlutil::cls();
    vTurno[jugadorActual][nroRonda] = 1;
    jugadorActual = otroJug;
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES PARA SUMAR/QUITAR/OBTENER/MOSTRAR PUNTOS

//-------------------------------------------------------------------------------------------------
void sumarTrufasRonda(int &nroRonda, int &nroJug, int vec[][5], int &puntos) {
    vec[nroJug][nroRonda]+=puntos;
}

void quitarTrufasRonda(int &nroRonda, int &nroJug, int vec[][5], int &puntos) {
    vec[nroJug][nroRonda]-=puntos;
}

int obtenerPuntos(int vec[][5], int nroJug) {
    int puntos = 0;
    for(int i=0; i<5; i++) {
        puntos+=vec[nroJug][i];
    }
    return puntos;
}

int obtenerPuntosRonda(int &nroRonda, int &nroJug, int vec[][5]) {
    int puntos = 0;
    puntos+=vec[nroJug][nroRonda];
    return puntos;
}

void mostrarPuntajes(string vecNom[], int vec[][5]) {
    titulo();
    cout << nombreJug(vecNom, 0) << ": " << obtenerPuntos(vec, 0) << " trufas acumuladas." << "        "
         << nombreJug(vecNom, 1) << ": " << obtenerPuntos(vec, 1) << " trufas acumuladas." << endl;
}

void mostrarDatosRonda(string vecNom[], int vec[][5], int &nroJug, int &nroRonda, int &lanzamientos) {
    // INDICA TURNO
    string largo = nombreJug(vecNom, nroJug);
    cout << endl << "TURNO DE " << nombreJug(vecNom, nroJug) << endl;
    // ----------------------------------------
    cout << "--------------------------------------------" << endl;
    cout << "RONDA #" << nroRonda + 1 << endl;
    cout << "TRUFAS DE LA RONDA: " << obtenerPuntosRonda(nroRonda, nroJug, vec) << endl;
    cout << "CANTIDAD DE LANZAMIENTOS: " << lanzamientos << endl;
    cout << "--------------------------------------------" << endl;
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES REGLAS DEL JUEGO

//-------------------------------------------------------------------------------------------------

// FUNCION COMPROBACION A
// Si ambos dados son distintos entre sí y no son 1

bool sonDistintosNiAses(int &cantDados, int dado1, int dado2, int dado3) {
    bool res;
    if(cantDados == 2) {
        if(dado1 != dado2 && dado1 != 1 && dado2 != 1) {
            //cout << "NO SON IGUALES, NI SON ASES" << endl;
            res = 1;
        } else {
            res = 0;
        }

    } else if(cantDados == 3) {

        if( (dado1 != dado2 && dado2 != dado3 && dado3 != dado1 && dado1 != 1 && dado2 != 1 && dado3 != 1) ||
            ( (dado1 == dado2 && dado3 != dado1 && dado1 != 1 && dado2 != 1 && dado3 != 1) ||
              (dado2 == dado3 && dado1 != dado2 && dado1 != 1 && dado2 != 1 && dado3 != 1) ||
              (dado3 == dado1 && dado2 != dado3 && dado1 != 1 && dado2 != 1 && dado3 != 1)) ) {
            //cout << "NO SON IGUALES, NI SON ASES" << endl;
            res = 1;
        } else {
            res = 0;
        }

        /* OTRA OPCION, PARA NO SUMAR SI SON DOS IGUALES Y NO HAY ASES
        if(dado1 != dado2 && dado2 != dado3 && dado3 != dado1 && dado1 != 1 && dado2 != 1 && dado3 != 1) {
            cout << "NO SON IGUALES, NI SON ASES" << endl;
            res = 1;
        } else {
            res = 0;
        }
        */
    }
    return res;
}

// FUNCION COMPROBACION B
// REALIZA UN OINK - Si son las caras iguales y no son Ases (1)
bool realizaOink(int &cantDados, int dado1, int dado2, int dado3) {
    bool res;
    if(cantDados == 2) {
        if( dado1 == dado2 && dado1 != 1 && dado2 !=1 ) {
                //cout << "CARAS IGUALES y DISTINTAS DE 1" << endl;
                //cout << "REALIZA UN OINK" << endl;
            res = 1;
        } else {
            res = 0;
        }
    } else if(cantDados == 3) {
        if( (dado1 == dado2 && dado2 == dado3 && dado3 == dado1) && dado1 != 1 && dado2 != 1 && dado3 != 1) {
                //cout << "CARAS IGUALES y DISTINTAS DE 1" << endl;
                //cout << "REALIZA UN OINK" << endl;
            res = 1;
        } else {
            res = 0;
        }
    }
    return res;
}

// FUNCION COMPROBACION C
// Si las caras son distintas y alguna de ellas hay un as

bool sonDistintasHayAs(int &cantDados, int dado1, int dado2, int dado3) {
    bool res;
    if(cantDados == 2) {
        if((dado1 != dado2) && (dado1 == 1 || dado2 == 1)) {
            //cout << "LAS CARAS SON DISTINTAS, pero HAY UN AS (1)" << endl;
            //cout << "DEBE CEDER SU TURNO AL OTRO CERDO" << endl;
            //cout << "TAMBIEN PIERDE LOS PUNTOS DE ESTA RONDA." << endl;
            res = 1;
        } else {
            res = 0;
        }
    } else if(cantDados == 3) {
        if( ((dado1 != dado2 && dado2 != dado3 && dado1 != dado3) && (dado1 == 1 || dado2 == 1 || dado3 == 1)) ||
            ((dado1 == dado2 && dado2 != dado3 && dado3 == 1) || (dado2 == dado3 && dado1 != dado2 && dado1 == 1) || (dado1 == dado3 && dado3 != dado2 && dado2 == 1)) )  {
            //cout << "DOS DE LAS CARAS SON DISTINTAS, pero HAY UN AS (1)" << endl;
            //cout << "DEBE CEDER SU TURNO AL OTRO JUEGO" << endl;
            //cout << "TAMBIEN PIERDE LOS PUNTOS DE ESTA RONDA." << endl;
            res = 1;
        } else {
            res = 0;
        }

    }
    return res;
}

// FUNCION COMPROBACION D
// Si son dos dados iguales y son ases, se hunde en el barro

bool seHundeEnElBarro(int &cantDados, int dado1, int dado2, int dado3) {
    bool res;
    if(cantDados == 2) {
        if(dado1 == dado2 && dado1 == 1 && dado2 == 1) {
            //cout << "SE HUNDE EN EL BARRO" << endl;
            //cout << "LAS CARAS SON IGUALES y SON ASES" << endl;
            //cout << "PIERDE TODOS LAS TRUFAS ACUMULADAS EN LAS RONDAS (y la actual)." << endl;
            //cout << "DEBE CEDER SU TURNO AL OTRO CERDO" << endl;
            res = 1;
        } else {
            res = 0;
        }
    } else if(cantDados == 3) {
        if( ((dado1 == dado2 && dado1 == 1 && dado2 == 1) && (dado3 != dado1 && dado3 != 1)) ||
            ((dado2 == dado3 && dado2 == 1 && dado3 == 1) && (dado1 != dado2 && dado1 != 1)) ||
            ((dado3 == dado1 && dado3 == 1 && dado1 == 1) && (dado2 != dado3 && dado2 != 1)) ) {
            //cout << "SE HUNDE EN EL BARRO (con tres dados)" << endl;
            //cout << "LAS CARAS SON IGUALES y SON ASES" << endl;
            //cout << "PIERDE TODOS LAS TRUFAS ACUMULADAS EN LAS RONDAS (y la actual)." << endl;
            //cout << "DEBE CEDER SU TURNO AL OTRO CERDO" << endl;
            res = 1;
        } else {
            res = 0;
        }
    }
    return res;
}

// FUNCION COMPROBACION E
// Si se juega con tres dados y son todos ases (iguales)

bool sonTodosAses(int dado1, int dado2, int dado3) {
    bool res;
    if(dado1 == dado2 && dado2 == dado3 && (dado1 == 1 || dado2 == 1 || dado3 == 1)) {
        //cout << "TODAS LAS CARAS SON IGUALES y SON ASES" << endl;
        //cout << "PIERDE TODOS LAS TRUFAS ACUMULADAS EN TOTAL." << endl;
        //cout << "LAS TRUFAS SERÁN TRASLADADAS AL OTRO CERDO." << endl;
        //cout << "DEBE CEDER SU TURNO AL OTRO CERDO" << endl;
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

// FUNCION COMPROBACION - DEFENSA EXAMEN INTEGRADOR
// Primer jugador que obtenga los dados cuyas caras sean primos. 2, 3 y 5

bool humcerdoPrimo(int &cantDados, int dado1, int dado2, int dado3) {
    bool res;
    if(cantDados == 2) {
        if( (dado1 == 2 || dado1 == 3 || dado1 == 5) && (dado2 == 2 || dado2 == 3 || dado2 == 5)) {
            cout << "LAS CARAS DE LOS DADOS SON NUMEROS PRIMOS" << endl;
            res = 1;
        } else {
            res = 0;
        }

    } else if(cantDados == 3) {
        if( (dado1 == 2 || dado1 == 3 || dado1 == 5) && (dado2 == 2 || dado2 == 3 || dado2 == 5) && (dado3 == 2 || dado3 == 3 || dado3 == 5)) {
            cout << "LAS CARAS DE LOS DADOS SON NUMEROS PRIMOS" << endl;
            res = 1;
        } else {
            res = 0;
        }

    }
    return res;
}



//-------------------------------------------------------------------------------------------------

// FUNCIONES HITOS

//-------------------------------------------------------------------------------------------------
int PDVporCantTrufas(int vecPtsTrufas[][5], int numJug, int cant) {
    int trufas = 0;
    int pdvPorCantTrufas;
    for(int i=0; i<5; i++) {
        trufas+=vecPtsTrufas[numJug][i];
    }
    pdvPorCantTrufas = trufas / cant;
    return pdvPorCantTrufas;
}

void calcularMayorLanzamientos(int &contLanzamientos, int mayorCantLanzamientos[], int &nroJug) {
    if(contLanzamientos > mayorCantLanzamientos[nroJug]) {
        mayorCantLanzamientos[nroJug] = contLanzamientos;
    }
}

//-------------------------------------------------------------------------------------------------

// FUNCIONES FINAL DEL JUEGO

//-------------------------------------------------------------------------------------------------
void finalJuego(int mayorCantLanzamientos[], int vec[][5], string vecNom[], int vOinks[], int vPDV[], string &nombreMaxPDV, int &cantMaxPDV, int &nroJug, int &recompensa) {
    cout << "Ha finalizado el juego. A continuación se mostrarán los hitos alcanzados por cada jugador...";
    rlutil::msleep(4000);
    rlutil::cls();


    titulo();
    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,4);
    cout << "HITO";
    rlutil::locate(sizeColumna,4);
    cout << vecNom[0];
    rlutil::locate(2*sizeColumna,4);
    cout << vecNom[1];
    rlutil::locate(1, 5);
    lineaAncho();
    // HITO - 5 PDV x más trufas en total
    hitoMayorCantTrufas(5, vec, vecNom, vPDV);

    cout << endl << endl;
    // HITO - 1 PDV x cada 50 trufas
    hitoPDVporCantTrufas(50, 1, vec, vecNom, vPDV);

    cout << endl << endl;
    // HITO - 2 PDV * cant. de oinks
    hitoPDVporOinks(2, vOinks, vec, vecNom, vPDV);

    cout << endl << endl;
    // HITO - 3 PDV x Cerdo codicioso
    hitoCerdoCodicioso(3, mayorCantLanzamientos, vecNom, vPDV);

    // nuevo hito
    hitoHumcerdoPrimo(nroJug, recompensa, vPDV);

    rlutil::locate(1,11);
    lineaAncho(); // ESPACIO 11

    // FUNCION PARA CALCULAR GANADORES
    rlutil::locate(1,12);
    cout << "TOTAL";
    rlutil::locate(sizeColumna, 12);
    cout << vPDV[0] << " PDV";
    rlutil::locate(2*sizeColumna, 12);
    cout << vPDV[1] << " PDV";

    // GANADOR EN UBICACIÓN 13
    rlutil::locate(1,14);
    obtenerGanador(vecNom, vPDV);
    // CALCULAR PDV FINALES y GANADOR



    // ACTUALIZA LAS ESTADÍSTICAS
    if(vPDV[0] > cantMaxPDV) {
        nombreMaxPDV = vecNom[0];
        cantMaxPDV = vPDV[0];
    } else if(vPDV[1] > cantMaxPDV) {
        nombreMaxPDV = vecNom[1];
        cantMaxPDV = vPDV[1];
    }
    cout << endl;
    string continuar;
    continuarFinDelJuego(continuar);
}

int obtenerTrufas(int nroJug, int cantRondas, int vec[][5]) {
    int trufas = 0;
    for(int i=0; i<cantRondas; i++) {
        trufas+=vec[nroJug][i];
    }
    return trufas;
}

void hitoMayorCantTrufas(int recompensaPDV, int vec[][5], string vecNom[], int vPDV[]) {
    int trufasA = obtenerTrufas(0, 5, vec);
    int trufasB = obtenerTrufas(1, 5, vec);

    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,6);
    cout << "Más trufas en total";
    // PRIMER JUG
    rlutil::locate(sizeColumna, 6);
    if(trufasA > trufasB || trufasA == trufasB) {
        cout << recompensaPDV << " PDV (" << trufasA << " trufas)";
    } else if(trufasA < trufasB) {
        cout << "0 PDV (" << trufasA << " trufas)";
    }
    // SEG JUG
    rlutil::locate(2*sizeColumna, 6);
    if(trufasB > trufasA || trufasB == trufasA) {
        cout << recompensaPDV << " PDV (" << trufasB << " trufas)";
    } else if(trufasB < trufasA) {
        cout << "0 PDV (" << trufasB << " trufas)";
    }
    if(trufasA > trufasB) {
        vPDV[0]+=recompensaPDV;
    } else if(trufasB > trufasA) {
        vPDV[1]+=recompensaPDV;
    } else if(trufasA == trufasB) {
        vPDV[0]+=recompensaPDV;
        vPDV[1]+=recompensaPDV;
    }
}

void hitoPDVporCantTrufas(int cantTrufas, int recompensaPDV, int vec[][5], string vecNom[], int vPDV[]) {
    int trufasA = obtenerTrufas(0, 5, vec);
    int trufasB = obtenerTrufas(1, 5, vec);

    int pdvA = PDVporCantTrufas(vec, 0, cantTrufas);
    int pdvB = PDVporCantTrufas(vec, 1, cantTrufas);

    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,7);
    cout << "Cada " << cantTrufas << " trufas";
    // PRIMER JUG
    rlutil::locate(sizeColumna,7);
    cout << pdvA << " PDV (" << trufasA << " trufas)";
    // SEG JUG
    rlutil::locate(2*sizeColumna, 7);
    cout << pdvB << " PDV (" << trufasB << " trufas)";
    vPDV[0]+=pdvA;
    vPDV[1]+=pdvB;
}

void hitoPDVporOinks(int recompensa, int vOinks[], int vec[][5], string vecNom[], int vPDV[]) {
    int PDVoinksA = recompensa * vOinks[0];
    int PDVoinksB = recompensa * vOinks[1];
    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,8);
    cout << "Oinks logrados";
    // PRIMER JUG
    rlutil::locate(sizeColumna,8);
    cout << PDVoinksA << " PDV (" << PDVoinksA << " oinks)";
    // SEG JUG
    rlutil::locate(2*sizeColumna, 8);
    cout << PDVoinksB << " PDV (" << PDVoinksB << " oinks)";
    vPDV[0]+=PDVoinksA;
    vPDV[1]+=PDVoinksB;
}

void hitoCerdoCodicioso(int recompensa, int mayorCantLanzamientos[], string vecNom[], int vPDV[]) {

    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,9);
    cout << "Cerdo codicioso";
    // PRIMER JUG
    rlutil::locate(sizeColumna, 9);
    if(mayorCantLanzamientos[0] > mayorCantLanzamientos[1] || mayorCantLanzamientos[0] == mayorCantLanzamientos[1]) {
        cout << recompensa << " PDV (" << mayorCantLanzamientos[0] << " lanzamientos)";
    } else if(mayorCantLanzamientos[0] < mayorCantLanzamientos[1]) {
        cout << "0 PDV (" << mayorCantLanzamientos[0] << " lanzamientos)";
    }
    // SEG JUG
    rlutil::locate(2*sizeColumna, 9);
    if(mayorCantLanzamientos[1] > mayorCantLanzamientos[0] || mayorCantLanzamientos[1] == mayorCantLanzamientos[0]) {
        cout << recompensa << " PDV (" << mayorCantLanzamientos[1] << " lanzamientos)";
    } else if(mayorCantLanzamientos[1] < mayorCantLanzamientos[0]) {
        cout << "0 PDV (" << mayorCantLanzamientos[1] << " lanzamientos)";
    }

    if(mayorCantLanzamientos[0] > mayorCantLanzamientos[1]) {
        vPDV[0]+=recompensa;
    } else if(mayorCantLanzamientos[1] > mayorCantLanzamientos[0]) {
        vPDV[1]+=recompensa;
    } else if(mayorCantLanzamientos[0] == mayorCantLanzamientos[1]) {
        vPDV[0]+=recompensa;
        vPDV[1]+=recompensa;
    }
}

void hitoHumcerdoPrimo(int &nroJug, int recompensa, int vPDV[]) {
    vPDV[nroJug]+=recompensa;
    int sizeColumna = rlutil::tcols() / 3;
    rlutil::locate(1,10);
    cout << "Humcerdo Primo";
    rlutil::locate(sizeColumna, 10);
    if(nroJug == 0) {
        cout << recompensa << " PDV";
    } else {
         cout << "0 PDV";
    }
    rlutil::locate(2*sizeColumna, 10);
    if(nroJug == 1) {
        cout << recompensa << " PDV";
    } else {
         cout << "0 PDV";
    }

}


void obtenerGanador(string vecNom[], int vPDV[]) {
    if(vPDV[0] > vPDV[1]) {
        cout << "GANADOR: " << vecNom[0] << " con " << vPDV[0] << " puntos de victoria." << endl;
    } else if(vPDV[1] > vPDV[0]) {
        cout << "GANADOR: " << vecNom[1] << " con " << vPDV[1] << " puntos de victoria." << endl;
    } else if(vPDV[0] == vPDV[1]) {
        cout << vecNom[0] << " y " << vecNom[1] << " han empatado obteniendo la misma cantidad de puntos de victoria. (" << vPDV[0] << " PDV)" << endl;
    }
}

void continuarFinDelJuego(string &continuar) {
    cout << "Ingrese 'Oink' para continuar: ";
    cin >> continuar;
    verificarOpFinJuego(continuar);
    cout << "Volverá al menú principal..." << endl;
    rlutil::msleep(3000);
    rlutil::cls();
}

string verificarOpFinJuego(string &continuar) {
    if(continuar == "Oink") {
        return continuar;
    } else if(continuar != "Oink") {
        while(continuar != "Oink") {
            cout << "Por favor, ingrese 'Oink' para continuar: ";
            cin >> continuar;
        }
    }
    return continuar;
}

void reiniciarDatosJuego(int vec[][5], string vecNom[], bool vJugoRonda[][5], int vPDV[], int vOinks[], int mayorCantLanzamientos[], int &cantDados) {
    for(int i=0; i<5; i++) {
        vec[0][i] = 0;
        vJugoRonda[0][i] = 0;
        vec[1][i] = 0;
        vJugoRonda[1][i] = 0;
    }
    vecNom[0] = "Jugador 1";
    vecNom[1] = "Jugador 2";
    vPDV[0] = 0;
    vPDV[1] = 0;
    vOinks[0] = 0;
    vOinks[1] = 0;
    mayorCantLanzamientos[0] = 0;
    mayorCantLanzamientos[1] = 0;
    cantDados = 2;
}


//-------------------------------------------------------------------------------------------------

// FUNCIONES APARIENCIA

//-------------------------------------------------------------------------------------------------

void titulo() {
    cout << endl;
    cout << "GRAN CERDO" << endl;
    lineaAncho();
    cout << endl;
}

void lineaAncho() {
    int ancho = rlutil::tcols();
    for(int i=0; i<ancho; i++) {
        cout << "-";
    }

}

void dibujarDado(int &valorDado) {
    if(valorDado == 1) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "|       |" << endl;
        cout << "|   O   |" << endl;
        cout << "|       |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
    if(valorDado == 2) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "|     O |" << endl;
        cout << "|       |" << endl;
        cout << "| O     |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
    if(valorDado == 3) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "|     O |" << endl;
        cout << "|   O   |" << endl;
        cout << "| O     |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
    if(valorDado == 4) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "| O   O |" << endl;
        cout << "|       |" << endl;
        cout << "| O   O |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
    if(valorDado == 5) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "| O   O |" << endl;
        cout << "|   O   |" << endl;
        cout << "| O   O |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
    if(valorDado == 6) {
        cout << endl;
        cout << "+-------+" << endl;
        cout << "| O   O |" << endl;
        cout << "| O   O |" << endl;
        cout << "| O   O |" << endl;
        cout << "+-------+" << endl;
        cout <<  endl;
    }
}

