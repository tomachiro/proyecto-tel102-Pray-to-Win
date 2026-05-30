#include "funciones.hpp"

// intentar implementar las funciones de clean_buffer y stop_system de mejor manera que en c
void clean_buffer(){
    char c;
    while ((c = getchar()) != EOF && c != '\n');
} /* This will clean the buffer */

void stop_system(){
    clean_buffer();
    std::cout<<"\033[37mPresiona enter para continuar...\033[0m";
    getchar();
} /* This will wait for the user to press Enter, similar to system("pause") */


int muerte_sub(int n,class configuracion config){
    if (n == config.ObtenerRondMuerteSub()){
        std::system("clear");
        std::cout << std::format("\033[31mEs la ronda {}. ¡La muerte súbita empieza!\033[0m", n) << std::endl;
        config.ModificarEstadoMuerteSub(true);
        stop_system();
        //retorna 1 para expresar si la muerte subita esta activa
        return 1;
    }else{
        return 0;
    }

}
void mostrar_vida(jugador* jugadores[]){
    for(int x=0;x!=2;x++){
        //la vida visual se inicia en 0 para ir aumentando en cada iteracion 
        jugadores[x]->ModificarVidaC("[----------]");
        //variable hecha para facilitar la lectura en un futuro y no tener que trabajar directamente con la vida del jugador
        double vida_t = jugadores[x]->ObtenerVida_t(); 
        double vida = jugadores[x]->ObtenerVida();
        //vida_f es la vida faltante para saber cuantas x (vida en enteros de 10) tiene que colocar
        int vida_f= (vida/vida_t)*10;
        for(int i=0;i!=vida_f;i+=1){
            jugadores[x]->Modificar_Vida_c_pos(i+1,'x');

        }
    }   
    std::cout<<std::format("\033[36m\t{}\t\t\t{}\033[0m",jugadores[0]->ObtenerVidaC(),jugadores[1]->ObtenerVidaC())<<std::endl;
    return;
}
int cura(jugador* jugadores[],int n,int dado,class configuracion config){
    if( config.ObtenerEstadoMuerteSub()){
        std::cout<<"\033[31mEstás en muerte súbita. No te puedes curar\033[0m"<<std::endl;
    }else{
        int cur=0;
        cur =((jugadores[n]->ObtenerVida_t()-jugadores[n]->ObtenerVida())/14)*dado; 
        if(jugadores[n]->ObtenerVida()>=jugadores[n]->ObtenerVida_t()){
            std::cout<<"\033[36mYa tienes vida suficiente\033[0m" <<std::endl; 
        }else if (cur>0)
        {
            jugadores[n]->ModificarVida(jugadores[n]->ObtenerVida()+cur);
            std::cout<<std::format("\033[32mTe curaste: {} puntos de vida\033[0m",(cur))<<std::endl;
            return 1;
        }
        else{
            std::cout<<"\033[31mNo te has podido curar\033[0m"<<std::endl;
            return 1;
        }
    }
    return 1;
}
void reglas(void){
   std::system("clear");
   std::cout<<"\033[37mReglas del juego\npara cada acción tienes que tirar un dado y referente a este define que tan efectivo\nes la acción. no olvides\033[0m"<<std::endl;
   std::cout<<"\033[36m1.ataca para eliminar al contrincante\n2.Cúrate para evitar ser eliminado\n3.Mejora el dado para tener mayores probabilidad de hacer más daño\n4.Reza por no fallar los ataques\033[0m"<<std::endl;
   stop_system();
   return; 
}

int tirar_dado(jugador* jugadores[],int n){
    int num;
    num = (rand()%jugadores[n]->ObtenerTipoDado() )+1;
    return num;
}
void mejora_d(jugador* jugadores[],int n){
    int mejora=0;
    mejora=tirar_dado(jugadores,n);
    if(mejora==jugadores[n]->ObtenerTipoDado()){
        jugadores[n]->ModificarTipoDado(jugadores[n]->ObtenerTipoDado()+2);
        std::cout<<"\033[32mTu dado ha sido mejorado\033[0m"<<std::endl;
    }else{
        std::cout<<"\033[31mNo ha sido mejorado tu dado\033[0m"<<std::endl;
    }
    return;
}


int golpe_crit(class configuracion config){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= config.ObtenerGolpeCritico()) {
        return 1; // Golpe Critico
    }
    return 0; // No es Golpe Critico
}

int acertar_golpe(class configuracion config,int dado,int n,jugador* jugadores[]){
    int probabilidad = (rand() % 100) + 1;
    if (dado ==jugadores[1]->ObtenerTipoDado()){return 1;}
    if (probabilidad <= config.ObtenerGolpeAcierto()) {
        return 1; // Golpe Acertado 80% en base
    }
    return 0; 
}
int ataque(jugador* jugadores[],int n,int dado,class configuracion config){
    int dmg=0;
    int acertado = acertar_golpe(config,dado,n,jugadores);
    if (acertado == 0) {
        std::cout<<"\033[31mGolpe fallido\033[0m"<<std::endl;
        return 0; // Golpe fallido, no causa daño
    }
    int critico = golpe_crit(config);
    dmg =(jugadores[n]->ObtenerAtqB()/2)*dado;
    if (critico == 1 ){
        // se podria coloar un mensaje de golpe critico
        std::cout<<"\033[33m¡Golpe crítico!\033[0m"<<std::endl;
        dmg=dmg*config.ObtenerGolpeCritico();
    }
    jugadores[(n+1)%2]->ModificarVida(jugadores[(n+1)%2]->ObtenerVida()-dmg);
    return dmg;
}

void configuraciones(class configuracion config){
    char eleccion;
    float cambio_f=0;
    int cambio=0;
    while(1){    
        std::system("clear");
        std::cout<<"\033[37melige lo que quieres modificar\033[0m\n";
        std::cout<<std::format("\033[36m1.ronda de muerte subita={}\n2.probabilidad de critico={}\n3.probabilidad de acierto={}\n4.Salir\033[0m",config.ObtenerRondMuerteSub(),config.ObtenerGolpeCritico(),config.ObtenerGolpeAcierto())<<std::endl;
        std::cin>>eleccion;
        switch (eleccion)
        {
        case '1':
            std::system("clear");
            std::cout<<std::format("\033[37mcambia el valor de ronda de muerte subita:\nactual={}\033[0m",config.ObtenerRondMuerteSub())<<std::endl;
            std::cin>>cambio;
            config.ModificarRondMuerteSub(cambio);
            std::system("clear");
            std::cout<<std::format("\033[32mse actualizo el valor a:{}\033[0m",config.ObtenerRondMuerteSub())<<std::endl;
            stop_system();
            break;
        case '2':
            std::system("clear");
            std::cout<<std::format("\033[37mcambia el valor de golpe critico:\nactual={}\033[0m",config.ObtenerGolpeCritico())<<std::endl;
            std::cin>>cambio_f;
            config.ModificarGolpeCritico(cambio_f);
            std::system("clear");
            std::cout<<std::format("\033[32mse actualizo el valor a:{}\033[0m",config.ObtenerGolpeCritico())<<std::endl;
            stop_system();
            break;
        case '3':
            std::system("clear");
            std::cout<<std::format("\033[37mcambia el valor de acierto:\nactual={}\033[0m",config.ObtenerGolpeAcierto())<<std::endl;
            std::cin>>cambio;
            config.ModificarGolpeAcierto(cambio);
            std::system("clear");
            std::cout<<std::format("\033[32mse actualizo el valor a:{}\033[0m",config.ObtenerGolpeAcierto())<<std::endl;
            stop_system();
            break;
        case '4':
            return;
            break;
        default:
            std::cout<<"\033[33mopcion no valida\033[0m"<<std::endl;
            stop_system();
            break;
        }
    }
}
void seleccion_personaje(jugador* jugadores[]){
    for (int i=0;i!=2;i++){
        char opcion;
        std::system("clear");
        std::cout<<std::format("\033[37mjugador {} selecciona un personaje\033[0m\n\033[36m1.tanque -> tiene 50 más de vida pero tiene una moneda\033[0m",i+1)<<std::endl;
        std::cout<<"\033[36m2.normal -> tiene los atributos por defecto\033[0m"<<std::endl;
        std::cout<<"\033[36m3.suertudo -> tiene 50 de vida pero su dado es de 10\033[0m"<<std::endl;
        std::cin>>opcion;
        switch (opcion)
        {
        case '1':
            std::system("clear");
            std::cout<<"\033[32mse selecciono tanque\033[0m"<<std::endl;
            stop_system();
            jugadores[i] = new tanque(i);
            break;
        case '2':
            std::system("clear");
            std::cout<<"\033[32mse selecciono normal\033[0m"<<std::endl;
            stop_system();
            jugadores[i] = new jugador(i);
            break;
        case '3':
            std::system("clear");
            std::cout<<"\033[32mse selecciono suertudo\033[0m"<<std::endl;
            stop_system();
            jugadores[i] = new suertudo(i);
            break;
        default:
            std::cout<<"\033[33mopcion no valida\033[0m";
            stop_system();
            break;
        }
    }
}

int jugar(jugador* jugadores[],int n,class configuracion config){
    //aqui se define la variable para cuando se implemente la configuracion decidir que jugador empieza
    seleccion_personaje(jugadores);
    int ronda=1;
    int turno = n;
    int inicio = n;
    char log[100][200];
    int log_count = 0;
    int muerte_sub_activa =0;
    
    do{
        //aqui el uso de variables se podria reducir evitando redundancias al re-iniciarlas en 0 todo el tiempo
        char eleccion;
        char rendirse;
        int dado;
        int dmg;
        int muerte_sub_activa = muerte_sub(ronda,config);
        std::system("clear");
        mostrar_vida(jugadores);
        std::cout<<std::format("\033[36mvida jugador 1:{}\t vida jugador 2:{}\033[0m",(jugadores[0]->ObtenerVida()),(jugadores[1]->ObtenerVida()))<<std::endl;
        std::cout<<std::format("\033[36mDado={}\t\t\t\t\tdado={}\033[0m",jugadores[0]->ObtenerTipoDado(),jugadores[1]->ObtenerTipoDado())<<std::endl;
        std::cout<<std::format("\033[37mturno del jugador {}, elije una opcion.\033[0m",turno+1)<<std::endl;
        std::cout<<"\033[36m1.atacar\t2.curar\t\t3.mejorar\t4.rendirse\t5.ver log\033[0m"<<std::endl;
        std::cin>>eleccion;
        switch (eleccion)
        {
        case '1':
            dado=0;
            dmg=0;
            dado = tirar_dado(jugadores,turno);
            dmg = ataque(jugadores,turno,dado,config);
            std::system("clear");
            std::cout<<std::format("\033[33mtocó {}\033[0m",dado)<<std::endl;
            std::cout<<std::format("\033[32mle quitaste: {} puntos de vida al jugador {}\033[0m",(dmg),((turno+1)%2)+1)<<std::endl;            
            stop_system();
            if (turno == inicio) {
                sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d ataca con dado %d, quita %d vida a Jugador %d", ronda, turno+1, dado, dmg, ((turno+1)%2)+1);
                log_count++;
            } else {
                char buffer[120];
                sprintf(buffer, ", Jugador %d ataca con dado %d, quita %d vida a Jugador %d", turno+1, dado, dmg, ((turno+1)%2)+1);
                strcat(log[log_count-1], buffer);
            }
            turno=(turno+1)%2;
            if (turno == inicio) {
                ronda+=1;
            }
            break;
        case '2': {
            dado=0;
            dado = tirar_dado(jugadores,turno);
            std::system("clear");
            std::cout<<std::format("\033[33mtocó {}\033[0m",dado)<<std::endl;
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
                std::cout<<std::format("\033[37mseguro de rendirte jugador {}?\033[0m",turno+1)<<std::endl;
                std::cout<<"\033[36m1.si\t2.no\033[0m"<<std::endl;
                std::cin>>rendirse;
                switch(rendirse){
                    case '1':
                        std::system("clear");
                        std::cout<<std::format("\033[31mel jugador {} es el ganador\033[0m",((turno+1)%2)+1)<<std::endl;
                        if (turno == inicio) {
                            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d se rinde, Jugador %d gana", ronda, turno+1, ((turno+1)%2)+1);
                            log_count++;
                        } else {
                            char buffer[120];
                            sprintf(buffer, ", Jugador %d se rinde, Jugador %d gana", turno+1, ((turno+1)%2)+1);
                            strcat(log[log_count-1], buffer);
                        }
                        stop_system();
                        delete jugadores[1];
                        delete jugadores[0];
                        return 1;
                        break;
                    case '2':
                        break;
                    default:
                        std::system("clear");
                        std::cout<<"\033[33mopción no valida\033[0m"<<std::endl;
                        stop_system();
                        break;
                }             
            }while(rendirse==0);
            break;
        case '5':{
            std::system("clear");
            for(int i=0;i<log_count;i++) std::cout<<"\033[36m"<<log[i]<<"\033[0m"<<std::endl;
            stop_system();
            break;}
        default:{
            std::system("clear");
            std::cout<<"\033[33mopción no valida\033[0m"<<std::endl;
            stop_system();
            break;}
        }
        
       for(int i=0;i!=2;i++){
        if(jugadores[i]->ObtenerVida()<=0){
            sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m Jugador %d gana por derrota del oponente", ronda, ((i+1)%2)+1);
            log_count++;
            std::system("clear");
            std::cout<<std::format("\033[32mjugador {} ha ganado..\033[0m",(((i+1)%2)+1))<<std::endl;
            stop_system();
            delete jugadores[1];
            delete jugadores[0];
            return 1;
        }
       }
    }while(true);
    if(muerte_sub_activa){
        sprintf(log[log_count], "\n\033[1mRonda %d:\033[0m \033[31mMuerte súbita activada\033[0m", ronda);
        log_count++;
    }
    return 1;
}
