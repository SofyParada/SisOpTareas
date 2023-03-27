#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>

bool estxt(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;

}

int ordenaractual(char *nombre, char *direccion,int *total1, int *total2, int *total3){
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
            int f;
            char des[255];
            fp = fopen(ent1->d_name, "r");
            fscanf(fp, "%i",&f);
            if (f>80000){
               char cat[50] = "/Mayor_a_80000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);
               strcpy(or,or1);  //Se restaura direccion de origen
               conteo1++;
            }
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
   *total1 = *total1 + conteo1;
   *total2 = *total2 + conteo2;
   *total3 = *total3 + conteo3;
   if (conteo1 == 0 && conteo2 == 0 && conteo3 == 0){
      closedir(dir1);
      return 0;  
   }
   else {
      printf("Cantidad de juegos de %s\n",name);
      printf("Juegos con una cantidad de jugadores actuales menor a 40000: %i\n",conteo2);
      printf("Juegos con una cantidad de jugadores actuales entre 40000 y 80000: %i\n",conteo3);
      printf("Juegos con una cantidad de jugadores actuales mayor a 80000: %i\n\n",conteo1);
   }
   closedir(dir1);
   return 0;
}

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
            int f,t;
            char des[255];
            fp = fopen(ent1->d_name, "r");
            fscanf(fp, "%i",&f);
            fscanf(fp, "%i",&t);
            if (t>80000){
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
   if (estxt(nombre)){
      char name[100];
      strcpy(name,nombre);
      FILE *fp;
      fp = fopen(nombre, "r"); 
      int f,s;
      char gen[30];
      fscanf(fp, "%i",&f);
      fscanf(fp, "%i",&s);
      fscanf(fp, "%s",gen);
      fclose(fp);

      struct stat st = {0};
      char dir[255]; //Cambiar a direccion de archivos
      char or[255];
      strcpy(or,direccion);
      strcpy(dir,direccion);
      strcat(dir,gen);
      strcat(or,name);

      if (stat(dir, &st) == -1) {
         mkdir(dir, 0700);
         chdir(dir);  //Crea carpetas para organizar segun cantidad
         mkdir("Menor_a_40000",0700);
         mkdir("Entre_40000_y_80000",0700);
         mkdir("Mayor_a_80000",0700);
         chdir(".."); //Vuelve a la carpeta original
         }
      strcat(dir,"/");
      strcat(dir,name);
      rename(or,dir);
   }
   return 0;
}


int main() {
   int i;
   char direct[255] = "direccion en donde se encuentran las carpetas";
   int total1 = 0;
   int total2 = 0;
   int total3 = 0;
   DIR *dir;
   struct dirent *ent;
   dir = opendir(".");
   chdir(direct);
   dir = opendir(".");
   while ((ent = readdir (dir)) != NULL){
         creardir(ent->d_name,direct);
   }
   printf("Se han creado las carpetas correctamente!\n\n");

   printf("Ingrese como quiere ordenar las carpetas:\n");
   printf("Segun cantidad de jugadores actuales (1)\n");
   printf("Segun mayor cantidad de jugadores totales en el dia (2)\n");
   printf("Ingrese el numero correspondiente a su eleccion:  ");
   scanf("%i",&i);
   printf("\n");
   rewinddir(dir);
   if (i == 1){
      printf("Su eleccion fue mayor cantidad de jugadores actuales.\n\n");
      while ((ent = readdir (dir)) != NULL){
         ordenaractual(ent->d_name,direct,&total1,&total2,&total3);
      }
      printf("Del total de juegos:\n");
      printf("Existen %i con una cantidad de jugadores actuales menor a 40000\n",total2);
      printf("Existen %i con una cantidad de jugadores actuales entre 40000 y 80000\n",total3);
      printf("Existen %i con una cantidad de jugadores actuales mayor a 80000\n\n",total1);
   }
   if (i == 2){
      printf("Su eleccion fue mayor cantidad de jugadores totales.\n\n");
      while ((ent = readdir (dir)) != NULL){
         ordenartotal(ent->d_name,direct,&total1,&total2,&total3);
      }
      printf("Del total de juegos:\n");
      printf("Existen %i con una mayor cantidad de jugadores menor a 40000\n",total2);
      printf("Existen %i con una mayor cantidad de jugadores entre 40000 y 80000\n",total3);
      printf("Existen %i con una mayor cantidad de jugadores mayor a 80000\n\n",total1);
      
   }
   else {
      closedir(dir);
      return 0;

   }
   closedir(dir);
   return 0;
}

