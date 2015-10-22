#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



pthread_mutex_t mutex_tabaco = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_papel = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fosforos = PTHREAD_MUTEX_INITIALIZER;

#define NHILOS 4

void * agente(void * arg){
    
    pthread_mutex_lock(&mutex_tabaco);
    pthread_mutex_lock(&mutex_papel);
    pthread_mutex_lock(&mutex_fosforos);
    
    
    int ing1, ing2;
    
    srand (time(NULL));
    ing1 = rand() % 3 + 1;
    ing2 = rand() % 3 + 1;
    
    while(ing2==ing1){
        ing2 = rand() % 3 + 1;
    }
    
    if(ing1 == 1 || ing2 == 1){
        pthread_mutex_unlock(&mutex_tabaco);
    }
    
    if(ing1 == 2 || ing2 == 2){
        pthread_mutex_unlock(&mutex_papel);
    }
    
    if(ing1 == 3 || ing2 == 3){
        pthread_mutex_unlock(&mutex_papel);
    }
    
}

void * fumador(void * arg){
    
    pthread_mutex_lock(&mutex_tabaco);
    
    while (pthread_mutex_trylock(&mutex_papel))
        {
            pthread_mutex_unlock(&mutex_tabaco);
            
            pthread_mutex_lock(&mutex_tabaco);
            
            while (pthread_mutex_trylock(&mutex_papel))
            {
                pthread_mutex_unlock(&mutex_fosforos);
            
                pthread_mutex_lock(&mutex_fosforos);
            }
        }
    
    printf("Enrollando y Fumando");
    
    pthread_mutex_unlock(&mutex_fosforos);
    pthread_mutex_unlock(&mutex_papel);
    pthread_mutex_unlock(&mutex_tabaco);
    
    sleep(4);
}

int main(int argc, const char * argv[])
{
    
    pthread_t * tid;
    int nhilos;
    int i;
    
    nhilos = NHILOS;
    
    tid = malloc(nhilos * sizeof(pthread_t));
    
    printf("Creando hilos ...\n");
    
    pthread_create(tid, NULL, fumador, (void *)0);
    pthread_create(tid+1, NULL, fumador, (void *)1);
    pthread_create(tid+2, NULL, fumador, (void *)2);
    pthread_create(tid+4, NULL, agente, (void *)2);
    
    printf("Se crearon %d hilos ...\n", nhilos);
    
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("Se unió el hilo %d con TID = %d...\n", i, *(tid+i));
    }
    
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    
    free(tid);
    
    return 0;
}