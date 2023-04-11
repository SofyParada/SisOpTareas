#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>

bool estxt(char const *name)  //Funcion que revisa si un archivo es de tipo .txt, recibe como parametro el nombre del archivo
{
    size_t len = strlen(name);  //Extrae el largo del nombre del archivo
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;  //Revisa que el archivo no solo sea llamado .txt y el strcmp revisa que los ultimos 4 caracteres
                                                            //del nombre sean tipo .txt, strcmp devuelve 0 cuando ambos string son iguales.
                                                            //A name se le mueven len espacios a la derecha y se le restan 4, lo que deberia ser justo el .txt

}

/*
Ordena archivos segun cant actual de jugadores
Nombre: Deberia ser el nombre de una carpeta genero
Direccion: Direccion en donde se encuentran los archivos
Totales: Punteros a int que van cambiando para sumar el total final
*/

int ordenaractual(char *nombre, char *direccion,int *total1, int *total2, int *total3){
                                                                                            
   char or[255];  //Variable para direccion de origen
   char or1[255];  //Respaldo para la direccion de origen
   int conteo1 = 0;  //Tres variables de conteo para los print de cuantos hay por genero
   int conteo2 = 0;
   int conteo3 = 0;
   strcpy(or,direccion); //Se copia la direccion de origen en las dos 
   strcpy(or1,direccion);
   char name[100]; //Variable para almacenar el nombre del archivo
   strcpy(name,nombre);  //Se guarda el nombre del archivo
   strcat(or,name);    //Direccion de el archivo actual que se quiere mover, que debe ser un genero
   strcat(or1,name);  //respaldo de la direccion
   chdir(or);  //Cambio hacia carpeta genero
   DIR *dir1;  //Se crea para analizar directorio dentro de carpeta genero
   struct dirent *ent1;
   dir1 = opendir("."); //Se abre carpeta
   while ((ent1 = readdir(dir1)) != NULL){  //Un loop que funciona hasta que no hayan mas JUEGOS por leer
         if (estxt(ent1->d_name)){  //Se verifica que archivo sea txt
            FILE *fp; //Se abre para leer archivo
            int f;  //INT que tomara valor de cant de actuales
            char des[255];  //Carpeta de destino en donde se movera el archivo
            fp = fopen(ent1->d_name, "r"); //Se abre archivo
            fscanf(fp, "%i",&f); //Se lee primera linea del archivo que debe ser la cant actual
            if (f>80000){
               char cat[50] = "/Mayor_a_80000"; //Se crea un string con el nombre de la carpeta
               strcpy(des,or);  //Se copia nombre carpeta en donde se encuentra el juego
               strcat(or,cat);  //Se concatena a la direccion en donde esta el juego el nombre de la carpeta a la que se desea mover
               strcat(des,"/");  //Se agrega un / para cumplir sintaxis
               strcat(or,"/");  //Lo mismo
               strcat(des,ent1->d_name); //Concatena a la direccion en donde se encuentra el juego, el nombre del juego
               strcat(or,ent1->d_name); //Concatena a la direccion en donde se quiere mover el juego, el nombre del juego
               rename(des,or);  //Se mueve juego hacia carpeta
               strcpy(or,or1);  //Se restaura direccion de origen para poder utilizarla denuevo en otro juego
               conteo1++; //Se le suma al total de mayor a 80000
            }
            //Los siguientes hacen lo mismo que el if anterior solo que con la carpeta correspondiente y suma para el total tambien correspondieite
            if (f<40000){
               char cat[50] = "/Menor_a_40000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo2++;
            }
            if (f>=40000 && f<=80000){
               char cat[50] = "/Entre_40000_y_80000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo3++;
            }

         }
   }
   *total1 = *total1 + conteo1;  //Se le suma al puntero total1, total2 y total 3, las cantidades acumuladas en conteo,
   *total2 = *total2 + conteo2;
   *total3 = *total3 + conteo3;
   if (conteo1 == 0 && conteo2 == 0 && conteo3 == 0){ //Si no hay valores, se cierra el directorio y return, indicando probablemente que es una carpeta x
      closedir(dir1);
      return 0;  
   }
   else {  //Printea la cantidad de juegos por criterio
      printf("Cantidad de juegos de %s\n",name);
      printf("Juegos con una cantidad de jugadores actuales menor a 40000: %i\n",conteo2);
      printf("Juegos con una cantidad de jugadores actuales entre 40000 y 80000: %i\n",conteo3);
      printf("Juegos con una cantidad de jugadores actuales mayor a 80000: %i\n\n",conteo1);
   }
   closedir(dir1);
   return 0;
}

/*
Ordena archivos segun cant total de jugadores
Nombre: Deberia ser el nombre de una carpeta genero
Direccion: Direccion en donde se encuentran los archivos
Totales: Punteros a int que van cambiando para sumar el total final
*/

//Esta funcion realiza exactamente lo mismo que la anterior, solo tiene un cambio que va a estar comentado en mayus
int ordenartotal(char *nombre,char *direccion,int *total1,int *total2, int *total3){
   char or[255];
   char or1[255];
   int conteo1 = 0;
   int conteo2 = 0;
   int conteo3 = 0;
   strcpy(or,direccion);
   strcpy(or1,direccion);
   char name[100];
   strcpy(name,nombre);
   strcat(or,name);    //Direccion hacia la carpeta actual
   strcat(or1,name);  //respaldo
   chdir(or);  //Cambio hacia carpeta
   DIR *dir1;
   struct dirent *ent1;
   dir1 = opendir(".");
   while ((ent1 = readdir(dir1)) != NULL){
         if (estxt(ent1->d_name)){
            FILE *fp;
            int f,t;  //SE CREAN 2 VARIABLES 
            char des[255];
            fp = fopen(ent1->d_name, "r");
            fscanf(fp, "%i",&f);  //SE LEE PRIMERA LINEA QUE ES CANTIDAD ACTUAL, QUE NO NOS SIRVE
            fscanf(fp, "%i",&t);  //SE LEE SEGUNDA LINEA QUE ES CANTIDAD TOTAL, QUE SI SIRVE
            if (t>80000){ //TODOS LOS IF SON CON t
               char cat[50] = "/Mayor_a_80000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);  //Se mueve archivo
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo1++;
            }
            if (t<40000){
               char cat[50] = "/Menor_a_40000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);   //Se mueve archivo
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo2++;
            }
            if (t>=40000 && t<=80000){
               char cat[50] = "/Entre_40000_y_80000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);   //Se mueve archivo
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo3++;
            }

         }
   }
   *total1 = *total1 + conteo1;
   *total2 = *total2 + conteo2;
   *total3 = *total3 + conteo3;
   if (conteo1 == 0 && conteo2 == 0 && conteo3 == 0){
      closedir(dir1);
      return 0;  
   }
   else {
      printf("Cantidad de juegos de %s\n",name);
      printf("Juegos con una cantidad de jugadores menor a 40000: %i\n",conteo2);
      printf("Juegos con una cantidad de jugadores entre 40000 y 80000: %i\n",conteo3);
      printf("Juegos con una mayor cantidad de jugadores mayor a 80000: %i\n\n",conteo1);
   }
   closedir(dir1);
   return 0;
}

int creardir(char *nombre, char *direccion){
   if (estxt(nombre)){ //Llama a estxt para saber si el archivo es un .txt
      char name[100]; //Va a almacenar el nombre del archivo en un string
      strcpy(name,nombre);  //Copia el nombre del archivo en el string name para poder utilizarlo
      FILE *fp;  //Se crea para poder manipular y leer un archivo
      fp = fopen(nombre, "r");   //Se abre el archivo en read
      int f,s;  //Almacenan valores actual y total
      char gen[30];  //Almacena genero
      fscanf(fp, "%i",&f);  //Jugadores actuales
      fscanf(fp, "%i",&s);  //Jugadores totales
      fscanf(fp, "%s",gen); //Genero
      fclose(fp);  //Se cierra el archivo

      struct stat st = {0};  //Se crea struct stat para verificar que la carpeta no se haya creado
      char dir[255]; //Cambiar a direccion de archivos
      char or[255]; //Direccion de origen
      strcpy(or,direccion);  //Copia la direccion en or
      strcpy(dir,direccion);  //Copia la direccion en dir
      strcat(dir,gen); //A la direccion de origen se le concatena el genero
      strcat(or,name); //A la direccion de origen se le concatena el nombre del archivo

      if (stat(dir, &st) == -1) { //Se verifica que la carpeta no haya sido creada
         mkdir(dir, 0700);  //Se crea la carpeta con el genero
         chdir(dir);  //Se mueve a la carpeta recien creada
         mkdir("Menor_a_40000",0700);  //Crea carpetas menor entre y mayor
         mkdir("Entre_40000_y_80000",0700);
         mkdir("Mayor_a_80000",0700);
         chdir(".."); //Vuelve a la carpeta anterior
         }
      strcat(dir,"/"); //Se le concatena un /
      strcat(dir,name);  //Se le concatena el nombre del archivo. de forma origen/genero/nombredelarchivo.txt
      rename(or,dir);  //Se mueve el archivo desde el origen hacia la direccion final, indicando la direccion original y la de destino.
   }
   return 0;
}


int main() {
   int i;  //variable contador
   char direct[255] = "direccion en donde se encuentran las carpetas";  //se almacena direccion en donde estan las carpetas
   int total1 = 0;  //variables que cuentan el total segun cantidad
   int total2 = 0;
   int total3 = 0;
   DIR *dir;  //Se crea variable DIR para acceder a los directorios
   struct dirent *ent;  //Struct para sacar datos de los archivos
   dir = opendir(".");  //Se abre el directorio
   chdir(direct);    //Se cambia la direccion del directorio actual al de donde estan las carpetas
   dir = opendir(".");  //Se abre nuevamente el directorio actual nuevo
   while ((ent = readdir (dir)) != NULL){  //Se realiza un readdir en el directorio actual, el cual leera todos los archivos hasta que llegue al final y no existan mas
         creardir(ent->d_name,direct);  //Se llama funcion creardir, que crea carpetas para ordenar
   }
   printf("Se han creado las carpetas correctamente!\n\n");

   printf("Ingrese como quiere ordenar las carpetas:\n");
   printf("Segun cantidad de jugadores actuales (1)\n");
   printf("Segun mayor cantidad de jugadores totales en el dia (2)\n");
   printf("Ingrese el numero correspondiente a su eleccion:  ");
   scanf("%i",&i);
   printf("\n");
   rewinddir(dir);  //Se devuelve el puntero hacia el primer archivo del directorio
   if (i == 1){
      printf("Su eleccion fue mayor cantidad de jugadores actuales.\n\n");
      while ((ent = readdir (dir)) != NULL){ //Mismo while anterior
         ordenaractual(ent->d_name,direct,&total1,&total2,&total3); //Se llama funcion que ordena archivos segun cant de jugadores actuales, lee carpetas GENERO
      }
      printf("Del total de juegos:\n");  //Printea valor de punteros total, que eran modificados en los conteos de ordenaractual
      printf("Existen %i con una cantidad de jugadores actuales menor a 40000\n",total2);
      printf("Existen %i con una cantidad de jugadores actuales entre 40000 y 80000\n",total3);
      printf("Existen %i con una cantidad de jugadores actuales mayor a 80000\n\n",total1);
   }
   if (i == 2){
      printf("Su eleccion fue mayor cantidad de jugadores totales.\n\n");
      while ((ent = readdir (dir)) != NULL){
         ordenartotal(ent->d_name,direct,&total1,&total2,&total3);  //Se llama funcion que ordena archivos segun cant de jugadores totales, lee carpetas GENERO
      }
      printf("Del total de juegos:\n");    //Printea valor de punteros total, que eran modificados en los conteos de ordenartotal
      printf("Existen %i con una mayor cantidad de jugadores menor a 40000\n",total2);
      printf("Existen %i con una mayor cantidad de jugadores entre 40000 y 80000\n",total3);
      printf("Existen %i con una mayor cantidad de jugadores mayor a 80000\n\n",total1);
      
   }
   else {  //Si no es ninguna de las opciones anteriores
      closedir(dir); //Se cierra directorio
      return 0;

   }
   closedir(dir);  //Se cierra directorio
   return 0;
}

