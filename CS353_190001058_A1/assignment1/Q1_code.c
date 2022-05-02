// Name -> Somya Mehta
// Roll No. 190001058
// Assignment 1

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


int main(){
  char flag = 'y';
  while(flag == 'y') {
    int z = fork();
    wait(NULL);
    if(z == 0) {      
      printf("Choose your option\n");
      printf("1. Firefox browser\n");
      printf("2. List files\n");
      printf("3. Gedit editor\n");
      printf("4. Libreoffice word\n");
      int turn;
      scanf("%d", &turn);
      printf("Options list %d\n\n", turn);
      switch(turn){
        case 1: {
          char *argv[] = {"firefox", NULL, NULL};
          execvp("/usr/bin/firefox", argv);
          break;
        }
        case 2: {
          char *argv[] = {"ls", NULL, NULL};
          execvp("/bin/ls", argv);
          break;
        }
        case 3: {
          char *argv[] = {"gedit", NULL};
          execvp("/usr/bin/gedit", argv);
          break;
        }
        case 4: {
          char *argv[] = {"libreoffice", NULL};
          execvp("/usr/bin/libreoffice", argv);
          break;
        }
      }
    }

    printf("Continue [y / N] ? ");
    scanf(" %c", &flag);
  }
  return 0;
}