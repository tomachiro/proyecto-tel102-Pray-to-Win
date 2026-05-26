#include "funciones.hpp"

// intentar implementar las funciones de clean_buffer y stop_system de mejor manera que en c
void clean_buffer(){
    char c;
    while ((c = getchar()) != EOF && c != '\n');
} /* This will clean the buffer */

void stop_system(){
    clean_buffer();
    printf("Presiona enter para continuar...");
    getchar();
} /* This will wait for the user to press Enter, similar to system("pause") */



int muerte_sub(int n,class configuracion config){
    if (n == config.rond_muerte_sub){
        std::system("clear");
        std::cout << std::format("Es la ronda {}. La muerte súbita empieza", n) << std::endl;
        config.modo_muerte_sub=1;
        stop_system();
        //retorna 1 para expresar si la muerte subita esta activa
        return 1;
    }else{
        return 0;
    }

}
void mostrar_vida(class jugador jugadores[]){
    for(int x=0;x!=2;x++){
        //la vida visual se inicia en 0 para ir aumentando en cada iteracion 
        std::strcpy(jugadores[x].vida_c, "[----------]");
        //variable hecha para facilitar la lectura en un futuro y no tener que trabajar directamente con la vida del jugador
        int vida = jugadores[x].vida;
        //vida_f es la vida faltante para saber cuantas x (vida en enteros de 10) tiene que colocar
        int vida_f= vida/10;
        for(int i=0;i!=vida_f;i+=1){
            jugadores[x].vida_c[i+1] = 'x';

        }
    }   
    std::cout<<std::format("\t{}\t\t\t{}",jugadores[0].vida_c,jugadores[1].vida_c)<<std::endl;
    return;
}
int cura(class jugador jugadores[],int n,int dado,class configuracion config){
    if( config.modo_muerte_sub==1){
        std::cout<<"Estas en muerte subita. no te puedes curar"<<std::endl;
    }else{
        int cur=0;
        cur =((100-jugadores[n].vida)/14)*dado; 
        if(jugadores[n].vida>=100){
            std::cout<<"ya tienes vida suficiente" <<std::endl; 
        }else if (cur>0)
        {
            jugadores[n].vida=jugadores[n].vida+cur;
            std::cout<<std::format("te curaste: {} puntos de vida",(cur))<<std::endl;
            return 1;
        }
        else{
            std::cout<<"no te has podido curar\n";
            return 1;
        }
    }
    return 1;
}
void reglas(void){
   std::system("clear");
   std::cout<<"Reglas del juego\npara cada acción tienes que tirar un dado y referente a este define que tan efectivo\nes la acción. no olvides"<<std::endl;
   std::cout<<"1.ataca para eliminar al contrincante\n2.Curate para evitar ser eliminado\n3.Mejora el dado para tener mayores probabilidad de hacer más daño\n4.Reza por no fallar los ataques\n";
   stop_system();
   return; 
}

int tirar_dado(class jugador jugadores[],int n){
    int num;
    num = (rand()%jugadores[n].tipo_dado )+1;
    return num;
}
void mejora_d(class jugador jugadores[],int n){
    int mejora=0;
    mejora=tirar_dado(jugadores,n);
    if(mejora==jugadores[n].tipo_dado){
        jugadores[n].tipo_dado +=2;
        std::cout<<"tu dado ha sido mejorado"<<std::endl;
    }else{
        std::cout<<"no ha sido mejorado tu dado"<<std::endl;
    }
    return;
}

// arreglar que no se esta usando la class de config
int golpe_crit(class configuracion config){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= 20) {
        return 1; // Golpe Critico
    }
    return 0; // No es Golpe Critico
}

int acertar_golpe(class configuracion config){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= config.acierto) {
        return 1; // Golpe Acertado 80% en base
    }
    return 0; 
}
int ataque(class jugador jugadores[],int n,int dado,class configuracion config){
    int dmg=0;
    int acertado = acertar_golpe(config);
    if (acertado == 0) {
        return 0; // Golpe fallido, no causa daño
    }
    int critico = golpe_crit(config);
    dmg =(jugadores[n].atq_b/2)*dado;
    if (critico == 1 ){
        // se podria coloar un mensaje de golpe critico
        dmg=dmg*config.golpe_critico;
    }
    jugadores[(n+1)%2].vida-=dmg;
    return dmg;
}

void configuraciones(class configuracion config){
    char eleccion;
    float cambio_f=0;
    int cambio=0;
    while(1){    
        std::system("clear");
        std::cout<<"elige lo que quieres modificar\n";
        std::cout<<std::format("1.ronda de muerte subita={}\n2.probabilidad de critico={}\n3.probabilidad de acierto={}\n4.Salir",config.rond_muerte_sub,config.golpe_critico,config.acierto)<<std::endl;
        std::cin>>eleccion;
        switch (eleccion)
        {
        case '1':
            std::system("clear");
            std::cout<<std::format("cambia el valor de ronda de muerte subita:\nactual={}",config.rond_muerte_sub)<<std::endl;
            std::cin>>cambio;
            config.rond_muerte_sub=cambio;
            std::system("clear");
            std::cout<<std::format("se actualizo el valor a:{}",config.rond_muerte_sub)<<std::endl;
            stop_system();
            break;
        case '2':
            std::system("clear");
            std::cout<<std::format("cambia el valor de golpe critico:\nactual={}",config.golpe_critico)<<std::endl;
            std::cin>>cambio_f;
            config.golpe_critico=cambio_f;
            std::system("clear");
            std::cout<<std::format("se actualizo el valor a:",config.golpe_critico)<<std::endl;
            stop_system();
            break;
        case '3':
            std::system("clear");
            std::cout<<std::format("cambia el valor de acierto:\nactual={}",config.acierto)<<std::endl;
            std::cin>>cambio;
            config.acierto=cambio;
            std::system("clear");
            std::cout<<std::format("se actualizo el valor a:{}",config.acierto)<<std::endl;
            stop_system();
            break;
        case '4':
            return;
            break;
        default:
            std::cout<<"opcion no valida"<<std::endl;
            stop_system();
            break;
        }
    }
}



int jugar(class jugador jugadores[],int n,class configuracion config){
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
    std::strcpy(jugadores[i].vida_c, "[----------]");  
    }
    

    do{
        //aqui el uso de variables se podria reducir evitando redundancias al re-iniciarlas en 0 todo el tiempo
        char eleccion;
        char rendirse;
        int dado;
        int dmg;
        int muerte_sub_activa = muerte_sub(ronda,config);
        std::system("clear");
        mostrar_vida(jugadores);
        std::cout<<std::format("vida jugador 1:{}\t vida jugador 2:{}",(jugadores[0].vida),(jugadores[1].vida))<<std::endl;
        std::cout<<std::format("Dado={}\t\t\t\t\tdado={}",jugadores[0].tipo_dado,jugadores[1].tipo_dado)<<std::endl;
        std::cout<<std::format("turno del jugador {}, elije una opcion.",turno+1)<<std::endl;
        std::cout<<"1.atacar\t2.curar\t\t3.mejorar\t4.rendirse\t5.ver log"<<std::endl;
        std::cin>>eleccion;
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
            std::system("clear");
            std::cout<<std::format("toco {}",dado)<<std::endl;
            std::cout<<std::format("le quitaste: {} puntos de vida al jugador {}",(dmg),((turno+1)%2)+1)<<std::endl;            
            stop_system();
            if (turno == inicio) {
                 //buscar la manera de traducir de sprintf a la fomra nativa de cpp
                sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d ataca con dado %d, quita %d vida a Jugador %d", ronda, turno+1, dado, dmg, ((turno+1)%2)+1);
                log_count++;
            } else {
                char buffer[120];
                 //buscar la manera de traducir de sprintf a la fomra nativa de cpp
                sprintf(buffer, ", Jugador %d ataca con dado %d, quita %d vida a Jugador %d", turno+1, dado, dmg, ((turno+1)%2)+1);
                strcat(log[log_count-1], buffer);
            }
            //solo hace el cambio de turno cuando es necesario
            turno=(turno+1)%2;
            if (turno == inicio) {
                ronda+=1;
            }
            break;
        case '2': {
            //posible cambio es pasar todo esto a la funcion de curar           
            dado=0;
            dado = tirar_dado(jugadores,turno);
            std::system("clear");
            std::cout<<std::format("toco {}",dado)<<std::endl;
            int cur =cura(jugadores,turno,dado,config);
            stop_system();
            if (turno == inicio) {
                sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d cura con dado %d, recupera %d vida", ronda, turno+1, dado, cur);
                log_count++;
            } else {
                char buffer[120];
                 //buscar la manera de traducir de sprintf a la fomra nativa de cpp
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

            break;}
        case '3':
            std::system("clear");
            mejora_d(jugadores,turno);
            turno=(turno+1)%2;
            stop_system();
            
            break;
        case '4':
            do{
                std::system("clear");
                std::cout<<std::format("seguro de rendirte jugador {}?",turno+1)<<std::endl;
                std::cout<<"1.si\t2.no"<<std::endl;
                std::cin>>rendirse;
                switch(rendirse){
                    case '1':
                        std::system("clear");
                        std::cout<<std::format("el jugador {} es el ganardor",((turno+1)%2)+1)<<std::endl;
                        if (turno == inicio) {
                            //buscar la manera de traducir de sprintf a la fomra nativa de cpp
                            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d se rinde, Jugador %d gana", ronda, turno+1, ((turno+1)%2)+1);
                            log_count++;
                        } else {
                            char buffer[120];
                             //buscar la manera de traducir de sprintf a la fomra nativa de cpp junto a strcat
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
                        std::system("clear");
                        std::cout<<"opción no valida"<<std::endl;
                        stop_system();
                        break;
                }             
            
            }while(rendirse==0);

            break;
        case '5':{
            std::system("clear");
            for(int i=0;i<log_count;i++) std::cout<<log[i]<<std::endl;
            stop_system();
            break;}
        default:{
            std::system("clear");
            std::cout<<"opción no valida"<<std::endl;
            stop_system();
            break;}
        }
        
       for(int i=0;i!=2;i++){
        if(jugadores[i].vida<=0){
             //buscar la manera de traducir de sprintf a la fomra nativa de cpp
            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d gana por derrota del oponente", ronda, ((i+1)%2)+1);
            log_count++;
            std::system("clear");
            std::cout<<std::format("jugador {} ha ganado..",(((i+1)%2)+1))<<std::endl;
            stop_system();
            return 1;
        }
       }
    



    }while(true);
    if(muerte_sub_activa){
         //buscar la manera de traducir de sprintf a la fomra nativa de cpp
    sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Muerte súbita activada", ronda);
    log_count++;}
    return 1;

}
