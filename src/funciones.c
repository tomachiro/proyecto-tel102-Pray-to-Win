#include "funciones.h"
#include <stdlib.h>


int reglas(void){
   system("clear");
   printf("aqui deberian ir reglas\naun no hay nada :3\n");
   return 1; 
}

int tirar_dado(struct jugador jugadores[],int n){
    int num;
    num = (rand()%jugadores[n].tipo_dado )+1;
    return num;
}
int ataque(struct jugador jugadores[],int n,int dado){
    int dmg=0;
    dmg =(jugadores[n].atq_b/2)*dado;
    jugadores[(n+1)%2].vida-=dmg;
    return dmg;
}

int jugar(struct jugador jugadores[],int n){
    system("clear");
    int turno = n;
    int eleccion=0;
    do{
        printf("turno del jugador %d, elije una opcion.\n",turno+1);
        printf("1.atacar\t2.dudar\n");
        scanf("%d",&eleccion);
        switch (eleccion)
        {
        case 1:
            //reinicia la variable dado para evitar errores en cada iteracion del while
            int dado=0;
            int dmg=0;
            //se asignan los valores correspondientes al turno
            dado = tirar_dado(jugadores,turno);
            dmg = ataque(jugadores,turno,dado);
            
            system("clear");
            printf("toco %d\n",dado);
            printf("le quitaste: %d puntos de vida al jugador %d\n",(dmg),(turno+1)%2);
            break;
        
        default:
            system("clear");
            printf("sueltenme\n");
            return 1;
            break;
        }
    turno=(turno+1)%2;
    }while(turno!=3);
    return 1;

}
