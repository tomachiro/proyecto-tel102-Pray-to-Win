#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DisenoPersonajes.h"

#include <QMainWindow>
#include "funciones.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_ataque_clicked();

    void on_iniciar_clicked();

    void on_mejorar_clicked();

    void on_p_normal_clicked();

    void on_p_tanque_clicked();

    void on_p_suertudo_clicked();

    void on_rendirse_clicked();

    void on_curacion_clicked();

    void on_nombre_textEdited(const QString &arg1);

    void on_siguiente_clicked();

    void on_reiniciar_clicked();

    void on_salir_clicked();

    void on_reglas_clicked();

    void on_config_clicked();

    void on_volver_clicked();

    void on_volver_2_clicked();

    void on_rond_muerte_s_textChanged(const QString &arg1);

    void on_multi_crit_textChanged(const QString &arg1);

    void on_prob_acierto_textChanged(const QString &arg1);



private:
    int turno;
    int rond;
    int m_muerte_sub;
    int dado;
    jugador* jugadores[2];
    configuracion config;
    Ui::MainWindow *ui;
    void muerte_sub(int rond, configuracion& config, Ui::MainWindow* ui,int m_muerte_sub);
    void actualizar_vida(jugador* jugadores[], Ui::MainWindow* ui);
    int tirar_dado(jugador* jugadores[], int turno);
    void ataque(jugador* jugadores[], int turno, int dado, configuracion& config, Ui::MainWindow* ui);
    void cura(jugador* jugadores[], int turno, int dado, configuracion& config, Ui::MainWindow* ui);
    int golpe_crit(configuracion& config);
    void mejora_d(jugador* jugadores[], int turno, Ui::MainWindow* ui);
    void actualizar_ui();
};
#endif // MAINWINDOW_H
