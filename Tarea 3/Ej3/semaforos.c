#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/sem.h>

union semun
{
	int val;
	// value for SETVAL
	struct semid_ds* buf;
	// buffer for IPC_STAT, IPC_SET
	unsigned short* array; // array for GETALL, SETALL
	struct seminfo* __buf; // buffer for IPC_INFO
};


long factorial(int n)
{
  long acum = 1;
  int x;

  for(x = 1; x <= n; ++x){
	  acum *= x;
  }
	
  return acum;
}

int CreateSemaphore()
{

	int id;
	id = semget(IPC_PRIVATE, 1, SHM_R | SHM_W);
	return id;
}

void SetValSemaphore(int id, int n)
{
	union semun arg;
	
	arg.val = n;
	semctl(id, 0, SETVAL, arg);

}

int GetValSemaphore(int id)
{
	
	int value;
	value = semctl(id, 0, GETVAL);
	return value;
}

int main()
{
    long f;
    int key_t = CreateSemaphore();
	int value;
  if (fork()) {  
      wait(3);
      value = GetValSemaphore(key_t);
	  f = factorial(value);
      printf("El factorial de %d es %ld\n", value, f);

    } else {                            
	
	printf("Numero:");
	printf("\n");
    scanf("%d", &value);
	SetValSemaphore(key_t, value);    

    }
}