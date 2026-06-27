// ruletadado.cpp
#include "ruletadado.h"
#include <cstdlib>

RuletaDado::RuletaDado(QWidget *parent) : QDialog(parent) {
    setStyleSheet("background-color: red;"); // ventana roja
    numeroLabel = new QLabel("0", this);
    numeroLabel->setAlignment(Qt::AlignCenter);
    numeroLabel->setStyleSheet("font-size: 48px; color: white;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(numeroLabel);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        int valor = (rand() % caras) + 1;
        numeroLabel->setText(QString::number(valor));
        tiempo += 100;
        if (tiempo >= 2000) { // 2 segundos de animación
            timer->stop();
            numeroLabel->setText(QString::number(resultado));
        }
    });
}

void RuletaDado::iniciarAnimacion(int c, int r) {
    caras = c;
    resultado = r;
    tiempo = 0;
    timer->start(100); // cambia número cada 100 ms
}
