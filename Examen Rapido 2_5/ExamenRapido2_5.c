#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


void * taquillas(void *);

void * web(void *);

void * movil(void *);

#define DISP_WEB 4
#define DISP_MOV 4
#define DISP_TAQ 2
#define SILLAS_CINE 10

pthread_mutex_t *mutex_silla;

int* sillas;

int main(int argc, const char * argv[]) {
    int i;
    mutex_silla = (pthread_mutex_t*)malloc(SILLAS_CINE*sizeof(pthread_mutex_t));
    
	//INIT MUTEX y COND
	for (i=0;i<SILLAS_CINE;++i){
		pthread_mutex_init(mutex_silla+i,NULL);
	}
	

	for (i=0;i<SILLAS_CINE;++i){
        *(sillas+i) = 0;
	}
	
	//Hilos
	int movil_web, total;
	
	movil_web = DISP_WEB + DISP_MOV;
	total = DISP_TAQ + movil_web;
	
    pthread_t * aux;
	pthread_t * dispositivos = (pthread_t *) malloc (sizeof(pthread_t) * total);
	int indice=0;

	//Crea hilos Web
	for (aux = dispositivos; aux < (dispositivos+DISP_WEB); ++aux) {
        printf("--- Creando el Dispositivo Web %d ---\n", ++indice);
        pthread_create(aux, NULL, web, (void *) indice);
    }
	
	indice = 0;
    //Crea hilos Movil
	for (aux = dispositivos; aux < (dispositivos+movil_web); ++aux) {
        printf("--- Creando el Dispositivo Movil %d ---\n", ++indice);
        pthread_create(aux, NULL, movil, (void *) indice);
    }
    
    indice = 0;
    //Crea hilos Taquilla
	for (aux = dispositivos; aux < (dispositivos+total); ++aux) {
        printf("--- Creando el Dispositivo Taquilla %d ---\n", ++indice);
        pthread_create(aux, NULL, taquillas, (void *) indice);
    }
    
    
    for (aux = dispositivos; aux < (dispositivos+total); ++aux) {
        pthread_join(*aux, NULL);
    }
    
    free(dispositivos);
    free(sillas);
    free(mutex_silla);
    
    return 0;
};

void * taquillas(void * arg){
    int salida=1;
    int quieroSilla;
    int id = (int) arg;
    
    while(salida==1){
        srand(time(NULL));
        quieroSilla = rand() % 10;
        
        pthread_mutex_lock(mutex_silla+quieroSilla);
        if(*(sillas+quieroSilla)==0){
            *(sillas+quieroSilla)==1;
            printf("El Disp Taquilla %d ocupo una silla.",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
        }
        else{
            printf("El Disp Taquilla %d encontro una silla ocupada... Buscando otra silla",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
        }
            
    }
}

void * web(void * arg){
    int salida=1;
    int quieroSilla;
    int id = (int) arg;
    
    while(salida==1){
        srand(time(NULL));
        quieroSilla = rand() % 10;
        
        pthread_mutex_lock(mutex_silla+quieroSilla);
        if(*(sillas+quieroSilla)==0){
            *(sillas+quieroSilla)==1;
            printf("El Disp Web %d ocupo una silla.",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
            salida = 0;
        }
        else{
            printf("El Disp Web %d encontro una silla ocupada... Buscando otra silla",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
        }
            
    }    
}

void * movil(void * arg){
    int salida=1;
    int quieroSilla;
    int id = (int) arg;
    
    while(salida==1){
        srand(time(NULL));
        quieroSilla = rand() % 10;
        
        pthread_mutex_lock(mutex_silla+quieroSilla);
        if(*(sillas+quieroSilla)==0){
            *(sillas+quieroSilla)==1;
            printf("El Disp Movil %d ocupo una silla.",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
            salida = 0;
        }
        else{
            printf("El Disp Movil %d encontro una silla ocupada... Buscando otra silla",id);
            pthread_mutex_unlock(mutex_silla+quieroSilla);
        }
            
    }   
}