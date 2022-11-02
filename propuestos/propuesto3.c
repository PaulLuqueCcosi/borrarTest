#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratasenial (int);

void main(){
  pid_t pidHijo1;
  pid_t pidHijo2;
  pidHijo1 = fork();

  if (pidHijo1==-1) { // ERROR
    perror("No se puede lanzar proceso Hijo 1");
    exit(-1);
  }


  // hijo 1
  if (pidHijo1 == 0) { // HIJO
		       //signal (SIGUSR1, tratasenial);
		       //while (1)
		       //  pause();
    pid_t pidHijo1_1;
    pidHijo1_1 = fork();
    if (pidHijo1_1==-1) { // ERROR
      perror("No se puede lanzar proceso Hijo 3\n");
      exit(-1);
    }
    
    // hijo 3
    if(pidHijo1_1 == 0){ // HIJO
      printf("HIJO 3: PID = %d, PPID = %d\n", getpid(), getppid());
      printf("Soy el proceso hijo 3 y voy a finalizar \n");
      exit(0);
    }

    // hijo 1
    if(pidHijo1_1 >  0){ // PADRE
      printf("HIJO 1: mi PID es %d y el de mi padre es %d \n", getpid(), getppid());
      
      printf("HIJO 1: el pid de hijo 2 es %d \n", pidHijo2);

      printf("Soy el proceso hijo 1 y voy a finalizar \n");
      sleep(3);
      exit(0);
    }
  }

  // fin hijo 1

  // padre
  if (pidHijo1 > 0) { // PADRE
    pidHijo2 = fork();

    if (pidHijo2==-1) { // ERROR
      perror("No se puede lanzar proceso Hijo 2");
      exit(-1);
    }

    // hijo 2
    if (pidHijo2 == 0) { // HIJO
      printf("HIJO 2:  mi PID es %d y el de mi padre es %d \n", getpid(), getppid());

      sleep(6);
      printf("Soy el hijo 2 y vot a finalizar \n");
      exit(0);
    }

    // padre
    if (pidHijo2 > 0) { // PADRE
      printf("PADRE: esperando a que finalicen los hijos \n");
      wait();
      wait();

      printf("PADRE: voy a finalizar \n");
    }
    // fin padre

  }

  // fin padre
}
void tratasenial (int nsenial) {
  printf ("Recibida la señal del Padre\n");
}
