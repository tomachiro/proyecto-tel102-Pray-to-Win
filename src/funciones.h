#include <stdio.h>
struct jugador
{
    //tipo de dado
    int tipo_dado;
    //vida maxima
    double vida;
    //ataque base
    int atq_b;
    //turno
    int turno;
    //vida que se mostrara en consola
    char vida_c[13];
    
};
//prototipo de las funciones
//int n se va a referir al jugador actual en turno
//int dado es el valor del dado que toco en el turno 
void reglas(void);
void mostrar_vida(struct jugador[]);
int tirar_dado(struct jugador[],int n);
int ataque(struct jugador[],int n,int dado);
int cura(struct jugador[],int n,int dado);
int golpe_crit(struct jugador[],int n);
int mejora_d(struct jugador[],int n);
//jugar es donde se ejecuta el juego por turnos
int jugar(struct jugador[],int n);

//evitar errores en el main.c prototipar las funciones sacadas de paginas externas
void clean_buffer(void);
void stop_system(void);