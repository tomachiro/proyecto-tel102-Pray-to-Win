#include <iostream>
#include <cstdlib>
#include <cstring>
#include <format>


class configuracion{
private:
    int rond_muerte_sub;
    bool modo_muerte_sub;
    int rond_mod;
    float golpe_critico;
    int acierto;
public:

// Constructor por defecto (valores iniciales del juego)
configuracion() : rond_muerte_sub(10), modo_muerte_sub(false), rond_mod(5), golpe_critico(1.5f), acierto(80) {}
configuracion(int rms,int mms, int rm, float gc, int ac) : rond_muerte_sub(rms), modo_muerte_sub(mms),rond_mod(rm), golpe_critico(gc), acierto (ac){}
 
// Esto es para  guardar los valores y calcular (el da;o, probabilidad de critico y si acierta o no) 

int ObtenerRondMuerteSub() {return rond_muerte_sub;} //para saber que ronda activa la muerte subita
bool ObtenerEstadoMuerteSub() {return modo_muerte_sub;}
int ObtenerRondMod() {return rond_mod;}
float ObtenerGolpeCritico() {return golpe_critico;} //Calcula si el golpe multiplico el da;o 
int ObtenerGolpeAcierto() {return acierto;} // Calcula si el ataque pego o fallo

//Aqui son los valores que el jugador modifica desde el menu de configuracion (cambiar la dificultad, activar modo muerte,etc.)

void ModificarRondMuerteSub(int v) {rond_muerte_sub = v;}
void ModificarEstadoMuerteSub(bool v) {modo_muerte_sub = v;}
void ModificarRondMod(int v) {rond_mod = v; }
void ModificarGolpeCritico(float v) {golpe_critico = v; }
void ModificarGolpeAcierto(int v) {acierto = v;}

};

class jugador{
private:
    int tipo_dado;
    //vida maxima
    double vida;
    //ataque base
    int atq_b;
    int turno;
    //vida que se mostrara en consola
    std::string vida_c;
public:
    jugador() : tipo_dado(6), vida(100), atq_b(10), turno(0) {
        vida_c = "[----------]"; // la barra vacia por defecto
    }
    jugador(int t) : tipo_dado(6), vida(100), atq_b(10), turno(t) {
        vida_c = "[----------]"; //el constructor con el turno especifico
    }

    // Obtener los valores (lectura)

    int ObtenerTipoDado() { return tipo_dado; }
    double ObtenerVida() { return vida; }
    int ObtenerAtqB() { return atq_b; }
    int ObtenerTurno() { return turno; }
    const std::string ObtenerVidaC() { return vida_c; }

    // Modificar los valores (escritura)
    void ModificarTipoDado(int v) { tipo_dado = v; }
    void ModificarVida(double v) { vida = v; }
    void ModificarAtqB(int v) { atq_b = v; }
    void ModificarTurno(int v) { turno = v; }
    void ModificarVidaC(const std::string v) { vida_c = v; }
    //funcion hecha ya que la barra de vida modificaba el arreglo de caracteres directamente y con modificarVidaC() no es capaz de hacer eso
    void Modificar_Vida_c_pos(int pos, char x){
        if(pos>=0 && pos <12 ){
            vida_c[pos] = x;
        }
    }
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