#include <iostream>
#include <cstdlib>
#include <cstring>
#include <format>


class configuracion{
public:
    int rond_muerte_sub;
    int modo_muerte_sub;
    int rond_mod;
    float golpe_critico;
    int acierto;
};

class jugador{
public:
    int tipo_dado;
    //vida maxima
    double vida;
    //ataque base
    int atq_b;
    int turno;
    //vida que se mostrara en consola
    char vida_c[13];
};


void reglas(void);
int muerte_sub(int n,class configuracion[]);

void mostrar_vida(class jugador[]);
int tirar_dado(class jugador[],int n);
int ataque(class jugador[],int n,int dado,class configuracion);
int cura(class jugador[],int n,int dado,class configuracion);
int golpe_crit(class configuracion);
int acertar_golpe(class configuracion);
void mejora_d(class jugador[],int n);


int jugar(class jugador[],int n,class configuracion);
void configuraciones(class configuracion);


void clean_buffer(void);
void stop_system(void);