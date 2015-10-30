#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define VACIO 0
#define MUJERES 1
#define HOMBRES 2

pthread_mutex_t mutex_bano = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_hom = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fem = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_hom = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_fem = PTHREAD_COND_INITIALIZER;

int personas_dentro = 0;
int espera_mujeres = 0;
int espera_hombres = 0;
int estado = VACIO;

void fem_busca();
void hom_busca();
void fem_sale();
void hom_sale();

void *mujer();
void *hombre();


int main(){

	printf("Baño vacio\n");
	pthread_t *hombres_t = (pthread_t*)malloc(4*sizeof(pthread_t));
	pthread_t *mujeres_t = (pthread_t*)malloc(4*sizeof(pthread_t));

	int i;
	for (i = 0; i<4; ++i){
		pthread_create(mujeres_t+i,NULL,mujer,NULL);
		pthread_create(hombres_t+i,NULL,hombre,NULL);
	}

	/****
     **** Al rato van a llegar mas personas		
	 ****/
	sleep(5);
    srand(time(NULL));
    int sexo; 
    pthread_t *random_t = (pthread_t*)malloc(8*sizeof(pthread_t));
	for (i=0;i<8;++i){
		sexo = rand() % 2;
		if (sexo == 0)
			pthread_create(random_t+i,NULL,mujer,NULL);
		else 
			pthread_create(random_t+i,NULL,hombre,NULL);
	}

	for (i=0;i<4;++i){
		pthread_join(*(hombres_t+i),NULL);
		pthread_join(*(mujeres_t+i),NULL);
	}

	for (i=0;i<8;++i){
		pthread_join(*(random_t+i),NULL);
	}
	free(hombres_t);
	free(mujeres_t);
	free(random_t);

	return 0;
}

void *mujer(){
	
	fem_busca();
	sleep(3);
	fem_sale();
	pthread_exit(NULL);
}

void fem_busca(){

	pthread_mutex_lock(&mutex_fem);
	printf("Llega mujer, %d en espera\n",++espera_mujeres);
	pthread_mutex_unlock(&mutex_fem);
	int listo = 0;

	while (!listo){

	pthread_mutex_lock(&mutex_bano);

		if (estado == HOMBRES){
			pthread_cond_wait(&cond_fem,&mutex_bano);
		}
			
		if (estado == VACIO){
			estado = MUJERES;
			printf("Entra mujer, %d espera\n",--espera_mujeres);
			++personas_dentro;
			printf("Baño ocupado por mujeres\n");
			listo = 1;
		}
			
		else if (estado == MUJERES) {
			printf("Entra mujer, %d espera\n",--espera_mujeres);
			++personas_dentro;
			listo = 1;
		}

		pthread_mutex_unlock(&mutex_bano);

	}
}

void fem_sale(){

	pthread_mutex_lock(&mutex_bano);
	printf("Sale mujer\n");
	--personas_dentro;
	if (personas_dentro == 0){
		estado = VACIO;
		pthread_cond_broadcast(&cond_hom);
		printf("Baño vacio\n");
	}
	pthread_mutex_unlock(&mutex_bano);
}

void *hombre(){
	hom_busca();
	sleep(2);
	hom_sale();
	pthread_exit(NULL);
}

void hom_busca(){

	pthread_mutex_lock(&mutex_hom);
	printf("Llega hombre, %d espera\n",++espera_hombres);
	pthread_mutex_unlock(&mutex_hom);

	int listo = 0;

	while (!listo){

	pthread_mutex_lock(&mutex_bano);

		if (estado == MUJERES){
			pthread_cond_wait(&cond_hom,&mutex_bano);
		}

		if (estado == VACIO){
			estado = HOMBRES;
			printf("Entra hombre, %d espera\n",--espera_hombres);
			++personas_dentro;
			printf("Baño ocupado por hombres\n");
			listo = 1;

		}
		else if (estado == HOMBRES){
			printf("Entra hombre, %d en espera\n",--espera_hombres);
			++personas_dentro;
			listo = 1;
		}

		pthread_mutex_unlock(&mutex_bano);
	}
}

void hom_sale(){
	pthread_mutex_lock(&mutex_bano);
	--personas_dentro;
	printf("Sale hombre\n");
	if (personas_dentro == 0){
		estado = VACIO;
		pthread_cond_broadcast(&cond_fem);
		printf("Baño vacio\n");
	}
	pthread_mutex_unlock(&mutex_bano);
}