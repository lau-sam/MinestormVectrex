#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QLine>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <iostream>
#include <math.h>

class GameObject
{
public:
    GameObject();
    GameObject(QLine line, QImage image);
    void draw(QPainter &painter);
    //getters setters
    QPoint getCenter();
    QLine getLine();
    QImage getImage();
    void setLine(QLine line);
    void setImage(QImage image);
    /**
     * @brief collision test s'il y a une collision
     * @param target to test
     * @return true if collision
     */
    bool collision(GameObject target);

protected:

    /**
     * @brief rotatePoint faire une rotation du QPoint ptRotate autour du QPoint origin un angle degree
     * @param degree l'angle de rotation
     * @param origin QPoint representant le point central
     * @param ptRotate QPoint representant le point à appliquer la rotation
     * @return QPoint représentant les nouvelles coordonnées du QPoint ptRotate
     */
    QPoint rotatePoint(int degree, QPoint origin, QPoint ptRotate);
    double getHypotenuse(int dx, int dy);

    QLine _line;
    QImage _image;
};

#endif // GAMEOBJECT_H
