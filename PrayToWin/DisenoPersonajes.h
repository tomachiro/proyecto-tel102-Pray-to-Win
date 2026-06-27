#ifndef DISENOPERSONAJES_H
#define DISENOPERSONAJES_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class CharacterWidget : public QWidget {
    Q_OBJECT
public:
    enum Type { Normal = 0, Tanque = 1, Suertudo = 2 };

    explicit CharacterWidget(QWidget* parent = nullptr, Type t = Normal)
        : QWidget(parent), m_type(t) { setMinimumSize(120, 180); }

    void setType(Type t) { m_type = t; update(); }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        int w = width(), h = height();
        switch (m_type) {
        case Normal:  drawNormal(p, w, h); break;
        case Tanque:  drawTanque(p, w, h); break;
        case Suertudo: drawSuertudo(p, w, h); break;
        }
    }

private:
    Type m_type;

    void drawNormal(QPainter& p, int w, int h) {
        QColor skin(255, 220, 177), outfit(60, 130, 200), dark(30, 30, 80);
        int cx = w / 2;
        // cabeza
        p.setBrush(skin); p.setPen(dark);
        p.drawEllipse(cx - 18, h*0.05, 36, 36);
        // cuerpo
        p.setBrush(outfit);
        p.drawRect(cx - 14, h*0.30, 28, 40);
        // piernas
        p.setBrush(dark);
        p.drawRect(cx - 13, h*0.62, 11, 28);
        p.drawRect(cx + 2,  h*0.62, 11, 28);
        // brazo izq (espada)
        p.setBrush(outfit);
        p.drawRect(cx - 24, h*0.31, 10, 30);
        // espada
        p.setPen(QPen(QColor(200, 200, 220), 3));
        p.drawLine(cx - 30, h*0.25, cx - 30, h*0.60);
        p.setPen(QPen(QColor(150, 100, 50), 2));
        p.drawLine(cx - 38, h*0.41, cx - 22, h*0.41);
        // brazo der
        p.setPen(dark); p.setBrush(outfit);
        p.drawRect(cx + 14, h*0.31, 10, 30);
    }

    void drawTanque(QPainter& p, int w, int h) {
        QColor armor(80, 80, 100), highlight(130, 130, 160), skin(255, 220, 177), dark(20, 20, 40);
        int cx = w / 2;
        // cabeza con casco
        p.setBrush(armor); p.setPen(dark);
        p.drawEllipse(cx - 20, h*0.04, 40, 38);
        p.setBrush(skin);
        p.drawEllipse(cx - 12, h*0.10, 24, 22);
        // visera
        p.setBrush(highlight);
        p.drawRect(cx - 12, h*0.13, 24, 8);
        // cuerpo armadura
        p.setBrush(armor);
        p.drawRect(cx - 18, h*0.29, 36, 44);
        // detalle pecho
        p.setPen(QPen(highlight, 1));
        p.drawLine(cx, h*0.31, cx, h*0.71);
        p.drawLine(cx - 16, h*0.45, cx + 16, h*0.45);
        // piernas
        p.setPen(dark); p.setBrush(QColor(60, 60, 80));
        p.drawRect(cx - 17, h*0.63, 14, 28);
        p.drawRect(cx + 3,  h*0.63, 14, 28);
        // escudo
        p.setBrush(QColor(150, 80, 30));
        QPainterPath shield;
        shield.moveTo(cx - 38, h*0.32);
        shield.lineTo(cx - 20, h*0.32);
        shield.lineTo(cx - 20, h*0.62);
        shield.lineTo(cx - 29, h*0.70);
        shield.lineTo(cx - 38, h*0.62);
        shield.closeSubpath();
        p.drawPath(shield);
        p.setPen(QPen(highlight, 1));
        p.drawLine(cx - 29, h*0.34, cx - 29, h*0.66);
        // brazo der con maza
        p.setPen(dark); p.setBrush(armor);
        p.drawRect(cx + 18, h*0.30, 10, 28);
        p.setBrush(QColor(100, 100, 120));
        p.drawEllipse(cx + 14, h*0.19, 18, 18);
    }

    void drawSuertudo(QPainter& p, int w, int h) {
        QColor skin(255, 220, 177), outfit(180, 50, 180), dark(40, 0, 60);
        QColor gold(255, 200, 0), green(50, 200, 80);
        int cx = w / 2;
        // cabeza
        p.setBrush(skin); p.setPen(dark);
        p.drawEllipse(cx - 14, h*0.05, 28, 28);
        // sombrero de mago
        p.setBrush(outfit);
        QPainterPath hat;
        hat.moveTo(cx - 18, h*0.17);
        hat.lineTo(cx + 18, h*0.17);
        hat.lineTo(cx + 10, h*0.03);
        hat.lineTo(cx - 10, h*0.03);
        hat.closeSubpath();
        p.drawPath(hat);
        // estrella en sombrero
        p.setPen(QPen(gold, 1)); p.setBrush(gold);
        p.drawEllipse(cx - 4, h*0.04, 8, 8);
        // cuerpo delgado
        p.setPen(dark); p.setBrush(outfit);
        p.drawRect(cx - 10, h*0.29, 20, 36);
        // piernas delgadas
        p.setBrush(dark);
        p.drawRect(cx - 9, h*0.62, 7, 26);
        p.drawRect(cx + 2, h*0.62, 7, 26);
        // brazo con dado D10
        p.setBrush(outfit);
        p.drawRect(cx + 10, h*0.30, 8, 24);
        // dado D10
        p.setBrush(gold); p.setPen(QPen(dark, 1));
        QPolygonF d10;
        float dx = cx + 22, dy = h*0.22;
        d10 << QPointF(dx, dy-12) << QPointF(dx+10, dy-4)
            << QPointF(dx+8,  dy+8) << QPointF(dx-8, dy+8)
            << QPointF(dx-10, dy-4);
        p.drawPolygon(d10);
        p.setPen(QPen(dark, 1));
        p.drawText(QRectF(dx-8, dy-6, 16, 14), Qt::AlignCenter, "10");
        // trebol
        p.setBrush(green); p.setPen(Qt::NoPen);
        float lx = cx - 22, ly = h*0.38;
        p.drawEllipse(QPointF(lx, ly-5), 6, 6);
        p.drawEllipse(QPointF(lx-6, ly+2), 6, 6);
        p.drawEllipse(QPointF(lx+6, ly+2), 6, 6);
        p.setPen(QPen(green, 2));
        p.drawLine(lx, ly+8, lx, ly+18);
    }
};

#endif // DISENOPERSONAJES_H