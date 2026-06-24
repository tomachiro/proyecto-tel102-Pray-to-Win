#include "funciones.h"

funciones::funciones(QObject *parent)
    : QObject{parent}
{}

/*int tirar_dado(jugador* jugadores[],int n){
    n-=1;
    int num;
    num = (rand()%jugadores[n]->ObtenerTipoDado() )+1;
    return num;
}
QString mejora_d(jugador* jugadores[],int n){
    n-=1;
    QString texto;
    int mejora=0;
    mejora=tirar_dado(jugadores,n);
    if(mejora==jugadores[n]->ObtenerTipoDado()){
        jugadores[n]->ModificarTipoDado(jugadores[n]->ObtenerTipoDado()+2);
        texto="Tu dado ha sido mejorado";
    }else{
        texto="ha sido mejorado tu dado";
    }
    return texto;
}


int golpe_crit(const configuracion &config){
    int probabilidad = (rand() % 100) + 1;
    if (probabilidad <= config.ObtenerGolpeCritico()) {
        return 1; // Golpe Critico
    }
    return 0; // No es Golpe Critico
}

int acertar_golpe(const configuracion &config, int dado, int n, jugador* jugadores[]){
    int probabilidad = (rand() % 100) + 1;

    // CORREGIDO: Tenías jugadores[1], lo cambié a jugadores[n] o al índice correcto de tu lógica
    if (dado == jugadores[n]->ObtenerTipoDado()){ return 1; }

    if (probabilidad <= config.ObtenerGolpeAcierto()) {
        return 1; // Golpe Acertado 80% en base
    }
    return 0;
}

int ataque(jugador* jugadores[], int n, int dado, const configuracion &config){
    n-=1;
    int dmg = 0;
    int acertado = acertar_golpe(config, dado, n, jugadores);

    if (acertado == 0) {
        return 0; // Golpe fallido, no causa daño
    }

    int critico = golpe_crit(config);
    dmg = (jugadores[n]->ObtenerAtqB() / 2) * dado;
    if (critico == 1 ){
        dmg = dmg * config.ObtenerGolpeCritico();
    }
    jugadores[(n + 1) % 2]->ModificarVida(jugadores[(n + 1) % 2]->ObtenerVida() - dmg);
    return dmg;

}
int cura(jugador* jugadores[],int n,int dado,const configuracion &config){
    QString texto;
    if( config.ObtenerEstadoMuerteSub()){
        texto = "Estás en muerte súbita. No te puedes curar";
    }else{
        int cur=0;
        cur =((jugadores[n]->ObtenerVida_t()-jugadores[n]->ObtenerVida())/14)*dado;
        if(jugadores[n]->ObtenerVida()>=jugadores[n]->ObtenerVida_t()){
            texto ="Ya tienes vida suficiente";
        }else if (cur>0)
        {
            jugadores[n]->ModificarVida(jugadores[n]->ObtenerVida()+cur);
            texto = "Te curaste: "+ QString::number(cur) +" puntos de vida";
            return 1;
        }
        else{
            texto ="No te has podido curar";
            return 1;
        }
    }
    return 1;
}
int muerte_sub(int n,class configuracion config){
    QString texto;
    if (n == config.ObtenerRondMuerteSub()){
        texto ="Es la ronda "+ QString::number(n)+". ¡La muerte súbita empieza";
        config.ModificarEstadoMuerteSub(true);
        //retorna 1 para expresar si la muerte subita esta activa
        return 1;
    }else{
        return 0;
    }

}*/