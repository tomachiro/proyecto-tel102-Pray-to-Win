#include "funciones.h"
#include <stdlib.h>
#include <string.h>


//aqui empieza el robo de codigo
void clean_buffer(){
    char c;
    while ((c = getchar()) != EOF && c != '\n');
} /* This will clean the buffer */

void stop_system(){
    clean_buffer();
    printf("Presiona enter para continuar...");
    getchar();
} /* This will wait for the user to press Enter, similar to system("pause") */

/*codigo sacado directamente de https://askubuntu.com/questions/980804/systempause-for-linux-in-gcc-c#:~:text=If%20you%20don't%20call%20clean_buffer()%20inside%20stop_system(),it's%20important%20to%20clean%20the%20buffer%20first.*/
//necesidad de querer pausar el codigo y no querer entender porque funciona (muchos intentos autonomos no dieron resultados)


//aqui vuelve a ser codigo a manita
void mostrar_vida(struct jugador jugadores[]){
    //no es necesario poner un largo para cada vida porque comparten largo en todo momento
    
    for(int x=0;x!=2;x++){
        //es la vida faltante actual del jugador para usarlo al modificar 
        strcpy(jugadores[x].vida_c, "[----------]");
        int vida = jugadores[x].vida;
        int vida_f= 10-((100-vida)/10);
        for(int i=0;i!=vida_f;i+=1){
            jugadores[x].vida_c[i+1] = 'x';

        }


    }   
    printf("\t%s\t\t\t%s\n",jugadores[0].vida_c,jugadores[1].vida_c);
    return;
}


int cura(struct jugador jugadores[],int n,int dado){
    int cur=0;
    cur =((100-jugadores[n].vida)/14)*dado; 
    if(jugadores[n].vida>=100){
        printf("ya tienes vida suficiente\n");
    }else if (cur>0)
    {
        jugadores[n].vida=jugadores[n].vida+cur;
        printf("te curaste: %d puntos de vida\n",(cur));
        return 1;
    }
    else{
        printf("no te has podido curar\n");
        return 1;
    }
}

void reglas(void){
   system("clear");
   printf("aqui deberian ir reglas\naun no hay nada :3\n");
   stop_system();
   return; 
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

    //aqui reinicia los valores base de los jugadores por si se vuelve a inciar e juego sin terminar el codigo
    for(int i=0;i!=2;i++){
    jugadores[i].tipo_dado = 6;
    jugadores[i].vida = 100;
    jugadores[i].atq_b = 10;
    strcpy(jugadores[i].vida_c, "[----------]");  
    }


    do{
        char eleccion;
        char rendirse;
        system("clear");
        mostrar_vida(jugadores);
        printf("vida jugador 1:%f\t vida jugador 2:%f\n",(jugadores[0].vida),(jugadores[1].vida));
        printf("turno del jugador %d, elije una opcion.\n",turno+1);
        printf("1.atacar\t2.curar\t\t3.mejorar\t4.rendirse\n");
        scanf(" %c",&eleccion);
        switch (eleccion)
        {
        case '1':
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
            stop_system();
            //solo hace el cambio de turno cuando es necesario
            turno=(turno+1)%2;
            break;
        case '2':            
            dado=0;
            int cur=0;
            dado = tirar_dado(jugadores,turno);
            system("clear");
            printf("toco %d\n",dado);
            cur =cura(jugadores,turno,dado);
            stop_system();
            //solo hace el cambio de turno cuando es necesario
            if(cur==1){turno=(turno+1)%2;}
            break;
        case '3':
            break;
        case '4':
            do{
                system("clear");
                printf("seguro de rendirte jugador %d?\n",turno+1);
                printf("1.si\t2.no\n");
                scanf(" %c",&rendirse);
                switch(rendirse){
                    case '1':
                        system("clear");
                        printf("el jugador %d es el ganardor\n",((turno+1)%2)+1);
                        stop_system();
                        return 1;
                        break;
                    case '2':
                        break;
                    default:
                        printf("opción no valida\n");
                        stop_system();
                        break;
                }             
            }while(rendirse==0);

            break;
        default:
            system("clear");
            printf("sueltenme\n");
            stop_system();
            break;
        }
        if (jugadores[0].vida<=0){
            system("clear");
            printf("jugador 2 ha ganado..");
            stop_system();
            return 1;
        }else if(jugadores[1].vida<=0){
            system("clear");
            printf("jugador 1 ha ganado..");
            stop_system();
            return 1;
        }
    
    }while(turno!=3);
    return 1;

}
