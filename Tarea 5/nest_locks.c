#include <stdio.h>
#include <omp.h>

omp_nest_lock_t bloqueo;

void leoLock();

int main(int argc, const char * argv[]){
   omp_init_nest_lock(&bloqueo);

   #pragma omp parallel num_threads(4)
   {
        int i, j;

        for (i = 0; i < 5; ++i) {
            omp_set_nest_lock(&bloqueo);
            
                if (i % 3){
                    leoLock();
                }
            
            omp_unset_nest_lock(&bloqueo);
        }
    }

    omp_destroy_nest_lock(&bloqueo);
}

void leoLock() {
   
   omp_set_nest_lock(&bloqueo);
   
   printf("+++ Hilo %d ** empieza la region bloqueda\n", omp_get_thread_num());
   printf("--- Hilo %d ** termina la region bloqueda\n", omp_get_thread_num());
   
   omp_unset_nest_lock(&bloqueo);
}