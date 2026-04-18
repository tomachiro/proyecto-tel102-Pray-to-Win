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
    int turno = n;
    int eleccion=0;
    do{
        int rendirse=0;
        system("clear");
        printf("vida jugador 1:%d\t vida jugador 2:%d\n",jugadores[0].vida,jugadores[1].vida);
        printf("turno del jugador %d, elije una opcion.\n",turno+1);
        printf("1.atacar\t2.cudar\t\t3.mejorar\t4.rendirse\n");
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
            /*el (turno+1)%2 representa a nivel de codigo el jugador contrario al turno es decir si el turno es 1 a nivel de codigo
            es el turno del jugador 2 y el turno 0 es del jugador 1*/ 
            system("clear");
            printf("toco %d\n",dado);
            printf("le quitaste: %d puntos de vida al jugador %d\n",(dmg),((turno+1)%2)+1);
            printf("pulsa enter para continuar\n");
            
            
            //intentar implementar un "pulsar enter para continuar"
            //solo hace el cambio de turno cuando es necesario
            turno=(turno+1)%2;
            break;
        case 2:
            printf("hola\n");
            break;
        case 3:
            break;
        case 4:
            do{
                system("clear");
                printf("seguro de rendirte jugador %d?\n",turno+1);
                printf("1.si\t2.no\n");
                scanf("%d",&rendirse);
                switch(rendirse){
                    case 1:
                        printf("el jugador %d es el ganardor\n",((turno+1)%2)+1);
                        //intentar implementar un "pulsar enter para continuar"
                        return 1;
                        break;
                    case 2:
                        break;
                    default:
                        printf("opción no valida");
                        break;
                }             
            }while(rendirse==0);

            break;
        default:
            system("clear");
            printf("sueltenme\n");
            return 1;
            break;
        }
    
    }while(turno!=3);
    return 1;

}
