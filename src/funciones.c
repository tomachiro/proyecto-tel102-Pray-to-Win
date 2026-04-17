#include "funciones.h"
#include <stdlib.h>

int tirar_dado(struct jugador jugadores[],int n){
    int num;
    num = (rand()%jugadores[n].tipo_dado )+1;
    return num;
}

int jugar(struct jugador jugadores[],int n){
    int turno = n;
    int eleccion=0;
    do{
        printf("turno del jugador%d, elije una opcion.\n",turno+1);
        printf("1.atacar\t2.dudar");
        scanf("%d",&eleccion);
        switch (eleccion)
        {
        case 1:
            printf("toco %d\n",tirar_dado(jugadores,turno));
            break;
        
        default:
            printf("sueltenme\n");
            return 1;
            break;
        }
    turno=(turno+1)%2;
    }while(turno!=3);
    return 1;

}