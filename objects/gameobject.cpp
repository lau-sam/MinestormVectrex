#include "gameobject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(QLine line, QImage image):_line(line), _image(image)
{
}

QPoint GameObject::getCenter()
{
    return QPoint((_line.p1().x()+_line.p2().x())/2,(_line.p1().y()+_line.p2().y())/2);
}

QLine GameObject::getLine()
{
    return _line;
}

QImage GameObject::getImage()
{
    return _image;
}

void GameObject::setLine(QLine line)
{
    _line.setLine(line.p1().x(),line.p1().y(),line.p2().x(),line.p2().y());
}

void GameObject::setImage(QImage image)
{
    _image = image;
}

QPoint GameObject::rotatePoint(int degree, QPoint origin, QPoint ptRotate)
{
    double radianAngle = (degree * M_PI) / 180.0;
    double sinAngle = sin(radianAngle);
    double cosAngle = cos(radianAngle);

    int px = ptRotate.x() - origin.x();
    int py = ptRotate.y() - origin.y();

    float xnew = px * cosAngle - py * sinAngle;
    float ynew = py * cosAngle + px * sinAngle;

    px = xnew + origin.x();
    py = ynew + origin.y();

    return QPoint(px, py);
}

bool GameObject::collision(GameObject target)
{
    int rayonGameObject = getHypotenuse(getLine().dx(),getLine().dy()) / 2;
    int rayonTarget = getHypotenuse(target.getLine().dx(), target.getLine().dy()) / 2;
    int distance = rayonGameObject + rayonTarget;

    auto xTarget = (target.getLine().p1().x()+target.getLine().p2().x())/2;
    auto yTarget = (target.getLine().p1().y()+target.getLine().p2().y())/2;
    auto xCurrent = (_line.p1().x()+_line.p2().x())/2;
    auto yCurrent = (_line.p1().y()+_line.p2().y())/2;

    return(abs(xCurrent-xTarget) < distance && abs(yCurrent-yTarget) < distance);
}

double GameObject::getHypotenuse(int dx, int dy)
{
    return sqrt( (abs(dx)*abs(dx)) + (abs(dy)*abs(dy)) );
}
