#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int x = 0;
int y = 0;
int contSeg = 3;
int idpadre;

void manejadorPrint(int ids);
void manejadorContador(int ids);
void manejadorSenal(int ids);

int main(){
    pid_t pid;
        
        pid = fork();
        
        if (pid == -1) {
                    return;
            }
            //HIJO
            if (pid == 0){
                idpadre=getppid();
                alarm(10);
                sleep(10);
                signal(SIGALRM, manejadorSenal);
                exit(1);
            }
            //PADRE
            else {
               int returnStatus;
               signal(SIGTSTP, manejadorContador);
               signal(SIGINT, manejadorContador);
               signal(SIGUSR1, manejadorPrint);
               printf("Aparezco cada %d segundos\n", contSeg);
               waitpid(pid, returnStatus, 0);
            }
        return 0;
}

void manejadorContador(int ids){
    
    if(ids == SIGTSTP){
        ++y;
        --contSeg;
    }
    
    if(ids == SIGINT){
        ++x;
        ++contSeg;
    }
}

void manejadorPrint(int ids){
    printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando…\n",x,y);
}

void manejadorSenal(int ids){
    kill(idpadre, SIGUSR1);
}