#include <stdio.h>
struct configuracion{
    int rond_muerte_sub;
    int modo_muerte_sub;
    int rond_mod;
    };
        
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

    double presicion;
    
};
//prototipo de las funciones
//int n se va a referir al jugador actual en turno
//int dado es el valor del dado que toco en el turno 
void reglas(void);
//el entero n en este caso se vera reflejado en numero de rondas que lleve el juego
//donde muerte_sub entregara un 1 o un 0 para definir si muerte subita esta activa o no 
//asi que ahora las funciones cura y ataque van a tener que ingresar un nuevo valor i para saber si la muerte subita esta activa o no
int muerte_sub(int n,struct configuracion[]);
void mostrar_vida(struct jugador[]);
int tirar_dado(struct jugador[],int n);
int ataque(struct jugador[],int n,int dado,struct configuracion[]);
//la funcion cura es 
int cura(struct jugador[],int n,int dado,struct configuracion[]);
int golpe_crit(struct jugador[],int n);
//mejora_d se refiere para poder mejorar el dado
int mejora_d(struct jugador[],int n);
//jugar es donde se ejecuta el juego por turnos
int jugar(struct jugador[],int n,struct configuracion[]);

//evitar errores en el main.c prototipar las funciones sacadas de paginas externas
void clean_buffer(void);
void stop_system(void);