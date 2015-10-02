#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


void processStatus();

void printStatus(long tgid);

int main(int argc, char **argv) {
     int c;
     int minutes = 0 ;
    while ((c = getopt (argc, argv, "m:")) != -1)
        switch (c)
    {
        case 'm':
            minutes = atoi(optarg);
	    if(minutes<=0)
	    {
		printf("El tiempo no puede ser menor a 0\n");
		abort();
	    }
            printf("Se veran los procesos cada %d minutos\n",minutes);
            break;
        case '?':
                printf ("No se reconoce la entrada usar -m MINUTOS\n");
            return 1;
        default:
	    printf("\n");
            abort ();
    }

pid_t pid, sid;     
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0) {
       	exit(EXIT_FAILURE);
    }

    while (1){
    	sleep(60*minutes);
    	processStatus();
    }

    return 0;
}

void printStatus(long tgid) {
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", tgid);

    statusf = fopen(path, "r");
    if(!statusf)
        return;

    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "State:", 6) != 0)
            continue;
        // Ignore "State:" and whitespace
        p = line + 7;
        while(isspace(*p)) ++p;

        printf("%ld %s", tgid, p);
        break;
    }

    fclose(statusf);
}

void processStatus(){
    pid_t pid;
    int i, c;
    
    DIR* proc = opendir("/proc");
    struct dirent* ent;
    long tgid;
    closedir(proc);


        proc = opendir("/proc");

        if(proc == NULL) {
        perror("opendir(/proc)");
        return;
        }
        
        while(ent = readdir(proc)) {
            if(!isdigit(*ent->d_name))
                continue;
    
            tgid = strtol(ent->d_name, NULL, 10);
    
            printStatus(tgid);
            }

        closedir(proc);
}