#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char * nombre;
    char * apellidos;
    int edad;
    char * rol;
} tripulante;

typedef struct {
    char * nombreBarco;
    int eslora;
    int manga;
    int maxTripulantes;
    tripulante * tripulantes;
    int cantidadTripultantes;
} barco;



int main(int argc, const char * argv[]){
    
    int tam = 0;
    printf("Cuantos Barcos quieres: ");
    scanf("%d", &tam);
    
    barco * puerto;
    puerto = (barco *)malloc(tam * sizeof(barco));
    
    barco * aux;
    
    barco * finBarcos = puerto + tam;
    
    
    tripulante * auxTri;
    tripulante * finTri;
    for(aux = puerto; aux < finBarcos;++aux){

        aux->nombreBarco = (char *)malloc(sizeof(char)*25);
        printf("Nombre del barco: ");
        scanf("%s", aux->nombreBarco);
        
        printf("Eslora: ");
        scanf("%d", &aux->eslora);
        
        printf("Manga: ");
        scanf("%d", &aux->manga);
        
        printf("Maxima Cantidad de Tripulatnes: ");
        scanf("%d", &aux->maxTripulantes);
        
        printf("Cantidad Actual de Tripulatnes: ");
        scanf("%d", &aux->cantidadTripultantes);
        
        aux->tripulantes = (tripulante *)malloc(aux->cantidadTripultantes * sizeof(tripulante));
        finTri = aux->cantidadTripultantes + aux->tripulantes;
        
        for(auxTri = aux->tripulantes; auxTri < finTri; ++auxTri){
            auxTri->nombre = (char *)malloc(sizeof(char)*25);
            printf("Nombre del Tripulante: ");
            scanf("%s", auxTri->nombre);
            
            auxTri->apellidos = (char *)malloc(sizeof(char)*25);
            printf("Apellidos del Tripulante: ");
            scanf("%s", auxTri->apellidos);
            
            printf("Edad: ");
            scanf("%d", &auxTri->edad);
            
            auxTri->rol = (char *)malloc(sizeof(char)*25);
            printf("Rol: ");
            scanf("%s", auxTri->rol);
            
        }
        
    }
    
    
    //Print Barcos
    int numBarco = 1;
    for(aux=puerto; aux <finBarcos; ++aux){
        printf("ID del Barco: %d \n", numBarco);
        printf("Nombre del Barco: %s\n", aux->nombreBarco);
        printf("Eslora: %d\n", aux->eslora);
        printf("Manga : %d\n",aux->manga);
        printf("Maxima Cantidad de Tripulantes: %d\n", aux->maxTripulantes);
        
        finTri = aux->tripulantes + aux->cantidadTripultantes;
        
        for(auxTri=aux->tripulantes; auxTri < finTri; ++auxTri){
            printf("\tNombre del Tripulante: %s\n",auxTri->nombre);
        }
    }
    
    //Nuevo Barco
    int cantNuevo = 0;
    printf("Deseas agregar un nuevo barco?: ");
    scanf("%d",&cantNuevo);
    
    if(cantNuevo > 0){
        puerto = (barco *)realloc(puerto, sizeof(barco)*(tam + cantNuevo));
        finBarcos = puerto + tam + cantNuevo;
        
        for(aux=puerto+tam;aux<finBarcos;++aux){
            aux->nombreBarco = (char *)malloc(sizeof(char)*25);
            printf("Nombre del barco: ");
            scanf("%s", aux->nombreBarco);
        
            printf("Eslora: ");
            scanf("%d", &aux->eslora);
        
            printf("Manga: ");
            scanf("%d", &aux->manga);
        
            printf("Maxima Cantidad de Tripulatnes: ");
            scanf("%d", &aux->maxTripulantes);
        
            printf("Cantidad Actual de Tripulatnes: ");
            scanf("%d", &aux->cantidadTripultantes);
        
            aux->tripulantes = (tripulante *)malloc(aux->cantidadTripultantes * sizeof(tripulante));
            finTri = aux->cantidadTripultantes + aux->tripulantes;
        
            for(auxTri = aux->tripulantes; auxTri < finTri; ++auxTri){
               auxTri->nombre = (char *)malloc(sizeof(char)*25);
               printf("Nombre del Tripulante: ");
                scanf("%s", auxTri->nombre);
            
                auxTri->apellidos = (char *)malloc(sizeof(char)*25);
                printf("Apellidos del Tripulante: ");
                scanf("%s", auxTri->apellidos);
            
                printf("Edad: ");
                scanf("%d", &auxTri->edad);
            
                auxTri->rol = (char *)malloc(sizeof(char)*25);
                printf("Rol: ");
                scanf("%s", auxTri->rol);
            }
            
        }
    }
    
    int numBarco = 1;
    for(aux=puerto; aux <finBarcos; ++aux){
        printf("ID del Barco: %d \n", numBarco);
        printf("Nombre del Barco: %s\n", aux->nombreBarco);
        printf("Eslora: %d\n", aux->eslora);
        printf("Manga : %d\n",aux->manga);
        printf("Maxima Cantidad de Tripulantes: %d\n", aux->maxTripulantes);
        
        finTri = aux->tripulantes + aux->cantidadTripultantes;
        
        for(auxTri=aux->tripulantes; auxTri < finTri; ++auxTri){
            printf("\tNombre del Tripulante: %s\n",auxTri->nombre);
        }
    }
    //Limpia Memoria
    
    for(aux = puerto; aux<finBarcos; ++aux){
        free(aux->nombreBarco);
        for(auxTri = aux->tripulantes; auxTri< (aux->tripulantes+aux->cantidadTripultantes);++auxTri){
            free(auxTri->nombre);
            free(auxTri->apellidos);
            free(auxTri->rol);
        }
        free(aux->tripulantes);
    }
    
    free(puerto);
    return 0;
}