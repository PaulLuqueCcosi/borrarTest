#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tratasenial (int);
void mostrarMensajeBienvenida();

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
      mostrarMensajeBienvenida();
      printf("HIJO 3: Soy el proceso hijo 3 y voy a finalizar \n");
      exit(0);
    }

    // hijo 2
    if(pidHijo2_1 >  0){
      signal(SIGUSR1, tratasenial);
      while(1){
	pause();
      }
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
    }

    // padre
    if (pidHijo1 > 0) {
      printf("PADRE: esperando a que finalicen los hijos \n");
      wait();
      wait();
    }
  }
}
void tratasenial (int nsenial) {

  printf("HIJO 2: senal recibida, PID = %d, PPID = %d\n", getpid(), getppid());
}

void mostrarMensajeBienvenida(){
  printf("**********************************************\n");
  printf("Bienvenido usuario %s \n", getlogin());
  time_t now;

  // Obtener la hora actual
  // time() devuelve la hora actual del sistema como un valor `time_t`
  time(&now);

  struct tm *local = localtime(&now);
  int hours = local->tm_hour;         // obtener horas desde la medianoche (0-23)
  int minutes = local->tm_min;        // obtener minutos pasados después de la hora (0-59)
  int seconds = local->tm_sec;        // obtener segundos pasados después de un minuto (0-59)

  int day = local->tm_mday;            // obtener el día del mes (1 a 31)
  int month = local->tm_mon + 1;      // obtener el mes del año (0 a 11)
  int year = local->tm_year + 1900;   // obtener el año desde 1900

  // imprime la hora local
  if (hours < 12) {    // antes del mediodia
    printf("La hora es: %02d:%02d:%02d am\n", hours, minutes, seconds);
  }
  else {    // Después de mediodía
    printf("La hora es: %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
  }
  // imprime la fecha actual
  printf("La fecha es: %02d/%02d/%d\n", day, month, year);
  printf("**********************************************\n");
}

