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
    hp_j1 =100;
    hp_j2 = 100;
    rond = 1;
    ui->ronda->display(rond);
    ui->vida_j1->display(hp_j1);
    ui->vida_j2->display(hp_j2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ataque_clicked()
{
    ui->ronda->display(rond);
    if (turno==1){
        hp_j2 -= 10;
        ui->vida_j2->display(hp_j2);
        turno+=1;
    }
    else{
        hp_j1 -=10;
        ui->vida_j1->display(hp_j1);
        turno=1;
        rond++;
    }
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
    ui->pp->setCurrentIndex(1);
}


void MainWindow::on_p_tanque_clicked()
{
    ui->pp->setCurrentIndex(1);
}


void MainWindow::on_p_suertudo_clicked()
{
    ui->pp->setCurrentIndex(1);
}

