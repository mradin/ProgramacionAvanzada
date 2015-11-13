#include <stdio.h>
#include <omp.h>

omp_lock_t simple_lock;                 

int main(int argc, const char * argv[]){
    omp_init_lock(&simple_lock);

    #pragma omp parallel num_threads(4)
    {

        while (!omp_test_lock(&simple_lock)){
            printf("=== Hilo %d: bloqueo ocupado\n", omp_get_thread_num());
        }
        printf("+++ Hilo %d: Consegui el bloque\n", omp_get_thread_num());
        printf("--- Hilo %d: Libere el bloqueo\n", omp_get_thread_num());
        omp_unset_lock(&simple_lock);    
        
    }

    omp_destroy_lock(&simple_lock);
}