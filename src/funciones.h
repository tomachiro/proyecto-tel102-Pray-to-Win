#include <stdio.h>
struct jugador
{
    //tipo de dado
    int tipo_dado;
    //vida maxima
    int vida;
    //ataque base
    int atq_b;
    //turno
    int turno;
};
//prototipo de las funciones
//int n se va a referir al jugador actual en turno
//int dado es el valor del dado que toco en el turno 
int reglas(void);
int tirar_dado(struct jugador[],int n);
int ataque(struct jugador[],int n,int dado);
int curacion(struct jugador[],int n);
int golpe_crit(struct jugador[],int n);
int mejora_d(struct jugador[],int n);
//jugar es donde se ejecuta el juego por turnos
int jugar(struct jugador[],int n);

