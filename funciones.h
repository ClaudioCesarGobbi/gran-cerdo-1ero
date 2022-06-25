#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

//-------------------------------------------------------------------------------------------------

// FUNCIONES EXTRAS
void mostrarEstadisticas(string &nombre, int &cantPDV);
void mostrarCerditos();
void volverAlMenu(char &op);
char verificarOpMenu(char &op);
void confirmarSalirJuego(char &car);
char verificarSalida(char &car);
void presionarTecla();
//-------------------------------------------------------------------------------------------------

// FUNCIONES COMIENZO DEL JUEGO
string nombreJug(string vec[], int numJ);
void pidoNombres(string &jug1, string &jug2);
void elegirPrimerTurno(string &jug1, string &jug2, int &jugActual);
void repetirPrimerTiro(string &jug1, string &jug2, int &jugActual, char &op, int &dado1, int &dado2, int &puntajeJug1, int &puntajeJug2, int &dadoMax1, int &dadoMax2);
//-------------------------------------------------------------------------------------------------

// FUNCIONES MENU PRINCIPAL
void mostrarMenuPrincipal(int &op);
void validarOpcionMenu(int &op);

//-------------------------------------------------------------------------------------------------

// FUNCIONES TIRADA DE DADOS
void lanzamientoDados(int &cantDados, int &dado1, int &dado2, int &dado3);
int tirarDados();
void generarRandom(int &num);

//-------------------------------------------------------------------------------------------------

// FUNCIONES DE COMPROBACIÓN
void confirmarLanzamiento(char &sigue);
char verificarOp(char &car);
bool sePlanta(char &car);
void tiroObligatorio(char &car);
char verificarOpObligatoria(char &car);
bool comprobarCantTrufas(int vec[][5], int cantTrufas);
//-------------------------------------------------------------------------------------------------

// FUNCIONES PARA TURNO JUGADORES
void lanzamientoJug(int &cantDados, int &nroJug, int &nroRonda, int &lanzamientos, int mayorCantLanzamientos[], int vec[][5], string vecNom[], bool vTurno[][5], int vOinks[], int vPDV[], int &jugHumcerdo, int &recompensaHumcerdo, bool &humcerdo);
int determinarProxTurno(int &jugadorActual);
void cambioTurno(int &jugadorActual, int otroJug, int &nroRonda, bool vTurno[][5]);

//-------------------------------------------------------------------------------------------------

// FUNCIONES PARA SUMAR/QUITAR/OBTENER/MOSTRAR PUNTOS
void sumarTrufasRonda(int &RONDAS, int &nroJug, int vec[][5], int &puntos);
void quitarTrufasRonda(int &nroRonda, int &nroJug, int vec[][5], int &puntos);
int obtenerPuntos(int vec[][5], int nroJug);
int obtenerPuntosRonda(int &nroRonda, int &nroJug, int vec[][5]);
void mostrarPuntajes(string vecNom[], int vec[][5]);
void mostrarDatosRonda(string vecNom[], int vec[][5], int &nroJug, int &nroRonda, int &lanzamientos);

//-------------------------------------------------------------------------------------------------

// FUNCIONES REGLAS DEL JUEGO

// regla A - Sumar trufas si los dados son distintos y no son as
bool sonDistintosNiAses(int &cantDados, int dado1, int dado2, int dado3);
// regla B - Realiza un OINK si dos dados son iguales y no son as
bool realizaOink(int &cantDados, int dado1, int dado2, int dado3);
// regla C - Cara distintas y hay un as, pierde los puntos de la ronda y cede el turno.
bool sonDistintasHayAs(int &cantDados, int dado1, int dado2, int dado3);
// regla D - Se hunde en el barro, pierde el total de los puntos, se juega con tres dados y cede el turno.
bool seHundeEnElBarro(int &cantDados, int dado1, int dado2, int dado3);
// REGLA E - Los dados son todos iguales y son ases
bool sonTodosAses(int dado1, int dado2, int dado3);
// funcion defensa examen
bool humcerdoPrimo(int &cantDados, int dado1, int dado2, int dado3);



//-------------------------------------------------------------------------------------------------

// FUNCIONES POR HITOS
int PDVporCantTrufas(int vecPtsTrufas[][5], int numJug, int cant);
void calcularMayorLanzamientos(int &contLanzamientos, int mayorCantLanzamientos[], int &nroJug);
//-------------------------------------------------------------------------------------------------

// FUNCIONES FINAL DEL JUEGO
void finalJuego(int mayorCantLanzamientos[], int vec[][5], string vecNom[], int vOinks[], int vPDV[], string &nombreMaxPDV, int &cantMaxPDV, int &nroJug, int &recompensa);
int obtenerTrufas(int nroJug, int cantRondas, int vec[][5]);
void hitoMayorCantTrufas(int recompensaPDV, int vec[][5], string vecNom[], int vPDV[]);
void hitoPDVporCantTrufas(int cantTrufas, int recompensaPDV, int vec[][5], string vecNom[], int vPDV[]);
void hitoPDVporOinks(int recompensa, int vOinks[], int vec[][5], string vecNom[], int vPDV[]);
void hitoCerdoCodicioso(int recompensa, int mayorCantLanzamientos[], string vecNom[], int vPDV[]);
// defensa
void hitoHumcerdoPrimo(int &nroJug, int recompensa, int vPDV[]);



void obtenerGanador(string vecNom[], int vPDV[]);
void continuarFinDelJuego(string &continuar);
string verificarOpFinJuego(string &continuar);
void reiniciarDatosJuego(int vec[][5], string vecNom[], bool vJugoRonda[][5], int vPDV[], int vOinks[], int mayorCantLanzamientos[], int &cantDados);

//-------------------------------------------------------------------------------------------------

// FUNCIONES APARIENCIA

//-------------------------------------------------------------------------------------------------
void titulo();
void lineaAncho();
void dibujarDado(int &valorDado);
#endif // FUNCIONES_H_INCLUDED
