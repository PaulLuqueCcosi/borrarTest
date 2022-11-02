#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratasenial (int);
void isCreatedHijo2 (int);

void main(){
  pid_t pidHijo1;
  pid_t pidHijo2;
  
  printf("PADRE: Soy el proceso padre y mi PID es %d\n", getpid());
  pidHijo2 = fork();

  if (pidHijo2==-1) { // ERROR
    perror("No se puede lanzar proceso Hijo 2");
    exit(-1);
  }


  // hijo 2
  if (pidHijo2 == 0) { 
    pid_t pidHijo2_1;
    pidHijo2_1 = fork();

    if (pidHijo2_1==-1) { // ERROR
      perror("No se puede lanzar proceso Hijo 3\n");
      exit(-1);
    }
    
    // hijo 3
    if(pidHijo2_1 == 0){ 
      printf("HIJO 3: PID = %d, PPID = %d\n", getpid(), getppid());
      printf("HIJO 3: Soy el proceso hijo 3 y voy a finalizar \n");
      exit(0);
    }

    // hijo 2
    if(pidHijo2_1 >  0){ 
      printf("HIJO 2: mi PID es %d y el de mi padre es %d \n", getpid(), getppid());

      printf("HIJO 2: Soy el proceso hijo 2 y voy a finalizar \n");
      exit(0);
    }
  }
  

  // padre
  if (pidHijo2 > 0) { 
    pidHijo1 = fork();

    if (pidHijo1==-1) { // ERROR
      perror("No se puede lanzar proceso Hijo 1");
      exit(-1);
    }

    // hijo 1
    if (pidHijo1 == 0) {
      printf("HIJO 1: mi PID es %d y el de mi padre es %d \n", getpid(), getppid());
      printf("HIJO 1: el PID del hijo 2 es %d \n", pidHijo2);

      // enviamos la señal al hijo 2 cada 20 seg

      while(1){
	sleep(20);
	printf("HIJO 1: envio señal al hijo 2 \n");
	kill(pidHijo2, SIGUSR1);
      }

      sleep(2);
      printf("HIJO 1: Soy el hijo 1 y vot a finalizar \n");
      exit(0);
    }

    // padre
    if (pidHijo1 > 0) {
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

void isCreatedHijo2 (int nsenial) {
  printf ("Hijo 2 creado\n");
}
