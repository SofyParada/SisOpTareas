#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int const CartasXjugador = 10;

static int baraja[44] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44};
static int MisCartas[10];
static int CartasJugador2[10];
static int CartasJugador3[10];
static int CartasJugador4[10];
static int FilasCartas[4][6];
static int ListaID[4];


/*
Funcion BotRevisarCarta | Toma de parametros el mazo de un jugador con el tamano de este y la matriz de las cartas en mesa

Primero elige una fila aleatoria en donde colocar la carta
Despues elige la carta menor del mazo en caso de que no se pueda tirar otra,
Elige la carta mas cercana a la ultima de la fila restandolas y comparando con las otras cartas quien tiene el resto menor

Retorna la carta a jugar.

*/

int BotRevisarCarta(int *mazo,int ncartas, int *matriz, int filas, int columnas){
        int i,menor,resto,ultimo,restomenor,retorno;
        int fila = rand() % 4;
        printf("La fila elegida fue: %i\n",fila+1);
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
            printf("La carta actual es: %d\n",mazo[i]);
            resto = mazo[i] - ultimo;  //Calcula resto
            printf("El resto es %d\n",resto);
            if(mazo[i] < menor){  //Busca la carta que sea menor en el mazo de un jugador
                menor = mazo[i];
            }
            if (resto < restomenor && resto > 0){  //Cambia la carta a una que sea mas cercana al numero
                printf("Se cambia retorno por uno menor\n");
                retorno = mazo[i];
                restomenor = resto;
            }
                
        }
    if (retorno != 0){
        printf("Se retorna cercana\n");
        return retorno;
    }
    else {
        printf("Se retorna menor\n");
        return menor;
    }
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

    //Siguientes lineas crean los 4 procesos respectivos para cada jugadores y almacena sus ID
    int i,ID_actual,ppid;
    int jugador1,jugador2,jugador3,jugador4;
    char string[10];
    ppid = getpid();
    printf("Soy el proceso padre con ID: %i\n",ppid);
    for (i = 0; i < 4; i++) {
        int pid = fork();
        if (pid == 0 && getppid() == ppid) {  //Si el proceso es un hijo y su proceso padre es el proceso original
            switch (i) {
                case 0:
                    jugador1 = getpid();
                    ListaID[0] = jugador1;
                    printf("Soy el jugador 1 de ID: %i\n",jugador1);
                    break;
                case 1:
                    jugador2 = getpid();
                    ListaID[1] = jugador2;
                    printf("Soy el jugador 2 de ID: %i\n",jugador2);
                    break;
                case 2:
                    jugador3 = getpid();
                    ListaID[2] = jugador3;
                    printf("Soy el jugador 3 de ID: %i\n",jugador3);
                    break;
                case 3:
                    jugador4 = getpid();
                    ListaID[3] = jugador4;
                    printf("Soy el jugador 4 de ID: %i\n",jugador4);
                    break;    
                }


            
        } 
        else {
            continue;
        }
    }
    


    //Se crean barajas para cada jugador, verificando que el padre sea quien las crea


    if(getpid() == ppid){
        for(int i = 0; i < CartasXjugador; i++){
            MisCartas[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }
        printf("Mis cartas: ");
        for(int i = 0; i < CartasXjugador; i++){
            if (i==0){
                printf("%d", MisCartas[i]);
            }
            else{
            printf(", %d", MisCartas[i]);
            }
        }
        printf("\n");    
    }   
    

    if(getpid() == ppid){
        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador2[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }
        printf("Cartas jugador 2: ");
        for(int i = 0; i < CartasXjugador; i++){
            if (i==0){
                printf("%d", CartasJugador2[i]);
            }
            else{
            printf(", %d", CartasJugador2[i]);
            }
        }
        printf("\n");
        
    }


    if(getpid() == ppid){
        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador3[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }
        printf("Cartas jugador 3: ");
        for(int i = 0; i < CartasXjugador; i++){
            if (i==0){
                printf("%d", CartasJugador3[i]);
            }
            else{
            printf(", %d", CartasJugador3[i]);
            }
        }
        printf("\n");
        
    }

    if(getpid() == ppid){
        for(int i = 0; i < CartasXjugador; i++){
            CartasJugador4[i] = baraja[CartasRepartidas];
            CartasRepartidas++;
        }
        printf("Cartas jugador 4: ");
        for(int i = 0; i < CartasXjugador; i++){
            if (i==0){
                printf("%d", CartasJugador4[i]);
            }
            else{
            printf(", %d", CartasJugador4[i]);
            }
        }
        printf("\n");
    }

    if (getpid() == ppid){
        int caca = BotRevisarCarta(CartasJugador4,10, &FilasCartas[0][0],4,6);
        printf("La carta a utilizar sera %i\n",caca);
    }
    

    return 0;
}
