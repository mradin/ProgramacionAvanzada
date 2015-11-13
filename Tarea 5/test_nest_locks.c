#include <stdio.h>
#include <omp.h>

omp_nest_lock_t bloqueo;    

int main(int argc, const char * argv[]){
   omp_init_nest_lock(&bloqueo);

   #pragma omp parallel num_threads(4)
   {
      int tid = omp_get_thread_num();
      while (!omp_test_nest_lock(&bloqueo)){
         printf("===Hilo %d: nest lock ocupado\n",omp_get_thread_num());
      }
      
      printf("+++Hilo %d: consegui el nest lock\n", omp_get_thread_num());

      if (omp_test_nest_lock(&bloqueo)) {
         printf("+++Hilo %d: consegui el nest lock otra vez\n", omp_get_thread_num());
         printf("---Hilo %d: libere el lock (dentro del test)\n", omp_get_thread_num());
         omp_unset_nest_lock(&bloqueo);
      }

      printf("---Hilo %d: libere el lock\n", omp_get_thread_num());
      omp_unset_nest_lock(&bloqueo);
   }

   omp_destroy_nest_lock(&bloqueo);
}