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


int calculopuntos(int a){
    int aux;
    if (a%11 == 0){
        //printf("Se le suman 5");
        return 5;
    }
    if (a%10 == 0){
        //printf("Se le suman 3");
        return 3;
    }
    if (a%5 == 0){
        //printf("Se le suman 2");
        return 2;
    }
    else{
        //printf("Se le suman 1");
        return 1;
    }
}


int ultimoxfila(int *matriz, int filas, int columnas, int carta){
    int ultimo, posx,posy,si,menor;
    int i,j;
    si = 50;
    //printf("La fila elegida fue: %i\n",fila+1);
    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas ; j++){
            if (*(matriz + i * columnas + j) != 0){
                ultimo = *(matriz + i * columnas + j); //Busca cual es la ultima carta de la fila elegida
            }
            else if (*(matriz + i * columnas + j) == 0){
                break;
            }        
        }
        menor = carta - ultimo;
        if (menor > 0 && menor < si){
            si = menor;
            posx = i;
            //printf("La fila a reemplazar es: %d",posx);

            posy = j;
            //printf("La columna a reemplazar es: %d",posy);

            //printf("La carta a jugar sera %d con un resto de %d, despues de %d\n",carta,menor,ultimo);
        }

        
    }

    if (posy == 5){
        int neg = 0;
        printf("La carta %d esta en la sexta posicion, se asignan puntos negativos\n",carta);
        for (i =0;i<5;i++){
            neg = neg + calculopuntos(*(matriz + posx * columnas + i));
        }
        printf("Los puntos negativos asignados son: %d",neg);
        *(matriz + posx * columnas + 0) = carta;
        *(matriz + posx * columnas + 1) = 0;
        *(matriz + posx * columnas + 2) = 0;
        *(matriz + posx * columnas + 3) = 0;
        *(matriz + posx * columnas + 4) = 0;
        *(matriz + posx * columnas + 5) = 0;
        return neg;
    }
    else if (si == 50){
        printf("La carta %d no cabe en ningun espacio, se asignan puntos negativos\n",carta);
        int neg = 0;
        int fila = rand() % 4;
        for (i =0;i<5;i++){
            neg = neg + calculopuntos(*(matriz + posx * columnas + i));
        }
        *(matriz + fila * columnas + 0) = carta;
        *(matriz + fila * columnas + 1) = 0;
        *(matriz + fila * columnas + 2) = 0;
        *(matriz + fila * columnas + 3) = 0;
        *(matriz + fila * columnas + 4) = 0;
        *(matriz + fila * columnas + 5) = 0;


        return neg;
    }
    else{
        *(matriz + posx * columnas + posy) = carta;
        return 0;
    }
}


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

int compare(const void *a, const void *b) {
    const int *auxa = (const int *)a;
    const int *auxb = (const int *)b;
    return *auxa - *auxb;
}

void sigcont_handler(int signal_number) {
}




int main() {

    signal(SIGCONT, sigcont_handler);
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


    //Se crean barajas para cada jugador, verificando que el padre sea quien las cree

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
    
    if (getpid() == jugador1){

        read(fd1[0], Mazo1, sizeof(Mazo1));

        /*
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
        */
    }

    if (getpid() == jugador2){
        read(fd2[0], Mazo2, sizeof(Mazo2));

        /*
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
        */
    }

    if (getpid() == jugador3){
        read(fd3[0], Mazo3, sizeof(Mazo3));

        /*
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
        */
    }

    if (getpid() == jugador4){

        read(fd4[0], Mazo4, sizeof(Mazo4));

        /*
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
        */
    }

    int Carta1,Carta2,Carta3,Carta4,j,neg;
    int buffer1,buffer2,buffer3,buffer4;
    int neg1 = 0;
    int neg2 = 0;
    int neg3 = 0;
    int neg4 = 0;
    bool flag = false;
    for(i=0;i<10;i++){

        if (getpid() == ppid){
            pause();
            sleep(3);
            printf("Turno numero: %d\n\n",i +1);

            read(fd1[0], &buffer1, sizeof(int));
            read(fd2[0], &buffer2, sizeof(int));
            read(fd3[0], &buffer3, sizeof(int));
            read(fd4[0], &buffer4, sizeof(int));

            int orden[4] = {buffer1,buffer2,buffer3,buffer4};
            int n = sizeof(orden) / sizeof(orden[0]);
            qsort(orden, n, sizeof(int), compare);
            printf("\n ");
            printf("\n ");

            printf("La carta que jugo 1 es: %d\n",buffer1);
            printf("La carta que jugo 2 es: %d\n",buffer2);
            printf("La carta que jugo 3 es: %d\n",buffer3);
            printf("La carta que jugo 4 es: %d\n",buffer4);

            //Se colocan cartas
            for (j=0;j<4;j++){
                neg = ultimoxfila(&FilasCartas[0][0],4,6,orden[j]);
                //Calculo puntajes
                if (orden[j] == buffer1){
                    neg1 = neg1 + neg;
                }
                if (orden[j] == buffer2){
                    neg2 = neg2 + neg;
                }
                if (orden[j] == buffer3){
                    neg3 = neg3 + neg;
                }
                if (orden[j] == buffer4){
                    neg4 = neg4 + neg;
                }
            }
            
            printf("\n ");

            printf("Las filas quedaron:\n");
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 6; j++){
                    printf("%d ", FilasCartas[i][j]);
                }
                printf("\n");
            }
            printf("\n ");

            kill(jugador1,SIGCONT);


        }

        if (getpid() == jugador1){
            sleep(3);
            int a;
            printf("Mis cartas son: ");
            for(int j = 0; j < 10; j++){
                if (j==0){
                    printf("%d", Mazo1[j]);
                }
                else{
                    printf(", %d", Mazo1[j]);
                }
            }
            printf("\n");
            flag = false;
            while(flag==false){
                printf("Ingresar carta a jugar: ");
                scanf("%d",&a);
                for(j = 0;j<10;j++){
                    if (Mazo1[j] == a){
                        flag = true;
                        Mazo1[j] = 0;
                        kill(jugador2,SIGCONT);
                        break;
                    }
                    
                }
                if (flag==false){
                    printf("No tiene esa carta, porfavor intentelo denuevo.\n");
                }
            }

            

            write(fd1[1], &a, sizeof(int));
            pause();
            

        }

        if (getpid() == jugador2){

            pause();
            Carta2 = BotRevisarCarta(Mazo2,10, &FilasCartas[0][0],4,6);
            write(fd2[1], &Carta2, sizeof(int));
            pause();

        }

        if (getpid() == jugador3){
            pause();
            Carta3 = BotRevisarCarta(Mazo3,10, &FilasCartas[0][0],4,6);
            write(fd3[1], &Carta3, sizeof(int));
            pause();

        }
        if (getpid() == jugador4){
            pause();
            Carta4 = BotRevisarCarta(Mazo4,10, &FilasCartas[0][0],4,6);
            write(fd4[1], &Carta4, sizeof(int));
            pause();

        }
    }
    close(fd2[1]);
    close(fd2[0]);
    close(fd3[1]);
    close(fd3[0]);
    close(fd4[1]);
    close(fd4[0]);
    
    if (getpid() == ppid){
        printf("Los puntajes finales fueron:\n");
        printf("Jugador 1: %d\n",neg1);
        printf("Jugador 2: %d\n",neg2);
        printf("Jugador 3: %d\n",neg3);
        printf("Jugador 4: %d\n",neg4);

        if(neg1 < neg2 && neg1 < neg3 && neg1 < neg4){
            printf("El ganador fue el jugador 1!\n");    
        }
        if(neg2 < neg1 && neg2 < neg3 && neg2 < neg4){
            printf("El ganador fue el jugador 2!\n");    
        }
        if(neg3 < neg1 && neg3 < neg2 && neg3 < neg4){
            printf("El ganador fue el jugador 3!\n");    
        }
        if(neg4 < neg1 && neg4 < neg2 && neg4 < neg3){
            printf("El ganador fue el jugador 4!\n");    
        }
    }

    return 0;
}



