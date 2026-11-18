#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 50

typedef char tString[MAX];

typedef struct{
    tString nombre;
    bool vivo;
    int rol;
    int puntos;
    int votos;
}tJugador;


typedef struct nodo{
    tJugador jugador;
    struct nodo *siguiente;
}tListaJugadores;

void iniciarLista(tListaJugadores **pPartida);
void agregarJugadores(tListaJugadores **pPartida, int *cantJugadores);
void asignarRoles(tListaJugadores **pPartida, int cantJugadores);
void iniciarJugadores(tListaJugadores **pPartida);
void inicioRonda(tListaJugadores **pPartida);
void inicioPartida(tListaJugadores **pPartida);
void faseNocturna(tListaJugadores **pPartida);
void faseDiurna(tListaJugadores **pPartida);
int verificarGanador(tListaJugadores *pPartida);
void sumarPuntos(tListaJugadores **pPartida);
void mostrarPuntos(tListaJugadores **pPartida);

int main(){
    tListaJugadores *pPartida;
    iniciarLista(&pPartida);
    int cantJugadores;
    srand(time(NULL));
    printf("\n===== IMPOSTOR =====");
    printf("aca van las reglas pero me dio paja ponerlas.");
    printf("\nPresione ""Enter"" para iniciar el juego.");
    getchar();
    agregarJugadores(&pPartida, &cantJugadores);
    asignarRoles(&pPartida, cantJugadores);
    inicioPartida(&pPartida);
    mostrarPuntos(&pPartida);
    return 0;
}

void iniciarLista(tListaJugadores **pPartida){
    *pPartida = NULL;
}

void agregarJugadores(tListaJugadores **pPartida, int *cantJugadores){
    int i;
    printf("\nIngrese la cantidad de jugadores que van a jugar (Min. 5):");
    scanf("%d", cantJugadores);
    getchar();
    for(i = 0; i < *cantJugadores; i++){
        tListaJugadores *nuevoJugador;
        nuevoJugador = (tListaJugadores*) malloc(sizeof(tListaJugadores));
        printf("\nIngrese el nombre del jugador:");
        fgets(nuevoJugador->jugador.nombre, MAX, stdin);
        nuevoJugador->siguiente = *pPartida;
        *pPartida = nuevoJugador;
    }
}

void asignarRoles(tListaJugadores **pPartida, int cantJugadores){
    int posPolicia = (rand() % cantJugadores) + 1;
    int posAsesino;
    do{
        posAsesino = (rand() % cantJugadores) + 1;
    }while(posAsesino == posPolicia);
    tListaJugadores *aux = *pPartida;
    int pos = 1;
    while(aux != NULL){
        if(pos == posPolicia){
            aux->jugador.rol = 1; // 1 es el rol de policia
        }else if(pos == posAsesino){
            aux->jugador.rol = 2; // 2 es el rol de asesino
        }else{
            aux->jugador.rol = 3; // 3 es el rol de ciudadano (solo puede votar)
        }
        aux = aux->siguiente;
        pos++;
    }
}

void iniciarJugadores(tListaJugadores **pPartida){
    tListaJugadores *aux = *pPartida;
    while(aux != NULL){
        aux->jugador.vivo = true;
        aux->jugador.puntos = 0;
        aux->jugador.votos = 0;
        aux =  aux->siguiente;
    }
}

void inicioRonda(tListaJugadores **pPartida){
    tListaJugadores *aux = *pPartida;
    while(aux != NULL){
        aux->jugador.votos = 0;
        aux =  aux->siguiente;
    }
}

void inicioPartida(tListaJugadores **pPartida){
    int estado = 0; // 0 continua la partida, 1 gano el pueblo, 2 gano el asesino
    iniciarJugadores(pPartida);
    do{
        inicioRonda(pPartida);
        faseNocturna(pPartida);
        sumarPuntos(pPartida);
        estado = verificarGanador(*pPartida);
        if(estado != 0){
            break;
        }
        faseDiurna(pPartida);
        estado = verificarGanador(*pPartida);
    }while(estado == 0);
    if(estado == 1){
        printf("\nEl pueblo gano la partida.");
    }else{
        printf("\nEl asesino gano la partida.");
    }
}

void faseNocturna(tListaJugadores **pPartida){
    tListaJugadores *aux = * pPartida;
    tListaJugadores *victima = NULL;
    tListaJugadores *temporal;
    int opcion, contador;
    while( aux != NULL){
        if(aux->jugador.vivo == true){
            printf("\nPasale el dispositivo a: %s", aux->jugador.nombre);
            printf("\nPresione Enter para ver su turno...");
            getchar();
            system("cls");
            if(aux->jugador.rol == 1){
                printf("\n--- Turno del policia ---");
                printf("\nElije a quien investigar:");
                temporal = *pPartida;
                contador = 1;
                while(temporal != NULL){
                    if(temporal->jugador.vivo == true && temporal != aux){
                        printf("\n%d) %s", contador, temporal->jugador.nombre);
                        contador++;
                    }
                    temporal = temporal->siguiente;
                }
                printf("\nOpcion:");
                scanf("%d", &opcion);
                getchar();
                temporal = *pPartida;
                contador = 1;
                while(temporal != NULL){
                    if(temporal->jugador.vivo == true && temporal != aux){
                        if(contador == opcion){
                            break;
                        }
                        contador++;
                    }
                    temporal = temporal->siguiente;
                }
                if(temporal != NULL){
                    if(temporal->jugador.rol == 3){
                        printf("\n %s es INOCENTE.",temporal->jugador.nombre);
                    }else{
                        printf("\n %s es el ASESINO.", temporal->jugador.nombre);
                    }
                }
                printf("\nPresiona enter para terminar tu turno....");
                getchar();
            }else if(aux->jugador.rol == 2){
                printf("\n--- Turno del asesino ---");
                printf("\nElije la victima de esta noche:");
                temporal = *pPartida;
                contador = 1;
                while(temporal != NULL){
                    if(temporal->jugador.vivo == true && temporal != aux){
                        printf("\n%d) %s.", contador, temporal->jugador.nombre);
                        contador++;
                    }
                    temporal = temporal->siguiente;
                }
                printf("\nOpcion:");
                scanf("%d", &opcion);
                getchar();
                temporal = *pPartida;
                contador = 1;
                while( temporal  != NULL){
                    if(temporal->jugador.vivo == true && temporal != aux){
                        if(contador == opcion){
                            break;
                        }
                        contador++;
                    }
                    temporal = temporal->siguiente;
                }
                victima = temporal;
                printf("\nObjetivo seleccionado.Presiona Enter para terminar tu turno.");
                getchar();
            }else{
                printf("\n--- Turno del ciudadano ---");
                printf("\nAhora mismo no puedes hacer nada. Disimula para no levantar sospechas.");
                printf("\nPreciona Enter para terminar tu turno...");
                getchar();
            }
            system("cls");
        }
        aux = aux->siguiente;
    }
    if(victima !=NULL){
        victima->jugador.vivo = false;
        printf("\n--- Amanece el pueblo ---");
        printf("\nDurante la noche  %s fue asesinado/a.", victima->jugador.nombre);
        printf("\nPresionen Enter para continuar...");
        getchar();
    } 
}

void faseDiurna(tListaJugadores **pPartida){
    tListaJugadores *aux = *pPartida; 
    tListaJugadores *temporal;
    tListaJugadores *expulsado = NULL;
    int maxVotos = -1;
    bool empate = false;
    int opcion, contador;
    while(aux != NULL){
        if(aux->jugador.vivo == true){
            printf("\nPasale el dispositivo a: %s", aux->jugador.nombre);
            printf("\nPresiona Enter para iniciar tu turno...");
            getchar();
            system("cls");
            printf("\n--- Votaciones ---");
            temporal = *pPartida;
            contador = 1;
            while(temporal != NULL){
                if(temporal->jugador.vivo == true && temporal != aux){
                    printf("\n%d) %s",contador, temporal->jugador.nombre);
                    contador++;
                }
                temporal = temporal->siguiente;
            }
            printf("\nSelecciona a quien votar:");
            scanf("%d", &opcion);
            getchar();
            temporal = *pPartida;
            contador = 1;
            while(temporal != NULL){
                if(temporal->jugador.vivo == true && temporal != aux){
                    if(opcion == contador){
                        temporal->jugador.votos++;
                        break;
                    }
                    contador++;
                }
                temporal = temporal->siguiente;
            }
            printf("\nVoto guardado con exito.");
            printf("\nPresiona Enter para terminar tu turno...");
            getchar();
            system("cls");
        }
        aux = aux->siguiente;
    }
    temporal = *pPartida;
    while(temporal != NULL){
        if(temporal->jugador.vivo == true){
            if(temporal->jugador.votos > maxVotos){
                maxVotos = temporal->jugador.votos;
                expulsado = temporal;
                empate = false;
            }else if(temporal->jugador.votos == maxVotos){
                empate = true;
            }
        }
        temporal = temporal->siguiente;
    }
    printf("\n--- Resultado de la votacion ---");
    if(empate){
        printf("\nHubo un empate en las votaciones. Nadie fue expulsado hoy.");
    }else if(expulsado != NULL){
        expulsado->jugador.vivo = false;
        printf("\nEl pueblo ha decidido. %s fue expulsado.", expulsado->jugador.nombre);
        if(expulsado->jugador.rol == 2){
            printf("Era el asesino.");
        }else{
            printf("\nNo era el asesino.");
        }
    }
    printf("\n\nPresion Enter para continuar...");
    getchar();
    system("cls");
}

int verificarGanador(tListaJugadores *pPartida){
    tListaJugadores *aux = pPartida;
    int vivos = 0;
    bool asesinoVivo = false;
    while(aux != NULL){
        if(aux->jugador.vivo == true){
            vivos++;
            if(aux->jugador.rol == 2){
                asesinoVivo = true;
            }
        }
        aux = aux->siguiente;
    }
    if(!asesinoVivo){
        return 1;
    }else if( vivos <= 2){
        return 2;
    }else{
        return 0;
    }
}

void sumarPuntos(tListaJugadores **pPartida){
    tListaJugadores *aux = *pPartida;
    while(aux != NULL){
        if(aux->jugador.vivo == true){
            aux->jugador.puntos++;
        }
        aux = aux->siguiente;
    }
}

void mostrarPuntos(tListaJugadores **pPartida){
    tListaJugadores *aux = *pPartida;
    while(aux != NULL){
        printf("%s : %d puntos", aux->jugador.nombre, aux->jugador.puntos);
        aux = aux->siguiente;
    }
}
