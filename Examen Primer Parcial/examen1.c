#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    char * nomina;
    int periodo;
    int simetrico; //1 Si 0 No
    int niveles;
    int * modales;
    char * fecha;
    
} edificio;

typedef struct{
    char * nomina;
    int modales;
    int periodo;
    char * techo;
    char * fecha;
} nave;

typedef struct{
    char * nomina;
    int niveles;
    int * modales;
    int periodo;
    int * diametros;
    char * fecha;
} torre;

typedef struct{
    char * nomina;
    char * nombre;
    char * apellidos;
    char * fechaNac;
    char * ingreso;
    int salario;
    char * puesto;
    
} ingeniero;



int main(){
    
    int numEmpleados = 2;
    
    ingeniero * empleados;
    empleados = (ingeniero *)malloc(sizeof(ingeniero) * numEmpleados);
    
    ingeniero * empAux;
    ingeniero * empFin = empleados + numEmpleados;;
    
    //Crea Empleados
    for(empAux = empleados; empAux < empFin; ++empAux){
        
        empAux->nomina = (char *)malloc(sizeof(char *) * 100);
        printf("Numero de Nomina: ");
        scanf("%s", empAux->nomina);
        
        empAux->nombre = (char *)malloc(sizeof(char *) * 100);
        printf("Nombre: ");
        scanf("%s", empAux->nombre);
        
        empAux->apellidos = (char *)malloc(sizeof(char *) * 200);
        printf("Apellidos: ");
        scanf("%s", empAux->apellidos);
        
        empAux->fechaNac = (char *)malloc(sizeof(char *) * 200);
        printf("Fecha de Nacimiento: ");
        scanf("%s", empAux->fechaNac);
        
        empAux->ingreso = (char *)malloc(sizeof(char *) * 200);
        printf("Fecha de Ingreso: ");
        scanf("%s", empAux->ingreso); 
        
        printf("Salario: ");
        scanf("%d", empAux->salario);
        
        empAux->puesto = (char *)malloc(sizeof(char *) * 200);
        printf("Puesto: ");
        scanf("%s", empAux->puesto); 

    }
    
    //Naves
    nave * casas;
    casas = (nave *)malloc(sizeof(nave) * 3);
    
    nave * casasAux;
    nave * casasFin;
    

    
    for(casasAux = casas; casasAux < casasFin; ++casasAux){
        
        casasAux->nomina = (char *)malloc(sizeof(char) * 100);
        printf("Numero de Nomina del empleado: ");
        scanf("%s", casasAux->nomina);
        
        printf("Modal: ");
        scanf("%d", casasAux->modales);

        printf("Periodo: ");
        scanf("%d", casasAux->periodo);   
        
        casasAux->techo = (char *)malloc(sizeof(char) * 100);
        printf("Tipo de techo: ");
        scanf("%s", casasAux->techo);
        
        casasAux->fecha = (char *)malloc(sizeof(char) * 100);
        printf("fecha (AAAA-MM-DD): ");
        scanf("%s", casasAux->fecha);
    }
    
    //Edificios
    edificio * edif;
    edif = (edificio *)malloc(sizeof(edificio) * 3);
    
    edificio * edifAux;
    edificio * edifFin;
    
    int * modalesAux;
    int * modalesFin;
    
    for(edifAux = edif; edifAux < edifFin; ++edifAux){
        
        edifAux->nomina = (char *)malloc(sizeof(char) * 100);
        printf("Numero de Nomina del empleado: ");
        scanf("%s", edifAux->nomina);
        
        printf("Periodo: ");
        scanf("%d", edifAux->periodo);  
        
        printf("Simetrico: ");
        scanf("%d", edifAux->simetrico);

        printf("Niveles: ");
        scanf("%d", edifAux->niveles);
        
        edifAux->fecha = (char *)malloc(sizeof(char) * 100);
        printf("fecha (AAAA-MM-DD): ");
        scanf("%s", edifAux->fecha);
        
        edifAux->modales = (int *)malloc(sizeof(int) * edifAux->niveles);
        modalesFin =edifAux->modales + edifAux->niveles;
        
        srand(time(NULL));
        
        for(modalesAux = edifAux->modales; modalesAux < modalesFin; ++modalesAux){
            *modalesAux = rand() % 100;
        }
        
    }
    
    //Torres
    torre * torres;
    torres = (torre *)malloc(sizeof(torre) * 3);
    
    torre * torresfAux;
    torre * torresFin;
    
    int * modalesAux2;
    int * modalesFin2;
    
    int * diamAux;
    int * diamFin;
    
    for(torresfAux = torres; torresfAux < torresFin; ++torresfAux){
        
        torresfAux->nomina = (char *)malloc(sizeof(char) * 100);
        printf("Numero de Nomina del empleado: ");
        scanf("%s", torresfAux->nomina);
        
        printf("Niveles: ");
        scanf("%d", torresfAux->niveles);
        
        printf("Periodo: ");
        scanf("%d", torresfAux->periodo);
        
        torresfAux->fecha = (char *)malloc(sizeof(char) * 100);
        printf("Fecha (AAAA-MM-DD): ");
        scanf("%s", torresfAux->fecha);
        
        torresfAux->modales = (int *)malloc(sizeof(int) * torresfAux->niveles);
        modalesFin =torresfAux->modales + torresfAux->niveles;
        
        srand(time(NULL));
        
        for(modalesAux2 = torresfAux->modales; modalesAux2 < modalesFin2; ++modalesAux2){
            *modalesAux2 = rand() % 100;
        }
        
        torresfAux->diametros = (int *)malloc(sizeof(int) * (torresfAux->niveles * 2));
        
        diamFin = torresfAux->diametros + (torresfAux->niveles * 2);
        for(diamAux = torresfAux->modales; diamAux < diamFin; ++diamAux){
            *diamAux = rand() % 100;
        }
        
    }
    
    //Reportes
    //Reporte de RH
    printf("Reporte RH\n");
    
    for(empAux=empleados; empAux < empFin; ++empAux){
        
        printf("Empleado \n");
        printf("Numero de Nomina: %d", empAux->nomina);
        printf("Nombre: &s", empAux->nombre);
        printf("Apellidos: &s", empAux->apellidos);
        printf("Fecha de Nacimiento: %s", empAux->fechaNac);
        printf("Fecha de Ingreso: %s", empAux->ingreso);
        printf("Puesto: %s", empAux->puesto);
        printf("Salario: $%d",empAux->salario);
    }
    
    //Modelos por fecha y empleado
    
    char * numNomina = (char *)malloc(sizeof(char)*100);
    char * fechaBus = (char *)malloc(sizeof(char) * 100);
    
    printf("Reporte de un empleado \n");
    printf("Numero de Nomina: ");
    scanf("%s", numNomina);
    
    printf("Fecha (AAAA-MM-DD: ");
    scanf("%s", fechaBus);
    
    
    for(casasAux=casas; casasAux < casasFin; ++casasAux){
        
        if(casasAux->fecha == fechaBus && casasAux->nomina == numNomina){
            printf("Modelos de Naves \n");
            printf("Numero de nomina del creador: %s\n", casasAux->nomina);
            printf("Tipo de techo: %s \n", casasAux->techo);
            printf("Resultado de modales: %d \n", casasAux->modales);
            printf("Periodo: %d \n", casasAux->periodo);
            printf("----------------");
            
        }
    }
    
    for(torresfAux=torres; torresfAux < torresFin; ++torresfAux){
        
        if(torresfAux->fecha == fechaBus && torresfAux->nomina == numNomina){
            printf("Modelos de Torres \n");
            printf("Numero de nomina del creador: %s\n", torresfAux->nomina);
            printf("Periodo: %d \n", torresfAux->periodo);
            for(modalesAux2=torresfAux->modales; modalesAux2<modalesFin2;++modalesAux2){
                printf("modales: %d", *modalesAux2);
            }
            for(diamAux=torresfAux->diametros; diamAux < diamFin; ++diamAux){
                printf("Diametros: %d",*diamAux);
            }
            printf("----------------");
            
        }
    }

    for(edifAux=torres; edifAux < edifFin; ++edifAux){
        
        if(edifAux->fecha == fechaBus && edifAux->nomina == numNomina){
            printf("Modelos de Edificios \n");
            printf("Numero de nomina del creador: %s\n", edifAux->nomina);
            printf("Niveles: %d\n", edifAux->niveles);
            if(edifAux->simetrico==1){
                printf("Simetrico: Si");
            }
            else{
                printf("Simetrico: No");                
            }
            printf("Periodo: %d \n", edifAux->periodo);
            for(modalesAux2=edifAux->modales; modalesAux2<modalesFin2;++modalesAux2){
                printf("modales: %d", *modalesAux2);
            }
            printf("----------------");
            
        }
    }
    
    
    //Liberar Memoria
    //Lista de empleados
    for(empAux=empleados;empAux<empFin;++empAux){
        free(empAux->nomina);
        free(empAux->nombre);
        free(empAux->apellidos);
        free(empAux->fechaNac);
        free(empAux->ingreso);
        free(empAux->puesto);
    
    }
    
    //Lista de Naves
        for(casasAux=casas;casasAux<casasFin;++casasAux){
        free(casasAux->nomina);
        free(casasAux->techo);
        free(casasAux->fecha);
    
    }
    
    //Lista de Edificios
    for(edifAux=edif;edifAux<edifFin;++edifAux){
        free(edifAux->nomina);
        free(edifAux->modales);
        free(edifAux->fecha);
    }
    
    //Lista de Torres
    for(torresfAux=torres;torresfAux<torresFin;++torresfAux){
        free(torresfAux->nomina);
        free(torresfAux->modales);
        free(torresfAux->fecha);
    }
  
    return 0;
}
