#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <QObject>

class funciones : public QObject
{
    Q_OBJECT
public:
    explicit funciones(QObject *parent = nullptr);

signals:
};

class configuracion:public QObject{
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

    int ObtenerRondMuerteSub() const{return rond_muerte_sub;} //para saber que ronda activa la muerte subita
    bool ObtenerEstadoMuerteSub() const{return modo_muerte_sub;}
    int ObtenerRondMod() const{return rond_mod;}
    float ObtenerGolpeCritico() const{return golpe_critico;} //Calcula si el golpe multiplico el da;o
    int ObtenerGolpeAcierto() const{return acierto;} // Calcula si el ataque pego o fallo

    //Aqui son los valores que el jugador modifica desde el menu de configuracion (cambiar la dificultad, activar modo muerte,etc.)

    void ModificarRondMuerteSub(int v) {rond_muerte_sub = v;}
    void ModificarEstadoMuerteSub(bool v) {modo_muerte_sub = v;}
    void ModificarRondMod(int v) {rond_mod = v; }
    void ModificarGolpeCritico(float v) {golpe_critico = v; }
    void ModificarGolpeAcierto(int v) {acierto = v;}

};

class jugador : public QObject{
private:
    int tipo_dado;
    //vida maxima
    double vida_t;
    double vida;
    //ataque base
    int atq_b;
    int turno;
    QString nombre;
    //vida que se mostrara en consola
    //std::string vida_c;
public:
    jugador() : tipo_dado(6),vida_t(100), vida(100), atq_b(10), turno(0) {
        //vida_c = "[----------]"; // la barra vacia por defecto
    }
    jugador(int t) : tipo_dado(6),vida_t(100), vida(100), atq_b(10), turno(t) {
        //vida_c = "[----------]"; //el constructor con el turno especifico
    }

    // Obtener los valores (lectura)

    int ObtenerTipoDado() { return tipo_dado; }
    double ObtenerVida() { return vida; }
    double ObtenerVida_t() { return vida_t; }
    int ObtenerAtqB() { return atq_b; }
    int ObtenerTurno() { return turno; }
    QString obtenernombre(){return nombre;}
    //const std::string ObtenerVidaC() { return vida_c; }

    // Modificar los valores (escritura)
    void modificarnombre(QString v){nombre =v;}
    void ModificarTipoDado(int v) { tipo_dado = v; }
    void ModificarVida(double v) { vida = v; }
    void ModificarVida_t(double v) { vida_t = v; }
    void ModificarAtqB(int v) { atq_b = v; }
    void ModificarTurno(int v) { turno = v; }
    //void ModificarVidaC(const std::string v) { vida_c = v; }
};
class tanque : public jugador {
public:
    tanque(int t) : jugador(t) {
        ModificarVida(150);
        ModificarVida_t(150);
        ModificarTipoDado(2);
    }
};
class suertudo:public jugador{
public:
    suertudo(int t):jugador(t){
        ModificarVida(50);
        ModificarVida_t(50);
        ModificarTipoDado(10);
    }
};

#endif // FUNCIONES_H
