#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define GRABAR 1

int main(int argc, const char * argv[]){
    
    sigset_t conjunto,pendientes;
    
    sigemptyset(&conjunto);
    sigfillset(&conjunto);
    sigdelset(&conjunto, SIGALRM);
    sigprocmask(SIG_BLOCK,&conjunto,NULL);
    
    struct stat s;
    
    int err=0;
    err = stat("../datos", &s);
    
    if(-1 == err) {
        mkdir("datos",0700);
    }
    else{
        system("exec rm -r /datos/*");
    }
    
    
    
    FILE * pFile;
    int x,y,temp;
    for(x=0;x<5;++x){
        pFile = fopen ("/datos/archivo0"+x+".txt","w");
        for(y=3;y>=0;--y){
            if(GRABAR == 1){
                fprintf(pFile,"x");
                sleep(1);
            }
            GRABAR = 0;
        }
        
    }
    
    
    
    return 0;
    
    
}