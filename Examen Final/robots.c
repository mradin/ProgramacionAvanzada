#include <mpi.h>

#include <stdio.h>
#include <omp.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

#define N 10
char *caminos[N];

void mover(int * tablero, int i,int j, int cont){

	caminos[cont] = i+","+j;
	if (x>N || y>N){
		printf("Ya llegue a mi destino");
		kill(tid,SIGUSR1);

	}
	else {
		
		if(tablero[i][j+1]==0){
		    printf("Avanazo el camnino hacia la derecha");
		    mover(tablero,i,j+1,++cont);
		}
		if(tablero[i+1][j]==0){
		    printf("Avanzo el camnino hacia abajo");
		    mover(tablero,i+1,j,++cont);
		}
	}

}

void manejador(){
	
	printf("El camino es: \n");
	for(i=0;i<N;++i){
		printf("%c",caminos[i]);
	}
}


int main(int argc, const char * argv[]){
    
    int myid, numprocs, nh, tid;
    int tablero[N][N];
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int  longitud;
    
    
    srand(time(NULL));
    
    for(i=0;i<N;++i){
        for(j=0;j<N;++j){
            tablero[i][j]= rand() % 2;
        }
    }
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(hostname, &longitud);
    
    
    MPI_Bcast(tablero, n, MPI_INT, 0, MPI_COMM_WORLD);
    	#pragma omp parallel private(tid)
		{
			
		#pragma omp for
		for(i=0;i<5;++i)[{
			mover(tablero,0,i,0);
		}   
    	
    	signal(SIGUSR1, manejador);
		}
  
  	MPI_Finalize();
    return 0;
}