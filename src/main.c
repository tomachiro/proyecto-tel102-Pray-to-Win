#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
int i=0;
int opcion;
int main(void){
    do{
        printf("Selecciona una opción\n1.Jugar\t\t2.Configuración\n3.Reglas\t4.Salir\n");
        scanf("%d",&opcion);
    switch (opcion)
        {
        case 1:
            printf("presionaste 1\n");
            i++;
            break;
        case 2:
            printf("presionaste 2\n");
            i++;
            break;
        case 3:
            printf("presionaste 3\n");
            i++;
            break;
        case 4:
            printf("seleccionaste 4\n");
            i++;
            break;
        
        default:
            printf("opción no valida\n");
            break;
        } 
    }while(i==0);
    return 1;
}

