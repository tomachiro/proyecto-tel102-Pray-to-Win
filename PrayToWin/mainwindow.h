#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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

private:
    int turno;
    int rond;
    jugador* j1;
    jugador* j2;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
