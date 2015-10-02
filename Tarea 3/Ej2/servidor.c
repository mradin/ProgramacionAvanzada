#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     32

long long factorial(int n);

int main()
{
    int num;
    int shmid;
    key_t key;
    
    int *numeros;
    int resultado = 0;

    key = 8349;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    if ((numeros = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    
    while(1)
    {
        printf("Que numero quieres factorizar: ");
        scanf("%d", numeros);
        printf("\n");
    }
    

    exit(0);
    
    return 0;
}