#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
int main(void){
    system("clear");
    int i=0;
    int n=0;
    char opcion;

    struct jugador jugadores[2];
        for (int i=0;i!=2;i++){
        jugadores[i].tipo_dado = 6;
        jugadores[i].vida = 100;
        jugadores[i].atq_b = 10;
        jugadores[i].turno=i;
        strcpy(jugadores[i].vida_c, "[----------]");    
        }
    do{
        system("clear");
        printf("Selecciona una opción\n1.Jugar\t\t2.Configuración\n3.Reglas\t4.Salir\n");
        scanf(" %c",&opcion);
    switch (opcion)
        {
        case '1':
            jugar(jugadores,n);
            break;
        case '2':
            system("clear");
            printf("aun no hay nada\n");
            stop_system();
            break;
        case '3':
            reglas();
            break;
        case '4':
            system("clear");
            printf("saliendo....\n");
            stop_system();
            system("clear");
            return 1;
            break;
        
        default:
            system("clear");
            printf("opción no valida\n");
            stop_system();
            break;
        } 
    }while(i==0);
    return 1;

}

