#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

bool estxt(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;

}

int creardir(char *nombre){
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
      char dir[100] = "/mnt/c/Users/benja/Escritorio/SO/"; //Cambiar a direccion de archivos
      char or[100] = "/mnt/c/Users/benja/Escritorio/SO/";
      strcat(dir,gen);
      strcat(or,name);

      if (stat(dir, &st) == -1) {
         mkdir(dir, 0700);
         }
      strcat(dir,"/");
      strcat(dir,name);
      rename(or,dir);

   }
   return 0;
}

int main() {
   DIR *dir;
   struct dirent *ent;
   dir = opendir(".");
   while ((ent = readdir (dir)) != NULL){
         creardir(ent->d_name);
   }
   printf("Se han creado las carpetas correctamente\n");
   closedir(dir);
   return 0;
}

