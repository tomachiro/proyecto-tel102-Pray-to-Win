#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
int main(void){
    system("clear");
    int i=0;
    int n=0;
    char opcion;
    struct jugador j1,j2;
    j1.tipo_dado = 6;
    j1.vida = 100;
    j1.atq_b = 10;
    j1.turno = 0;

    j2.tipo_dado = 6;
    j2.vida = 100;
    j2.atq_b = 10;
    j2.turno=1;


    struct jugador jugadores[2];
    jugadores[0] = j1;
    jugadores[1] = j2;
    do{
        system("clear");
        printf("Selecciona una opción\n1.Jugar\t\t2.Configuración\n3.Reglas\t4.Salir\n");
        scanf("%c",&opcion);
    switch (opcion)
        {
        case '1':
            printf("presionaste 1\n");
            jugar(jugadores,n);
            break;
        case '2':
            printf("presionaste 2\n");
            printf("aun no hay nada\n");
            break;
        case '3':
            printf("presionaste 3\n");
            reglas();
            break;
        case '4':
            printf("seleccionaste 4\nsaliendo.\n");
            system("clear");
            return 1;
            break;
        
        default:
            printf("opción no valida\n");
            break;
        } 
    }while(i==0);
    return 1;

}

