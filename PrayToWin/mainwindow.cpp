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
        if (j2->ObtenerVida() <= 0) {
            ui->resultado->setText("Ganó Jugador " + QString::number(j1->ObtenerTurno()));
            return;
        }
        turno = 2;
    } else {
       double dano = (j2->ObtenerAtqB() / 2.0) * (rand() % j2->ObtenerTipoDado() + 1);
        j1->ModificarVida(j1->ObtenerVida() - dano);
        ui->vida_j1->display(j1->ObtenerVida());
        if (j1->ObtenerVida() <= 0) {
            ui->resultado->setText("Ganó Jugador " + QString::number(j2->ObtenerTurno()));
            return;
        }
        turno = 1;
        rond++;
    }
    ui->ronda->display(rond);
}

void MainWindow::on_iniciar_clicked()
{
    ui->pp->setCurrentIndex(2);
}

void MainWindow::on_mejorar_clicked()
{
    ui->pp->setCurrentIndex(0);
}

void MainWindow::on_p_normal_clicked()
{
    delete j1;
    j1 = new jugador(1);
    j2 = new jugador(2);
    ui->vida_j1->display(j1->ObtenerVida());
    ui->vida_j2->display(j2->ObtenerVida());
    ui->pp->setCurrentIndex(1);
}

void MainWindow::on_p_tanque_clicked()
{
    delete j1;
    j1 = new tanque(1);
    j2 = new jugador(2);
    ui->vida_j1->display(j1->ObtenerVida());
    ui->vida_j2->display(j2->ObtenerVida());
    ui->pp->setCurrentIndex(1);
}

void MainWindow::on_p_suertudo_clicked()
{
    delete j1;
    j1 = new jugador(1);
    j2 = new jugador(2);
    ui->vida_j1->display(j1->ObtenerVida());
    ui->vida_j2->display(j2->ObtenerVida());
    ui->pp->setCurrentIndex(1);
}

void MainWindow::on_curacion_clicked()
{
    if (turno == 1) {
        double nuevaVida = j1->ObtenerVida() + 20;
        if (nuevaVida > j1->ObtenerVida_t()) nuevaVida = j1->ObtenerVida_t();
        j1->ModificarVida(nuevaVida);
        ui->vida_j1->display(j1->ObtenerVida());
        turno = 2;
    } else {
        double nuevaVida = j2->ObtenerVida() + 20;
        if (nuevaVida > j2->ObtenerVida_t()) nuevaVida = j2->ObtenerVida_t();
        j2->ModificarVida(nuevaVida);
        ui->vida_j2->display(j2->ObtenerVida());
        turno = 1;
        rond++;
    }
    ui->ronda->display(rond);
}
