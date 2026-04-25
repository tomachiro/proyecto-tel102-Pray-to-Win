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


int muerte_sub(int n,struct configuracion config[]){
    if (n == config[0].rond_muerte_sub){
        system("clear");
        printf("Es la ronda %d. la muerte subita empieza\n",n);
        config[0].modo_muerte_sub=1;
        stop_system();
        //retorna 1 para expresar si la muerte subita esta activa
        return 1;
    }else{
        return 0;
    }

}

void mostrar_vida(struct jugador jugadores[]){
    for(int x=0;x!=2;x++){
        //la vida visual se inicia en 0 para ir aumentando en cada iteracion 
        strcpy(jugadores[x].vida_c, "[----------]");
        //variable hecha para facilitar la lectura en un futuro y no tener que trabajar directamente con la vida del jugador
        int vida = jugadores[x].vida;
        //vida_f es la vida faltante para saber cuantas x (vida en enteros de 10) tiene que colocar
        int vida_f= vida/10;
        for(int i=0;i!=vida_f;i+=1){
            jugadores[x].vida_c[i+1] = 'x';

        }
    }   
    printf("\t%s\t\t\t%s\n",jugadores[0].vida_c,jugadores[1].vida_c);
    return;
}


int cura(struct jugador jugadores[],int n,int dado,struct configuracion config[]){
    if( config[0].modo_muerte_sub==1){
        printf("Estas en muerte subita. no te puedes curar\n");
    }else{
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
}

void reglas(void){
   system("clear");
   printf("Reglas del juego\npara cada acción tienes que tirar un dado y referente a este define que tan efectivo\nes la acción. no olvides\n");
   printf("1.ataca para eliminar al contrincante\n2.Curate para evitar ser eliminado\n3.Mejora el dado para tener mayores probabilidad de hacer más daño\n4.Reza por no fallar los ataques\n");
   stop_system();
   return; 
}

int tirar_dado(struct jugador jugadores[],int n){
    int num;
    num = (rand()%jugadores[n].tipo_dado )+1;
    return num;
}
void mejora_d(struct jugador jugadores[],int n){
    int mejora=0;
    mejora=tirar_dado(jugadores,n);
    if(mejora==jugadores[n].tipo_dado){
        jugadores[n].tipo_dado +=2;
        printf("tu dado ha sido mejorado");
    }else{
        printf("no ha sido mejorado tu dado");
    }
    return;
}
int golpe_crit(struct configuracion config[]){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= 20) {
        return 1; // Golpe Critico
    }
    return 0; // No es Golpe Critico
}
int acertar_golpe(struct configuracion config[]){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= 100-config[0].acierto) {
        return 1; // Golpe Acertado 80% en base
    }
    return 0; 
}
int ataque(struct jugador jugadores[],int n,int dado,struct configuracion config[]){
    int dmg=0;
    int acertado = acertar_golpe(config);
    if (acertado == 0) {
        return 0; // Golpe fallido, no causa daño
    }
    int critico = golpe_crit(config);
    dmg =(jugadores[n].atq_b/2)*dado;
    if (critico == 1 ){
        // se podria coloar un mensaje de golpe critico
        dmg=dmg*config[0].golpe_critico;
    }
    jugadores[(n+1)%2].vida-=dmg;
    return dmg;
}
void configuraciones(struct configuracion config[]){
    char eleccion;
    float cambio_f=0;
    int cambio=0;
    while(1){    
        system("clear");
        printf("elige lo que quieres modificar\n");
        printf("1.ronda de muerte subita=%d\n2.probabilidad de critico=%f\n3.probabilidad de acierto=%d\n",config[0].rond_muerte_sub,config[0].golpe_critico,config[0].acierto);
        scanf(" %c",&eleccion);
        switch (eleccion)
        {
        case '1':
            system("clear");
            printf("cambia el valor de ronda de muerte subita:\nactual=%d\n",config[0].rond_muerte_sub);
            scanf("%d",&cambio);
            config[0].rond_muerte_sub=cambio;
            system("clear");
            printf("se actualizo el valor a:%d",config[0].rond_muerte_sub);
            stop_system();
            break;
        case '2':
            system("clear");
            printf("cambia el valor de golpe critico:\nactual=%f\n",config[0].golpe_critico);
            scanf("%f",&cambio_f);
            config[0].golpe_critico=cambio_f;
            system("clear");
            printf("se actualizo el valor a:%f",config[0].golpe_critico);
            stop_system();
            break;
        case '3':
            system("clear");
            printf("cambia el valor de acierto:\nactual=%d\n",config[0].acierto);
            scanf("%d",&cambio);
            config[0].acierto=cambio;
            system("clear");
            printf("se actualizo el valor a:%d",config[0].acierto);
            stop_system();
            break;
        default:
            printf("opcion no valida");
            stop_system();
            break;
        }
    }
}


int jugar(struct jugador jugadores[],int n,struct configuracion config[]){
    //aqui se define la variable para cuando se implemente la configuracion decidir que jugador empieza
    int ronda=1;
    int turno = n;
    int inicio = n;
    char log[100][200];
    int log_count = 0;
    int muerte_sub_activa =0;
    //aqui el for funciona para cambiar entre jugador 1 y 2
    for(int i=0;i!=2;i++){
    //aqui reinicia los valores base de los jugadores por si se vuelve a inciar e juego sin terminar el codigo
    jugadores[i].tipo_dado = 6;
    jugadores[i].vida = 100;
    jugadores[i].atq_b = 10;
    strcpy(jugadores[i].vida_c, "[----------]");  
    }
    

    do{
        //aqui el uso de variables se podria reducir evitando redundancias al re-iniciarlas en 0 todo el tiempo
        char eleccion;
        char rendirse;
        int dado;
        int dmg;
        int muerte_sub_activa = muerte_sub(ronda,config);
        system("clear");
        mostrar_vida(jugadores);
        printf("vida jugador 1:%f\t vida jugador 2:%f\n",(jugadores[0].vida),(jugadores[1].vida));
        printf("Dado=%d\t\t\t\t\tdado=%d\n",jugadores[0].tipo_dado,jugadores[1].tipo_dado);
        printf("turno del jugador %d, elije una opcion.\n",turno+1);
        printf("1.atacar\t2.curar\t\t3.mejorar\t4.rendirse\t5.ver log\n");
        scanf(" %c",&eleccion);
        switch (eleccion)
        {
        case '1':
            //todo este codigo se podria migrar a la funcion ataque tirando el dado directamente en la función 
        
            //reinicia la variable dado para evitar errores en cada iteracion del while
            dado=0;
            dmg=0;
            //se asignan los valores correspondientes al turno
            dado = tirar_dado(jugadores,turno);
            dmg = ataque(jugadores,turno,dado,config);
            /*el (turno+1)%2 representa a nivel de codigo el jugador contrario al turno es decir si el turno es 1 a nivel de codigo
            es el turno del jugador 2 y el turno 0 es del jugador 1*/ 
            system("clear");
            printf("toco %d\n",dado);
            printf("le quitaste: %d puntos de vida al jugador %d\n",(dmg),((turno+1)%2)+1);            
            stop_system();
            if (turno == inicio) {
                sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d ataca con dado %d, quita %d vida a Jugador %d", ronda, turno+1, dado, dmg, ((turno+1)%2)+1);
                log_count++;
            } else {
                char buffer[120];
                sprintf(buffer, ", Jugador %d ataca con dado %d, quita %d vida a Jugador %d", turno+1, dado, dmg, ((turno+1)%2)+1);
                strcat(log[log_count-1], buffer);
            }
            //solo hace el cambio de turno cuando es necesario
            turno=(turno+1)%2;
            if (turno == inicio) {
                ronda+=1;
            }
            break;
        case '2': 
            //posible cambio es pasar todo esto a la funcion de curar           
            dado=0;
            dado = tirar_dado(jugadores,turno);
            system("clear");
            printf("toco %d\n",dado);
            int cur =cura(jugadores,turno,dado,config);
            stop_system();
            if (turno == inicio) {
                sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d cura con dado %d, recupera %d vida", ronda, turno+1, dado, cur);
                log_count++;
            } else {
                char buffer[120];
                sprintf(buffer, ", Jugador %d cura con dado %d, recupera %d vida", turno+1, dado, cur);
                strcat(log[log_count-1], buffer);
            }
            //solo hace el cambio de turno cuando se la acción de curar si se completa 
            if(cur==1){
                turno=(turno+1)%2;
            if (turno == inicio) {
                ronda+=1;
            }

            }

            break;
        case '3':
            system("clear");
            mejora_d(jugadores,turno);
            turno=(turno+1)%2;
            stop_system();
            
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
                        if (turno == inicio) {
                            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d se rinde, Jugador %d gana", ronda, turno+1, ((turno+1)%2)+1);
                            log_count++;
                        } else {
                            char buffer[120];
                            sprintf(buffer, ", Jugador %d se rinde, Jugador %d gana", turno+1, ((turno+1)%2)+1);
                            strcat(log[log_count-1], buffer);
                        }
                        stop_system();
                        return 1;
                        break;
                    case '2':
                        // no seria necesario poner codigo ya que simplemente cerraria el switch y si se rinde volvemos a la funcion main
                        break;
                    default:
                        system("clear");
                        printf("opción no valida\n");
                        stop_system();
                        break;
                }             
            
            }while(rendirse==0);

            break;
        case '5':
            system("clear");
            for(int i=0;i<log_count;i++) printf("%s\n",log[i]);
            stop_system();
            break;
        default:
            system("clear");
            printf("opción no valida\n");
            stop_system();
            break;
        }
        
       for(int i=0;i!=2;i++){
        if(jugadores[i].vida<=0){
            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d gana por derrota del oponente", ronda, ((i+1)%2)+1);
            log_count++;
            system("clear");
            printf("jugador %d ha ganado..\n",(((i+1)%2)+1));
            stop_system();
            return 1;
        }
       }
    


    //deja while 1 ya que en todas las condiciones anteriores se retorna asi que nunca es un bucle infinito 
    }while(1);
    if(muerte_sub_activa){
    sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Muerte súbita activada", ronda);
    log_count++;}
    return 1;

}
