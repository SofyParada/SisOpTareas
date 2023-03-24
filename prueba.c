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

int ordenaractual(char *nombre, char *direccion){
   char or[255];
   char or1[255];
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
            }

         }
   }
   closedir(dir1);
   return 0;
}

int ordenartotal(char *nombre,char *direccion){
   char or[255];
   char or1[255];
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
            }
            if (t>=40000 && f<=80000){
               char cat[50] = "/Entre_40000_y_80000";
               strcpy(des,or);  //Carpeta de origen del juego
               strcat(or,cat);  //Carpeta de destino del juego 
               strcat(des,"/");
               strcat(or,"/");
               strcat(des,ent1->d_name);
               strcat(or,ent1->d_name);
               rename(des,or);   //Se mueve archivo
               strcpy(or,or1);  //Se restaura direccion de origen
            }

         }
   }
   closedir(dir1);
   return 0;
   return 0;
}

int crearcarpetas(char *direccion){
   chdir(direccion);
   mkdir("Menor_a_40000",0700);
   mkdir("Entre_40000_y_80000",0700);
   mkdir("Mayor_a_80000",0700);
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
   DIR *dir;
   int i;
   char direct[255] = "/mnt/c/Users/benja/Escritorio/SO/";
   struct dirent *ent;
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
   printf("Su eleccion fue: %i\n",i);
   rewinddir(dir);
   if (i == 1){
      printf("Su eleccion fue mayor cantidad de jugadores actuales\n");
      while ((ent = readdir (dir)) != NULL){
         ordenaractual(ent->d_name,direct);
         
      }
   }
   if (i == 2){
      printf("Su eleccion fue mayor cantidad de jugadores totales\n");
      while ((ent = readdir (dir)) != NULL){
         ordenartotal(ent->d_name,direct);
   }
   }
   closedir(dir);
   return 0;
}

