#include <stdio.h>
#include <omp.h>

omp_lock_t bloqueo;

int main(int argc, const char * argv[]){

    omp_init_lock(&bloqueo);
    int suma = 0;
    int i;
    
    #pragma omp parallel num_threads (4)
    {
        for (i = 0; i < 5; ++i){
            
            omp_set_lock(&bloqueo);
            printf("+++ Hilo %d: Estoy en la region bloqueada\n", omp_get_thread_num());
            printf("--- Hilo %d: Saliendo de la region\n", omp_get_thread_num());
            omp_unset_lock(&bloqueo);
            

        }
    }
    omp_destroy_lock(&bloqueo);    
    
    return 0;
}