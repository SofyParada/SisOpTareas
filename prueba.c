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
      FILE *fp;
      fp = fopen(nombre, "r"); 
      int f,s;
      char si[30];
      fscanf(fp, "%i",&f);
      fscanf(fp, "%i",&s);
      fscanf(fp, "%s",si);
      fclose(fp);

      struct stat st = {0};
      char dir[50] = "/mnt/c/Users/benja/Escritorio/SO/";
      strcat(dir,si);

      if (stat(dir, &st) == -1) {
         mkdir(dir, 0700);
         }
      
   }
   return 0;
}

int main() {
   DIR *dir;
   struct dirent *ent;
   dir = opendir(".");
   while ((ent = readdir (dir)) != NULL){
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
         creardir(ent->d_name);
         printf("Se han creado las carpetas correctamente");
      }
      }
   closedir(dir);
   return 0;
}

