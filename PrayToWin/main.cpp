#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(R"(
        QWidget { background-color: #1A1A2E; color: #E8E8E8; font-family: Arial; }
        QPushButton {
            background-color: #E94560; color: white; border: none;
            border-radius: 6px; padding: 8px 16px; font-weight: bold;
            min-width: 80px; min-height: 30px;
        }
        QPushButton:hover { background-color: #c73652; }
        QPushButton#curacion { background-color: #28C76F; }
        QPushButton#curacion:hover { background-color: #1ea85a; }
        QPushButton#rendirse { background-color: #6c757d; }
        QPushButton#mejorar { background-color: #3A9BDC; }
        QLCDNumber { background-color: #0F3460; color: #E94560; border: 2px solid #E94560; border-radius: 4px; }
        QProgressBar { background-color: #0F3460; border: 1px solid #E94560; border-radius: 4px; }
        QProgressBar::chunk { background-color: #28C76F; border-radius: 3px; }
        QLineEdit { background-color: #0F3460; border: 1px solid #E94560; border-radius: 4px; padding: 4px; }
        QLabel#letoca { color: #E94560; font-weight: bold; font-size: 15px; }
        QLabel#resultado { color: #E94560; font-size: 22px; font-weight: bold; }
        QLabel#accion { color: #A0C8F0; font-style: italic; }
    )");

    MainWindow w;
    w.show();
    return QApplication::exec();
}
