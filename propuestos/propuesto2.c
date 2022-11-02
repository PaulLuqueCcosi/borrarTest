#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define LEER 0
#define ESCRIBIR 1
extern int errno;
int main(){
  int fd[2], bytesLeidos;
  char mensaje[100];
  int controlFork;
    // se crea la tuberia
  controlFork = pipe(fd);

  if ( controlFork != 0 ) { // Error al crear el pipe
    perror("pipe:");
    exit(errno);
  }
  controlFork = fork() ;

  if ( controlFork == -1 ) { // Error al crear el proceso hijo
    perror("fork:");
    exit(errno);
  
  }else if(controlFork == 0){ // HIJO - lee del pipe
    close(fd[ESCRIBIR]);
    bytesLeidos = read(fd[LEER], mensaje, 100);
    printf("Leidos %d bytes : %s\n", bytesLeidos, mensaje);
    close(fd[LEER]);
  
  }else{ // PADRE - escribe en el pipe
    // ingresamos el mensaje que queremos enviar
    char inputString[100];
    fgets(inputString, 100 , stdin);


    close(fd[LEER]);
    printf("Padre: bytes enviados: %ld\n", strlen(inputString)+1);
    write(fd[ESCRIBIR], inputString, strlen(inputString) + 1);
    close(fd[ESCRIBIR]);
    wait();
  }
  exit(0);
}
