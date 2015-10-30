#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 7
#define ROBOTS 3

typedef struct {
	int peso;
	int id;
} datos;

pthread_mutex_t *mutex_niveles;
pthread_cond_t *cond_niveles;
int *pesos;
int *acums;

void *robot(void *arg);

int main(){

	mutex_niveles = (pthread_mutex_t*)malloc(N*sizeof(pthread_mutex_t));
	cond_niveles = (pthread_cond_t*)malloc(N*sizeof(pthread_cond_t));
	pesos = (int*)malloc(N*sizeof(int));
	acums = (int*)malloc(N*sizeof(int));

	
	srand(time(NULL));
	int i;
	for (i=0;i<N;++i){
		*(pesos+i) = rand() % 10 + 6;
		*(acums+i) = 0;
		printf("La seccion %d pesa: %d \n",i,*(pesos+i));
	}

	
	for (i=0;i<N;++i){
		pthread_mutex_init(mutex_niveles+i,NULL);
		pthread_cond_init(cond_niveles+i,NULL);
	}

	
	pthread_t *robots_t = (pthread_t*)malloc(ROBOTS*2*sizeof(pthread_t));
	datos *d = (datos*)malloc(ROBOTS*sizeof(datos));

	for (i=0; i < ROBOTS; i++){
		
		(d+i)->peso = rand() % 5 + 2;
		(d+i)->id = i;
		pthread_create(robots_t+i,NULL,robot,(void*)(d+i));
	}

	sleep(8);

	
	datos *d_2 = (datos*)malloc(ROBOTS*sizeof(datos));
	for (i=0+ROBOTS; i < ROBOTS+ROBOTS; i++){
		
		(d_2+i)->peso = rand() % 5 + 2;
		(d_2+i)->id = i;
		pthread_create(robots_t+i,NULL,robot,(void*)(d_2+i));
	}


	//Esperar a que terminen
	for (i=0;i<2*ROBOTS;++i){
		pthread_join(*(robots_t+i),NULL);
	}

	free(d);
	free(d_2);
	free(mutex_niveles);
	free(cond_niveles);
	free(pesos);
	free(acums);
	free(robots_t);

	return 0;
}

void *robot(void *arg){

	datos *d = (datos*)arg;
	int peso = d->peso;
	int id = d->id;
	printf("----Iniciando compra, soy el robot %d con peso %d\n",id,peso);

	
	int j = 0;
	while (j < N){

		pthread_mutex_lock(mutex_niveles+j);
		if (peso + *(acums+j) > *(pesos+j)){
			printf("+++%d y me toco esperar a que baje un poco el peso\n",id);
			pthread_cond_wait(cond_niveles+j,mutex_niveles+j);
			pthread_mutex_unlock(mutex_niveles+j);
		}
		

		else {
			*(acums+j) += peso;
			pthread_mutex_unlock(mutex_niveles+j);
			printf("****Robot %d haciendo mi shopping en el nivel %d que esta pesando %d/%d\n",id,j,*(acums+j),*(pesos+j));
			int shopping = rand() % 4 + 1;
			sleep(shopping);
			printf("////Robot %d ya me puedo ir del nivel %d\n",id,j);
			pthread_mutex_lock(mutex_niveles+j);
			*(acums+j) -= peso;
			pthread_cond_broadcast(cond_niveles+j);
			pthread_mutex_unlock(mutex_niveles+j);
			j++;
		}	
	}

	pthread_exit(NULL);
}
