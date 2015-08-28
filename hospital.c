#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 3
typedef struct
{
    int edad;
    char* nombre;
    char* apellido;

} Paciente;

typedef struct
{
    Paciente* paciente;
    int id_cama;
    int status;

} Cama;

typedef struct
{
    Cama* camas;
    int total;
    int ocupadas;

} Hospital;

void imprimir(Hospital*);
void agregar(Hospital*);
void libera(Hospital *);

typedef void (*Opcion) (Hospital *);


Opcion opciones[] = {agregar, imprimir, libera };

int main() {
    Hospital *h = (Hospital*)malloc(sizeof(Hospital));
    h->total = N;
    h->ocupadas = 0;
    h->camas = (Cama*)malloc(h->total * sizeof(Cama));

    int cama_id =0;
    Cama * aux;
    for(aux = h->camas + h->ocupadas; aux < h->camas + h->total; aux++)
    {
        aux->id_cama = cama_id++;
        aux->status = 0;
    }

    int opcion = 0;
    while(opcion != 3)
    {
        printf("Menu\n");
        printf("1. Nuevo Paciente\n");
        printf("2. Ver Hospital\n");
        printf("3. Salir\n");

        scanf("%d", &opcion);

        if(opcion == 5)
        {
            printf("Programa terminado");
            break;
        }
        opciones[opcion-1](h);

    }

    libera(h);
    free(h);
}

void imprimir(Hospital *h){

    Cama* aux;
    for (aux = h->camas; aux < h->camas + h->ocupadas; aux++){
    if(aux->status != 0)
        printf("\nCama: %d\nNombre: %s\nApellido: %s\nEdad: %d\n",aux->id_cama, aux->paciente->nombre, aux->paciente->apellido, aux->paciente->edad);
        printf("\n-------------------------------------------------\n");
    }

}
void agregar(Hospital *h){

    Paciente *p = (Paciente*)malloc(sizeof(Paciente));

    p->nombre = (char*)malloc(20*sizeof(char));
    p->apellido = (char*)malloc(20*sizeof(char));

    printf("Nombre: ");
    scanf("%s", p->nombre);
    printf("\nApellido: ");
    scanf("%s", p->apellido);
    printf("\nEdad: ");
    scanf("%d", &p->edad);

    if (h->ocupadas < h->total){
        Cama * aux = h->camas;
        while( aux->status == 1)
        {
            aux++;
        }
        aux->paciente = p;
        aux->status = 1;

        h->ocupadas++;
    }
    else {

        h->camas = (Cama*)realloc(h->camas,sizeof(Cama)*(h->total+N));
        h->total = h->total+N;
        Cama * aux = h->camas+ h->ocupadas;

        int cama_id = aux->id_cama+1;

        for(aux = h->camas + h->ocupadas; aux < h->camas + h->total; aux++)
        {
            aux->id_cama = cama_id++;
            aux->status = 0;
        }
        aux = h->camas + h-> ocupadas;

        while( aux->status == 1 && aux < h->camas+ h->total)
        {
            aux++;
        }
        aux->paciente = p;
        aux->status = 1;
        h->ocupadas++;


    }
}

void libera(Hospital * h)
{
    Cama * aux;
    for(aux = h->camas; aux < h->camas+h->total; aux++)
    {
        if(aux->paciente != NULL)
        {
            free(aux->paciente->apellido);
            free(aux->paciente->nombre);
            free(aux->paciente);
        }

    }
    free(h->camas);
}