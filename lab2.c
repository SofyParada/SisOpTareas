#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>


int const CartasXjugador = 10;

static int baraja[44] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44};
static int MisCartas[10];
static int CartasJugador2[10];
static int CartasJugador3[10];
static int CartasJugador4[10];
static int FilasCartas[4][6];

int main() {

    // Barajamos las cartas
    srand(time(NULL));
    for(int i = 0; i < 44; i++) {
        int j = rand() % 44;
        int temp = baraja[i];
        baraja[i] = baraja[j]; //baraja revuelta
        baraja[j] = temp;
    }
    
    // Imprimimos la baraja
    for(int i = 0; i < 44; i++) {
        printf("%d\n", baraja[i]);
    }

    int CartasRepartidas = 0;

    for(int i = 0; i < 4; i++){
        FilasCartas[i][0] = baraja[i];
        CartasRepartidas++;
    }

    printf("Primeras 4 filas\n");
    for(int i = 0; i < 4; i++) {  
        printf("%d\n", FilasCartas[i][0]);
    }

    
    

    for(int i = 0; i < CartasXjugador; i++){
        MisCartas[i] = baraja[CartasRepartidas];
        CartasRepartidas++;
    }

    pid_t jugador2 = fork();

    if(jugador2 == 0){
        
        exit(0);
    }
    for(int i = 0; i < CartasXjugador; i++){
            CartasJugador2[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }

    pid_t jugador3 = fork();

    if(jugador3 == 0){
        int id;
        int id1 = getpid();
        if(id == id1){
            for(int i = 0; i < CartasXjugador; i++){
            CartasJugador3[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
            }
        }
       
        exit(0);
    }

    for(int i = 0; i < CartasXjugador; i++){
        CartasJugador3[i] = baraja[CartasRepartidas];
        CartasRepartidas++;
    }

    pid_t jugador4 = fork();

    if(jugador4 == 0){
        
        exit(0);
    }
    for(int i = 0; i < CartasXjugador; i++){
            CartasJugador4[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }
    
    printf("Mis cartas: ");
    for(int i = 0; i < CartasXjugador; i++){
        printf(", %d", MisCartas[i]);
    }
    printf("\n");

    printf("cartas jugador 2: ");
    for(int i = 0; i < CartasXjugador; i++){
        printf(", %d", CartasJugador2[i]);
    }
    printf("\n");

    printf("cartas jugador 3: ");
    for(int i = 0; i < CartasXjugador; i++){
        printf(", %d", CartasJugador3[i]);
    }
    printf("\n");

    printf("cartas jugador 4: ");
    for(int i = 0; i < CartasXjugador; i++){
        printf(", %d", CartasJugador4[i]);
    }
    printf("\n");


    wait(NULL);
    wait(NULL);
    wait(NULL);
    

    return 0;
}
