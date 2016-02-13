#include "bullet.h"

Bullet::Bullet(QLine& bulletLine, QImage& bulletImage):GameObject(bulletLine,bulletImage)
{
}

Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

void Bullet::draw(QPainter &painter)
{
    painter.drawLine(getLine());
    painter.drawImage(QRect(QPoint(((getLine().p1().x()+getLine().p2().x())/2)-10,
                                   ((getLine().p1().y()+getLine().p2().y())/2)-10),
                            QSize(20,20)),
                      getImage());
}

void Bullet::bang()
{
    auto x = (getLine().p1().x()-getLine().p2().x()) / 2;
    auto y = (getLine().p1().y()-getLine().p2().y()) / 2;
    QLine bulletLine(getLine());
    bulletLine.translate(QPoint(x,y));
    setLine(bulletLine);
}
