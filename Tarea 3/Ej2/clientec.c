#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     32
long factorial(int n);

main()
{
    int shmid;
    key_t key;
    int num;
    int *numeros;
    int res = 0;
    
    key = 8349;
    
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((numeros = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    
    
    res = factorial(*numeros);
    
    printf("El factorial es: \t%d", res);
    printf("\n");
    
    
    exit(0);
}

long factorial(int n) {
    long res = 1;
    int i;
    for (i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}