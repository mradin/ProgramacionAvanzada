#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SILLAS 5
#define ENANOS 8

pthread_mutex_t mutex_silla = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_esperando = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_sentarse = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_sentado = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_comer = PTHREAD_COND_INITIALIZER;

int sillas_libres = 5;
int enanos_esperando = 0;

void *enano(void *arg);
void *blancanieves (void *arg);
void mina();

int main(){
	srand(time(NULL));
	int i;
	pthread_t *threads_enanos = (pthread_t*)malloc(ENANOS*sizeof(pthread_t));
	pthread_t threads_blancanieves;
	pthread_create(&threads_blancanieves,NULL,blancanieves,NULL);
	for (i=0;i<ENANOS;++i){
		pthread_create(threads_enanos+i,NULL,enano,i);
	}


	for (i=0;i<ENANOS;++i){
		pthread_join(*(threads_enanos+i),NULL);
	}
	pthread_join(threads_blancanieves,NULL);
	free(threads_enanos);
	return 0;
}

void *enano(void *arg){
	int id = (int)arg;

	while (1){
		mina(id);
		printf("Enano %d: Buscando silla\n",id);
		int sentado = 0;
		
		while (!sentado){
			pthread_mutex_lock(&mutex_silla);
			if (sillas_libres > 0){
				sillas_libres--;
				sentado = 1;
				printf("Enano %d: Sentado\n",id);
				pthread_mutex_lock(&mutex_esperando);
				++enanos_esperando;
				pthread_mutex_unlock(&mutex_esperando);
			}
			else {
				printf("Enano %d: esperando silla\n",id);
				pthread_cond_wait(&cond_sentarse,&mutex_silla);
			}
		}
		pthread_mutex_unlock(&mutex_silla);

		pthread_cond_signal(&cond_sentado);

		pthread_mutex_lock(&mutex_esperando);
		pthread_cond_wait(&cond_comer,&mutex_esperando);
	
		pthread_mutex_unlock(&mutex_esperando);

		printf("Enano %d: comiendo-- a trabajar\n",id);
		sleep(4);

		pthread_mutex_lock(&mutex_silla);
		printf("Enano %d: sali de la silla\n",id);
		sillas_libres++;
		pthread_mutex_unlock(&mutex_silla);
	}

	pthread_exit(NULL);
}

void *blancanieves(void *arg){
	while (1){
		pthread_mutex_lock(&mutex_silla);
		if (sillas_libres == 0){
			printf("Voy a salir un rato\n");
			pthread_cond_wait(&cond_sentado,&mutex_silla);
		}
		pthread_mutex_unlock(&mutex_silla);
		
		pthread_mutex_lock(&mutex_esperando);
		if (enanos_esperando > 0){
			printf("Voy a cocinar para un enanito\n");
			pthread_cond_signal(&cond_comer);
			--enanos_esperando;
		}
		pthread_mutex_unlock(&mutex_esperando);
	}
	
	pthread_exit(NULL);
}

void mina(int i){
	int trabajando = rand() % 15;
	printf("Trabajando Mina+++ Soy el enano %d y voy a trabajar %d ++++ Trabajando MIna\n",i,trabajando);
	sleep(trabajando);
}