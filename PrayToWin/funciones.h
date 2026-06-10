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

class jugador : public QObject{
private:
    int tipo_dado;
    //vida maxima
    double vida_t;
    double vida;
    //ataque base
    int atq_b;
    int turno;
    //vida que se mostrara en consola
    std::string vida_c;
public:
    jugador() : tipo_dado(6),vida_t(100), vida(100), atq_b(10), turno(0) {
        vida_c = "[----------]"; // la barra vacia por defecto
    }
    jugador(int t) : tipo_dado(6),vida_t(100), vida(100), atq_b(10), turno(t) {
        vida_c = "[----------]"; //el constructor con el turno especifico
    }

    // Obtener los valores (lectura)

    int ObtenerTipoDado() { return tipo_dado; }
    double ObtenerVida() { return vida; }
    double ObtenerVida_t() { return vida_t; }
    int ObtenerAtqB() { return atq_b; }
    int ObtenerTurno() { return turno; }
    const std::string ObtenerVidaC() { return vida_c; }

    // Modificar los valores (escritura)
    void ModificarTipoDado(int v) { tipo_dado = v; }
    void ModificarVida(double v) { vida = v; }
    void ModificarVida_t(double v) { vida_t = v; }
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
#endif // FUNCIONES_H
