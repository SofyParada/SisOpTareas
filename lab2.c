#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>


int const CartasXjugador = 10;

static int baraja[44] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44};
static int MisCartas[10];
static int CartasJugador2[10];
static int CartasJugador3[10];
static int CartasJugador4[10];
static int FilasCartas[4][6];
static int fd1[2];
static int fd2[2];
static int fd3[2];
static int fd4[2];




/*
Funcion BotRevisarCarta | Toma de parametros el mazo de un jugador con el tamano de este y la matriz de las cartas en mesa

Primero elige una fila aleatoria en donde colocar la carta
Despues elige la carta menor del mazo en caso de que no se pueda tirar otra,
Elige la carta mas cercana a la ultima de la fila restandolas y comparando con las otras cartas quien tiene el resto menor

Retorna la carta a jugar.

*/

int BotRevisarCarta(int *mazo,int ncartas, int *matriz, int filas, int columnas){
        int i,menor,resto,ultimo,restomenor,retorno,posm,pos;
        int fila = rand() % 4;
        //printf("La fila elegida fue: %i\n",fila+1);
        for(i = 0; i < columnas ; i++){
            if (*(matriz + fila * columnas + i) != 0){
                ultimo = *(matriz + fila * columnas + i); //Busca cual es la ultima carta de la fila elegida
            }
            else if (*(matriz + fila * columnas + i) == 0){
                break;
            }        
        }
        
        restomenor = 50;
        menor = 50;
        for (i=0;i<ncartas;i++){
            resto = mazo[i] - ultimo;  //Calcula resto
            if(mazo[i] < menor && mazo[i] != 0){  //Busca la carta que sea menor en el mazo de un jugador
                menor = mazo[i];
                posm = i;
            }
            if (resto < restomenor && resto > 0 && mazo[i] != 0){  //Cambia la carta a una que sea mas cercana al numero
                retorno = mazo[i];
                pos = i;
                restomenor = resto;
            }
                
        }
    if (retorno != 0){
        mazo[pos] = 0;
        return retorno;
    }
    else {
        mazo[posm] = 0;
        return menor;
    }
}

int compare_integers(const void *a, const void *b) {
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ia - *ib;
}






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
    /*
    for(int i = 0; i < 44; i++) {
        printf("%d\n", baraja[i]);
    }
    */

    int CartasRepartidas = 0;

    for(int i = 0; i < 4; i++){
        FilasCartas[i][0] = baraja[i];
        CartasRepartidas++;
    }

    printf("Primeras 4 filas\n");
    for(int i = 0; i < 4; i++) {  
        printf("%d\n", FilasCartas[i][0]);
    }
    //Creamos pipe
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pipe(fd4);

    //Siguientes lineas crean los 4 procesos respectivos para cada jugadores y almacena sus ID
    int i,ID_actual,ppid;
    int jugador1,jugador2,jugador3,jugador4;
    char str[32];
    ppid = getpid();
    //printf("Soy el proceso padre con ID: %i\n",ppid);
    for (i = 0; i < 4; i++) {
        int pid = fork();
        if (pid == 0 && getppid() == ppid) {  //Si el proceso es un hijo y su proceso padre es el proceso original
            switch (i) {
                case 0:
                    jugador1 = getpid();
                    //printf("Soy el jugador 1 de ID: %i\n",jugador1);
                    break;
                case 1:
                    jugador2 = getpid();
                    //printf("Soy el jugador 2 de ID: %i\n",jugador2);
                    break;
                case 2:
                    jugador3 = getpid();
                    //printf("Soy el jugador 3 de ID: %i\n",jugador3);
                    break;
                case 3:
                    jugador4 = getpid();
                    //printf("Soy el jugador 4 de ID: %i\n",jugador4);
                    break;    
                }


            
        } 
        if (pid == 0 && getppid() != ppid){
            exit(0);
        }
        else {
            continue;
        }
    }
    int Mazo1[10];
    int Mazo2[10];
    int Mazo3[10];
    int Mazo4[10];


    //Se crean barajas para cada jugador, y las manda a cada jugador a traves de pipes

    if(getpid() == ppid){

        sleep(2);
        for(int i = 0; i < CartasXjugador; i++){
            MisCartas[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }


        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador2[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }

        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador3[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }

        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador4[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }

        printf("\n");    

        

        write(fd1[1], MisCartas, sizeof(MisCartas));
        close(fd1[1]);


        write(fd2[1], CartasJugador2, sizeof(CartasJugador2));
        close(fd2[1]);


        write(fd3[1], CartasJugador3, sizeof(CartasJugador3));
        close(fd3[1]);


        write(fd4[1], CartasJugador4, sizeof(CartasJugador4));
        close(fd4[1]);
             
    }
    //Jugadores reciben sus cartas
        
    if (getpid() == jugador1){

        read(fd1[0], Mazo1, sizeof(Mazo1));

        printf("Cartas jugador 1: ");
            for(int i = 0; i < 10; i++){
                if (i==0){
                    printf("%d", Mazo1[i]);
                }
                else{
                    printf(", %d", Mazo1[i]);
                }
            }
        printf("\n");
    }

    if (getpid() == jugador2){
        sleep(2);
        read(fd2[0], Mazo2, sizeof(Mazo2));

        printf("Cartas jugador 2: ");
            for(int i = 0; i < 10; i++){
                if (i==0){
                    printf("%d", Mazo2[i]);
                }
                else{
                    printf(", %d", Mazo2[i]);
                }
            }
        printf("\n");
    }

    if (getpid() == jugador3){
        sleep(3);
        read(fd3[0], Mazo3, sizeof(Mazo3));

        printf("Cartas jugador 3: ");
            for(int i = 0; i < 10; i++){
                if (i==0){
                    printf("%d", Mazo3[i]);
                }
                else{
                    printf(", %d", Mazo3[i]);
                }
            }
        printf("\n");
    }

    if (getpid() == jugador4){
        sleep(4);

        read(fd4[0], Mazo4, sizeof(Mazo4));

        printf("Cartas jugador 4: ");
            for(int i = 0; i < 10; i++){
                if (i==0){
                    printf("%d", Mazo4[i]);
                }
                else{
                    printf(", %d", Mazo4[i]);
                }
            }
        printf("\n");
    }

    int Carta1,Carta2,Carta3,Carta4,j;
    int buffer1,buffer2,buffer3,buffer4;

    for(i=0;i<2;i++){

        if (getpid() == ppid){ //Recibe cartas jugadas por cada jugador y las imprime
            int orden[4];
            sleep(3);
            printf("Turno numero: %d\n\n",i +1);

            read(fd1[0], &buffer1, sizeof(int));
            orden[0] = buffer1;
            read(fd2[0], &buffer2, sizeof(int));
            orden[1] = buffer2;
            read(fd3[0], &buffer3, sizeof(int));
            orden[2] = buffer3;
            read(fd4[0], &buffer4, sizeof(int));
            orden[3] = buffer4;


            printf("La carta culia que jugo 1 es: %d\n",buffer4);
            printf("La carta culia que jugo 2 es: %d\n",buffer2);
            printf("La carta culia que jugo 3 es: %d\n",buffer3);
            printf("La carta culia que jugo 4 es: %d\n",buffer4);     
        }

        if (getpid() == jugador1){  //Ejecuta funcion para jugar carta y la manda a padre
            int a;
            Carta1 = BotRevisarCarta(Mazo1,10, &FilasCartas[0][0],4,6);
            write(fd1[1], &Carta1, sizeof(int));

        }

        if (getpid() == jugador2){ //Ejecuta funcion para jugar carta y la manda a padre
            Carta2 = BotRevisarCarta(Mazo2,10, &FilasCartas[0][0],4,6);
            //printf("El jugador 2 ha elegido la carta: %d\n",Carta2);
            write(fd2[1], &Carta2, sizeof(int));
        }

        if (getpid() == jugador3){ //Ejecuta funcion para jugar carta y la manda a padre
            Carta3 = BotRevisarCarta(Mazo3,10, &FilasCartas[0][0],4,6);
            //printf("El jugador 3 ha elegido la carta: %d\n",Carta3);
            write(fd3[1], &Carta3, sizeof(int));
        }
        if (getpid() == jugador4){ //Ejecuta funcion para jugar carta y la manda a padre
            Carta4 = BotRevisarCarta(Mazo4,10, &FilasCartas[0][0],4,6);
            //printf("El jugador 4 ha elegido la carta: %d\n",Carta4);
            write(fd4[1], &Carta4, sizeof(int));
        }
    }
    close(fd2[1]);  //Cierra todas las pipes
    close(fd2[0]);
    close(fd3[1]);
    close(fd3[0]);
    close(fd4[1]);
    close(fd4[0]);

    return 0;
}


