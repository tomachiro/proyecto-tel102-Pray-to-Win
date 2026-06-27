#ifndef RULETADADO_H
#define RULETADADO_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

class RuletaDado : public QDialog {
    Q_OBJECT
public:
    explicit RuletaDado(QWidget *parent = nullptr);
    void iniciarAnimacion(int caras, int resultado);

private:
    QLabel *numeroLabel;
    QTimer *timer;
    int tiempo;
    int caras;
    int resultado;
};

#endif // RULETADADO_H
