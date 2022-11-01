#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  pid_t idProceso;
  int estadoHijo;
  int descriptorTuberia[2];
  char buffer[100];

  if (pipe (descriptorTuberia) == -1) { // Error al crear la tuberia
    perror ("No se puede crear Tuberia");
    exit(-1);
  }
  idProceso = fork(); // Crear proceso hijo
  if (idProceso == -1) { // Error al crear el proceso hijo
    perror ("No se puede crear proceso");
    exit(-1);
  }
  
  if (idProceso == 0) {	  // Proceso hijo
    close (descriptorTuberia[1]);
    read (descriptorTuberia[0], buffer, 5);
    printf ("Hijo : Recibido \"%s\"\n", buffer);
    exit(1);
  }
  
  if (idProceso > 0) { // Proceso padre
    close (descriptorTuberia[0]);
    printf ("Padre : Envio \"Sistemas\"\n");
    strcpy (buffer, "Sistemas");
    write (descriptorTuberia[1], buffer, strlen(buffer)+1);
    wait(&estadoHijo);
    exit(0);
  }

  return(1);
}
