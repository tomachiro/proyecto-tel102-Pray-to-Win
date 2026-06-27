#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLCDNumber"
#include "QPushButton"
#include "QStackedWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    turno = 1;
    rond = 1;
    m_muerte_sub = 0;
    dado = 0;
    jugadores[0] = nullptr;   // inicializar punteros
    jugadores[1] = nullptr;
}
MainWindow::~MainWindow()
{
    if (jugadores[0]) { delete jugadores[0]; jugadores[0] = nullptr; }
    if (jugadores[1]) { delete jugadores[1]; jugadores[1] = nullptr; }
    delete ui;
}
void MainWindow::actualizar_ui() {
    if (!jugadores[0] || !jugadores[1]) return; // protección

    ui->vida_j1->display(jugadores[0]->ObtenerVida());
    ui->vida_j2->display(jugadores[1]->ObtenerVida());
    ui->dado_1->setText("dado: " + QString::number(jugadores[0]->ObtenerTipoDado()));
    ui->dado_2->setText("dado: " + QString::number(jugadores[1]->ObtenerTipoDado()));

    int siguiente = (turno == 1) ? 2 : 1;
    ui->letoca->setText("le toca a " + jugadores[siguiente-1]->obtenernombre());
    ui->ronda->display(rond);
    ui->barra_j1->setRange(0, jugadores[0]->ObtenerVida_t());
    ui->barra_j1->setValue(jugadores[0]->ObtenerVida());
    ui->barra_j2->setRange(0, jugadores[1]->ObtenerVida_t());
    ui->barra_j2->setValue(jugadores[1]->ObtenerVida());
}

void MainWindow::muerte_sub(int rond, configuracion& config, Ui::MainWindow* ui,int m_muerte_sub) {
    if ((rond == config.ObtenerRondMuerteSub()) && (m_muerte_sub==0)) {
        ui->accion->setText("Es la ronda " + QString::number(rond) + ". ¡La muerte súbita empieza!");
        config.ModificarEstadoMuerteSub(true);
        //QMessageBox::warning(nullptr, "Muerte súbita", "¡La muerte súbita ha comenzado!");
        return;
    }
    return;
}
void MainWindow::actualizar_vida(jugador* jugadores[], Ui::MainWindow* ui) {
    double vida_t1 = jugadores[0]->ObtenerVida_t();
    double vida1   = jugadores[0]->ObtenerVida();
    double vida_t2 = jugadores[1]->ObtenerVida_t();
    double vida2   = jugadores[1]->ObtenerVida();

    ui->vida_j1->display(vida1);
    ui->barra_j1->setValue((vida1 / vida_t1) * 100);

    ui->vida_j2->display(vida2);
    ui->barra_j2->setValue((vida2 / vida_t2) * 100);
}
void MainWindow::cura(jugador* jugadores[], int turno, int dado, configuracion& config, Ui::MainWindow* ui) {
    int idx = turno - 1; // turno 1 -> jugador[0], turno 2 -> jugador[1]

    if (config.ObtenerEstadoMuerteSub()) {
        ui->accion->setText("Estás en muerte súbita. No te puedes curar");
        return;
    }

    int cur = ((jugadores[idx]->ObtenerVida_t() - jugadores[idx]->ObtenerVida()) / 14) * dado;

    if (jugadores[idx]->ObtenerVida() >= jugadores[idx]->ObtenerVida_t()) {
        ui->accion->setText("Ya tienes vida suficiente");
    } else if (cur > 0) {
        jugadores[idx]->ModificarVida(jugadores[idx]->ObtenerVida() + cur);
        ui->accion->setText(jugadores[idx]->obtenernombre() + " se curó " + QString::number(cur) + " puntos de vida");
        actualizar_vida(jugadores, ui);
        return;
    } else {
        ui->accion->setText("No te has podido curar");
    }
    return;
}
int MainWindow::tirar_dado(jugador* jugadores[], int turno) {
    int idx = turno - 1;
    return (rand() % jugadores[idx]->ObtenerTipoDado()) + 1;
}
void MainWindow::mejora_d(jugador* jugadores[], int turno, Ui::MainWindow* ui) {
    int idx = turno - 1;
    int mejora = tirar_dado(jugadores, turno);

    if (mejora == jugadores[idx]->ObtenerTipoDado()) {
        jugadores[idx]->ModificarTipoDado(jugadores[idx]->ObtenerTipoDado() + 2);
        ui->accion->setText(jugadores[idx]->obtenernombre() + " mejoró su dado a " +
                            QString::number(jugadores[idx]->ObtenerTipoDado()) + " caras");
    } else {
        ui->accion->setText(jugadores[idx]->obtenernombre() + " no mejoró su dado");
    }
}
int MainWindow::golpe_crit(configuracion& config) {
    int probabilidad = (rand() % 100) + 1;
    return (probabilidad <= config.ObtenerGolpeCritico()) ? 1 : 0;
}
void MainWindow::ataque(jugador* jugadores[], int turno, int dado, configuracion& config, Ui::MainWindow* ui) {
    if (!jugadores[0] || !jugadores[1]) return;

    int idx_atacante = turno - 1;
    int idx_defensor = (turno == 1) ? 1 : 0;

    int probabilidad = (rand() % 100) + 1;
    bool acierto = (dado == jugadores[idx_atacante]->ObtenerTipoDado()) || (probabilidad <= config.ObtenerGolpeAcierto());

    if (!acierto) {
        ui->accion->setText(jugadores[idx_atacante]->obtenernombre() + " falló el golpe");
        return;
    }

    int dmg = (jugadores[idx_atacante]->ObtenerAtqB() / 2) * dado;
    int probCrit = (rand() % 100) + 1;
    if (probCrit <= config.ObtenerGolpeCritico()) {
        dmg *= config.ObtenerGolpeCritico();
        ui->accion->setText("¡Golpe crítico de " + jugadores[idx_atacante]->obtenernombre() + "!");
    }

    jugadores[idx_defensor]->ModificarVida(jugadores[idx_defensor]->ObtenerVida() - dmg);

    // Verificar si el defensor murió
    if (jugadores[idx_defensor]->ObtenerVida() <= 0) {
        ui->pp->setCurrentIndex(1); // cambiar a pantalla de resultado
        ui->resultado->setText("Ganó Jugador " + QString::number(jugadores[idx_atacante]->ObtenerTurno()));
        return;
    }

    ui->accion->setText(jugadores[idx_atacante]->obtenernombre() + " hizo " +
                        QString::number(dmg) + " de daño a " +
                        jugadores[idx_defensor]->obtenernombre());

    actualizar_vida(jugadores, ui);
}



void MainWindow::on_ataque_clicked()
{
    muerte_sub(rond,config,ui,m_muerte_sub);
    dado = tirar_dado(jugadores,turno);
    ataque(jugadores,turno,dado,config,ui);
    actualizar_ui();
    rond++;
    turno = (turno == 1) ? 2 : 1;
}

void MainWindow::on_iniciar_clicked()
{
    turno = 1;
    rond = 1;
    ui->turno->setText("Jugador 1");
    ui->pp->setCurrentIndex(3);
}


void MainWindow::on_mejorar_clicked()
{
    mejora_d(jugadores,turno,ui);
    actualizar_ui();
    rond++;
    turno = (turno == 1) ? 2 : 1;
}

void MainWindow::on_p_normal_clicked()
{

    if (turno==1){
        jugadores[0] = new jugador(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        jugadores[1] = new jugador(2);
        ui->pp->setCurrentIndex(4);
    }
}

void MainWindow::on_p_tanque_clicked()
{
    if (turno==1){
        jugadores[0] = new tanque(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        jugadores[1] = new tanque(2);
        ui->pp->setCurrentIndex(4);
    }
}

void MainWindow::on_p_suertudo_clicked()
{
    if (turno==1){
        jugadores[0] = new suertudo(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        jugadores[1] = new suertudo(2);

        ui->pp->setCurrentIndex(4);
    }
}
void MainWindow::on_rendirse_clicked()
{
    if (turno == 1) {
        ui->resultado->setText("Ganó " + jugadores[1]->obtenernombre() + "!");
    } else {
        ui->resultado->setText("Ganó " + jugadores[0]->obtenernombre() + "!");
    }
    ui->pp->setCurrentIndex(1);
}
void MainWindow::on_curacion_clicked()
{
    dado =tirar_dado(jugadores,turno);
    cura(jugadores,turno,dado,config,ui);
    actualizar_ui();
}


void MainWindow::on_nombre_textEdited(const QString &arg1)
{
    if (turno==1){
        jugadores[0]->modificarnombre(arg1);
    }
    else{
        jugadores[1]->modificarnombre(arg1);
    }
}


void MainWindow::on_siguiente_clicked()
{
    if(turno==1){
        ui->turno->setText("Jugador 2");
        turno+=1;
        ui->pp->setCurrentIndex(3);
        ui->nombre->clear();
    }
    else{
        turno=1;
        ui->nom_1->setText(jugadores[0]->obtenernombre());
        ui->nom_2->setText(jugadores[1]->obtenernombre());
        ui->vida_j1->display(jugadores[0]->ObtenerVida());
        ui->vida_j2->display(jugadores[1]->ObtenerVida());
        ui->dado_1->setText("dado: "+QString::number(jugadores[0]->ObtenerTipoDado()));
        ui->dado_2->setText("dado: "+QString::number(jugadores[1]->ObtenerTipoDado()));
        ui->letoca->setText("le toca a "+jugadores[0]->obtenernombre());
        ui->barra_j1->setRange(0,jugadores[0]->ObtenerVida_t());
        ui->barra_j1->setValue(jugadores[0]->ObtenerVida());
        ui->barra_j2->setRange(0,jugadores[1]->ObtenerVida_t());
        ui->barra_j2->setValue(jugadores[1]->ObtenerVida());
        ui->ronda->display(rond);
        ui->pp->setCurrentIndex(2);
        ui->nombre->clear();
        ui->accion->clear();
    }
}





void MainWindow::on_reiniciar_clicked()
{
    turno=1;
    delete jugadores[0];
    delete jugadores[1];
    ui->pp->setCurrentIndex(0);
}


void MainWindow::on_salir_clicked()
{

    close();

}


void MainWindow::on_reglas_clicked()
{
    ui->pp->setCurrentIndex(5);

}


void MainWindow::on_config_clicked()
{
    ui->pp->setCurrentIndex(6);
}


void MainWindow::on_volver_clicked()
{
    ui->pp->setCurrentIndex(0);
}


void MainWindow::on_volver_2_clicked()
{
    ui->pp->setCurrentIndex(0);
}


void MainWindow::on_rond_muerte_s_textChanged(const QString &arg1)
{
    config.ModificarRondMuerteSub(arg1.toInt());
}


void MainWindow::on_multi_crit_textChanged(const QString &arg1)
{
    config.ModificarGolpeCritico(arg1.toFloat());
}


void MainWindow::on_prob_acierto_textChanged(const QString &arg1)
{
    config.ModificarGolpeAcierto(arg1.toInt());
}

