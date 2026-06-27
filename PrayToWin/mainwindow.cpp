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
    j1 = nullptr;
    j2 = nullptr;

}

MainWindow::~MainWindow()
{
    delete j1;
    delete j2;
    delete ui;
}

void MainWindow::on_ataque_clicked()
{
    ui->ronda->display(rond);
    if (turno == 1) {
        double dano = (j1->ObtenerAtqB() / 2.0) * (rand() % j1->ObtenerTipoDado() + 1);
        j2->ModificarVida(j2->ObtenerVida() - dano);
        ui->vida_j2->display(j2->ObtenerVida());
        ui->barra_j2->setValue(j2->ObtenerVida());
        if (j2->ObtenerVida() <= 0) {
            ui->pp->setCurrentIndex(1);
            ui->resultado->setText("Ganó " + j1->obtenernombre() + "!");
            return;
        }
        turno = 2;
        ui->letoca->setText("le toca a "+j2->obtenernombre());
    } else {
       double dano = (j2->ObtenerAtqB() / 2.0) * (rand() % j2->ObtenerTipoDado() + 1);
        j1->ModificarVida(j1->ObtenerVida() - dano);
        ui->vida_j1->display(j1->ObtenerVida());
        ui->barra_j1->setValue(j1->ObtenerVida());
        if (j1->ObtenerVida() <= 0) {
            ui->pp->setCurrentIndex(1);
            ui->resultado->setText("Ganó " + j2->obtenernombre() + "!");
            return;
        }
        turno = 1;
        ui->letoca->setText("le toca a "+j1->obtenernombre());
        rond++;
    }
    ui->ronda->display(rond);
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
    ui->ronda->display(rond);
    int dado=0;
    if(turno==1){
        dado=rand() % j1->ObtenerTipoDado() + 1;
        if (dado==j1->ObtenerTipoDado()){
            j1->ModificarTipoDado(j1->ObtenerTipoDado()+2);
            ui->dado_1->setText("dado: "+QString::number(j1->ObtenerTipoDado()));
            ui->accion->setText(j1->obtenernombre()+" mejoraste el dado ahora es de " + QString::number(j1->ObtenerTipoDado())+" caras");
            turno+=1;
        }
        else{
            ui->accion->setText(j1->obtenernombre()+" no mejoraste el dado sigue siendo de " + QString::number(j1->ObtenerTipoDado())+" caras");
            turno+=1;
        }
        ui->letoca->setText("le toca a "+j2->obtenernombre());
    }
    else if(turno==2){
        dado=rand() % j2->ObtenerTipoDado() + 1;
        if (dado==j1->ObtenerTipoDado()){
            j2->ModificarTipoDado(j2->ObtenerTipoDado()+2);
            ui->dado_2->setText("dado: "+QString::number(j2->ObtenerTipoDado()));
            ui->accion->setText(j2->obtenernombre()+" mejoraste el dado ahora es de " + QString::number(j2->ObtenerTipoDado())+" caras");
            turno=1;
        }
        else{
            ui->accion->setText(j2->obtenernombre()+" no mejoraste el dado sigue siendo de " + QString::number(j2->ObtenerTipoDado())+" caras");
            turno=1;
        }
        ui->letoca->setText("le toca a "+j1->obtenernombre());
    }
    rond++;
}

void MainWindow::on_p_normal_clicked()
{

    if (turno==1){
        j1 = new jugador(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        j2 = new jugador(2);
        ui->pp->setCurrentIndex(4);
    }
}

void MainWindow::on_p_tanque_clicked()
{
    if (turno==1){
        j1 = new tanque(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        j2 = new tanque(2);
        ui->pp->setCurrentIndex(4);
    }
}

void MainWindow::on_p_suertudo_clicked()
{
    if (turno==1){
        j1 = new suertudo(1);
        ui->pp->setCurrentIndex(4);
    }
    else if(turno==2){
        j2 = new suertudo(2);

        ui->pp->setCurrentIndex(4);
    }
}
void MainWindow::on_rendirse_clicked()
{
    if (turno == 1) {
        ui->resultado->setText("Ganó " + j2->obtenernombre() + "!");
    } else {
        ui->resultado->setText("Ganó " + j1->obtenernombre() + "!");
    }
    ui->pp->setCurrentIndex(1);
}
void MainWindow::on_curacion_clicked()
{
    if (turno == 1) {
        double nuevaVida = j1->ObtenerVida() + 20;
        if (nuevaVida > j1->ObtenerVida_t()) nuevaVida = j1->ObtenerVida_t();
        j1->ModificarVida(nuevaVida);
        ui->vida_j1->display(j1->ObtenerVida());
        ui->barra_j1->setValue(j1->ObtenerVida());
        ui->accion->setText(j1->obtenernombre()+" te curaste " + QString::number(20)+" puntos de vida");
        turno = 2;
    } else {
        double nuevaVida = j2->ObtenerVida() + 20;
        if (nuevaVida > j2->ObtenerVida_t()) nuevaVida = j2->ObtenerVida_t();
        j2->ModificarVida(nuevaVida);
        ui->vida_j2->display(j2->ObtenerVida());
        ui->barra_j2->setValue(j2->ObtenerVida());
        ui->accion->setText(j2->obtenernombre()+" te curaste " + QString::number(20)+" puntos de vida");
        turno = 1;
        rond++;
    }
    ui->ronda->display(rond);
}


void MainWindow::on_nombre_textEdited(const QString &arg1)
{
    if (turno==1){
        j1->modificarnombre(arg1);
    }
    else{
        j2->modificarnombre(arg1);
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
        ui->nom_1->setText(j1->obtenernombre());
        ui->nom_2->setText(j2->obtenernombre());
        ui->vida_j1->display(j1->ObtenerVida());
        ui->vida_j2->display(j2->ObtenerVida());
        ui->dado_1->setText("dado: "+QString::number(j1->ObtenerTipoDado()));
        ui->dado_2->setText("dado: "+QString::number(j2->ObtenerTipoDado()));
        ui->letoca->setText("le toca a "+j1->obtenernombre());
        ui->barra_j1->setRange(0,j1->ObtenerVida_t());
        ui->barra_j1->setValue(j1->ObtenerVida());
        ui->barra_j2->setRange(0,j2->ObtenerVida_t());
        ui->barra_j2->setValue(j2->ObtenerVida());
        ui->pp->setCurrentIndex(2);
        ui->nombre->clear();
        ui->accion->clear();
    }
}





void MainWindow::on_reiniciar_clicked()
{
    delete j1;
    j1 = nullptr;
    delete j2;
    j2 = nullptr;
    turno = 1;
    rond = 1;
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

