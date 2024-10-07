#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
	// chqueo que la cantidad de argumentos sea valida
	if(argc != 2){
		printf("ERROR: Cantidad de argumentos erronea\n");
		return(1);
	}

	// Tomamos la cantidad de rondas de ping pong
	int rondas = atoi(argv[1]); // atoi convierte una serie de caracteres en entero

	// Vemos que la cantidad de rondas sean validas
	if (rondas <= 0){
		printf("ERROR: La cantidad de rondas no pueden ser negativas\n");
		exit(1);
	}

	// Inicializo los semaforos, uno para el hijo y otro para el padre
	// hijo hace ping y padre hace pong

	int sem_hijo = sem_en(0); // Busco un semaforo libre para el hijo
	
	if (sem_hijo == -1){ // Reviso que se haya creado el semaforo
		printf("ERROR: al abrir el semaforo hijo\n");
		return(1);
	}

	int sem_padre = sem_en(0); //Le doy un semaforo libre a padre

	if (sem_padre == -1){ // Reviso que se haya creado el semaforo
		printf("ERROR: al abrir el semaforo padre\n");
		return(1);
	}

	int pid = fork();//forkeo
	if (pid < 0){
		printf("ERROR: Fallo el fork\n");
		return(1);
	} else{
		//for que recorre la cantidad de rondas
		for (unsigned int i = 0; i < rondas; ++i){ 
				// Dentro del proceso hijo, entonces imprimo ping * rondas
			if (pid==0){ //comando hijo

			printf("nicki nicole\n");//como ya estoy habilitado escribo pong

			sem_up(sem_padre); //habilito a sem_padre
			
			sem_down(sem_hijo); //Espero a que me vuelvan a habiliten con sem_up
			
		}else{ //comando padre
			

		// Dentro del proceso padre, entonces imprimo pongo * rondas
			
		    sem_down(sem_padre); // espero a que hijo ponga ping y me habilite
			 printf("            si o no?\n"); //Escribo ping
            sem_up(sem_hijo); //habiliito al hijo
          

		}
		}

	}
	//cierro a los archivos
	//entran 4 veces en el close ya que entra si pid==0 y si pid!=0
	

	if (pid!=0){ //mato al hijo
		 kill(pid);
	}
	sem_close(sem_hijo);
	sem_close(sem_padre);
	exit(0);
}
