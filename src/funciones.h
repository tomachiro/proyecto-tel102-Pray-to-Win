#include <stdio.h>
struct jugador
{
    //tipo de dado
    int tipo_dado;
    //vida maxima
    int vida;
    //ataque base
    int atq_b;
    
};
//prototipo de las funciones
int vida_consola(struct jugador[]);
int tirar_dado(struct jugador[]);
int ataque(struct jugador[]);
int curacion(struct jugador[]);
int golpe_crit(struct jugador[]);
int mejora_d(struct jugador[]);


