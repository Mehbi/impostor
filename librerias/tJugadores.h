#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tString.h"


typedef struct {
    int idPartida; 
    tString nombre;
    bool estaVivo;
}tJugador; 

typedef struct nodo { 
    tJugador jugador; 
    struct nodo *siguiente; 
}tJugadores;


tJugador crearJugador(); 
void inicializarJugadores(tJugadores**); 
bool sinJugadores(tJugadores*); 
void insertarPrimero(tJugadores**, tJugador); 
void insertarAdelante(tJugadores**, tJugador); 
void eliminarJugador(tJugadores**, tJugador);
void visualizarJugadores(tJugadores**); 
void liberarLista(tJugadores**); 

void inicializarLista(tJugadores **lista) {
    *lista = NULL; 
}

bool sinJugadores(tJugadores *lista) {
    return lista == NULL; 
}
void insertarPrimero(tJugadores **lista, tJugador jugador) {
    tJugadores *nuevoNodo = (tJugadores *)malloc(sizeof(tJugadores));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    nuevoNodo->jugador = jugador;
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
}

void insertarAdelante(tJugadores **lista, tJugador jugador) {
    tJugadores *nuevoNodo = (tJugadores *)malloc(sizeof(tJugadores));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    nuevoNodo->jugador = jugador;
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
}


tJugador crearJugador() {
    tJugador nuevoJugador; 
    
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", nuevoJugador.nombre);
    
    nuevoJugador.estaVivo = true;
    return nuevoJugador;
}

void insertarJugador(tJugadores** pJugadores, tJugador pJugador) {
    if (sinJugadores(*pJugadores)) {
        insertarPrimero(pJugadores, pJugador); 
    } else {
        insertarAdelante(pJugadores, pJugador); 
    }
}